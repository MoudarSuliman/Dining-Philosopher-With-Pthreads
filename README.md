# Dining-Philosopher-With-Pthreads

## Overview

This solution to the Dining Philosophers problem uses threads (pthreads) and mutexes for synchronization instead of processes and semaphores. It demonstrates how to avoid deadlocks and ensure fairness among philosophers using mutexes for mutual exclusion and condition synchronization.

## Compilation

To compile the program, use the following command:

```sh
gcc -o dining_philosophers dining_philosophers.c -lpthread
```

This command compiles the source code into an executable named `dining_philosophers`, linking the pthread library for thread support.

## Running the Program

Execute the compiled program with:

```sh
./dining_philosophers
```

Upon running, the program simulates philosophers who alternate between thinking and eating. It ensures that no two adjacent philosophers eat simultaneously, preventing deadlocks.

## Implementation Details

- **Philosophers' States:** Each philosopher can be THINKING, HUNGRY, or EATING.
- **Mutexes for Synchronization:** The program uses a global mutex `m` for protecting the state changes and an array of mutexes `s[]` for controlling when each philosopher can start eating.
- **State Testing:** The `test()` function checks whether a philosopher can start eating based on the states of their neighbors.

## Program Functions

- **`philosopher(void* arg)`:** Simulates the behavior of a philosopher (thinking and eating).
- **`grab_forks(int i)`:** A philosopher attempts to grab forks to eat.
- **`put_away_forks(int i)`:** A philosopher releases their forks after eating.
- **`test(int i)`:** Checks if a philosopher can start eating.

## Additional Questions

### 1. Adding an Additional Mutex Variable

Simply adding an additional mutex variable to organize critical sections in `grab_forks()` and `put_away_forks()` functions would not be sufficient because mutexes ensure mutual exclusion but do not support atomic changes on multiple mutexes simultaneously. This limitation necessitates a different approach to synchronization, such as the one implemented in this program, where a global mutex controls access to changing states and condition checks.

### 2. Initialization of Mutexes

- The `m` mutex is initialized to 1 (unlocked) because it is used to protect shared data (philosophers' states) and should be initially available.
- The mutexes in the array `s` are initialized to 0 (locked) to ensure that each philosopher thread blocks on these mutexes until it is allowed to eat. This mechanism prevents a philosopher from eating until their `test()` function is called and determines that it is safe to change their state to EATING and unlock their corresponding mutex in `s[]`.
