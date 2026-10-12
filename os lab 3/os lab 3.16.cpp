#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time = 0;
    int turnaround_time = 0;
    int wait_time = 0;
    bool completed = false;
};

void schedule_sjf(vector<Process> &processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
        int min_burst = INT_MAX;
        int idx = -1;

        // Find available process with minimum burst_time
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) { // No process available
            current_time++;
            continue;
        }

        processes[idx].completion_time = current_time + processes[idx].burst_time;
        processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
        processes[idx].wait_time = processes[idx].turnaround_time - processes[idx].burst_time;
        processes[idx].completed = true;

        current_time = processes[idx].completion_time;
        completed++;
    }

    // Print metrics
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t" << p.turnaround_time << "\t" << p.wait_time << "\n";
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 6, 0, 0, 0, false},
        {2, 1, 2, 0, 0, 0, false},
        {3, 2, 8, 0, 0, 0, false},
        {4, 3, 3, 0, 0, 0, false}
    };

    schedule_sjf(processes);
    return 0;
}