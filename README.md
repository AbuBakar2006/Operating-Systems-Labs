# Operating Systems Labs

A comprehensive repository containing laboratory exercises, assignments, and implementations for operating systems concepts. All code is written in C and targets Linux/Unix system APIs.

## Directory Structure

- **`01-Process-Management/`**
  - Explores process creation, hierarchy, and orchestration using `fork()`, `exec()`, `wait()`, and `exit()`.
  - Implements multi-threading programs using POSIX threads (`pthread`), parallel array summation, signal handling, and thread synchronization.
  - Features process trees, chains, and fans.

- **`02-File-Systems-and-IO/`**
  - Covers low-level file I/O operations using standard system calls (`open`, `read`, `write`, `close`).
  - Includes scripts for manual file copying, a directory crawler, file/char/line/blank counters, and link management (`link1`/`link2`).

- **`03-Inter-Process-Communication/`**
  - Explores IPC mechanisms, focusing on Pipes and Shared Memory.
  - Implements unidirectional and bidirectional pipe communication, I/O redirection (stdout and tee redirection), and shell-like process chains.

- **`04-Synchronization-and-Deadlocks/`**
  - Deals with concurrency issues, race conditions, and resource allocation.
  - Implements synchronization solutions using mutexes and semaphores.
  - Includes a simulation of the Banker's Algorithm for deadlock safety, along with demonstrations of deadlocks and starvation.

- **`05-Manuals-and-Documents/`**
  - Contains reference manuals, course profiles, assignment question sheets, and deadlocks documentation.

## Getting Started

### Prerequisites
- GCC compiler
- Linux/Unix environment (or WSL/MinGW for Windows)

### Compilation & Running
To compile any C file, run:
```bash
gcc -pthread filename.c -o filename
./filename
```
*(Note: `-pthread` flag is required for compiling programs using POSIX threads).*
