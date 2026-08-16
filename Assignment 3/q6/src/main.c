#include <stdio.h>
#include <stdlib.h>

void sort(int a[], int n, int *count)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            (*count)++;

            if (a[j] < a[min])
                min = j;
        }

        if (min != i)
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main(void)
{
    int n;

    printf("========== SORTING USING LOOP INVARIANT ==========\n\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of elements must be positive.\n");
        return 1;
    }

    int *a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int count = 0;

    sort(a, n, &count);

    printf("\nSorted array:\n");
    printArray(a, n);

    printf("\nNumber of comparisons: %d\n", count);
    printf("Worst-case time: Theta(n^2)\n");
    printf("Best-case time: Theta(n^2)\n");

    free(a);

    return 0;
}
