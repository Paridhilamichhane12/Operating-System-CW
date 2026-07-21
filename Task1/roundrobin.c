#include <stdio.h>
#define MAX_PROCESSES 10
int main(void)
{
    int n = 5;
    int quantum = 4;
    int pid[MAX_PROCESSES]      = {1, 2, 3, 4, 5};
    int burst[MAX_PROCESSES]    = {12, 7, 9, 5, 11};
    int remaining[MAX_PROCESSES];
    int completion[MAX_PROCESSES] = {0};
    int turnaround[MAX_PROCESSES] = {0};
    int waiting[MAX_PROCESSES]    = {0};
    int done[MAX_PROCESSES]       = {0};
    for (int i = 0; i < n; i++)
        remaining[i] = burst[i];
    printf("Time Quantum = %d ms\n\n", quantum);
    int time = 0;
    int completed = 0;
    while (completed < n) {
        int any_ran_this_pass = 0;
        for (int i = 0; i < n; i++) {
            if (remaining[i] > 0) {
                any_ran_this_pass = 1;
                int run_time = (remaining[i] > quantum) ? quantum : remaining[i];
                printf("Time %2d -> %2d : Process P%d executes for %d ms\n",
                       time, time + run_time, pid[i], run_time);
                time += run_time;
                remaining[i] -= run_time;
                if (remaining[i] == 0 && !done[i]) {
                    done[i] = 1;
                    completed++;
                    completion[i]  = time;
                    turnaround[i]  = completion[i] - 0;   /* arrival time = 0 for all */
                    waiting[i]     = turnaround[i] - burst[i];
                    printf("Process P%d completed.\n\n", pid[i]);
                }
            }
        }
        if (!any_ran_this_pass) break;   /* safety guard, should not trigger here */
    }
    /* ----- Summary table ----- */
    printf("\nPID\tBurst\tCompletion\tTurnaround\tWaiting\n");
    printf("----------------------------------------------------------\n");
    int total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t\t%d\t\t%d\n",
               pid[i], burst[i], completion[i], turnaround[i], waiting[i]);
        total_waiting    += waiting[i];
        total_turnaround += turnaround[i];
    }
    printf("\nAverage Waiting Time    : %.2f ms\n", (float)total_waiting / n);
    printf("Average Turnaround Time : %.2f ms\n", (float)total_turnaround / n);
    return 0;
}
