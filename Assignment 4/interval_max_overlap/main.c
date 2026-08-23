#include <stdio.h>
#include <stdlib.h>

/*
 * Application of Sorting - VI
 * Find a point that belongs to the maximum number of intervals.
 *
 * Idea:
 * Each interval (l, r) produces two events:
 *   +1 at l  -> an interval starts
 *   -1 just after r -> an interval ends
 *
 * Since endpoints are included, a point r still belongs to its interval.
 * We therefore process a START event before an END event when they have
 * the same coordinate.
 */

typedef struct {
    int value;
    int type;   /* 0 = start, 1 = end */
} Event;

/* Start comes before end at the same point. */
int compareEvents(const void *a, const void *b) {
    const Event *x = (const Event *)a;
    const Event *y = (const Event *)b;

    if (x->value < y->value)
        return -1;
    if (x->value > y->value)
        return 1;

    return x->type - y->type;
}

void findBestPoint(int left[], int right[], int n, int *bestPoint, int *maxCount) {
    Event *events;
    int i;
    int count = 0;

    events = (Event *)malloc(2 * n * sizeof(Event));
    if (events == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++) {
        events[2 * i].value = left[i];
        events[2 * i].type = 0;            /* start */

        events[2 * i + 1].value = right[i];
        events[2 * i + 1].type = 1;        /* end */
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    *maxCount = 0;
    *bestPoint = events[0].value;

    for (i = 0; i < 2 * n; i++) {
        if (events[i].type == 0) {
            count++;
            if (count >= *maxCount) {
                *maxCount = count;
                *bestPoint = events[i].value;
            }
        } else {
            count--;
        }
    }

    free(events);
}

int main(void) {
    int n;
    int *left;
    int *right;
    int bestPoint;
    int maxCount;
    int i;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of intervals must be positive.\n");
        return 1;
    }

    left = (int *)malloc(n * sizeof(int));
    right = (int *)malloc(n * sizeof(int));

    if (left == NULL || right == NULL) {
        printf("Memory allocation failed.\n");
        free(left);
        free(right);
        return 1;
    }

    printf("Enter the intervals (left right):\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &left[i], &right[i]);

        if (left[i] > right[i]) {
            printf("Invalid interval at position %d. Left endpoint cannot be greater than right endpoint.\n", i + 1);
            free(left);
            free(right);
            return 1;
        }
    }

    findBestPoint(left, right, n, &bestPoint, &maxCount);

    printf("\nPoint with maximum overlap: %d\n", bestPoint);
    printf("Maximum number of intervals: %d\n", maxCount);

    free(left);
    free(right);

    return 0;
}
