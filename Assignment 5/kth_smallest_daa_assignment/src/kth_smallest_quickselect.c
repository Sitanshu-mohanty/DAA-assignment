#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int left, int right)
{
    int pivot = arr[right];
    int i = left;

    for (int j = left; j < right; j++)
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

int quickSelect(int arr[], int left, int right, int k)
{
    while (left <= right)
    {
        int pivotIndex = left + (right - left) / 2;
        swap(&arr[pivotIndex], &arr[right]);

        int position = partition(arr, left, right);

        if (position == k)
        {
            return arr[position];
        }
        else if (k < position)
        {
            right = position - 1;
        }
        else
        {
            left = position + 1;
        }
    }

    return -1;
}

int main(void)
{
    int n, k;

    printf("Enter number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    printf("Enter k (1 for smallest): ");
    if (scanf("%d", &k) != 1 || k < 1 || k > n)
    {
        printf("Invalid value of k. It must be between 1 and %d.\n", n);
        free(arr);
        return 1;
    }

    int answer = quickSelect(arr, 0, n - 1, k - 1);

    printf("The %dth smallest element is: %d\n", k, answer);

    free(arr);
    return 0;
}
