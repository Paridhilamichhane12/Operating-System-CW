#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;

void *task(void *arg)
{
    pthread_mutex_lock(&lock);

    printf("Thread %ld is using the shared resource.\n", (long)arg);

    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, task, (void *)1);
    pthread_create(&t2, NULL, task, (void *)2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);

    printf("Deadlock prevented by using a single mutex.\n");

    return 0;
}
