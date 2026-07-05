#include <stdio.h>

int main()
{
    int burst[3] = {5, 7, 4};
    int remain[3];
    int tq = 2;
    int completed = 0;

    for (int i = 0; i < 3; i++)
        remain[i] = burst[i];

    printf("Round Robin Scheduling\n");

    while (completed < 3)
    {
        for (int i = 0; i < 3; i++)
        {
            if (remain[i] > 0)
            {
                if (remain[i] > tq)
                {
                    printf("P%d executes for %d units\n", i + 1, tq);
                    remain[i] -= tq;
                }
                else
                {
                    printf("P%d executes for %d units and finishes\n", i + 1, remain[i]);
                    remain[i] = 0;
                    completed++;
                }
            }
        }
    }

    return 0;
}
