#include <stdio.h>

#define MAX_FRAMES 20
#define MAX_PAGES 100

void fifo(int pages[], int n, int frames)
{
    int memory[MAX_FRAMES];
    int i, j, pointer = 0, found;
    int pageFaults = 0;

    for (i = 0; i < frames; i++)
        memory[i] = -1;

    printf("\n===== FIFO Page Replacement =====\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < frames; j++)
        {
            if (memory[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            memory[pointer] = pages[i];
            pointer = (pointer + 1) % frames;
            pageFaults++;
            printf("Page %d -> Fault\n", pages[i]);
        }
        else
        {
            printf("Page %d -> Hit\n", pages[i]);
        }

        printf("Frames: ");
        for (j = 0; j < frames; j++)
        {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }
        printf("\n");
    }

    printf("\nFIFO Results\n");
    printf("Page Faults : %d\n", pageFaults);
    printf("Hits        : %d\n", n - pageFaults);
    printf("Hit Ratio   : %.2f\n", (float)(n - pageFaults) / n);
    printf("Miss Ratio  : %.2f\n", (float)pageFaults / n);
}

void lru(int pages[], int n, int frames)
{
    int memory[MAX_FRAMES];
    int recent[MAX_FRAMES];
    int i, j, found;
    int pageFaults = 0;

    for (i = 0; i < frames; i++)
    {
        memory[i] = -1;
        recent[i] = -1;
    }

    printf("\n===== LRU Page Replacement =====\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < frames; j++)
        {
            if (memory[j] == pages[i])
            {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found)
        {
            int empty = -1;

            for (j = 0; j < frames; j++)
            {
                if (memory[j] == -1)
                {
                    empty = j;
                    break;
                }
            }

            if (empty != -1)
            {
                memory[empty] = pages[i];
                recent[empty] = i;
            }
            else
            {
                int lruIndex = 0;

                for (j = 1; j < frames; j++)
                {
                    if (recent[j] < recent[lruIndex])
                        lruIndex = j;
                }

                memory[lruIndex] = pages[i];
                recent[lruIndex] = i;
            }

            pageFaults++;
            printf("Page %d -> Fault\n", pages[i]);
        }
        else
        {
            printf("Page %d -> Hit\n", pages[i]);
        }

        printf("Frames: ");
        for (j = 0; j < frames; j++)
        {
            if (memory[j] == -1)
                printf("- ");
            else
                printf("%d ", memory[j]);
        }
        printf("\n");
    }

    printf("\nLRU Results\n");
    printf("Page Faults : %d\n", pageFaults);
    printf("Hits        : %d\n", n - pageFaults);
    printf("Hit Ratio   : %.2f\n", (float)(n - pageFaults) / n);
    printf("Miss Ratio  : %.2f\n", (float)pageFaults / n);
}

int main()
{
    int pageSize;
    int frames;
    int n;
    int pages[MAX_PAGES];
    int i;

    printf("========== Memory Management Simulation ==========\n");

    printf("Enter Page Size (KB): ");
    scanf("%d", &pageSize);

    printf("Enter Number of Frames: ");
    scanf("%d", &frames);

    printf("Enter Number of Page References: ");
    scanf("%d", &n);

    printf("Enter Page Reference String:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("\nConfigured Page Size: %d KB\n", pageSize);

    fifo(pages, n, frames);

    lru(pages, n, frames);

    return 0;
}

