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

/* Find a pair whose sum is x */
int findPair(int s1[], int s2[], int n, int x, int *first, int *second)
{
    int i = 0;
    int j = n - 1;

    while (i < n && j >= 0)
    {
        int sum = s1[i] + s2[j];

        if (sum == x)
        {
            *first = s1[i];
            *second = s2[j];
            return 1;
        }

        if (sum < x)
            i++;
        else
            j--;
    }

    return 0;
}

int main()
{
    int n, x;
    int *s1, *s2;
    int first, second;

    printf("Enter the size of both sets: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Size must be greater than 0.\n");
        return 1;
    }

    s1 = malloc(n * sizeof(int));
    s2 = malloc(n * sizeof(int));

    if (s1 == NULL || s2 == NULL)
    {
        printf("Memory allocation failed.\n");
        free(s1);
        free(s2);
        return 1;
    }

    printf("Enter %d elements of S1: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &s1[i]);

    printf("Enter %d elements of S2: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &s2[i]);

    printf("Enter x: ");
    scanf("%d", &x);

    /* Sort both sets */
    qsort(s1, n, sizeof(int), compare);
    qsort(s2, n, sizeof(int), compare);

    if (findPair(s1, s2, n, x, &first, &second))
        printf("Pair found: %d + %d = %d\n", first, second, x);
    else
        printf("No pair found.\n");

    free(s1);
    free(s2);

    return 0;
}
