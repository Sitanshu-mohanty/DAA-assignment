# DAA Assignment 3 - Quick Sort with File Storage

## Problem Statement
Implement Quick Sort for N random elements and store the elements in a file.

## Objective
- Generate N random integers.
- Store the generated elements in an input file.
- Sort the elements using Quick Sort.
- Store the sorted elements in an output file.
- Analyze the time and space complexity of Quick Sort.

## Algorithm
1. Read the value of N.
2. Generate N random integers.
3. Store the unsorted integers in `data/input.txt`.
4. Apply Quick Sort using the last element as the pivot.
5. Store the sorted integers in `data/output.txt`.
6. Display a short confirmation message.

## Complexity Analysis
| Case | Time Complexity |
|---|---|
| Best Case | O(N log N) |
| Average Case | O(N log N) |
| Worst Case | O(N^2) |

The recursive Quick Sort implementation uses O(log N) average recursion stack space and O(N) worst-case recursion stack space.

## Compile

```bash
gcc -Wall -Wextra -std=c11 src/quicksort_file.c -o quicksort_file
```

## Run

### Windows PowerShell
```powershell
.\quicksort_file.exe
```

Enter the number of random elements when prompted.

## Files
- `src/quicksort_file.c` - main Quick Sort implementation
- `docs/complexity_analysis.md` - detailed complexity analysis
- `tests/test_cases.md` - suggested test cases
- `results/` - place your own generated output/screenshots here
- `data/` - created automatically by the program

## Note
The program creates `data/input.txt` and `data/output.txt` automatically. These files contain results generated on your own device, so they can be committed after you run the program if your lab requires output files.
