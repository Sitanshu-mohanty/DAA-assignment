#include "merge_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int test_case(const int *input, size_t n)
{
    int *a = malloc(n * sizeof(*a));
    int *b = malloc(n * sizeof(*b));

    if ((n > 0) && (a == NULL || b == NULL)) {
        free(a);
        free(b);
        return 0;
    }

    if (n > 0) {
        memcpy(a, input, n * sizeof(*a));
        memcpy(b, input, n * sizeof(*b));
    }

    merge_sort(a, n);
    merge_sort_3way(b, n);

    int ok = is_sorted(a, n) &&
             is_sorted(b, n) &&
             (n == 0 || memcmp(a, b, n * sizeof(*a)) == 0);

    free(a);
    free(b);
    return ok;
}

int main(void)
{
    const int cases[][12] = {
        {0},
        {42},
        {2, 1},
        {3, 2, 1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {4, 1, 4, 2, 4, 3},
        {9, 1, 8, 2, 7, 3, 6, 4, 5},
        {10, -1, 5, 0, -4, 8, 8, 2, 7, 3, 6, 1}
    };

    const size_t lengths[] = {0, 1, 2, 3, 5, 5, 6, 9, 11};
    const size_t count = sizeof(lengths) / sizeof(lengths[0]);

    for (size_t i = 0; i < count; ++i) {
        if (!test_case(cases[i], lengths[i])) {
            fprintf(stderr, "FAILED test case %zu\n", i + 1);
            return EXIT_FAILURE;
        }
    }

    /* Non-power-of-two and larger random case. */
    int random_data[1003];
    unsigned int state = 12345U;

    for (size_t i = 0; i < 1003; ++i) {
        state = 1664525U * state + 1013904223U;
        random_data[i] = (int)(state % 10000U);
    }

    if (!test_case(random_data, 1003)) {
        fprintf(stderr, "FAILED random test\n");
        return EXIT_FAILURE;
    }

    printf("All Merge Sort tests passed.\n");
    return EXIT_SUCCESS;
}
