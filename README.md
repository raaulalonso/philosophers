# philosophers

 [![Intro](https://img.shields.io/badge/Cursus-Philosphers-success?style=for-the-badge&logo=42)](https://github.com/Apeslx/philosophers)
 
 [![Stars](https://img.shields.io/github/stars/Apeslx/philosophers?color=ffff00&label=Stars&logo=Stars&style=?style=flat)](https://github.com/Apeslx/philosophers)
 [![Size](https://img.shields.io/github/repo-size/Apeslx/philosophers?color=blue&label=Size&logo=Size&style=?style=flat)](https://github.com/Apeslx/philosophers)
 [![Activity](https://img.shields.io/github/last-commit/Apeslx/philosophers?color=red&label=Last%20Commit&style=flat)](https://github.com/Apeslx/philosophers)
 
The dining philosophers problem is a classic synchronization and concurrency challenge in computer science that illustrates issues related to resource sharing and deadlock avoidance, using the metaphor of philosophers seated around a dining table who must acquire multiple shared resources (forks) to eat, but must avoid deadlock and data races.

## Problem explanation

- One or more philosophers sit at a round table.
- In the center of the table is a large bowl of spaghetti.
- Philosophers can only eat, think, or sleep.
- While they are eating, they cannot think or sleep;
- While they are thinking, they cannot sleep or eat;
- And, of course, while they are sleeping, they cannot eat or think.
- There are also forks on the table, as many forks as philosophers.
- Because picking up and eating spaghetti with a single fork can be awkward, philosophers must take the fork on the right and the one on the left, one in each hand.
- When a philosopher finishes eating, they will leave the forks on the table and immediately start sleeping. Once they wake up, they will start thinking again.
- The simulation will stop when a philosopher dies of starvation.
- All philosophers need to eat and should never die of hunger.
- Philosophers do not speak to each other.
- Philosophers do not know if another philosopher is going to die.
- Needless to say, everyone should avoid dying.

## Getting Started

### Prerequisites

Before you can start installing philosophers, make sure you have the following prerequisites installed on your computer:

- C Compiler (e.g., GCC)
- Make

### Installation

1. Clone the philosophers repository to your local machine:

   ```shell
   git clone https://github.com/Apeslx/philosophers.git philosophers
2. Change your current working directory to the project folder:
   
   ```shell
   cd philosophers
   cd philo
3. Compile the proyect using the provided Makefile:

   ```shell
   make

## Running the program

To launch the philosophers simulation you can use the following command:

   ```shell
   ./philo [num_of_philo] [time_to_die] [time_to_eat] [time_to_sleep] [num_of_meals_OPTIONAL]
   ```

- Replace "[num_of_philo]" with the number of philosophers for the simulation.  
- Replace "[time_to_die]" with the time in miliseconds a philosopher has before dying of hunger.  
- Replace "[time_to_ear]" with the time in miliseconds a philosopher will spend eating.  
- Replace "[time_to_sleep]" with the time in miliseconds a philosopher will spend sleeping.  
- Replace "[num_of_meals_OPTIONAL]" with the number of meals every philosopher should have before ending the program. THIS ARGUMENT IS OPTIONAL.

## Screenshots

4 650 200 150
- Here, the simulation is executed with the arguments 4 650 200 150. As a result, all of the philosophers are able to eat at time and no one dies.
![Demo GIF](https://github.com/Apeslx/philosophers/blob/main/screenshots/Screenrecording1.gif)
- Here, the simulation is executed with the arguments 4 200 400 300. As a result a philosopher dies because could not eat in time and the simulation ends.
![Demo GIF](https://github.com/Apeslx/philosophers/blob/main/screenshots/Screenrecording2.gif)
