#include <stdio.h>
#include <stdlib.h>

struct Event
{
    int time;
    int type; /* 1 = entry, -1 = exit */
};

/* Compare two events by time */
int compare(const void *a, const void *b)
{
    const struct Event *first = (const struct Event *)a;
    const struct Event *second = (const struct Event *)b;

    if (first->time < second->time)
        return -1;
    if (first->time > second->time)
        return 1;

    return 0;
}

/* Find the maximum number of people and the time it is reached */
void findMax(struct Event events[], int total, int *maxPeople, int *maxTime)
{
    int count = 0;
    *maxPeople = 0;
    *maxTime = 0;

    for (int i = 0; i < total; i++)
    {
        if (events[i].type == 1)
        {
            count++;

            if (count > *maxPeople)
            {
                *maxPeople = count;
                *maxTime = events[i].time;
            }
        }
        else
        {
            count--;
        }
    }
}

int main(void)
{
    int n;
    struct Event *events;
    int maxPeople, maxTime;

    printf("Enter the number of people: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of people must be greater than 0.\n");
        return 1;
    }

    /* Each person produces two events: one entry and one exit. */
    events = malloc(2 * n * sizeof(struct Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter entry and exit time for each person:\n");

    for (int i = 0; i < n; i++)
    {
        int entry, exit;

        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry, &exit);

        if (exit <= entry)
        {
            printf("Exit time must be greater than entry time.\n");
            free(events);
            return 1;
        }

        events[2 * i].time = entry;
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit;
        events[2 * i + 1].type = -1;
    }

    /* Sort all entry and exit events by time. */
    qsort(events, 2 * n, sizeof(struct Event), compare);

    findMax(events, 2 * n, &maxPeople, &maxTime);

    printf("\nMaximum people present: %d\n", maxPeople);
    printf("Time when maximum was reached: %d\n", maxTime);

    free(events);
    return 0;
}
