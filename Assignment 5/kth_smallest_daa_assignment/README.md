# DAA Assignment: K-th Smallest Element Without Sorting

## Problem Statement

Find the **K-th smallest element** in a given list of **N numbers without sorting the list**. Analyze the time and space complexity of the algorithm.

## Approach

This solution uses the **Quickselect** algorithm.

Quickselect is based on the partitioning idea of Quicksort, but it does not recursively process both sides of the pivot. After partitioning:

- If the pivot is at position `k`, that pivot is the answer.
- If `k` is smaller, only the left part is searched.
- If `k` is larger, only the right part is searched.

Therefore, the complete list is not sorted.

The program uses the middle element as the pivot before partitioning. The algorithm is implemented iteratively to keep the code simple.

## Complexity

Let `N` be the number of elements.

- **Average time:** `O(N)`
- **Worst-case time:** `O(N^2)`
- **Auxiliary space:** `O(1)` apart from the input array
- **Input array storage:** `O(N)`

The worst case occurs when the selected pivot produces very unbalanced partitions repeatedly.

## Correctness Idea

After partitioning, every element to the left of the pivot is less than or equal to the pivot, and every element to the right is greater than the pivot. Therefore, if the pivot has the required rank, it is the K-th smallest element. Otherwise, only the side containing the K-th position needs to be processed.

## Folder Structure

```text
kth_smallest_daa_assignment/
├── README.md
├── COMPARISON.md
├── Makefile
├── .gitignore
├── src/
│   ├── kth_smallest_quickselect.c
│   └── kth_smallest_sorting.c
├── docs/
│   └── complexity_analysis.md
├── tests/
│   └── sample_input.txt
└── results/
    └── sample_output.txt
```

## How to Compile and Run

### Quickselect solution

On Linux/macOS:

```bash
gcc src/kth_smallest_quickselect.c -o kth_smallest_quickselect
./kth_smallest_quickselect
```

On Windows PowerShell with GCC/MinGW:

```powershell
gcc src/kth_smallest_quickselect.c -o kth_smallest_quickselect.exe
.\kth_smallest_quickselect.exe
```

### Comparison solution

```bash
gcc src/kth_smallest_sorting.c -o kth_smallest_sorting
./kth_smallest_sorting
```

Windows PowerShell:

```powershell
gcc src/kth_smallest_sorting.c -o kth_smallest_sorting.exe
.\kth_smallest_sorting.exe
```

## Sample Input

```text
Enter number of elements: 8
Enter the elements:
12 3 7 1 9 15 6 10
Enter k (1 for smallest): 4
```

## Sample Output

```text
The 4th smallest element is: 7
```

## Why Quickselect?

Sorting the complete list is not required when only one order statistic is needed. Quickselect focuses only on the portion of the array that can contain the K-th smallest element, giving an average linear running time.

## Notes for Submission

- The main answer to the assignment is `src/kth_smallest_quickselect.c`.
- `src/kth_smallest_sorting.c` is included only as a baseline for comparison.
- No graph is included because the assignment only asks for the algorithm and complexity analysis.
- The code accepts duplicate values and supports negative integers.
