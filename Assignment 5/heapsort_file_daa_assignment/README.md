# DAA Assignment 4 - Heap Sort with File Storage

## Problem Statement
Implement Heap Sort to sort N randomly generated elements stored in a file. Perform the complexity analysis of the algorithm.

## Objective
- Generate N random integers.
- Store the generated elements in an input file.
- Read the elements from the file.
- Sort them using Heap Sort.
- Store the sorted elements in an output file.
- Analyze the time and space complexity.

## Algorithm
1. Read N from the user.
2. Generate N random integers.
3. Store the random integers in `data/input.txt`.
4. Read the elements from the input file.
5. Build a max heap.
6. Repeatedly move the largest element to the end of the array and restore the heap.
7. Store the sorted array in `data/output.txt`.

## Complexity Analysis

| Operation / Case | Time Complexity |
|---|---:|
| Build Max Heap | O(N) |
| Heapify | O(log N) |
| Best Case | O(N log N) |
| Average Case | O(N log N) |
| Worst Case | O(N log N) |

Auxiliary space is **O(1)** for the sorting operation because Heap Sort works in-place. The implementation uses no additional array proportional to N.

## Compile

```bash
gcc -Wall -Wextra -std=c11 src/heapsort_file.c -o heapsort_file
```

## Run

### Windows PowerShell
```powershell
.\heapsort_file.exe
```

Enter the number of random elements when prompted.

The program creates:
- `data/input.txt` - randomly generated unsorted elements
- `data/output.txt` - sorted elements

These files are generated on your own device and are not included as pre-generated results.

## Project Structure

```text
heapsort_file_daa_assignment/
├── README.md
├── COMPARISON.md
├── Makefile
├── .gitignore
├── src/
│   └── heapsort_file.c
├── docs/
│   └── complexity_analysis.md
├── tests/
│   └── test_cases.md
└── results/
    └── README.md
```
