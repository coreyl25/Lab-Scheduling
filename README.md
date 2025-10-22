# CPU Scheduling Algorithms - Lab Assignment

## Overview
This project implements various CPU scheduling algorithms in C++ as part of an Operating Systems course lab assignment. The implementation covers both Part 2 (Exercises) and Part 3 (Task Scheduling Simulator).

### Exercises
1. Exercise 1: FCFS (First Come First Served)
   - Non-preemptive scheduling
   - Processes executed in arrival order

2. Exercise 2: SJF (Shortest Job First - Non-Preemptive)
   - Selects process with shortest burst time
   - Non-preemptive execution

3. Exercise 3: SRTF (Shortest Remaining Time First - Preemptive)
   - Preemptive version of SJF
   - Switches to shorter jobs when they arrive

4. Exercise 4: Round Robin (Non-Preemptive)
   - Fixed quantum of 4 time units
   - Processes run to completion within quantum

5. Exercise 5: Round Robin
   - Standard Round Robin with configurable quantum
   - Preemptive time-sharing

### Task Scheduling Simulator
Comprehensive scheduler supporting:
- FCFS (First Come First Served)
- SJF (Shortest Job First)
- SRTF (Shortest Remaining Time First)
- RR (Round Robin with configurable quantum)
- Priority Scheduling (lower number = higher priority)

## Compilation Instructions
```bash
# Compile the project
make

## Running the Program

```bash
# After compilation
./scheduler
```

The program will automatically run all test cases and display results for:
- All Part 2 exercises (Exercise 1-5)
- All Part 3 scheduler variations (FCFS, SJF, SRTF, RR, Priority)

## Testing Instructions

### Automated Testing
The `main.cpp` file includes comprehensive test cases for all algorithms. Simply run the compiled program:
```bash
./scheduler
```

