#include "merge_arrays.h"

#include <stdlib.h>

void free_int_array(IntArray *array)
{
    if (array == NULL) {
        return;
    }

    free(array->data);
    array->data = NULL;
    array->size = 0;
}

IntArray merge_two_sorted_arrays(const IntArray *left, const IntArray *right)
{
    IntArray result = {NULL, 0};
    size_t left_index = 0;
    size_t right_index = 0;
    size_t result_index = 0;

    if (left == NULL || right == NULL) {
        return result;
    }

    result.size = left->size + right->size;

    if (result.size > 0) {
        result.data = malloc(result.size * sizeof(*result.data));
        if (result.data == NULL) {
            result.size = 0;
            return result;
        }
    }

    while (left_index < left->size && right_index < right->size) {
        if (left->data[left_index] <= right->data[right_index]) {
            result.data[result_index++] = left->data[left_index++];
        } else {
            result.data[result_index++] = right->data[right_index++];
        }
    }

    while (left_index < left->size) {
        result.data[result_index++] = left->data[left_index++];
    }

    while (right_index < right->size) {
        result.data[result_index++] = right->data[right_index++];
    }

    return result;
}

IntArray merge_sequential(const IntArray *arrays, size_t count)
{
    IntArray result = {NULL, 0};

    if (arrays == NULL || count == 0) {
        return result;
    }

    if (count == 1) {
        result.size = arrays[0].size;

        if (result.size == 0) {
            return result;
        }

        result.data = malloc(result.size * sizeof(*result.data));
        if (result.data == NULL) {
            result.size = 0;
            return result;
        }

        for (size_t i = 0; i < result.size; ++i) {
            result.data[i] = arrays[0].data[i];
        }

        return result;
    }

    result = merge_two_sorted_arrays(&arrays[0], &arrays[1]);

    if (result.size > 0 && result.data == NULL) {
        return result;
    }

    for (size_t i = 2; i < count; ++i) {
        IntArray next = merge_two_sorted_arrays(&result, &arrays[i]);
        free_int_array(&result);

        if (next.size > 0 && next.data == NULL) {
            return next;
        }

        result = next;
    }

    return result;
}

IntArray merge_pairwise(const IntArray *arrays, size_t count)
{
    IntArray result = {NULL, 0};

    if (arrays == NULL || count == 0) {
        return result;
    }

    /*
     * Make an owned copy of every input array. This lets every round
     * safely release its previous level.
     */
    IntArray *current = calloc(count, sizeof(*current));

    if (current == NULL) {
        return result;
    }

    for (size_t i = 0; i < count; ++i) {
        current[i].size = arrays[i].size;

        if (current[i].size == 0) {
            continue;
        }

        current[i].data = malloc(current[i].size * sizeof(*current[i].data));

        if (current[i].data == NULL) {
            for (size_t j = 0; j <= i; ++j) {
                free_int_array(&current[j]);
            }
            free(current);
            return result;
        }

        for (size_t j = 0; j < current[i].size; ++j) {
            current[i].data[j] = arrays[i].data[j];
        }
    }

    size_t current_count = count;

    while (current_count > 1) {
        size_t next_count = (current_count + 1) / 2;
        IntArray *next = calloc(next_count, sizeof(*next));

        if (next == NULL) {
            for (size_t i = 0; i < current_count; ++i) {
                free_int_array(&current[i]);
            }
            free(current);
            return result;
        }

        size_t next_index = 0;

        for (size_t i = 0; i < current_count; i += 2) {
            if (i + 1 < current_count) {
                next[next_index] =
                    merge_two_sorted_arrays(&current[i], &current[i + 1]);
            } else {
                /*
                 * For an odd number of arrays, carry the last array
                 * into the next round without copying it.
                 */
                next[next_index] = current[i];
                current[i].data = NULL;
                current[i].size = 0;
            }

            if (next[next_index].size > 0 &&
                next[next_index].data == NULL) {
                for (size_t j = 0; j < next_count; ++j) {
                    free_int_array(&next[j]);
                }

                free(next);

                for (size_t j = 0; j < current_count; ++j) {
                    free_int_array(&current[j]);
                }

                free(current);
                return result;
            }

            ++next_index;
        }

        for (size_t i = 0; i < current_count; ++i) {
            free_int_array(&current[i]);
        }

        free(current);
        current = next;
        current_count = next_count;
    }

    result = current[0];
    free(current);

    return result;
}

int is_sorted(const IntArray *array)
{
    if (array == NULL) {
        return 0;
    }

    for (size_t i = 1; i < array->size; ++i) {
        if (array->data[i - 1] > array->data[i]) {
            return 0;
        }
    }

    return 1;
}

int arrays_equal(const IntArray *left, const IntArray *right)
{
    if (left == NULL || right == NULL || left->size != right->size) {
        return 0;
    }

    for (size_t i = 0; i < left->size; ++i) {
        if (left->data[i] != right->data[i]) {
            return 0;
        }
    }

    return 1;
}
