#include <stdio.h>
#include <stdlib.h>

long long totalCost = 0;
long long totalReversals = 0;

void reverseRange(int a[], int l, int r)
{
    if (l >= r)
        return;

    int i = l, j = r;

    while (i < j)
    {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        i++;
        j--;
    }

    totalReversals++;
    totalCost += (r - l + 1);
}

int stablePartition(int a[], int l, int r, int x)
{
    if (l == r)
        return (a[l] <= x) ? l + 1 : l;

    int m = (l + r) / 2;

    int left = stablePartition(a, l, m, x);
    int right = stablePartition(a, m + 1, r, x);

    if (left <= m && right > m + 1)
    {
        reverseRange(a, left, m);
        reverseRange(a, m + 1, right - 1);
        reverseRange(a, left, right - 1);
    }

    return left + right - m - 1;
}

void sortByReversal(int a[], int l, int r, int low, int high)
{
    if (l >= r || low >= high)
        return;

    int mid = (low + high) / 2;
    int pos = stablePartition(a, l, r, mid);

    sortByReversal(a, l, pos - 1, low, mid);
    sortByReversal(a, pos, r, mid + 1, high);
}

int isValidPermutation(int a[], int n)
{
    int *visited = calloc(n + 1, sizeof(int));

    if (visited == NULL)
        return 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] < 1 || a[i] > n || visited[a[i]])
        {
            free(visited);
            return 0;
        }

        visited[a[i]] = 1;
    }

    free(visited);
    return 1;
}

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid input\n");
        return 1;
    }

    int *a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter permutation: ");

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if (!isValidPermutation(a, n))
    {
        printf("Invalid permutation\n");
        free(a);
        return 1;
    }

    printf("\nOriginal permutation: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    sortByReversal(a, 0, n - 1, 1, n);

    printf("\nSorted permutation: ");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n\nNumber of reversals: %lld", totalReversals);
    printf("\nTotal reversal cost: %lld", totalCost);


    for (int i = 0; i < n; i++)
    {
        if (a[i] != i + 1)
        {
            printf("FAILED\n");
            free(a);
            return 0;
        }
    }

    free(a);

    return 0;
}