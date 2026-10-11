#include <stdio.h>
#include <stdlib.h>

void insert(long long heap[], int *size, long long value)
{
    int i = (*size)++;

    while (i > 0 && value < heap[(i - 1) / 2])
    {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap[i] = value;
}

void minHeapify(long long heap[], int size, int i)
{
    long long value = heap[i];
    int child;

    while (2 * i + 1 < size)
    {
        child = 2 * i + 1;

        if (child + 1 < size && heap[child + 1] < heap[child])
            child++;

        if (heap[child] >= value)
            break;

        heap[i] = heap[child];
        i = child;
    }

    heap[i] = value;
}

long long extractMin(long long heap[], int *size)
{
    long long min = heap[0];

    heap[0] = heap[--(*size)];

    minHeapify(heap, *size, 0);

    return min;
}

long long minimumCost(int sticks[], int n)
{
    long long *heap = malloc(n * sizeof(long long));
    int size = n;
    long long cost = 0;
    int i;
    long long x, y, sum;

    if (heap == NULL)
        return -1;

    for (i = 0; i < n; i++)
        heap[i] = (long long)sticks[i];

    for (i = (size / 2) - 1; i >= 0; i--)
        minHeapify(heap, size, i);

    while (size > 1)
    {
        x = extractMin(heap, &size);
        y = extractMin(heap, &size);

        sum = x + y;
        cost += sum;

        insert(heap, &size, sum);
    }

    free(heap);

    return cost;
}

int main()
{
    int n, i;
    int *sticks;
    long long result;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    sticks = malloc(n * sizeof(int));

    if (sticks == NULL)
        return 1;

    printf("Enter stick lengths:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &sticks[i]);

    result = minimumCost(sticks, n);

    if (result == -1)
        printf("Memory allocation failed.\n");
    else
        printf("Minimum cost = %lld\n", result);

    free(sticks);

    return 0;
}