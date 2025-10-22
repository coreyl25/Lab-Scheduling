#include "scheduler.h"
#include <iostream>

void testExercise1() {
    std::cout << "\n Exercise 1: FCFS \n";
    FCFSScheduler fcfs;
    fcfs.addProcess(Process(1, 0, 8));
    fcfs.addProcess(Process(2, 1, 4));
    fcfs.addProcess(Process(3, 2, 9));
    fcfs.addProcess(Process(4, 3, 5));
    
    fcfs.schedule();
    fcfs.printResults();
}

void testExercise2() {
    std::cout << "\n Exercise 2: SJF (Non-Preemptive) \n";
    SJFScheduler sjf;
    sjf.addProcess(Process(1, 0, 8));
    sjf.addProcess(Process(2, 1, 4));
    sjf.addProcess(Process(3, 2, 9));
    sjf.addProcess(Process(4, 3, 5));
    
    sjf.schedule();
    sjf.printResults();
}

void testExercise3() {
    std::cout << "\n Exercise 3: SRTF (Preemptive) \n";
    SRTFScheduler srtf;
    srtf.addProcess(Process(1, 0, 8));
    srtf.addProcess(Process(2, 1, 4));
    srtf.addProcess(Process(3, 2, 9));
    srtf.addProcess(Process(4, 3, 5));
    
    srtf.schedule();
    srtf.printResults();
}

void testExercise4() {
    std::cout << "\n Exercise 4: RR (Non-Preemptive, Quantum=4) \n";
    RRNonPreemptiveScheduler rr_np(4);
    rr_np.addProcess(Process(1, 0, 8));
    rr_np.addProcess(Process(2, 1, 4));
    rr_np.addProcess(Process(3, 2, 9));
    rr_np.addProcess(Process(4, 3, 5));
    
    rr_np.schedule();
    rr_np.printResults();
}

void testExercise5() {
    std::cout << "\n Exercise 5: Round Robin (Quantum=3) \n";
    RoundRobinScheduler rr(3);
    rr.addProcess(Process(1, 0, 8));
    rr.addProcess(Process(2, 1, 4));
    rr.addProcess(Process(3, 2, 9));
    rr.addProcess(Process(4, 3, 5));
    
    rr.schedule();
    rr.printResults();
}

void testPart3_FCFS() {
    std::cout << "\n Part 3: Task Scheduler - FCFS \n";
    TaskScheduler scheduler("FCFS");
    scheduler.addTask(Task(1, 0, 5, 2));
    scheduler.addTask(Task(2, 1, 3, 1));
    scheduler.addTask(Task(3, 2, 8, 3));
    scheduler.addTask(Task(4, 3, 6, 2));
    
    scheduler.run();
    scheduler.printMetrics();
}

void testPart3_SJF() {
    std::cout << "\n Part 3: Task Scheduler - SJF \n";
    TaskScheduler scheduler("SJF");
    scheduler.addTask(Task(1, 0, 5, 2));
    scheduler.addTask(Task(2, 1, 3, 1));
    scheduler.addTask(Task(3, 2, 8, 3));
    scheduler.addTask(Task(4, 3, 6, 2));
    
    scheduler.run();
    scheduler.printMetrics();
}

void testPart3_SRTF() {
    std::cout << "\n Part 3: Task Scheduler - SRTF \n";
    TaskScheduler scheduler("SRTF");
    scheduler.addTask(Task(1, 0, 5, 2));
    scheduler.addTask(Task(2, 1, 3, 1));
    scheduler.addTask(Task(3, 2, 8, 3));
    scheduler.addTask(Task(4, 3, 6, 2));
    
    scheduler.run();
    scheduler.printMetrics();
}

void testPart3_RR() {
    std::cout << "\n Part 3: Task Scheduler - Round Robin (Q=4) \n";
    TaskScheduler scheduler("RR", 4);
    scheduler.addTask(Task(1, 0, 5, 2));
    scheduler.addTask(Task(2, 1, 3, 1));
    scheduler.addTask(Task(3, 2, 8, 3));
    scheduler.addTask(Task(4, 3, 6, 2));
    
    scheduler.run();
    scheduler.printMetrics();
}

void testPart3_Priority() {
    std::cout << "\n Part 3: Task Scheduler - Priority (Lower=Higher) \n";
    TaskScheduler scheduler("Priority");
    scheduler.addTask(Task(1, 0, 5, 2));
    scheduler.addTask(Task(2, 1, 3, 1));
    scheduler.addTask(Task(3, 2, 8, 3));
    scheduler.addTask(Task(4, 3, 6, 2));
    
    scheduler.run();
    scheduler.printMetrics();
}

int main() {
    std::cout << "CPU Scheduling Algorithms - Lab Assignment\n";
    
    // Part 2: Exercises
    testExercise1();
    testExercise2();
    testExercise3();
    testExercise4();
    testExercise5();
    
    // Part 3: Task Scheduler
    testPart3_FCFS();
    testPart3_SJF();
    testPart3_SRTF();
    testPart3_RR();
    testPart3_Priority();
    
    std::cout << "All tests completed successfully!\n";
    
    return 0;
}