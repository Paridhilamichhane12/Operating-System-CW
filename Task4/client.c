#include "common.h"

int main()
{
    int client_socket;

    struct sockaddr_in server_addr;

    Packet packet;

    char response[BUFFER_SIZE];

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(client_socket < 0)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(connect(client_socket,
              (struct sockaddr *)&server_addr,
              sizeof(server_addr)) < 0)
    {
        printf("Connection failed.\n");
        return 1;
    }

    printf("=====================================\n");
    printf(" Connected to Server\n");
    printf("=====================================\n");

    printf("Username : ");
    scanf("%49s", packet.username);

    printf("Password : ");
    scanf("%49s", packet.password);

    send(client_socket,
         &packet,
         sizeof(packet),
         0);

    recv(client_socket,
         response,
         sizeof(response),
         0);

    printf("\n%s\n", response);

    if(strcmp(response,"Authentication Successful") != 0)
    {
        close(client_socket);
        return 0;
    }

    getchar();

    while(1)
    {
        memset(&packet,0,sizeof(packet));

        printf("\nEnter Message (type 'exit' to quit): ");

        fgets(packet.message,
              BUFFER_SIZE,
              stdin);

        packet.message[strcspn(packet.message,"\n")] = '\0';

        if(strcmp(packet.message,"exit") == 0)
        {
            break;
        }

        if(strlen(packet.message)==0)
        {
            printf("Message cannot be empty.\n");
            continue;
        }

        send(client_socket,
             &packet,
             sizeof(packet),
             0);

        recv(client_socket,
             response,
             sizeof(response),
             0);

        printf("Server : %s\n", response);
    }

    close(client_socket);

    printf("\nDisconnected from server.\n");

    return 0;
}
