# Quick Sort Complexity Analysis

## Partition
Partition scans the current subarray once.

Time:
**O(N)** for a partition of N elements.

## Quick Sort

### Best Case
The pivot divides the array into two nearly equal parts.

T(N) = 2T(N/2) + O(N)

Therefore:

**O(N log N)**

### Average Case
For reasonably balanced random input, the expected running time is:

**O(N log N)**

### Worst Case
If the pivot is always the smallest or largest element:

T(N) = T(N-1) + O(N)

Therefore:

**O(N^2)**

## Space Complexity
The sorting is performed in-place.

- Average recursion stack: **O(log N)**
- Worst-case recursion stack: **O(N)**
- Extra array storage: **O(1)**

## File Complexity
Writing N generated values to the input file takes O(N) time. Reading/writing the N values also takes O(N) time.
