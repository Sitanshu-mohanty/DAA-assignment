# Benchmark Methodology

The benchmark validates the predicted **order of growth** experimentally. Timings do not mathematically prove Big-O.

## Input sizes

`100, 500, 1,000, 5,000, 10,000, 50,000, 100,000`

## Timing

The C program uses `clock_gettime(CLOCK_MONOTONIC, ...)` and reports average nanoseconds per operation. Repetition counts are adjusted according to `n` so short operations get enough samples.

## Worst-case-oriented cases

- **Search:** absent key for structures requiring traversal.
- **Sorted-array insert:** smallest key, forcing maximum shifts.
- **Sorted-list insert:** largest key, forcing traversal to the tail.
- **Delete:** a target pointer is obtained before timing; sorted-array deletion removes the first item, while singly linked lists delete the tail so finding the predecessor is worst-case.
- **Min/max:** full scan when no endpoint is directly available.
- **Predecessor/successor:** an existing item pointer is supplied.

For mutating operations, restoration is performed outside the timed region.

## Interpreting the graphs

The graphs use logarithmic x and y axes because measured times span several orders of magnitude.

- Nearly horizontal → O(1)-like growth.
- Approximately proportional growth → O(n)-like growth.
- Much slower-than-linear search growth in the sorted array → consistent with O(log n).

Actual nanosecond values vary with CPU, compiler, operating system, cache effects and background load. The growth trend is the important result.
