#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int year;
    int type;
} Event;

int compare(const void *a, const void *b)
{
    const Event *e1 = (const Event *)a;
    const Event *e2 = (const Event *)b;

    if (e1->year != e2->year)
        return e1->year - e2->year;

    return e1->type - e2->type;
}
int main()
{
    int n, i;
    int current = 0;
    int maximum = 0;
    int bestYear = 0;

    printf("Enter number of scientists: ");
    scanf("%d", &n);
    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 1;
    }
    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
    for (i = 0; i < n; i++)
    {
        int birth, death;
        printf("Enter birth and death year of scientist %d: ", i + 1);
        scanf("%d %d", &birth, &death);

        events[2 * i].year = birth;
        events[2 * i].type = 1;

        events[2 * i + 1].year = death;
        events[2 * i + 1].type = -1;
    }
    qsort(events, 2 * n, sizeof(Event), compare);

    for (i = 0; i < 2 * n; i++)
    {
        current += events[i].type;
        if (current > maximum)
        {
            maximum = current;
            bestYear = events[i].year;
        }
    }
    printf("\nBest time to be alive: %d\n", bestYear);
    printf("Maximum number of scientists alive: %d\n", maximum);

    free(events);
    return 0;
}