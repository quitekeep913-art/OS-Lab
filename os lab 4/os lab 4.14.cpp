#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

int compute_result() {
    cout << "[Worker] Computing heavy result..." << endl;
    this_thread::sleep_for(chrono::seconds(2));
    return 42;
}

void worker_thread(promise<int> prom) {
    // data = compute_result()
    int data = compute_result();

    // promise.send_value(data)
    prom.set_value(data); // Worker sends result
    cout << "[Worker] Result sent!" << endl;
}

int main() {
    // Channel created (Promise <--> Future)
    promise<int> prom;
    future<int> fut = prom.get_future();

    jthread jt(worker_thread, move(prom)); // Worker thread owns promise

    cout << "[Master] Doing other work while waiting..." << endl;

    // value = future.read_and_block_until_delivered()
    int result = fut.get(); // Blocks until value is ready

    cout << "[Master] Got result: " << result << endl;

    return 0;
}