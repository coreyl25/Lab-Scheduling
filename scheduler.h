#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <vector>
#include <queue>
#include <memory>

// Process structure
struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    
    Process(int p, int at, int bt, int pr = 0) 
        : pid(p), arrival_time(at), burst_time(bt), 
          remaining_time(bt), priority(pr), 
          waiting_time(0), turnaround_time(0), completion_time(0) {}
};

// Task structure
struct Task {
    int task_id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
    int start_time;
    bool started;
    
    Task(int id, int at, int bt, int pr = 0)
        : task_id(id), arrival_time(at), burst_time(bt), priority(pr),
          remaining_time(bt), waiting_time(0), turnaround_time(0),
          completion_time(0), start_time(-1), started(false) {}
};

// Scheduler interface
class Scheduler {
protected:
    std::vector<Process> processes;
    int current_time;
    
public:
    Scheduler() : current_time(0) {}
    virtual ~Scheduler() = default;
    
    virtual void addProcess(const Process& p) {
        processes.push_back(p);
    }
    
    virtual void schedule() = 0;
    virtual void printResults() const;
    void calculateMetrics();
};

// FCFS Scheduler
class FCFSScheduler : public Scheduler {
public:
    void schedule() override;
};

// SJF Non-Preemptive Scheduler
class SJFScheduler : public Scheduler {
public:
    void schedule() override;
};

// SRTF Preemptive Scheduler
class SRTFScheduler : public Scheduler {
public:
    void schedule() override;
};

// Round Robin Non-Preemptive
class RRNonPreemptiveScheduler : public Scheduler {
private:
    int quantum;
public:
    RRNonPreemptiveScheduler(int q = 4) : quantum(q) {}
    void schedule() override;
};

// Round Robin Scheduler
class RoundRobinScheduler : public Scheduler {
private:
    int quantum;
public:
    RoundRobinScheduler(int q) : quantum(q) {}
    void schedule() override;
};

// Comprehensive Task Scheduler
class TaskScheduler {
private:
    std::vector<Task> tasks;
    std::string algorithm;
    int quantum;
    int current_time;
    
    void scheduleFCFS();
    void scheduleSJF();
    void scheduleSRTF();
    void scheduleRR();
    void schedulePriority();
    
public:
    TaskScheduler(const std::string& algo, int q = 4) 
        : algorithm(algo), quantum(q), current_time(0) {}
    
    void addTask(const Task& t) { tasks.push_back(t); }
    void run();
    void printMetrics() const;
};

#endif