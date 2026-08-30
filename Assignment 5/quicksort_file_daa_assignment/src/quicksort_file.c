#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INPUT_FILE "data/input.txt"
#define OUTPUT_FILE "data/output.txt"

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        quickSort(arr, p + 1, high);
    }
}

void writeFile(const char *filename, int arr[], int n)
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error: Could not open %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }

    fprintf(file, "\n");
    fclose(file);
}

int main(void)
{
    int n;

    printf("Enter number of random elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of elements must be greater than 0.\n");
        return 1;
    }

    int *arr = malloc(n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    /* Create the data directory on the user's system. */
#ifdef _WIN32
    system("if not exist data mkdir data");
#else
    system("mkdir -p data");
#endif

    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000 + 1;
    }

    writeFile(INPUT_FILE, arr, n);

    quickSort(arr, 0, n - 1);

    writeFile(OUTPUT_FILE, arr, n);

    printf("\n%d random elements generated.\n", n);
    printf("Unsorted elements stored in: %s\n", INPUT_FILE);
    printf("Sorted elements stored in:   %s\n", OUTPUT_FILE);
    printf("Quick Sort completed successfully.\n");

    free(arr);
    return 0;
}
