#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

// Default username and password
#define USERNAME "admin"
#define PASSWORD "admin123"

// Structure used for communication
typedef struct
{
    char username[50];
    char password[50];
    char message[BUFFER_SIZE];
} Packet;

#endif
