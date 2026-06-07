<i>This project has been created as part of the 42 curriculum by ligharbi.</i>

# Philosophers

## Description

This project is a simulation of the classical Dining Philosophers problem.

The goal is to learn and understand:
- multithreading
- synchronization
- mutex usage
- race conditions
- deadlock prevention

Each philosopher is represented by a thread and alternates between thinking, eating, and sleeping. They share forks (mutexes), and must coordinate access to them to avoid conflicts and ensure correct execution.

The simulation ends when:
- a philosopher dies (time_to_die exceeded), or
- all philosophers have eaten a defined number of meals (optional argument)

---

## Instructions

 Compilation
To compile the project, run: make

 Execution
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]

 To clean
 make fclean   # removes objects and executable
 make re       # full rebuild


### Resources
    Unix Threads in C by CodeVault:
        https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=QTzWkcYwb5G3hngs

#### AI Usage

AI (ChatGPT) was used for:

understanding threads
debugging race conditions in thread synchronization
identifying issues related to mutex usage and simulation state handling
improving code structure without changing program behavior
assistance in writing and structuring this README file
