#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Process creation failed.\n");
    }
    else if (pid == 0)
    {
        printf("Child Process\n");
        printf("Child PID: %d\n", getpid());
    }
    else
    {
        printf("Parent Process\n");
        printf("Parent PID: %d\n", getpid());
    }

    return 0;
}
