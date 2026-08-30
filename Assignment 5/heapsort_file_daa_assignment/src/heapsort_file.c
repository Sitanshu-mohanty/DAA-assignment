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

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        largest = right;
    }

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    /* Build a max heap. */
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    /* Move the largest element to the end one by one. */
    for (int i = n - 1; i > 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
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

int readFile(const char *filename, int arr[], int n)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Error: Could not open %s\n", filename);
        return 0;
    }

    for (int i = 0; i < n; i++)
    {
        if (fscanf(file, "%d", &arr[i]) != 1)
        {
            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}

int main(void)
{
    int n;

    printf("Enter number of random elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Number of elements must be greater than 0.\n");
        return 1;
    }

    int *arr = malloc((size_t)n * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

#ifdef _WIN32
    system("if not exist data mkdir data");
#else
    system("mkdir -p data");
#endif

    srand((unsigned int)time(NULL));

    /* Generate random elements and store them in the input file. */
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000 + 1;
    }

    writeFile(INPUT_FILE, arr, n);

    /* Read the elements back from the file. */
    if (!readFile(INPUT_FILE, arr, n))
    {
        printf("Error: Could not read the input file.\n");
        free(arr);
        return 1;
    }

    heapSort(arr, n);

    /* Store the sorted elements in the output file. */
    writeFile(OUTPUT_FILE, arr, n);

    printf("\n%d random elements generated.\n", n);
    printf("Unsorted elements stored in: %s\n", INPUT_FILE);
    printf("Sorted elements stored in:   %s\n", OUTPUT_FILE);
    printf("Heap Sort completed successfully.\n");

    free(arr);
    return 0;
}
