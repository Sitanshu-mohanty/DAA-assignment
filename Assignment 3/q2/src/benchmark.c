#include <stdio.h>
#include <stdlib.h>

/* Return -1 if left is lighter, 1 if right is lighter, 0 if equal. */
int weigh(int a[], int left, int right, int size)
{
    int leftWeight = 0;
    int rightWeight = 0;

    for (int i = 0; i < size; i++)
    {
        leftWeight += a[left + i];
        rightWeight += a[right + i];
    }

    if (leftWeight < rightWeight)
        return -1;

    if (leftWeight > rightWeight)
        return 1;

    return 0;
}

/* Divide-and-conquer search. */
int findCoin(int a[], int left, int right, int *count)
{
    int n = right - left + 1;

    if (n == 1)
        return left;

    if (n == 2)
    {
        (*count)++;

        if (a[left] < a[right])
            return left;

        if (a[right] < a[left])
            return right;

        return -1;
    }

    int size = n / 2;

    int result = weigh(a, left, left + size, size);
    (*count)++;

    if (result == -1)
        return findCoin(a, left, left + size - 1, count);

    if (result == 1)
        return findCoin(a, left + size,
                        left + 2 * size - 1, count);

    if (n % 2 == 0)
        return -1;

    (*count)++;

    if (a[right] < a[left])
        return right;

    return -1;
}

/* Ceiling of log2(n), using only integer arithmetic. */
int log2Ceil(int n)
{
    int value = 1;
    int count = 0;

    while (value < n)
    {
        value *= 2;
        count++;
    }

    return count;
}

int main(void)
{
    int sizes[] = {10, 100, 1000, 10000, 100000, 1000000};
    int total = 6;

    FILE *file = fopen("results/benchmark.csv", "w");

    if (file == NULL)
    {
        printf("Could not create results/benchmark.csv\n");
        printf("Make sure the results folder exists.\n");
        return 1;
    }

    fprintf(file, "n,weighings,theoretical\n");

    for (int s = 0; s < total; s++)
    {
        int n = sizes[s];

        int *a = malloc(n * sizeof(int));

        if (a == NULL)
        {
            printf("Memory allocation failed for n = %d\n", n);
            fclose(file);
            return 1;
        }

        /* All coins are normal weight 10. */
        for (int i = 0; i < n; i++)
            a[i] = 10;

        /*
            Put the defective coin at the beginning.
            This forces the algorithm to keep following
            the lighter half, giving a worst-case style test.
        */
        a[0] = 9;

        int count = 0;

        findCoin(a, 0, n - 1, &count);

        int theoretical = log2Ceil(n);

        fprintf(file, "%d,%d,%d\n",
                n, count, theoretical);

        free(a);
    }

    fclose(file);

    printf("Benchmark completed.\n");
    printf("File created: results/benchmark.csv\n");

    return 0;
}
