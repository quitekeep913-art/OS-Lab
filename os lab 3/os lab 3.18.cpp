#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time = 0;
    int turnaround_time = 0;
    int wait_time = 0;
};

void schedule_round_robin(vector<Process> &processes, int quantum) {
    queue<int> q; // store index of process
    int current_time = 0;
    int n = processes.size();
    vector<bool> in_queue(n, false);
    int completed = 0;

    // Sort by arrival to handle initial enqueue
    sort(processes.begin(), processes.end(), [](Process a, Process b){
        return a.arrival_time < b.arrival_time;
    });

    // Enqueue processes arrived at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time) {
            q.push(i);
            in_queue[i] = true;
        }
    }

    while (!q.empty()) {
        int idx = q.front();
        q.pop();

        int slice = min(quantum, processes[idx].remaining_time);
        processes[idx].remaining_time -= slice;
        current_time += slice;

        // Enqueue new arrivals up to current_time
        for (int i = 0; i < n; i++) {
            if (!in_queue[i] && processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                q.push(i);
                in_queue[i] = true;
            }
        }

        if (processes[idx].remaining_time > 0) {
            q.push(idx); // Re-enqueue if not finished
        } else {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].wait_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        }
    }

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t" << p.turnaround_time << "\t" << p.wait_time << "\n";
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 5, 5, 0, 0, 0},
        {2, 1, 3, 3, 0, 0, 0},
        {3, 2, 8, 8, 0, 0, 0}
    };
    int quantum = 2;

    schedule_round_robin(processes, quantum);
    return 0;
}