#include <stdio.h>
#include <stdlib.h>

/* Swap two integer values. */
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Simple insertion sort used only for comparison. */
void sortArray(int arr[], int n)
{
    int i;
    int j;
    int key;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

double findMedian(int arr[], int n)
{
    sortArray(arr, n);

    if (n % 2 != 0)
    {
        return (double)arr[n / 2];
    }

    return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
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
