#include <stdio.h>
#include <stdlib.h>

/* Compare two integers for qsort */
int compare(const void *a, const void *b)
{
    int first = *(const int *)a;
    int second = *(const int *)b;

    if (first < second)
        return -1;

    if (first > second)
        return 1;

    return 0;
}

/* Search for a value in a sorted part of the array */
int binarySearch(int a[], int left, int right, int value)
{
    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        if (a[mid] == value)
            return 1;

        if (a[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return 0;
}

/* Find k values whose sum is T */
int findSum(int a[], int n, int start, int left, long long sum, int T)
{
    int i;

    /* Choose k - 1 values, then binary-search for the last one */
    if (left == 0)
    {
        long long remaining = (long long)T - sum;

        if (remaining < -2147483648LL || remaining > 2147483647LL)
            return 0;

        return binarySearch(a, start, n - 1, (int)remaining);
    }

    /*
     * We need at least 'left' elements from the remaining array.
     * Therefore, i only goes up to n - left.
     */
    for (i = start; i <= n - left; i++)
    {
        if (findSum(a, n, i + 1, left - 1,
                    sum + a[i], T))
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int n, k, T;
    int *a;

    printf("Enter the size of the set: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Size must be greater than 0.\n");
        return 1;
    }

    a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d integers: ", n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    printf("Enter k: ");
    scanf("%d", &k);

    printf("Enter T: ");
    scanf("%d", &T);

    if (k < 1 || k > n)
    {
        printf("k must be between 1 and n.\n");
        free(a);
        return 1;
    }

    /* Sort the input set */
    qsort(a, n, sizeof(int), compare);

    if (findSum(a, n, 0, k - 1, 0, T))
        printf("A set of %d integers with sum %d exists.\n", k, T);
    else
        printf("No solution found.\n");

    free(a);

    return 0;
}
