#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int compare(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y)
        return -1;
    if (x > y)
        return 1;
    return 0;
}

void copyArray(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

int findMaximum(int arr[], int n)
{
    int max = arr[0];

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

int findLargestTwo(int arr[], int n, int *largest, int *second)
{
    *largest = arr[0];
    int foundSecond = 0;

    for (int i = 1; i < n; i++)
    {
        if (arr[i] > *largest)
        {
            *second = *largest;
            *largest = arr[i];
            foundSecond = 1;
        }
        else if (arr[i] < *largest &&
                 (!foundSecond || arr[i] > *second))
        {
            *second = arr[i];
            foundSecond = 1;
        }
    }

    return foundSecond;
}

double findMean(int arr[], int n)
{
    long long sum = 0;

    for (int i = 0; i < n; i++)
        sum += arr[i];

    return (double)sum / n;
}

double findStandardDeviation(int arr[], int n)
{
    double mean = findMean(arr, n);
    double sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += pow(arr[i] - mean, 2);

    return sqrt(sum / n);
}

double findMedian(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);

    if (n % 2 != 0)
        return arr[n / 2];
    else
        return (arr[n / 2 - 1] + arr[n / 2]) / 2.0;
}

int findMode(int arr[], int n)
{
    int mode = arr[0];
    int maxFreq = 0;

    for (int i = 0; i < n; i++)
    {
        int freq = 0;

        for (int j = 0; j < n; j++)
        {
            if (arr[i] == arr[j])
                freq++;
        }

        if (freq > maxFreq)
        {
            maxFreq = freq;
            mode = arr[i];
        }
    }

    if (maxFreq == 1)
        return -1;

    return mode;
}

int removeDuplicates(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = i + 1;

        while (j < n)
        {
            if (arr[i] == arr[j])
            {
                for (int k = j; k < n - 1; k++)
                    arr[k] = arr[k + 1];

                n--;
            }
            else
            {
                j++;
            }
        }
    }

    return n;
}

void reverseArray(int arr[], int n)
{
    int left = 0;
    int right = n - 1;

    while (left < right)
    {
        swap(&arr[left], &arr[right]);
        left++;
        right--;
    }
}

void partitionArray(int arr[], int n, int pivot)
{
    int left = 0;
    int right = n - 1;

    while (left <= right)
    {
        while (left <= right && arr[left] >= pivot)
            left++;

        while (left <= right && arr[right] < pivot)
            right--;

        if (left < right)
        {
            swap(&arr[left], &arr[right]);
            left++;
            right--;
        }
    }
}

int main()
{
    int n;
    int pivot;
    int largest;
    int secondLargest;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("At least 2 elements are required.\n");
        return 0;
    }

    int *arr = malloc(n * sizeof(int));
    int *temp = malloc(n * sizeof(int));

    if (arr == NULL || temp == NULL)
    {
        printf("Memory allocation failed.\n");
        free(arr);
        free(temp);
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("\nOriginal Array: ");
    printArray(arr, n);

    printf("\n1. Maximum Element = %d\n",
           findMaximum(arr, n));

    if (findLargestTwo(arr, n, &largest, &secondLargest))
    {
        printf("2. Largest = %d\n", largest);
        printf("   Second Largest = %d\n", secondLargest);
    }
    else
    {
        printf("2. Largest = %d\n", largest);
        printf("   Second Largest = Does not exist\n");
    }

    printf("3. Mean = %.2f\n",
           findMean(arr, n));

    copyArray(arr, temp, n);

    printf("4. Median = %.2f\n",
           findMedian(temp, n));

    printf("5. Standard Deviation = %.2f\n",
           findStandardDeviation(arr, n));

    int mode = findMode(arr, n);

    if (mode == -1)
        printf("6. Mode = No mode exists\n");
    else
        printf("6. Mode = %d\n", mode);

    copyArray(arr, temp, n);

    int newSize = removeDuplicates(temp, n);

    printf("7. After removing duplicates: ");
    printArray(temp, newSize);

    copyArray(arr, temp, n);

    reverseArray(temp, n);

    printf("8. Reversed Array: ");
    printArray(temp, n);

    printf("9. Enter pivot element: ");
    scanf("%d", &pivot);

    copyArray(arr, temp, n);

    partitionArray(temp, n, pivot);

    printf("Array after partitioning: ");
    printArray(temp, n);

    free(temp);
    free(arr);

    return 0;
}