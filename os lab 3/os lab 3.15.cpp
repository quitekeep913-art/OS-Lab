#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int wait_time;
};

void print_metrics(vector<Process> &processes) {
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t" << p.turnaround_time << "\t" << p.wait_time << "\n";
    }
}

void schedule_fcfs(vector<Process> &processes) {
    // Sort by arrival time
    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival_time < b.arrival_time;
    });

    int current_time = 0;
    for (auto &p : processes) {
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time;
        }
        p.completion_time = current_time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.wait_time = p.turnaround_time - p.burst_time;
        current_time = p.completion_time;
    }

    print_metrics(processes);
}

int main() {
    vector<Process> processes = {
        {1, 0, 5, 0, 0, 0},
        {2, 1, 3, 0, 0, 0},
        {3, 2, 8, 0, 0, 0}
    };

    schedule_fcfs(processes);
    return 0;
}