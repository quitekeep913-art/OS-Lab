#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int pid;
    int burst_time;
    int remaining_time;
    int waiting_time_in_queue = 0; // for aging
    int completion_time = 0;
};

int main() {
    vector<Process> processes = {
        {1, 10, 10},
        {2, 6, 6},
        {3, 8, 8},
        {4, 4, 4}
    };

    queue<int> Q1, Q2, Q3; // Store pid index
    const int Q1_QUANTUM = 2;
    const int Q2_QUANTUM = 4;
    const int AGING_THRESHOLD = 10;

    int current_time = 0;

    // Initially all in Q1
    for (int i = 0; i < processes.size(); i++) Q1.push(i);

    auto apply_aging = [&]() {
        queue<int> temp;
        while(!Q2.empty()){
            int idx = Q2.front(); Q2.pop();
            processes[idx].waiting_time_in_queue += 1;
            if(processes[idx].waiting_time_in_queue > AGING_THRESHOLD){
                cout << "Time " << current_time << ": P" << processes[idx].pid << " promoted from Q2 to Q1 by AGING\n";
                processes[idx].waiting_time_in_queue = 0;
                Q1.push(idx);
            } else {
                temp.push(idx);
            }
        }
        Q2 = temp;
        // Similar for Q3
        while(!Q3.empty()){
            int idx = Q3.front(); Q3.pop();
            processes[idx].waiting_time_in_queue += 1;
            if(processes[idx].waiting_time_in_queue > AGING_THRESHOLD){
                cout << "Time " << current_time << ": P" << processes[idx].pid << " promoted from Q3 to Q1 by AGING\n";
                processes[idx].waiting_time_in_queue = 0;
                Q1.push(idx);
            } else {
                temp.push(idx);
            }
        }
        Q3 = temp;
    };

    int completed = 0;
    while (completed < processes.size()) {
        if (!Q1.empty()) {
            int idx = Q1.front(); Q1.pop();
            int run = min(Q1_QUANTUM, processes[idx].remaining_time);
            cout << "Time " << current_time << " to " << current_time+run << ": P" << processes[idx].pid << " runs in Q1\n";
            processes[idx].remaining_time -= run;
            current_time += run;

            if (processes[idx].remaining_time > 0) {
                Q2.push(idx);
            } else {
                processes[idx].completion_time = current_time;
                completed++;
            }
        }
        else if (!Q2.empty()) {
            int idx = Q2.front(); Q2.pop();
            int run = min(Q2_QUANTUM, processes[idx].remaining_time);
            cout << "Time " << current_time << " to " << current_time+run << ": P" << processes[idx].pid << " runs in Q2\n";
            processes[idx].remaining_time -= run;
            current_time += run;

            if (processes[idx].remaining_time > 0) {
                Q3.push(idx);
            } else {
                processes[idx].completion_time = current_time;
                completed++;
            }
        }
        else if (!Q3.empty()) {
            int idx = Q3.front(); Q3.pop();
            int run = processes[idx].remaining_time; // FCFS till finish
            cout << "Time " << current_time << " to " << current_time+run << ": P" << processes[idx].pid << " runs in Q3 (FCFS)\n";
            processes[idx].remaining_time = 0;
            current_time += run;
            processes[idx].completion_time = current_time;
            completed++;
        }
        // APPLY_AGING
        // apply_aging(); // Uncomment to enable aging logic
    }

    cout << "\nPID\tBT\tCT\n";
    for(auto &p: processes) cout << p.pid << "\t" << p.burst_time << "\t" << p.completion_time << "\n";
    return 0;
}