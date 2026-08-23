# Application of Sorting-III - K-Sum Problem

## Lab Assignment

Given a set `S` of `n` integers and an integer `T`, determine whether `k` integers from `S` add up to `T`.

The required time complexity is:

**O(n^(k-1) log n)**

## Approach

This solution uses **sorting + recursion + binary search**.

1. Sort the array `S`.
2. Recursively select `k - 1` elements.
3. After selecting `k - 1` elements, calculate the remaining value needed:
   `remaining = T - current_sum`
4. Use binary search on the remaining part of the sorted array to check whether that value exists.
5. If it exists, the required `k` integers have been found.
6. If no combination works, report that no solution exists.

The array is searched from `start` onward, so the same array position is never selected twice.

## Complexity

The program selects up to `k - 1` elements recursively.

There are approximately `O(n^(k-1))` combinations to check, and each final search uses binary search in `O(log n)`.

Therefore:

**O(n^(k-1) log n)**

Sorting takes `O(n log n)`, which is smaller than the main bound for the intended `k >= 2`.

## Input Format

```text
n
S elements
k
T
```

Example:

```text
6
2 4 7 9 11 15
3
22
```

## Example Output

```text
Found: 2 + 9 + 11 = 22
```

If no such combination exists:

```text
No solution found.
```

## Project Structure

```text
k_sum_sorting_lab/
├── docs/
│   ├── algorithm.md
│   └── comparison.md
├── src/
│   └── sorting.c
├── tests/
│   └── test_cases.txt
├── .gitignore
└── README.md
```

## Compile on Windows

From the project folder:

```cmd
gcc src\sorting.c -o sorting.exe
```

Run:

```cmd
sorting.exe
```

## Compile on Linux/macOS

```bash
gcc src/sorting.c -o sorting
./sorting
```

## Note

For a normal lab input, use:

```text
2 <= k <= n
```

The program also checks invalid values of `k` and `n`.

## Author

Lab Assignment - Application of Sorting-III
