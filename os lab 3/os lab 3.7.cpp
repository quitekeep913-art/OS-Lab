#include <iostream>
#include <thread>
#include <vector>

using namespace std;

// Global data for simplicity
int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int vec[3] = {1, 2, 3};
int result[3] = {0};

void worker_multiply_row(int row_idx) {
    int sum = 0;
    for (int col = 0; col < 3; col++) {
        sum = sum + matrix[row_idx][col] * vec[col];
    }
    result[row_idx] = sum;
}

int main() {
    // Initialize thread list
    vector<thread> thread_list;

    // Spawn 3 threads, one for each row
    for (int i = 0; i < 3; i++) {
        thread_list.push_back(thread(worker_multiply_row, i));
    }

    // Join all threads
    for (auto& t : thread_list) {
        t.join();
    }

    cout << "Result Vector: ";
    for (int i = 0; i < 3; i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}