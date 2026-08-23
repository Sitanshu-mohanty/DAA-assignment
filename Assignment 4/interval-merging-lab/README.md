# Application of Sorting-V: Merge Overlapping Intervals

## Lab Assignment

Given a list of `n` intervals represented as `(start, end)` pairs, merge all overlapping intervals and return the resulting list.

### Example

Input intervals:

```text
(1, 3), (2, 6), (8, 10), (7, 18)
```

Output:

```text
(1, 6), (7, 18)
```

## Approach

The solution uses sorting first, which gives a worst-case time complexity of `O(n log n)`.

1. Store each interval using a simple C `struct` with `start` and `end` fields.
2. Sort all intervals by their starting value using `qsort()`.
3. Scan the sorted intervals from left to right.
4. If the current interval overlaps the last merged interval, extend the last merged interval when necessary.
5. Otherwise, store the current interval as a new merged interval.

The merge is done in the same array, so no separate output array is required.

## Files

```text
interval-merging-lab/
├── src/
│   └── merge_intervals.c
├── tests/
│   └── sample_input.txt
├── Makefile
├── README.md
├── analysis.md
└── .gitignore
```

## Requirements

- GCC or another C compiler with C99 support
- `make` (optional, but recommended)

## Compile and Run
```bash
gcc -std=c99 -Wall -Wextra -pedantic src/merge_intervals.c -o merge_intervals
./merge_intervals
```

## Sample Run

```text
Enter number of intervals: 4
Enter 4 intervals as start end:
1 3
2 6
8 10
7 18

Original intervals: [(1, 3), (2, 6), (8, 10), (7, 18)]
Merged intervals:   [(1, 6), (7, 18)]
```

## Complexity

| Operation | Complexity |
|---|---|
| Sorting | `O(n log n)` worst case |
| Merging scan | `O(n)` |
| Total | `O(n log n)` |
| Extra space | `O(log n)` auxiliary stack space for `qsort` in typical implementations; the interval storage itself is `O(n)` |

The required worst-case running time is therefore satisfied.

## Notes for Lab Submission

- The interval representation is a `struct`, which makes the code easier to read than storing separate arrays for starts and ends.
- The input array is also used as the output storage after sorting, which keeps the implementation simple.
- The code treats intervals that touch at an endpoint as overlapping. For example, `(1, 3)` and `(3, 5)` are merged into `(1, 5)` because the condition used is `current.start <= last.end`.
