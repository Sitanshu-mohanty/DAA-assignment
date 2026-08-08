#ifndef MERGE_ARRAYS_H
#define MERGE_ARRAYS_H

#include <stddef.h>

typedef struct {
    int *data;
    size_t size;
} IntArray;

/* Releases the dynamically allocated data inside an IntArray. */
void free_int_array(IntArray *array);

/* Merges two sorted arrays into a newly allocated sorted array. */
IntArray merge_two_sorted_arrays(const IntArray *left, const IntArray *right);

/* Method 1: merges arrays one at a time. */
IntArray merge_sequential(const IntArray *arrays, size_t count);

/* Method 2: repeatedly merges arrays in pairs. */
IntArray merge_pairwise(const IntArray *arrays, size_t count);

/* Checks whether an array is sorted in nondecreasing order. */
int is_sorted(const IntArray *array);

/* Checks whether two arrays contain exactly the same sequence of values. */
int arrays_equal(const IntArray *left, const IntArray *right);

#endif
