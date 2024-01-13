# philosophers

 [![Intro](https://img.shields.io/badge/Cursus-Philosphers-success?style=for-the-badge&logo=42)](https://github.com/Apeslx/philosophers)
 
 [![Stars](https://img.shields.io/github/stars/Apeslx/philosophers?color=ffff00&label=Stars&logo=Stars&style=?style=flat)](https://github.com/Apeslx/philosophers)
 [![Size](https://img.shields.io/github/repo-size/Apeslx/philosophers?color=blue&label=Size&logo=Size&style=?style=flat)](https://github.com/Apeslx/philosophers)
 [![Activity](https://img.shields.io/github/last-commit/Apeslx/philosophers?color=red&label=Last%20Commit&style=flat)](https://github.com/Apeslx/philosophers)
 
The dining philosophers problem is a classic synchronization and concurrency challenge in computer science that illustrates issues related to resource sharing and deadlock avoidance, using the metaphor of philosophers seated around a dining table who must acquire multiple shared resources (forks) to eat, but must avoid deadlock and data races.

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

## Running the programs

To launch minitalk, you need to execute the server first with the following command:

   ```shell
   ./server
   ```

Then, in a new shell window, execute the client with the following command:

   ```shell
   ./client [PID] [String]
   ```

Replace [PID] with the process id that the server will print when executed. Also replace [String] with the string you want to send to the server (it can be as long as you like).
The server should print the string correctly and considerably fast.

## Screenshots

![Demo GIF](https://github.com/Apeslx/minitalk/blob/main/screenshots/ScreenRecording.gif)
