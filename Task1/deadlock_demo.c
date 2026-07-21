#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_ACCOUNTS  2
#define NUM_TRANSFERS 5000

typedef struct {
    int balance;
    pthread_mutex_t lock;
} account_t;

static account_t accounts[NUM_ACCOUNTS];

typedef struct {
    int from;
    int to;
    int amount;
    const char *label;
} transfer_job_t;
void *transfer_worker(void *arg)
{
    transfer_job_t *job = (transfer_job_t *)arg;
 
    for (int i = 0; i < NUM_TRANSFERS; i++) {
        int a = job->from, b = job->to;
 
        printf("[%s] iteration %d: locking account %d (source)...\n", job->label, i, a);
        pthread_mutex_lock(&accounts[a].lock);
 
        usleep(1000); /* widen the window so the deadlock reliably triggers */
 
        printf("[%s] iteration %d: locking account %d (destination)...\n", job->label, i, b);
        pthread_mutex_lock(&accounts[b].lock);
 
        if (accounts[a].balance >= job->amount) {
            accounts[a].balance -= job->amount;
            accounts[b].balance += job->amount;
        }
 
        pthread_mutex_unlock(&accounts[b].lock);
        pthread_mutex_unlock(&accounts[a].lock);
    }
    return NULL;
}
 
int main(void)
{
    printf("================ DEADLOCK DEMONSTRATION (naive locking - BUGGY) ================\n");
 
    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        accounts[i].balance = 1000000;
        pthread_mutex_init(&accounts[i].lock, NULL);
    }
 
    pthread_t t1, t2;
    transfer_job_t jobA_to_B = { .from = 0, .to = 1, .amount = 3, .label = "Thread1 A->B" };
    transfer_job_t jobB_to_A = { .from = 1, .to = 0, .amount = 5, .label = "Thread2 B->A" };
 
    printf("Starting two threads transferring in OPPOSITE directions concurrently...\n");
    printf("Watch: this will likely hang forever once both threads hold one lock\n");
    printf("       each and wait on the other's lock. Press Ctrl+C to stop.\n\n");
 
    pthread_create(&t1, NULL, transfer_worker, &jobA_to_B);
    pthread_create(&t2, NULL, transfer_worker, &jobB_to_A);
 
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
 
    /* This line is only reached if no deadlock occurred on this run. */
    printf("\nBoth threads finished without deadlocking (got lucky with timing).\n");
 
    for (int i = 0; i < NUM_ACCOUNTS; i++)
        pthread_mutex_destroy(&accounts[i].lock);
 
    return 0;
}
