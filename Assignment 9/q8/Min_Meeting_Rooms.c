#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int x = *(int *)a;
    int y = *(int *)b;

    if (x < y)
        return -1;
    else if (x > y)
        return 1;
    else
        return 0;
}

int main()
{
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of meetings.\n");
        return 0;
    }

    int *start = (int *)malloc(n * sizeof(int));
    int *end = (int *)malloc(n * sizeof(int));

    if (start == NULL || end == NULL)
    {
        printf("Memory allocation failed.\n");
        free(start);
        free(end);
        return 0;
    }

    printf("Enter start and end time of each meeting:\n");

    for (int i = 0; i < n; i++)
    {
        printf("Meeting %d: ", i + 1);
        scanf("%d %d", &start[i], &end[i]);
    }

    qsort(start, n, sizeof(int), compare);
    qsort(end, n, sizeof(int), compare);

    int i = 0;
    int j = 0;
    int rooms = 0;
    int maxRooms = 0;

    while (i < n)
    {
        if (start[i] < end[j])
        {
            rooms++;

            if (rooms > maxRooms)
                maxRooms = rooms;

            i++;
        }
        else
        {
            rooms--;
            j++;
        }
    }

    printf("\nMinimum number of meeting rooms required = %d\n",
           maxRooms);

    free(start);
    free(end);

    return 0;
}