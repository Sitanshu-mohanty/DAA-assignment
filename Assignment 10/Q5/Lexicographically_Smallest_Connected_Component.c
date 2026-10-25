#include <stdio.h>
#include <stdlib.h>

int *parent, *rank;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int u, int v)
{
    int ru = find(u);
    int rv = find(v);

    if (ru == rv)
        return;

    if (rank[ru] < rank[rv])
    {
        parent[ru] = rv;
    }
    else if (rank[ru] > rank[rv])
    {
        parent[rv] = ru;
    }
    else
    {
        parent[rv] = ru;
        rank[ru]++;
    }
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int n, m;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter permutation:\n");

    for (int i = 1; i <= n; i++)
        scanf("%d", &A[i]);

    parent = (int *)malloc((n + 1) * sizeof(int));
    rank = (int *)malloc((n + 1) * sizeof(int));

    for (int i = 1; i <= n; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &m);

    printf("Enter edges (u v):\n");

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    int **positions = (int **)malloc((n + 1) * sizeof(int *));
    int **values = (int **)malloc((n + 1) * sizeof(int *));
    int *count = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++)
    {
        int root = find(i);
        count[root]++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (count[i] > 0)
        {
            positions[i] = (int *)malloc(count[i] * sizeof(int));
            values[i] = (int *)malloc(count[i] * sizeof(int));
        }
    }

    int *index = (int *)calloc(n + 1, sizeof(int));

    for (int i = 1; i <= n; i++)
    {
        int root = find(i);

        positions[root][index[root]] = i;
        values[root][index[root]] = A[i];

        index[root]++;
    }

    for (int i = 1; i <= n; i++)
    {
        if (count[i] > 0)
        {
            qsort(positions[i], count[i], sizeof(int), compare);
            qsort(values[i], count[i], sizeof(int), compare);

            for (int j = 0; j < count[i]; j++)
                A[positions[i][j]] = values[i][j];
        }
    }

    printf("Lexicographically smallest permutation:\n");

    for (int i = 1; i <= n; i++)
        printf("%d ", A[i]);

    printf("\n");

    for (int i = 1; i <= n; i++)
    {
        if (count[i] > 0)
        {
            free(positions[i]);
            free(values[i]);
        }
    }

    free(A);
    free(parent);
    free(rank);
    free(positions);
    free(values);
    free(count);
    free(index);

    return 0;
}