#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n, long long *count)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            (*count)++;

            if (a[j] < a[min])
                min = j;
        }

        if (min != i)
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

int main(void)
{
    int sizes[] = {10, 100, 1000, 5000, 10000};
    int total = sizeof(sizes) / sizeof(sizes[0]);

    FILE *file = fopen("results/comparisons.csv", "w");

    if (file == NULL)
    {
        printf("Could not create results/comparisons.csv\n");
        printf("Make sure the results folder exists.\n");
        return 1;
    }

    fprintf(file, "n,comparisons,theoretical_n2\n");

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

        /* Descending order gives the worst case for swaps. */
        for (int i = 0; i < n; i++)
            a[i] = n - i;

        long long count = 0;

        sort(a, n, &count);

        long long theoretical = (long long)n * (n - 1) / 2;

        fprintf(file, "%d,%lld,%lld\n",
                n, count, theoretical);

        free(a);
    }

    fclose(file);

    printf("Benchmark completed.\n");
    printf("File created: results/comparisons.csv\n");

    return 0;
}
