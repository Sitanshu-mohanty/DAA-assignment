#include <stdio.h>
#include <stdlib.h>

int *parent, *rank, *active;
long long *weight, *sum;

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
        sum[rv] += sum[ru];
    }
    else if (rank[ru] > rank[rv])
    {
        parent[rv] = ru;
        sum[ru] += sum[rv];
    }
    else
    {
        parent[rv] = ru;
        sum[ru] += sum[rv];
        rank[ru]++;
    }
}

int main()
{
    int V, E;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    weight = (long long *)malloc((V + 1) * sizeof(long long));
    parent = (int *)malloc((V + 1) * sizeof(int));
    rank = (int *)malloc((V + 1) * sizeof(int));
    active = (int *)calloc(V + 1, sizeof(int));
    sum = (long long *)malloc((V + 1) * sizeof(long long));

    printf("Enter vertex weights:\n");

    for (int i = 1; i <= V; i++)
        scanf("%lld", &weight[i]);

    int *head = (int *)malloc((V + 1) * sizeof(int));
    int *to = (int *)malloc(2 * E * sizeof(int));
    int *next = (int *)malloc(2 * E * sizeof(int));

    for (int i = 1; i <= V; i++)
        head[i] = -1;

    int edgeIndex = 0;

    printf("Enter edges (u v):\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        to[edgeIndex] = v;
        next[edgeIndex] = head[u];
        head[u] = edgeIndex++;

        to[edgeIndex] = u;
        next[edgeIndex] = head[v];
        head[v] = edgeIndex++;
    }

    int *order = (int *)malloc(V * sizeof(int));

    printf("Enter deletion order:\n");

    for (int i = 0; i < V; i++)
        scanf("%d", &order[i]);

    long long *answer = (long long *)malloc(V * sizeof(long long));

    long long maximum = 0;

    for (int i = V - 1; i >= 0; i--)
    {
        int u = order[i];

        active[u] = 1;
        parent[u] = u;
        rank[u] = 0;
        sum[u] = weight[u];

        if (sum[u] > maximum)
            maximum = sum[u];

        for (int j = head[u]; j != -1; j = next[j])
        {
            int v = to[j];

            if (active[v])
            {
                int ru = find(u);
                int rv = find(v);

                if (ru != rv)
                {
                    unite(ru, rv);
                    int root = find(u);

                    if (sum[root] > maximum)
                        maximum = sum[root];
                }
            }
        }

        answer[i] = maximum;
    }

    printf("\nMaximum component weight after each deletion:\n");

    for (int i = 0; i < V; i++)
    {
        if (i == V - 1)
            printf("After deleting %d: 0\n", order[i]);
        else
            printf("After deleting %d: %lld\n", order[i], answer[i + 1]);
    }

    free(weight);
    free(parent);
    free(rank);
    free(active);
    free(sum);
    free(head);
    free(to);
    free(next);
    free(order);
    free(answer);

    return 0;
}