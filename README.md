Dining Philosophers Problem Simulation (C)
This repository contains C code for simulating the classic Dining Philosophers Problem, divided into two folders: philo and philo_bonus. Each folder has its own Makefile and source organization.

### Overview

The simulation depicts philosophers seated at a round table with a bowl of spaghetti in the center. Each philosopher cycles through thinking, eating, and sleeping. To eat, philosophers require two forks, one on their left and one on their right.

The simulation enforces these rules:

An equal number of forks and philosophers are present.
Philosophers can only hold two forks at a time (one each hand).
If a philosopher can't eat within a specified timeframe, they starve.
Philosophers don't communicate or know each other's state.
### Building and Running

Requirements:

 - C compiler (e.g., GCC)
 - POSIX threads library (pthreads) for the philo program

Building:

- Navigate to the root directory of the project and run make on the sub directories philo and philo_bonus since each is with it's own Makefile.

Running:

> Mandatory

- ./philo/philo <number_of_philosophers> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms> [<number_of_times_to_eat>]

> Bonus Part
- ./philo_bonus/philo_bonus <number_of_philosophers> <time_to_die_ms> <time_to_eat_ms> <time_to_sleep_ms> [<number_of_times_to_eat>]

# Arguments:
* <number_of_philosophers>: Number of philosophers (also number of forks)
* <time_to_die_ms>: Time (milliseconds) before starvation for a philosopher
* <time_to_eat_ms>: Time (milliseconds) a philosopher spends eating
* <time_to_sleep_ms>: Time (milliseconds) a philosopher spends sleeping
* [<number_of_times_to_eat>] (optional): Minimum number of times each philosopher must eat before simulation stops (defaults to philosopher starvation)
Use code with caution.
content_copy
### Program Descriptions

philo (Mandatory Part):

Located in the philo folder.
Implements the simulation using threads and mutexes.
Each philosopher is a separate thread.
Mutexes ensure mutual exclusion for accessing forks, preventing deadlocks.
philo_bonus (Bonus Part - Optional):

Located in the philo_bonus folder.
Implements the simulation using processes and semaphores (if implemented).
Each philosopher is a separate process.
A semaphore tracks the number of available forks, eliminating race conditions.
### Logs

The program outputs philosopher state changes with timestamps:

Philosopher X has taken a fork
Philosopher X is eating
Philosopher X is sleeping
Philosopher X is thinking
Philosopher X died
### Bonus Part

The philo_bonus program (if implemented) uses processes and semaphores. This is an optional extension and requires a perfect implementation of philo for evaluation.

### Contributing

Feel free to fork this repository and contribute improvements to the code or documentation.

### References

https://medium.com/swlh/the-dining-philosophers-problem-bbdb92e6b788 (Dining Philosophers Problem tutorial)
https://stackoverflow.com/questions/2332765/what-is-the-difference-between-lock-mutex-and-semaphore#:~:text=A%20mutex%20is%20the%20same,running%20at%20the%20same%20time.
https://medium.com/@jalal92/mutexes-vs-spinlocks-choosing-the-right-locking-mechanism-58ed024fa559


### Additional Notes

The provided Makefiles should compile both programs without relinking unnecessary files.
Thorough error handling is crucial for both philo and philo_bonus (if implemented) to provide informative messages and prevent unexpected crashes.
Implement proper memory management (e.g., using malloc and free responsibly) to avoid memory leaks.
### Disclaimer

While the simulation aims to realistically depict the Dining Philosophers Problem, keep in mind that real-world scenarios might involve more complex conditions and considerations. This simulation primarily focuses on understanding the core concepts of the problem.
### Cleaning Up

To clean up the generated object files and executables, cd to the sub directory & run:

```
make clean && make fclean
```

This will remove all compiled files from the project directory.

### Notes

- Make sure to have a compatible C compiler installed on your system, such as GCC.
- If you encounter any issues during compilation or testing, refer to the error messages for troubleshooting or consult the project documentation.

## Authors

This project was developed by NabilHY for 42 common core's.