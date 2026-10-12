#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority; // lower number = higher priority
    int completion_time = 0;
    int turnaround_time = 0;
    int wait_time = 0;
};

void schedule_preemptive_priority(vector<Process> &processes) {
    int current_time = 0;
    int completed = 0;
    int n = processes.size();

    while (completed < n) {
        int idx = -1;
        int highest_priority = INT_MAX;

        // Find highest priority among ready processes
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) { // No process ready
            current_time++;
            continue;
        }

        // Execute 1 unit
        processes[idx].remaining_time--;
        current_time++;

        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].wait_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        }
    }

    cout << "PID\tAT\tBT\tPrio\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.priority << "\t" << p.completion_time << "\t" << p.turnaround_time << "\t" << p.wait_time << "\n";
    }
}

int main() {
    vector<Process> processes = {
        {1, 0, 5, 5, 2, 0, 0, 0},
        {2, 1, 3, 3, 1, 0, 0, 0}, // Highest priority
        {3, 2, 8, 8, 3, 0, 0, 0},
        {4, 3, 6, 6, 2, 0, 0, 0}
    };

    schedule_preemptive_priority(processes);
    return 0;
}