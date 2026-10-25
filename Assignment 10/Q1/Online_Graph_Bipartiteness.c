#include <stdio.h>
#include <stdlib.h>

int *parent, *rank, *parity;

int find(int x)
{
    if (parent[x] != x)
    {
        int p = parent[x];
        parent[x] = find(parent[x]);
        parity[x] ^= parity[p];
    }
    return parent[x];
}

void unite(int u, int v)
{
    int ru = find(u);
    int rv = find(v);

    int pu = parity[u];
    int pv = parity[v];

    if (ru == rv)
        return;

    if (rank[ru] < rank[rv])
    {
        parent[ru] = rv;
        parity[ru] = pu ^ pv ^ 1;
    }
    else if (rank[ru] > rank[rv])
    {
        parent[rv] = ru;
        parity[rv] = pu ^ pv ^ 1;
    }
    else
    {
        parent[rv] = ru;
        parity[rv] = pu ^ pv ^ 1;
        rank[ru]++;
    }
}

int addEdge(int u, int v)
{
    int ru = find(u);
    int rv = find(v);

    if (ru == rv)
    {
        if ((parity[u] ^ parity[v]) == 1)
            return 1;
        else
            return 0;
    }

    unite(u, v);
    return 1;
}

int main()
{
    int V, E;

    printf("Enter number of vertices: ");
    if (scanf("%d", &V) != 1)
        return 1;

    printf("Enter number of edges: ");
    if (scanf("%d", &E) != 1)
        return 1;

    parent = (int *)malloc((V + 1) * sizeof(int));
    rank = (int *)malloc((V + 1) * sizeof(int));
    parity = (int *)malloc((V + 1) * sizeof(int));

    for (int i = 0; i <= V; i++)
    {
        parent[i] = i;
        rank[i] = 0;
        parity[i] = 0;
    }

    printf("Enter edges (u v):\n");

    for (int i = 0; i < E; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);

        if (addEdge(u, v))
        {
            printf("Edge (%d, %d) accepted\n", u, v);
        }
        else
        {
            printf("Edge (%d, %d) rejected - violates bipartiteness\n", u, v);
        }
    }

    free(parent);
    free(rank);
    free(parity);

    return 0;
}