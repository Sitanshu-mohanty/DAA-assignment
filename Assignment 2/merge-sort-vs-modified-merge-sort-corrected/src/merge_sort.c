#include "merge_sort.h"

#include <stdlib.h>
#include <string.h>

/* ---------- Standard two-way Merge Sort ---------- */

static void merge_two(int *arr, int *tmp, size_t left, size_t mid, size_t right)
{
    size_t i = left;
    size_t j = mid;
    size_t k = left;

    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
        }
    }

    while (i < mid) {
        tmp[k++] = arr[i++];
    }

    while (j < right) {
        tmp[k++] = arr[j++];
    }

    memcpy(arr + left, tmp + left, (right - left) * sizeof(*arr));
}

static void merge_sort_recursive(int *arr, int *tmp, size_t left, size_t right)
{
    if (right - left <= 1) {
        return;
    }

    size_t mid = left + (right - left) / 2;

    merge_sort_recursive(arr, tmp, left, mid);
    merge_sort_recursive(arr, tmp, mid, right);
    merge_two(arr, tmp, left, mid, right);
}

void merge_sort(int *arr, size_t n)
{
    if (n <= 1) {
        return;
    }

    int *tmp = malloc(n * sizeof(*tmp));
    if (tmp == NULL) {
        return;
    }

    merge_sort_recursive(arr, tmp, 0, n);
    free(tmp);
}

/* ---------- Modified three-way Merge Sort ---------- */

static void merge_three(
    int *arr, int *tmp,
    size_t left, size_t mid1, size_t mid2, size_t right)
{
    size_t i = left;
    size_t j = mid1;
    size_t k = mid2;
    size_t out = left;

    while (i < mid1 || j < mid2 || k < right) {
        if (i < mid1 &&
            (j >= mid2 || arr[i] <= arr[j]) &&
            (k >= right || arr[i] <= arr[k])) {
            tmp[out++] = arr[i++];
        } else if (j < mid2 &&
                   (k >= right || arr[j] <= arr[k])) {
            tmp[out++] = arr[j++];
        } else {
            tmp[out++] = arr[k++];
        }
    }

    memcpy(arr + left, tmp + left, (right - left) * sizeof(*arr));
}

static void merge_sort_3way_recursive(
    int *arr, int *tmp, size_t left, size_t right)
{
    size_t length;
    size_t third;
    size_t remainder;
    size_t first;
    size_t second;
    size_t mid1;
    size_t mid2;

    if (right - left <= 1) {
        return;
    }

    length = right - left;

    /* A two-element range is the only case where a 3rd part is empty. */
    if (length == 2) {
        merge_two(arr, tmp, left, left + 1, right);
        return;
    }

    third = length / 3;
    remainder = length % 3;

    /*
     * Split sizes differ by at most one:
     * n = first + second + third.
     */
    first = third + (remainder > 0 ? 1 : 0);
    second = third + (remainder > 1 ? 1 : 0);

    mid1 = left + first;
    mid2 = mid1 + second;

    merge_sort_3way_recursive(arr, tmp, left, mid1);
    merge_sort_3way_recursive(arr, tmp, mid1, mid2);
    merge_sort_3way_recursive(arr, tmp, mid2, right);

    merge_three(arr, tmp, left, mid1, mid2, right);
}

void merge_sort_3way(int *arr, size_t n)
{
    if (n <= 1) {
        return;
    }

    int *tmp = malloc(n * sizeof(*tmp));
    if (tmp == NULL) {
        return;
    }

    merge_sort_3way_recursive(arr, tmp, 0, n);
    free(tmp);
}

int is_sorted(const int *arr, size_t n)
{
    for (size_t i = 1; i < n; ++i) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }

    return 1;
}
