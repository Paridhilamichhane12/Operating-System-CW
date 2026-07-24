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

Overview

TaskTopicKey Techniques1CPU Scheduling, Deadlock & ThreadingRound Robin scheduling, deadlock detection/demo, process simulation, thread creation & synchronization2Memory ManagementFIFO and LRU page replacement, page fault/hit ratio analysis3Secure File Management SystemUser authentication, audit logging, file create/read/write/delete, Unix-style rwx permissions, XOR file encryption/decryption4Client-Server CommunicationMultithreaded TCP server (pthreads + sockets), client-server authentication, message exchange

Task 1 — CPU Scheduling, Deadlock & Threading

roundrobin.c simulates classic Round Robin scheduling (5 processes, quantum = 4), producing a Gantt-style execution trace along with a completion/turnaround/waiting time summary table. The folder also includes standalone demos for deadlock detection (deadlock.c, deadlock_demo.c), process behavior (process1.c), and POSIX thread creation/synchronization (threadcreation.c, threadsynchronization.c).

Task 2 — Memory Management

task2.c simulates paging with configurable page size, frame count, and a page reference string. It implements both FIFO and LRU page replacement algorithms, printing a hit/fault trace per page and a final summary (page faults, hits, hit ratio, miss ratio) for each algorithm.

Task 3 — Secure File Management System

A menu-driven file management system that:


Authenticates users against users.txt (auto-created with default admin/student accounts on first run)
Logs every action (login, create, read, write, delete, encrypt, decrypt, logout) with a timestamp to audit_log.txt
Supports file create / write (append) / read / delete
Enforces a Unix-style rwx permission model (owner/group/others) before allowing operations
Provides simple XOR-cipher encryption and decryption of files


Task 4 — Client-Server Communication

A multithreaded TCP chat/auth system built on BSD sockets:


server.c listens on port 8080, spawning a pthread per connected client (handle_client)
Clients authenticate with a hardcoded username/password (admin / admin123) before exchanging messages
common.h defines the shared Packet struct (username, password, message) and connection constants
client.c connects, logs in, then lets the user send messages until typing exit


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
