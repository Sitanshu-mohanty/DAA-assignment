#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;

void print_intervals(const Interval intervals[], int count) {
    printf("[");

    for (int i = 0; i < count; i++) {
        printf("(%d, %d)", intervals[i].start, intervals[i].end);
        if (i < count - 1) {
            printf(", ");
        }
    }

    printf("]\n");
}

int compare_intervals(const void *a, const void *b) {
    const Interval *first = (const Interval *)a;
    const Interval *second = (const Interval *)b;

    if (first->start < second->start) {
        return -1;
    }
    if (first->start > second->start) {
        return 1;
    }

    if (first->end < second->end) {
        return -1;
    }
    if (first->end > second->end) {
        return 1;
    }

    return 0;
}

int merge_intervals(Interval intervals[], int n) {
    if (n <= 0) {
        return 0;
    }

    qsort(intervals, n, sizeof(Interval), compare_intervals);

    int count = 1;

    for (int i = 1; i < n; i++) {
        if (intervals[i].start <= intervals[count - 1].end) {
            if (intervals[i].end > intervals[count - 1].end) {
                intervals[count - 1].end = intervals[i].end;
            }
        } else {
            intervals[count] = intervals[i];
            count++;
        }
    }

    return count;
}

int main(void) {
    int n;

    printf("Enter number of intervals: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid number of intervals.\n");
        return 1;
    }

    Interval *intervals = malloc((size_t)n * sizeof(Interval));
    if (intervals == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d intervals as start end:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d %d", &intervals[i].start, &intervals[i].end) != 2) {
            printf("Invalid interval input.\n");
            free(intervals);
            return 1;
        }

        if (intervals[i].start > intervals[i].end) {
            printf("Invalid interval: start cannot be greater than end.\n");
            free(intervals);
            return 1;
        }
    }

    printf("\nOriginal intervals: ");
    print_intervals(intervals, n);

    int merged_count = merge_intervals(intervals, n);

    printf("Merged intervals:   ");
    print_intervals(intervals, merged_count);

    free(intervals);
    return 0;
}
