#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int distance;
    int fuel;
} Station;

int compareStations(const void *a, const void *b)
{
    Station *s1 = (Station *)a;
    Station *s2 = (Station *)b;

    if (s1->distance < s2->distance)
        return -1;
    if (s1->distance > s2->distance)
        return 1;

    return 0;
}

void insertMaxHeap(int heap[], int *size, int value)
{
    int i = (*size)++;

    while (i > 0 && value > heap[(i - 1) / 2])
    {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap[i] = value;
}

int extractMax(int heap[], int *size)
{
    int maximum = heap[0];
    int value = heap[--(*size)];
    int i = 0;
    int child;

    while (2 * i + 1 < *size)
    {
        child = 2 * i + 1;

        if (child + 1 < *size &&
            heap[child + 1] > heap[child])
        {
            child++;
        }

        if (heap[child] <= value)
            break;

        heap[i] = heap[child];
        i = child;
    }

    heap[i] = value;

    return maximum;
}

int minimumStops(int D, int F, Station stations[], int n)
{
    int *heap = malloc((n + 1) * sizeof(int));
    int heapSize = 0;
    int currentFuel = F;
    int currentPosition = 0;
    int stops = 0;
    int i;

    if (heap == NULL)
        return -1;

    qsort(stations, n, sizeof(Station), compareStations);

    for (i = 0; i <= n; i++)
    {
        int nextPosition;
        int distance;

        if (i == n)
            nextPosition = D;
        else
            nextPosition = stations[i].distance;

        if (nextPosition > D)
            nextPosition = D;

        distance = nextPosition - currentPosition;

        while (currentFuel < distance)
        {
            if (heapSize == 0)
            {
                free(heap);
                return -1;
            }

            currentFuel += extractMax(heap, &heapSize);
            stops++;
        }

        currentFuel -= distance;
        currentPosition = nextPosition;

        if (i < n && stations[i].distance <= D)
            insertMaxHeap(heap, &heapSize, stations[i].fuel);

        if (currentPosition == D)
            break;
    }

    free(heap);
    return stops;
}

int main()
{
    int n, D, F;
    int i, result;
    Station *stations;

    printf("Enter target distance: ");
    scanf("%d", &D);

    printf("Enter initial fuel: ");
    scanf("%d", &F);

    printf("Enter number of stations: ");
    scanf("%d", &n);

    if (D <= 0 || F < 0 || n < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    stations = malloc((n > 0 ? n : 1) * sizeof(Station));

    if (stations == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (n > 0)
    {
        printf("Enter station distance and fuel:\n");

        for (i = 0; i < n; i++)
        {
            scanf("%d %d",
                  &stations[i].distance,
                  &stations[i].fuel);

            if (stations[i].distance < 0 ||
                stations[i].fuel < 0)
            {
                printf("Invalid station data.\n");
                free(stations);
                return 1;
            }
        }
    }

    result = minimumStops(D, F, stations, n);

    if (result == -1)
        printf("Target cannot be reached.\n");
    else
        printf("Minimum refuelling stops = %d\n", result);

    free(stations);

    return 0;
}