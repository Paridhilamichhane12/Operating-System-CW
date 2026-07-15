#include "common.h"

void *handle_client(void *socket_desc)
{
    int client_socket = *(int *)socket_desc;
    Packet packet;

    // Receive login packet
    if (recv(client_socket, &packet, sizeof(packet), 0) <= 0)
    {
        printf("Client disconnected.\n");
        close(client_socket);
        free(socket_desc);
        pthread_exit(NULL);
    }

    // Authentication
    if (strcmp(packet.username, USERNAME) != 0 ||
        strcmp(packet.password, PASSWORD) != 0)
    {
        char msg[] = "Authentication Failed";
        send(client_socket, msg, sizeof(msg), 0);

        printf("Authentication failed for client.\n");

        close(client_socket);
        free(socket_desc);
        pthread_exit(NULL);
    }

    char success[] = "Authentication Successful";
    send(client_socket, success, sizeof(success), 0);

    printf("Client authenticated successfully.\n");

    while (1)
    {
        memset(&packet, 0, sizeof(packet));

        int bytes = recv(client_socket, &packet, sizeof(packet), 0);

        if (bytes <= 0)
        {
            printf("Client disconnected.\n");
            break;
        }

        // Basic validation
        if (strlen(packet.message) == 0)
        {
            char err[] = "Empty message not allowed.";
            send(client_socket, err, sizeof(err), 0);
            continue;
        }

        printf("Client: %s\n", packet.message);

        char reply[BUFFER_SIZE];

        snprintf(reply,
                 BUFFER_SIZE,
                 "Server received: %s",
                 packet.message);

        send(client_socket,
             reply,
             strlen(reply) + 1,
             0);
    }

    close(client_socket);

    free(socket_desc);

    pthread_exit(NULL);
}

int main()
{
    int server_socket;
    int client_socket;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    socklen_t client_len = sizeof(client_addr);

    server_socket = socket(AF_INET,
                           SOCK_STREAM,
                           0);

    if (server_socket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
    {
        printf("Bind failed.\n");
        return 1;
    }

    if (listen(server_socket,
               MAX_CLIENTS) < 0)
    {
        printf("Listen failed.\n");
        return 1;
    }

    printf("=====================================\n");
    printf("Server Started\n");
    printf("Listening on Port %d...\n", PORT);
    printf("=====================================\n");

    while (1)
    {
        client_socket = accept(server_socket,
                               (struct sockaddr *)&client_addr,
                               &client_len);

        if (client_socket < 0)
        {
            printf("Accept failed.\n");
            continue;
        }

        printf("Client Connected.\n");

        pthread_t thread;

        int *new_socket = malloc(sizeof(int));

        *new_socket = client_socket;

        if (pthread_create(&thread,
                           NULL,
                           handle_client,
                           (void *)new_socket) != 0)
        {
            printf("Thread creation failed.\n");

            close(client_socket);

            free(new_socket);
        }

        pthread_detach(thread);
    }

    close(server_socket);

    return 0;
}
