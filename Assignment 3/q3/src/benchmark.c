#include <stdio.h>
#include <stdlib.h>

struct Result
{
    int min;
    int max;
};

struct Result findMinMax(int a[], int left, int right, int *count)
{
    struct Result result;
    struct Result leftResult;
    struct Result rightResult;

    if (left == right)
    {
        result.min = a[left];
        result.max = a[left];
        return result;
    }

    if (right == left + 1)
    {
        (*count)++;

        if (a[left] < a[right])
        {
            result.min = a[left];
            result.max = a[right];
        }
        else
        {
            result.min = a[right];
            result.max = a[left];
        }

        return result;
    }

    int mid = left + (right - left) / 2;

    leftResult = findMinMax(a, left, mid, count);
    rightResult = findMinMax(a, mid + 1, right, count);

    (*count)++;
    result.min = (leftResult.min < rightResult.min)
                     ? leftResult.min
                     : rightResult.min;

    (*count)++;
    result.max = (leftResult.max > rightResult.max)
                     ? leftResult.max
                     : rightResult.max;

    return result;
}

int main(void)
{
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
                   4096, 16384, 65536, 262144, 1048576};
    int total = sizeof(sizes) / sizeof(sizes[0]);

    FILE *file = fopen("results/comparisons.csv", "w");

    if (file == NULL)
    {
        printf("Could not create results/comparisons.csv\n");
        printf("Make sure the results folder exists.\n");
        return 1;
    }

    fprintf(file, "n,actual,theoretical_bound\n");

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

        /*
            The number of comparisons depends on the recursion
            structure, not on the actual values. Use a simple array.
        */
        for (int i = 0; i < n; i++)
            a[i] = i;

        int count = 0;

        findMinMax(a, 0, n - 1, &count);

        /*
            The assignment asks for an upper bound of 3n/2.
            For even n, 3n/2 is an integer.
        */
        int theoretical = (3 * n) / 2;

        fprintf(file, "%d,%d,%d\n",
                n, count, theoretical);

        free(a);
    }

    fclose(file);

    printf("Benchmark completed.\n");
    printf("File created: results/comparisons.csv\n");

    return 0;
}
