#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stddef.h>

void merge_sort(int *arr, size_t n);
void merge_sort_3way(int *arr, size_t n);
int is_sorted(const int *arr, size_t n);

#endif
