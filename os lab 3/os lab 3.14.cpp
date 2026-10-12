#include <iostream>
#include <unistd.h>
#include <sys/mman.h> // for shm_open, mmap
#include <sys/wait.h>
#include <fcntl.h> // for O_CREAT, O_RDWR
#include <cstring>

using namespace std;

int main() {
    const char* shm_name = "/shm_os_lab";
    const int SIZE = 1024;

    // Create shared memory object
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open failed");
        return 1;
    }

    // Set size
    ftruncate(shm_fd, SIZE);

    // Map to process memory
    char* ptr = (char*)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child - Reader
        sleep(1); // Wait for parent to write
        cout << "Child read from SHM: " << ptr << endl;
    } else {
        // Parent - Writer
        strcpy(ptr, "OS Shared Memory Payload");
        cout << "Parent wrote to SHM" << endl;
        
        wait(NULL);
        
        // Cleanup
        shm_unlink(shm_name);
    }

    return 0;
}