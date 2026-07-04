#include <stdio.h>
#include <pthread.h>

void *display(void *arg)
{
    int id = *(int *)arg;
    printf("Thread %d is running.\n", id);
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread[3];
    int id[3] = {1, 2, 3};

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&thread[i], NULL, display, &id[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}
