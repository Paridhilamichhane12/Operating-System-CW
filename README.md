# Operating Systems Coursework

This repository contains C implementations of four fundamental Operating Systems topics, including CPU scheduling, deadlock handling, memory management, secure file systems, and client-server communication. Each task demonstrates key operating system concepts through practical implementations.

---

## Repository Structure

```
Operating-System-CW/
│
├── Task1/                        # CPU Scheduling, Deadlock & Threading
│   ├── deadlock.c
│   ├── deadlock_demo.c
│   ├── process1.c
│   ├── roundrobin.c
│   ├── threadcreation.c
│   └── threadsynchronization.c
│
├── Task2/                        # Memory Management
│   └── task2.c
│
├── Task3/                        # Secure File Management System
│   ├── 1.c
│   ├── 2.c
│   ├── 3.c
│   ├── main.c
│   └── task3.c
│
├── Task4/                        # Client-Server Communication
│   ├── client.c
│   ├── common.h
│   └── server.c
│
└── README.md
```

---

## Features

### Task 1 – CPU Scheduling, Deadlock & Threading
- Round Robin CPU Scheduling
- Process Creation using `fork()`
- Thread Creation using POSIX Threads
- Thread Synchronization with Mutex Locks
- Deadlock Demonstration

### Task 2 – Memory Management
- Virtual Memory Simulation
- Page Replacement using FIFO
- Page Fault Tracking
- Memory Frame Management

### Task 3 – Secure File Management System
- User Authentication
- File Creation, Reading and Writing
- File Deletion
- Permission Checking
- File Encryption and Decryption
- Audit Logging

### Task 4 – Client-Server Communication
- TCP Socket Programming
- Multi-threaded Server
- Multiple Client Support
- Message Communication between Server and Clients

---

## Requirements

- GCC (C99 compatible compiler)
- POSIX Threads (`pthread`)
- BSD Socket API (`sys/socket.h`, `netinet/in.h`)
- Linux, macOS, or Windows using WSL

---

## Clone the Repository

```bash
git clone https://github.com/Paridhilamichhane12/Operating-System-CW.git
cd Operating-System-CW
```

---

# Compilation and Execution

## Task 1 – CPU Scheduling, Deadlock & Threads

### Round Robin Scheduling

```bash
gcc Task1/roundrobin.c -o roundrobin
./roundrobin
```

### Deadlock Demonstration

```bash
gcc Task1/deadlock.c -o deadlock
./deadlock
```

### Process Creation

```bash
gcc Task1/process1.c -o process1
./process1
```

### Thread Creation

```bash
gcc Task1/threadcreation.c -o threadcreation -lpthread
./threadcreation
```

### Thread Synchronization

```bash
gcc Task1/threadsynchronization.c -o threadsynchronization -lpthread
./threadsynchronization
```

---

## Task 2 – Memory Management

```bash
gcc Task2/task2.c -o task2
./task2
```

---

## Task 3 – Secure File Management System

```bash
gcc Task3/main.c -o filesystem
./filesystem
```

---

## Task 4 – Client-Server Communication

Compile the server:

```bash
gcc Task4/server.c -o server -lpthread
```

Compile the client:

```bash
gcc Task4/client.c -o client
```

Run the server first:

```bash
./server
```

Open another terminal and run one or more clients:

```bash
./client
```

---

## Learning Outcomes

This coursework demonstrates practical knowledge of:

- CPU Scheduling Algorithms
- Process and Thread Management
- Synchronization Techniques
- Deadlock Concepts
- Virtual Memory Management
- Secure File System Operations
- Authentication and Encryption
- Audit Logging
- TCP/IP Socket Programming
- Multi-threaded Client-Server Systems

---

## Author

**Paridhi Lamichhane**

Operating Systems Coursework
