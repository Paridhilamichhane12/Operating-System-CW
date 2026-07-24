Operating Systems Coursework

This repository contains C implementations of four Operating Systems topics: CPU scheduling & deadlock handling, memory management, secure file systems, and client-server communication.

Repository Structure

.
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



Requirements


GCC (or any C99-compatible compiler)
POSIX threads (pthread) — required for Task1 and Task4
BSD sockets (sys/socket.h, netinet/in.h) — required for Task4 (Linux/macOS; on Windows use WSL)


Getting Started

Clone the repository:

bashgit clone https://github.com/Paridhilamichhane12/Operating-System-CW.git
cd Operating-System-CW

Task 1 — Scheduling, Deadlock & Threads

bashgcc Task1/roundrobin.c -o roundrobin && ./roundrobin
gcc Task1/deadlock.c -o deadlock && ./deadlock
gcc Task1/threadcreation.c -o threadcreation -lpthread && ./threadcreation

Task 2 — Memory Management

bashgcc Task2/task2.c -o task2 && ./task2

Task 3 — Secure File Management System

bashgcc Task3/main.c -o filesystem && ./filesystem

Task 4 — Client-Server Communication

Run the server first, then one or more clients in separate terminals:

bashgcc Task4/server.c -o server -lpthread && ./server
gcc Task4/client.c -o client && ./client
