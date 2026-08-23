# Sorting Application - Pair Sum

## Lab Assignment

Given two sets `S1` and `S2`, each of size `n`, and a number `x`, determine whether there exists a pair of elements, one from `S1` and one from `S2`, whose sum is `x`.

The required time complexity is **O(n log n)**.

## Approach

This program uses:

1. Sort `S1`.
2. Sort `S2`.
3. Use two pointers:
   - Start from the smallest element of `S1`.
   - Start from the largest element of `S2`.
4. Compare their sum with `x`.
5. Move the appropriate pointer until a pair is found or all possibilities are checked.

### Complexity

- Sorting `S1`: `O(n log n)`
- Sorting `S2`: `O(n log n)`
- Two-pointer search: `O(n)`

Overall:

**O(n log n)**

## Project Structure

```text
sorting_pair_sum_lab/
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

## Compile

Using GCC:

```bash
gcc src/sorting.c -o sorting
```

## Run

```bash
./sorting
```

On Windows:

```bash
sorting.exe
```

## Example

Input:

```text
Enter the size of both sets: 5
Enter 5 elements of S1: 1 4 7 10 15
Enter 5 elements of S2: 2 5 8 11 20
Enter x: 12
```

Output:

```text
Pair found: 4 + 8 = 12
```

## Author

Lab Assignment - Application of Sorting-II
