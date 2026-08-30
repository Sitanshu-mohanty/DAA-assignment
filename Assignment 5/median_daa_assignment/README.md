# DAA Assignment: Median Without Sorting

## Problem Statement

Find the median of a list of `N` numbers **without sorting the complete list** and analyze the complexity of the algorithm.

## Approach Used

This submission uses the **Quickselect** technique.

Quickselect is based on the same partition idea used in Quicksort, but it only continues on the part of the array that contains the required rank. Therefore, it does not completely sort the input.

For an array of size `N`:

- Odd `N`: select the element at rank `N/2`.
- Even `N`: select the elements at ranks `N/2 - 1` and `N/2`, then take their average.

## Complexity Analysis

### Quickselect solution

- Average time: **O(N)**
- Worst-case time: **O(N^2)** when partitions are highly unbalanced
- Auxiliary space: **O(1)** for the iterative selection itself
- Input storage: **O(N)**

The implementation modifies the input array while partitioning it. The complete list is never sorted.

### Comparison program

`src/median_sorting.c` is included only to compare the non-sorting approach with a simple sorting-based solution.

- Insertion sort worst-case time: **O(N^2)**
- Insertion sort auxiliary space: **O(1)**
- Median retrieval after sorting: **O(1)**

For general-purpose sorting algorithms such as Merge Sort or Heap Sort, sorting normally takes **O(N log N)** time, which is higher than Quickselect's expected **O(N)** time for this specific median-selection problem.

## Folder Structure

```text
median_daa_assignment/
├── README.md
├── Makefile
├── src/
│   ├── median_quickselect.c
│   └── median_sorting.c
├── docs/
│   └── complexity_analysis.md
├── tests/
│   └── sample_input.txt
└── results/
    └── sample_output.txt
```

## Compilation

Using GCC:

```bash
gcc -Wall -Wextra -std=c11 src/median_quickselect.c -o median_quickselect
gcc -Wall -Wextra -std=c11 src/median_sorting.c -o median_sorting
```

Or simply use:

```bash
make
```

## Running

```bash
./median_quickselect
```

On Windows with MinGW:

```powershell
.\median_quickselect.exe
```

## Sample Input

```text
Enter number of elements: 7
Enter 7 numbers:
12 4 7 3 9 15 6
```

## Sample Output

```text
Median = 7.00
```

## Important Note

Quickselect does not guarantee linear time for every input when a simple pivot strategy is used. The current implementation uses the last element as pivot, so its worst case is `O(N^2)`.

If a guaranteed linear-time solution is required, the **Median of Medians** selection algorithm can be used. For a standard DAA laboratory submission, Quickselect is a simple and commonly used solution for demonstrating selection without full sorting.
