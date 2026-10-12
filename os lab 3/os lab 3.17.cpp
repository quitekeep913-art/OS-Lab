#include <iostream>
#include <vector>
#include <climits>

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

void schedule_srtf(vector<Process> &processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
        int idx = -1;
        int min_remaining = INT_MAX;

        // Find process with minimum remaining time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].remaining_time < min_remaining) {
                    min_remaining = processes[i].remaining_time;
                    idx = i;
                }
            }
        }

        if (idx == -1) { // No process available
            current_time++;
            continue;
        }

        // Execute for 1 unit
        processes[idx].remaining_time--;
        current_time++;

        // If finished
        if (processes[idx].remaining_time == 0) {
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
        {1, 0, 8, 8, 0, 0, 0},
        {2, 1, 4, 4, 0, 0, 0},
        {3, 2, 9, 9, 0, 0, 0},
        {4, 3, 5, 5, 0, 0, 0}
    };

    schedule_srtf(processes);
    return 0;
}