#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF (LLONG_MAX / 4)

typedef struct {
    int to;
    int weight;
    int next;
} Edge;

typedef struct {
    int state;
    int next;
} DequeNode;

typedef struct {
    DequeNode *items;
    int capacity;
    int head;
    int size;
} Deque;

static int deque_init(Deque *dq, int capacity) {
    dq->items = (DequeNode *)malloc((size_t)capacity * sizeof(DequeNode));
    if (dq->items == NULL) return 0;
    dq->capacity = capacity;
    dq->head = 0;
    dq->size = 0;
    return 1;
}

static int deque_grow(Deque *dq) {
    int new_capacity = dq->capacity * 2;
    DequeNode *new_items = (DequeNode *)malloc((size_t)new_capacity * sizeof(DequeNode));
    if (new_items == NULL) return 0;

    for (int i = 0; i < dq->size; ++i) {
        new_items[i] = dq->items[(dq->head + i) % dq->capacity];
    }
    free(dq->items);
    dq->items = new_items;
    dq->capacity = new_capacity;
    dq->head = 0;
    return 1;
}

static int deque_push_front(Deque *dq, int state) {
    if (dq->size == dq->capacity && !deque_grow(dq)) return 0;
    dq->head = (dq->head - 1 + dq->capacity) % dq->capacity;
    dq->items[dq->head].state = state;
    dq->size++;
    return 1;
}

static int deque_push_back(Deque *dq, int state) {
    if (dq->size == dq->capacity && !deque_grow(dq)) return 0;
    int index = (dq->head + dq->size) % dq->capacity;
    dq->items[index].state = state;
    dq->size++;
    return 1;
}

static int deque_pop_front(Deque *dq, int *state) {
    if (dq->size == 0) return 0;
    *state = dq->items[dq->head].state;
    dq->head = (dq->head + 1) % dq->capacity;
    dq->size--;
    return 1;
}

static int state_id(int vertex, int parity) {
    return 2 * (vertex - 1) + parity;
}

int main(void) {
    int n, m;
    int source;
    long long penalty;

    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || m < 0) {
        fprintf(stderr, "Error: expected positive n and non-negative m.\n");
        return EXIT_FAILURE;
    }
    if (scanf("%d %lld", &source, &penalty) != 2 ||
        source < 1 || source > n || penalty < 0) {
        fprintf(stderr, "Error: invalid source or penalty C.\n");
        return EXIT_FAILURE;
    }

    int state_count = 2 * n;
    int *head = (int *)malloc((size_t)n * sizeof(int));
    Edge *edges = (Edge *)malloc((size_t)(m > 0 ? m : 1) * sizeof(Edge));
    long long *dist = (long long *)malloc((size_t)state_count * sizeof(long long));
    if (head == NULL || edges == NULL || dist == NULL) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(head);
        free(edges);
        free(dist);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; ++i) head[i] = -1;
    for (int i = 0; i < state_count; ++i) dist[i] = INF;

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        if (scanf("%d %d %d", &u, &v, &w) != 3 ||
            u < 1 || u > n || v < 1 || v > n || (w != 0 && w != 1)) {
            fprintf(stderr, "Error: invalid edge on input line %d.\n", i + 3);
            free(head);
            free(edges);
            free(dist);
            return EXIT_FAILURE;
        }
        edges[i].to = v - 1;
        edges[i].weight = w;
        edges[i].next = head[u - 1];
        head[u - 1] = i;
    }

    Deque dq;
    if (!deque_init(&dq, state_count > 0 ? state_count : 1)) {
        fprintf(stderr, "Error: memory allocation failed for deque.\n");
        free(head);
        free(edges);
        free(dist);
        return EXIT_FAILURE;
    }

    int start = state_id(source, 0);
    dist[start] = 0;
    if (!deque_push_front(&dq, start)) {
        fprintf(stderr, "Error: deque allocation failed.\n");
        free(dq.items); free(head); free(edges); free(dist);
        return EXIT_FAILURE;
    }

    int current_state;
    while (deque_pop_front(&dq, &current_state)) {
        int u = current_state / 2;      /* zero-based vertex */
        int parity = current_state % 2;

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].weight;
            int next_parity = parity ^ w;
            int next_state = state_id(v + 1, next_parity);
            long long candidate = dist[current_state] + w;

            if (candidate < dist[next_state]) {
                dist[next_state] = candidate;
                int pushed = (w == 0)
                    ? deque_push_front(&dq, next_state)
                    : deque_push_back(&dq, next_state);
                if (!pushed) {
                    fprintf(stderr, "Error: deque allocation failed.\n");
                    free(dq.items); free(head); free(edges); free(dist);
                    return EXIT_FAILURE;
                }
            }
        }
    }

    printf("Minimum effective costs from source %d (penalty C = %lld):\n",
           source, penalty);
    for (int v = 1; v <= n; ++v) {
        long long even_cost = dist[state_id(v, 0)];
        long long odd_base = dist[state_id(v, 1)];
        long long odd_cost = (odd_base == INF || odd_base > INF - penalty)
                             ? INF : odd_base + penalty;
        long long answer = even_cost < odd_cost ? even_cost : odd_cost;

        if (answer == INF) {
            printf("Vertex %d: UNREACHABLE\n", v);
        } else {
            printf("Vertex %d: %lld\n", v, answer);
        }
    }

    free(dq.items);
    free(head);
    free(edges);
    free(dist);
    return EXIT_SUCCESS;
}
