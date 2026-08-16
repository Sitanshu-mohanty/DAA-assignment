#include <stdio.h>
#include <stdlib.h>

int binarySearch(int a[], int n, int x, int *count)
{
    int left = 0, right = n - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        (*count)++;

        if (a[mid] == x)
            return mid;

        if (a[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int ternarySearch(int a[], int n, int x, int *count)
{
    int left = 0, right = n - 1;

    while (left <= right)
    {
        int third = (right - left) / 3;

        int mid1 = left + third;
        int mid2 = right - third;

        (*count)++;

        if (a[mid1] == x)
            return mid1;

        (*count)++;

        if (a[mid2] == x)
            return mid2;

        if (x < a[mid1])
        {
            right = mid1 - 1;
        }
        else if (x > a[mid2])
        {
            left = mid2 + 1;
        }
        else
        {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }

    return -1;
}

void createBenchmark(void)
{
    int sizes[] = {100, 1000, 10000, 100000, 1000000};
    int numberOfSizes = 5;
    int repeats = 1000;

    FILE *file = fopen("results/benchmark.csv", "w");

    if (file == NULL)
    {
        printf("\nCould not create results/benchmark.csv\n");
        printf("Make sure the 'results' folder exists.\n");
        return;
    }

    fprintf(file, "n,binary_comparisons,ternary_comparisons\n");

    for (int s = 0; s < numberOfSizes; s++)
    {
        int n = sizes[s];

        int *a = malloc(n * sizeof(int));

        if (a == NULL)
        {
            printf("Memory allocation failed for n = %d\n", n);
            fclose(file);
            return;
        }

        /* Create sorted array */
        for (int i = 0; i < n; i++)
            a[i] = i;

        int binaryCount = 0;
        int ternaryCount = 0;

        /*
         * Search for the last element.
         * Repeating the search gives a stable average.
         */
        for (int i = 0; i < repeats; i++)
        {
            binarySearch(a, n, n - 1, &binaryCount);
            ternarySearch(a, n, n - 1, &ternaryCount);
        }

        int binaryAverage = binaryCount / repeats;
        int ternaryAverage = ternaryCount / repeats;

        fprintf(file, "%d,%d,%d\n",
                n,
                binaryAverage,
                ternaryAverage);

        free(a);
    }

    fclose(file);

    printf("\nBenchmark completed successfully.\n");
    printf("Benchmark file: results/benchmark.csv\n");
}

int main(void)
{
    int n, x;

    printf("========== BINARY VS TERNARY SEARCH ==========\n\n");

    /* ---------------- USER INPUT ---------------- */

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements in sorted order:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    /* Check whether array is sorted */
    for (int i = 1; i < n; i++)
    {
    if (a[i] < a[i - 1])
    {
        printf("Error: Array is not sorted.\n");
        free(a);
        return 1;
    }
    }

    printf("Enter element to search: ");
    scanf("%d", &x);

    /* ---------------- SEARCH ---------------- */

    int binaryCount = 0;
    int ternaryCount = 0;

    int binaryResult = binarySearch(a, n, x, &binaryCount);
    int ternaryResult = ternarySearch(a, n, x, &ternaryCount);

    printf("\n========== SEARCH RESULT ==========\n");

    printf("\nBinary Search:\n");

    if (binaryResult != -1)
        printf("Element found at index: %d\n", binaryResult);
    else
        printf("Element not found\n");

    printf("Comparisons: %d\n", binaryCount);

    printf("\nTernary Search:\n");

    if (ternaryResult != -1)
        printf("Element found at index: %d\n", ternaryResult);
    else
        printf("Element not found\n");

    printf("Comparisons: %d\n", ternaryCount);

    /* ---------------- CONCLUSION ---------------- */

    printf("\n========== CONCLUSION ==========\n");

    if (binaryCount < ternaryCount)
        printf("Binary Search used fewer comparisons.\n");
    else if (ternaryCount < binaryCount)
        printf("Ternary Search used fewer comparisons.\n");
    else
        printf("Both used the same number of comparisons.\n");

    free(a);

    /* ---------------- BENCHMARK ---------------- */

    printf("\nGenerating benchmark data...\n");

    createBenchmark();

    return 0;
}