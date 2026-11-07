#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int to;
    int next;
} Edge;

int main(void) {
    int n, m, k, radius;

    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m < 0) {
        fprintf(stderr, "Error: expected n > 0 and m >= 0.\n");
        return EXIT_FAILURE;
    }
    if (scanf("%d %d", &k, &radius) != 2 ||
        k <= 0 || k > n || radius < 0) {
        fprintf(stderr, "Error: invalid hub count K or radius R.\n");
        return EXIT_FAILURE;
    }

    int *head = malloc((size_t)n * sizeof(*head));
    Edge *edges = malloc((size_t)(m > 0 ? 2 * m : 1) * sizeof(*edges));
    int *owner = malloc((size_t)n * sizeof(*owner));
    int *distance = malloc((size_t)n * sizeof(*distance));
    int *queue = malloc((size_t)n * sizeof(*queue));
    int *hub_seen = calloc((size_t)n, sizeof(*hub_seen));

    if (!head || !edges || !owner || !distance || !queue || !hub_seen) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(head); free(edges); free(owner); free(distance);
        free(queue); free(hub_seen);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; ++i) {
        head[i] = -1;
        owner[i] = -1;
        distance[i] = -1;
    }

    int queue_tail = 0;
    for (int i = 1; i <= k; ++i) {
        int hub;
        if (scanf("%d", &hub) != 1 || hub < 1 || hub > n) {
            fprintf(stderr, "Error: invalid hub vertex at hub index %d.\n", i);
            free(head); free(edges); free(owner); free(distance);
            free(queue); free(hub_seen);
            return EXIT_FAILURE;
        }
        if (hub_seen[hub - 1]) {
            fprintf(stderr, "Error: hub vertices must be distinct.\n");
            free(head); free(edges); free(owner); free(distance);
            free(queue); free(hub_seen);
            return EXIT_FAILURE;
        }
        hub_seen[hub - 1] = 1;
        owner[hub - 1] = i;
        distance[hub - 1] = 0;
        queue[queue_tail++] = hub - 1;
    }

    int edge_count = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > n || v < 1 || v > n || u == v) {
            fprintf(stderr, "Error: invalid edge at edge record %d.\n", i + 1);
            free(head); free(edges); free(owner); free(distance);
            free(queue); free(hub_seen);
            return EXIT_FAILURE;
        }

        edges[edge_count].to = v - 1;
        edges[edge_count].next = head[u - 1];
        head[u - 1] = edge_count++;

        edges[edge_count].to = u - 1;
        edges[edge_count].next = head[v - 1];
        head[v - 1] = edge_count++;
    }

    int front = 0;
    int back = queue_tail;

    while (front < back) {
        int u = queue[front++];

        if (distance[u] >= radius) {
            continue;
        }

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            if (owner[v] == -1) {
                owner[v] = owner[u];
                distance[v] = distance[u] + 1;
                queue[back++] = v;
            }
        }
    }

    printf("Multi-source BFS: radius-constrained hub assignment\n");
    printf("Radius R = %d\n", radius);
    for (int v = 0; v < n; ++v) {
        printf("Vertex %d: owner = %d, distance = %d\n",
               v + 1, owner[v], distance[v]);
    }

    free(head);
    free(edges);
    free(owner);
    free(distance);
    free(queue);
    free(hub_seen);
    return EXIT_SUCCESS;
}
