#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bubbleSortOptimized(int arr[], int n)
{
    int comparisons = 0;

    for (int i = 0; i < n - 1; i++)
    {
        int swapped = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }

    return comparisons;
}

int bubbleSortNormal(int arr[], int n)
{
    int comparisons = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comparisons++;

            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    return comparisons;
}

int main()
{
    int sizes[] = {100, 200, 300, 400, 500};
    int total = 5;

    srand(time(NULL));

    printf("Size\tOptimized\tNormal\n");

    for (int i = 0; i < total; i++)
    {
        int n = sizes[i];

        int arr1[500];
        int arr2[500];

        for (int j = 0; j < n; j++)
        {
            int value = rand() % 1000;
            arr1[j] = value;
            arr2[j] = value;
        }

        int c1 = bubbleSortOptimized(arr1, n);
        int c2 = bubbleSortNormal(arr2, n);

        printf("%d\t%d\t\t%d\n", n, c1, c2);
    }

    return 0;
}