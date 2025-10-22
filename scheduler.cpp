#include "scheduler.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>

// Base Scheduler methods
void Scheduler::calculateMetrics() {
    for (auto& p : processes) {
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;
    }
}

void Scheduler::printResults() const {
    std::cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    std::cout << "---------------------------------------------------------------\n";
    
    double total_waiting = 0, total_turnaround = 0;
    
    for (const auto& p : processes) {
        std::cout << "P" << p.pid << "\t" 
                  << p.arrival_time << "\t"
                  << p.burst_time << "\t"
                  << p.completion_time << "\t\t"
                  << p.turnaround_time << "\t\t"
                  << p.waiting_time << "\n";
        total_waiting += p.waiting_time;
        total_turnaround += p.turnaround_time;
    }
    
    std::cout << "\nAverage Waiting Time: " 
              << total_waiting / processes.size() << "\n";
    std::cout << "Average Turnaround Time: " 
              << total_turnaround / processes.size() << "\n";
}

// Exercise 1: FCFS Implementation
void FCFSScheduler::schedule() {
    std::sort(processes.begin(), processes.end(), 
              [](const Process& a, const Process& b) {
                  return a.arrival_time < b.arrival_time;
              });
    
    current_time = 0;
    for (auto& p : processes) {
        if (current_time < p.arrival_time) {
            current_time = p.arrival_time;
        }
        current_time += p.burst_time;
        p.completion_time = current_time;
    }
    
    calculateMetrics();
}

// Exercise 2: SJF Non-Preemptive Implementation
void SJFScheduler::schedule() {
    std::vector<bool> completed(processes.size(), false);
    current_time = 0;
    int completed_count = 0;
    
    while (completed_count < processes.size()) {
        int idx = -1;
        int min_burst = INT_MAX;
        
        for (int i = 0; i < processes.size(); i++) {
            if (!completed[i] && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < min_burst) {
                    min_burst = processes[i].burst_time;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            current_time += processes[idx].burst_time;
            processes[idx].completion_time = current_time;
            completed[idx] = true;
            completed_count++;
        } else {
            current_time++;
        }
    }
    
    calculateMetrics();
}

// Exercise 3: SRTF Preemptive Implementation
void SRTFScheduler::schedule() {
    current_time = 0;
    int completed = 0;
    int n = processes.size();
    std::vector<int> remaining_time(n);
    
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }
    
    while (completed < n) {
        int idx = -1;
        int min_remaining = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && 
                remaining_time[i] > 0 && 
                remaining_time[i] < min_remaining) {
                min_remaining = remaining_time[i];
                idx = i;
            }
        }
        
        if (idx != -1) {
            remaining_time[idx]--;
            current_time++;
            
            if (remaining_time[idx] == 0) {
                processes[idx].completion_time = current_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    
    calculateMetrics();
}

// Exercise 4: Round Robin Non-Preemptive
void RRNonPreemptiveScheduler::schedule() {
    std::queue<int> ready_queue;
    std::vector<bool> in_queue(processes.size(), false);
    current_time = 0;
    int completed = 0;
    
    // Sort by arrival time
    std::vector<int> indices(processes.size());
    for (int i = 0; i < processes.size(); i++) indices[i] = i;
    std::sort(indices.begin(), indices.end(), 
              [this](int a, int b) {
                  return processes[a].arrival_time < processes[b].arrival_time;
              });
    
    int next_process = 0;
    
    while (completed < processes.size()) {
        // Newly arrived processes
        while (next_process < processes.size() && 
               processes[indices[next_process]].arrival_time <= current_time) {
            if (!in_queue[indices[next_process]] && 
                processes[indices[next_process]].remaining_time > 0) {
                ready_queue.push(indices[next_process]);
                in_queue[indices[next_process]] = true;
            }
            next_process++;
        }
        
        if (!ready_queue.empty()) {
            int idx = ready_queue.front();
            ready_queue.pop();
            in_queue[idx] = false;
            
            int exec_time = std::min(quantum, processes[idx].remaining_time);
            current_time += exec_time;
            processes[idx].remaining_time -= exec_time;
            
            // Newly arrived processes during execution
            while (next_process < processes.size() && 
                   processes[indices[next_process]].arrival_time <= current_time) {
                if (!in_queue[indices[next_process]] && 
                    processes[indices[next_process]].remaining_time > 0) {
                    ready_queue.push(indices[next_process]);
                    in_queue[indices[next_process]] = true;
                }
                next_process++;
            }
            
            if (processes[idx].remaining_time > 0) {
                ready_queue.push(idx);
                in_queue[idx] = true;
            } else {
                processes[idx].completion_time = current_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    
    calculateMetrics();
}

// Exercise 5: Round Robin Scheduler
void RoundRobinScheduler::schedule() {
    std::queue<int> ready_queue;
    std::vector<bool> in_queue(processes.size(), false);
    current_time = 0;
    int completed = 0;
    
    std::vector<int> indices(processes.size());
    for (int i = 0; i < processes.size(); i++) indices[i] = i;
    std::sort(indices.begin(), indices.end(), 
              [this](int a, int b) {
                  return processes[a].arrival_time < processes[b].arrival_time;
              });
    
    int next_process = 0;
    
    while (completed < processes.size()) {
        while (next_process < processes.size() && 
               processes[indices[next_process]].arrival_time <= current_time) {
            if (!in_queue[indices[next_process]] && 
                processes[indices[next_process]].remaining_time > 0) {
                ready_queue.push(indices[next_process]);
                in_queue[indices[next_process]] = true;
            }
            next_process++;
        }
        
        if (!ready_queue.empty()) {
            int idx = ready_queue.front();
            ready_queue.pop();
            in_queue[idx] = false;
            
            int exec_time = std::min(quantum, processes[idx].remaining_time);
            current_time += exec_time;
            processes[idx].remaining_time -= exec_time;
            
            while (next_process < processes.size() && 
                   processes[indices[next_process]].arrival_time <= current_time) {
                if (!in_queue[indices[next_process]] && 
                    processes[indices[next_process]].remaining_time > 0) {
                    ready_queue.push(indices[next_process]);
                    in_queue[indices[next_process]] = true;
                }
                next_process++;
            }
            
            if (processes[idx].remaining_time > 0) {
                ready_queue.push(idx);
                in_queue[idx] = true;
            } else {
                processes[idx].completion_time = current_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    
    calculateMetrics();
}

// Part 3: Task Scheduler Implementation
void TaskScheduler::run() {
    if (algorithm == "FCFS") {
        scheduleFCFS();
    } else if (algorithm == "SJF") {
        scheduleSJF();
    } else if (algorithm == "SRTF") {
        scheduleSRTF();
    } else if (algorithm == "RR") {
        scheduleRR();
    } else if (algorithm == "Priority") {
        schedulePriority();
    }
}

void TaskScheduler::scheduleFCFS() {
    std::sort(tasks.begin(), tasks.end(), 
              [](const Task& a, const Task& b) {
                  return a.arrival_time < b.arrival_time;
              });
    
    current_time = 0;
    for (auto& t : tasks) {
        if (current_time < t.arrival_time) {
            current_time = t.arrival_time;
        }
        t.start_time = current_time;
        current_time += t.burst_time;
        t.completion_time = current_time;
        t.turnaround_time = t.completion_time - t.arrival_time;
        t.waiting_time = t.turnaround_time - t.burst_time;
    }
}

void TaskScheduler::scheduleSJF() {
    std::vector<bool> completed(tasks.size(), false);
    current_time = 0;
    int completed_count = 0;
    
    while (completed_count < tasks.size()) {
        int idx = -1;
        int min_burst = INT_MAX;
        
        for (int i = 0; i < tasks.size(); i++) {
            if (!completed[i] && tasks[i].arrival_time <= current_time) {
                if (tasks[i].burst_time < min_burst) {
                    min_burst = tasks[i].burst_time;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            tasks[idx].start_time = current_time;
            current_time += tasks[idx].burst_time;
            tasks[idx].completion_time = current_time;
            tasks[idx].turnaround_time = tasks[idx].completion_time - tasks[idx].arrival_time;
            tasks[idx].waiting_time = tasks[idx].turnaround_time - tasks[idx].burst_time;
            completed[idx] = true;
            completed_count++;
        } else {
            current_time++;
        }
    }
}

void TaskScheduler::scheduleSRTF() {
    current_time = 0;
    int completed = 0;
    int n = tasks.size();
    
    while (completed < n) {
        int idx = -1;
        int min_remaining = INT_MAX;
        
        for (int i = 0; i < n; i++) {
            if (tasks[i].arrival_time <= current_time && 
                tasks[i].remaining_time > 0 && 
                tasks[i].remaining_time < min_remaining) {
                min_remaining = tasks[i].remaining_time;
                idx = i;
            }
        }
        
        if (idx != -1) {
            if (!tasks[idx].started) {
                tasks[idx].start_time = current_time;
                tasks[idx].started = true;
            }
            
            tasks[idx].remaining_time--;
            current_time++;
            
            if (tasks[idx].remaining_time == 0) {
                tasks[idx].completion_time = current_time;
                tasks[idx].turnaround_time = tasks[idx].completion_time - tasks[idx].arrival_time;
                tasks[idx].waiting_time = tasks[idx].turnaround_time - tasks[idx].burst_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
}

void TaskScheduler::scheduleRR() {
    std::queue<int> ready_queue;
    std::vector<bool> in_queue(tasks.size(), false);
    current_time = 0;
    int completed = 0;
    
    std::vector<int> indices(tasks.size());
    for (int i = 0; i < tasks.size(); i++) indices[i] = i;
    std::sort(indices.begin(), indices.end(), 
              [this](int a, int b) {
                  return tasks[a].arrival_time < tasks[b].arrival_time;
              });
    
    int next_task = 0;
    
    while (completed < tasks.size()) {
        while (next_task < tasks.size() && 
               tasks[indices[next_task]].arrival_time <= current_time) {
            if (!in_queue[indices[next_task]] && 
                tasks[indices[next_task]].remaining_time > 0) {
                ready_queue.push(indices[next_task]);
                in_queue[indices[next_task]] = true;
            }
            next_task++;
        }
        
        if (!ready_queue.empty()) {
            int idx = ready_queue.front();
            ready_queue.pop();
            in_queue[idx] = false;
            
            if (!tasks[idx].started) {
                tasks[idx].start_time = current_time;
                tasks[idx].started = true;
            }
            
            int exec_time = std::min(quantum, tasks[idx].remaining_time);
            current_time += exec_time;
            tasks[idx].remaining_time -= exec_time;
            
            while (next_task < tasks.size() && 
                   tasks[indices[next_task]].arrival_time <= current_time) {
                if (!in_queue[indices[next_task]] && 
                    tasks[indices[next_task]].remaining_time > 0) {
                    ready_queue.push(indices[next_task]);
                    in_queue[indices[next_task]] = true;
                }
                next_task++;
            }
            
            if (tasks[idx].remaining_time > 0) {
                ready_queue.push(idx);
                in_queue[idx] = true;
            } else {
                tasks[idx].completion_time = current_time;
                tasks[idx].turnaround_time = tasks[idx].completion_time - tasks[idx].arrival_time;
                tasks[idx].waiting_time = tasks[idx].turnaround_time - tasks[idx].burst_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
}

void TaskScheduler::schedulePriority() {
    std::vector<bool> completed(tasks.size(), false);
    current_time = 0;
    int completed_count = 0;
    
    while (completed_count < tasks.size()) {
        int idx = -1;
        int highest_priority = INT_MAX;
        
        for (int i = 0; i < tasks.size(); i++) {
            if (!completed[i] && tasks[i].arrival_time <= current_time) {
                if (tasks[i].priority < highest_priority) {
                    highest_priority = tasks[i].priority;
                    idx = i;
                }
            }
        }
        
        if (idx != -1) {
            tasks[idx].start_time = current_time;
            current_time += tasks[idx].burst_time;
            tasks[idx].completion_time = current_time;
            tasks[idx].turnaround_time = tasks[idx].completion_time - tasks[idx].arrival_time;
            tasks[idx].waiting_time = tasks[idx].turnaround_time - tasks[idx].burst_time;
            completed[idx] = true;
            completed_count++;
        } else {
            current_time++;
        }
    }
}

void TaskScheduler::printMetrics() const {
    std::cout << "\n=== Task Scheduler Results (" << algorithm << ") ===\n";
    std::cout << "Task\tArrival\tBurst\tPriority\tStart\tCompletion\tTurnaround\tWaiting\n";
    std::cout << "--------------------------------------------------------------------------------\n";
    
    double total_waiting = 0, total_turnaround = 0;
    double total_burst = 0;
    int min_arrival = INT_MAX, max_completion = 0;
    
    for (const auto& t : tasks) {
        std::cout << "T" << t.task_id << "\t"
                  << t.arrival_time << "\t"
                  << t.burst_time << "\t"
                  << t.priority << "\t\t"
                  << t.start_time << "\t"
                  << t.completion_time << "\t\t"
                  << t.turnaround_time << "\t\t"
                  << t.waiting_time << "\n";
        
        total_waiting += t.waiting_time;
        total_turnaround += t.turnaround_time;
        total_burst += t.burst_time;
        min_arrival = std::min(min_arrival, t.arrival_time);
        max_completion = std::max(max_completion, t.completion_time);
    }
    
    double avg_waiting = total_waiting / tasks.size();
    double avg_turnaround = total_turnaround / tasks.size();
    double throughput = tasks.size() / (double)(max_completion - min_arrival);
    double cpu_utilization = (total_burst / (max_completion - min_arrival)) * 100;
    
    std::cout << "\n--- Performance Metrics ---\n";
    std::cout << "Average Waiting Time: " << std::fixed << std::setprecision(2) 
              << avg_waiting << "\n";
    std::cout << "Average Turnaround Time: " << avg_turnaround << "\n";
    std::cout << "Throughput: " << throughput << " tasks/time unit\n";
    std::cout << "CPU Utilization: " << cpu_utilization << "%\n";
}