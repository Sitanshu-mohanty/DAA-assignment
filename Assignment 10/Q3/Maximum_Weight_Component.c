#include <stdio.h>
#include <stdlib.h>

int *parent, *rank, *size;
long long *sum;

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
        size[rv] += size[ru];
        sum[rv] += sum[ru];
    }
    else if (rank[ru] > rank[rv])
    {
        parent[rv] = ru;
        size[ru] += size[rv];
        sum[ru] += sum[rv];
    }
    else
    {
        parent[rv] = ru;
        size[ru] += size[rv];
        sum[ru] += sum[rv];
        rank[ru]++;
    }
}

long long getMaximum(int V, int K)
{
    long long maximum = 0;
    int found = 0;

    for (int i = 1; i <= V; i++)
    {
        if (parent[i] == i && size[i] <= K)
        {
            if (!found || sum[i] > maximum)
            {
                maximum = sum[i];
                found = 1;
            }
        }
    }

    if (!found)
        return 0;

    return maximum;
}

int main()
{
    int V, E, K;

    printf("Enter number of vertices: ");
    if (scanf("%d", &V) != 1)
        return 1;

    printf("Enter size threshold K: ");
    if (scanf("%d", &K) != 1)
        return 1;

    parent = (int *)malloc((V + 1) * sizeof(int));
    rank = (int *)malloc((V + 1) * sizeof(int));
    size = (int *)malloc((V + 1) * sizeof(int));
    sum = (long long *)malloc((V + 1) * sizeof(long long));

    printf("Enter vertex weights:\n");

    for (int i = 1; i <= V; i++)
    {
        long long weight;
        scanf("%lld", &weight);

        parent[i] = i;
        rank[i] = 0;
        size[i] = 1;
        sum[i] = weight;
    }

    printf("Enter number of edges: ");
    if (scanf("%d", &E) != 1)
        return 1;

    printf("Enter edges (u v):\n");

    for (int i = 1; i <= E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        unite(u, v);

        printf("Maximum weight component after edge %d: %lld\n",
               i, getMaximum(V, K));
    }

    free(parent);
    free(rank);
    free(size);
    free(sum);

    return 0;
}