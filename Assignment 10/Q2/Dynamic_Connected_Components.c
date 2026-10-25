#include <stdio.h>
#include <stdlib.h>

int *parent, *rank, *land;

int find(int x)
{
    if (parent[x] != x)
        parent[x] = find(parent[x]);

    return parent[x];
}

void unite(int a, int b)
{
    int ra = find(a);
    int rb = find(b);

    if (ra == rb)
        return;

    if (rank[ra] < rank[rb])
    {
        parent[ra] = rb;
    }
    else if (rank[ra] > rank[rb])
    {
        parent[rb] = ra;
    }
    else
    {
        parent[rb] = ra;
        rank[ra]++;
    }
}

int main()
{
    int R, C, K;

    printf("Enter number of rows: ");
    if (scanf("%d", &R) != 1)
        return 1;

    printf("Enter number of columns: ");
    if (scanf("%d", &C) != 1)
        return 1;

    printf("Enter number of land additions: ");
    if (scanf("%d", &K) != 1)
        return 1;

    int total = R * C;

    parent = (int *)malloc(total * sizeof(int));
    rank = (int *)malloc(total * sizeof(int));
    land = (int *)calloc(total, sizeof(int));

    for (int i = 0; i < total; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    int components = 0;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    printf("Enter land positions (row column):\n");

    for (int i = 0; i < K; i++)
    {
        int r, c;
        scanf("%d %d", &r, &c);

        r--;
        c--;

        int id = r * C + c;

        if (land[id] == 0)
        {
            land[id] = 1;
            components++;

            for (int j = 0; j < 4; j++)
            {
                int nr = r + dr[j];
                int nc = c + dc[j];

                if (nr >= 0 && nr < R && nc >= 0 && nc < C)
                {
                    int nid = nr * C + nc;

                    if (land[nid] == 1)
                    {
                        int root1 = find(id);
                        int root2 = find(nid);

                        if (root1 != root2)
                        {
                            unite(root1, root2);
                            components--;
                        }
                    }
                }
            }
        }

        printf("Number of islands after operation %d: %d\n",
               i + 1, components);
    }

    free(parent);
    free(rank);
    free(land);

    return 0;
}