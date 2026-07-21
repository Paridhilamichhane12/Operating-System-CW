#include <stdio.h>
#include <pthread.h>

#define NUM_ACCOUNTS  2
#define NUM_TRANSFERS 5000   /* transfers performed by each thread */

typedef struct {
    int balance;
    pthread_mutex_t lock;
} account_t;

static account_t accounts[NUM_ACCOUNTS];
 typedef struct {
    int from;
    int to;
    int amount;
} transfer_job_t;

void *transfer_worker(void *arg)
{
    transfer_job_t *job = (transfer_job_t *)arg;

    for (int i = 0; i < NUM_TRANSFERS; i++) {
        int a = job->from, b = job->to;

        /* --- deadlock-prevention rule --- */
        int first  = (a < b) ? a : b;
        int second = (a < b) ? b : a;

        pthread_mutex_lock(&accounts[first].lock);
        pthread_mutex_lock(&accounts[second].lock);

        if (accounts[a].balance >= job->amount) {
            accounts[a].balance -= job->amount;
            accounts[b].balance += job->amount;
        }

        pthread_mutex_unlock(&accounts[second].lock);
        pthread_mutex_unlock(&accounts[first].lock);
    }
    return NULL;
}

int main(void)
{
    printf("================ DEADLOCK PREVENTION (ordered locking) ================\n");

    for (int i = 0; i < NUM_ACCOUNTS; i++) {
        accounts[i].balance = 1000000;
        pthread_mutex_init(&accounts[i].lock, NULL);
    }
    int total_before = accounts[0].balance + accounts[1].balance;

    pthread_t t1, t2;
    transfer_job_t jobA_to_B = { .from = 0, .to = 1, .amount = 3 };
    transfer_job_t jobB_to_A = { .from = 1, .to = 0, .amount = 5 };

    printf("Starting two threads transferring in OPPOSITE directions concurrently...\n");
    printf("Thread 1: Account0 -> Account1  (%d transfers)\n", NUM_TRANSFERS);
    printf("Thread 2: Account1 -> Account0  (%d transfers)\n\n", NUM_TRANSFERS);

    pthread_create(&t1, NULL, transfer_worker, &jobA_to_B);
    pthread_create(&t2, NULL, transfer_worker, &jobB_to_A);
     pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    int total_after = accounts[0].balance + accounts[1].balance;

    printf("No deadlock occurred - both threads completed all %d transfers each.\n", NUM_TRANSFERS);
    printf("Account 0 balance : %d\n", accounts[0].balance);
    printf("Account 1 balance : %d\n", accounts[1].balance);
    printf("Total before : %d\n", total_before);
    printf("Total after  : %d\n", total_after);
    printf("%s\n", (total_before == total_after)
                    ? "Balances consistent - no lost updates."
                    : "MISMATCH! (should not happen)");

    for (int i = 0; i < NUM_ACCOUNTS; i++)
        pthread_mutex_destroy(&accounts[i].lock);
    return 0;
}
