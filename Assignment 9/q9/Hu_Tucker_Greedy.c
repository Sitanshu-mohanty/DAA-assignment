#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    long long weight;
    int is_leaf;
    int parent;
    int depth;
} Node;

int main()
{
    int n;

    printf("Enter number of weights: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of weights.\n");
        return 0;
    }

    int max_nodes = 2 * n - 1;

    Node *nodes = (Node *)malloc(max_nodes * sizeof(Node));
    int *seq = (int *)malloc(n * sizeof(int));

    if (nodes == NULL || seq == NULL)
    {
        printf("Memory allocation failed.\n");
        free(nodes);
        free(seq);
        return 0;
    }

    printf("Enter the weights in order:\n");

    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &nodes[i].weight);
        nodes[i].is_leaf = 1;
        nodes[i].parent = -1;
        nodes[i].depth = 0;
        seq[i] = i;
    }

    int count = n;
    int total_nodes = n;

    while (count > 1)
    {
        long long best_cost = -1;
        int best_a = -1;
        int best_b = -1;

        for (int a = 0; a < count; a++)
        {
            for (int b = a + 1; b < count; b++)
            {
                int compatible = 1;

                for (int k = a + 1; k < b; k++)
                {
                    if (nodes[seq[k]].is_leaf)
                    {
                        compatible = 0;
                        break;
                    }
                }

                if (compatible)
                {
                    long long cost = nodes[seq[a]].weight +
                                     nodes[seq[b]].weight;

                    if (best_cost == -1 || cost < best_cost)
                    {
                        best_cost = cost;
                        best_a = a;
                        best_b = b;
                    }
                }
            }
        }

        if (best_a == -1)
        {
            printf("Error: No valid merge found.\n");
            free(nodes);
            free(seq);
            return 0;
        }

        printf("Merge %lld and %lld -> %lld\n",
               nodes[seq[best_a]].weight,
               nodes[seq[best_b]].weight,
               best_cost);

        int new_node = total_nodes++;

        nodes[new_node].weight = best_cost;
        nodes[new_node].is_leaf = 0;
        nodes[new_node].parent = -1;
        nodes[new_node].depth = 0;

        nodes[seq[best_a]].parent = new_node;
        nodes[seq[best_b]].parent = new_node;

        seq[best_a] = new_node;

        for (int i = best_b; i < count - 1; i++)
        {
            seq[i] = seq[i + 1];
        }

        count--;
    }

    long long weighted_path_length = 0;

    printf("\nFinal Leaf Depths:\n");
    printf("Index\tWeight\tDepth\n");
    printf("------------------------\n");

    for (int i = 0; i < n; i++)
    {
        int depth = 0;
        int current = i;

        while (nodes[current].parent != -1)
        {
            depth++;
            current = nodes[current].parent;
        }

        nodes[i].depth = depth;

        weighted_path_length += nodes[i].weight * depth;

        printf("%d\t%lld\t%d\n",
               i + 1,
               nodes[i].weight,
               nodes[i].depth);
    }

    printf("\nTotal Weighted Path Length: %lld\n", weighted_path_length);

    free(nodes);
    free(seq);

    return 0;
}