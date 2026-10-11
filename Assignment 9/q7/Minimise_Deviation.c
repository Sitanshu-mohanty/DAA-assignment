#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef long long ll;

void swap(ll *a, ll *b)
{
    ll temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(ll heap[], int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left] > heap[largest])
        largest = left;

    if (right < size && heap[right] > heap[largest])
        largest = right;

    if (largest != i)
    {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, size, largest);
    }
}

void insert(ll heap[], int *size, ll value)
{
    int i = (*size)++;

    while (i > 0 && value > heap[(i - 1) / 2])
    {
        heap[i] = heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap[i] = value;
}

ll extractMax(ll heap[], int *size)
{
    ll max = heap[0];
    heap[0] = heap[--(*size)];

    if (*size > 0)
        maxHeapify(heap, *size, 0);

    return max;
}

int main()
{
    int n, i;
    ll *heap;
    ll minValue, maxValue, minDeviation, currentDeviation, value;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input.\n");
        return 1;
    }

    heap = malloc(n * sizeof(ll));
    if (heap == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter elements:\n");
    minValue = LLONG_MAX;

    for (i = 0; i < n; i++)
    {
        scanf("%lld", &value);

        if (value % 2 != 0)
            value = value * 2;

        heap[i] = value;

        if (value < minValue)
            minValue = value;
    }

    for (i = n / 2 - 1; i >= 0; i--)
        maxHeapify(heap, n, i);

    minDeviation = heap[0] - minValue;

    while (heap[0] % 2 == 0)
    {
        maxValue = extractMax(heap, &n);
        value = maxValue / 2;

        if (value < minValue)
            minValue = value;

        insert(heap, &n, value);

        currentDeviation = heap[0] - minValue;
        if (currentDeviation < minDeviation)
        {
            minDeviation = currentDeviation;
        }
    }

    printf("Minimum deviation = %lld\n", minDeviation);

    free(heap);
    return 0;
}