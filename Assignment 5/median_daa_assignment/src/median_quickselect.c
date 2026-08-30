#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Swap two integer values. */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Partition the array around the last element as pivot. */
int partition(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = left;
    int j;

    for (j = left; j < right; j++)
    {
        if (arr[j] <= pivot)
        {
            swap(&arr[i], &arr[j]);
            i++;
        }
    }

    swap(&arr[i], &arr[right]);
    return i;
}

/*
 * Return the element with the given zero-based rank.
 * Average time: O(N), Worst case: O(N^2).
 */
int quickSelect(int arr[], int n, int rank)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        int pivotIndex = partition(arr, left, right);

        if (pivotIndex == rank)
        {
            return arr[pivotIndex];
        }
        else if (rank < pivotIndex)
        {
            right = pivotIndex - 1;
        }
        else
        {
            left = pivotIndex + 1;
        }
    }

    return -1; /* This point should never be reached for valid input. */
}

/* Find the median without sorting the complete list. */
double findMedian(int arr[], int n)
{
    if (n % 2 != 0)
    {
        int middle = n / 2;
        return (double)quickSelect(arr, n, middle);
    }
    else
    {
        int leftMiddle = quickSelect(arr, n, n / 2 - 1);
        int rightMiddle = quickSelect(arr, n, n / 2);
        return (leftMiddle + rightMiddle) / 2.0;
    }
}

int main(void)
{
    int n;
    int i;
    int *arr;
    double median;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d numbers:\n", n);
    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    median = findMedian(arr, n);
    printf("Median = %.2f\n", median);

    free(arr);
    return 0;
}
