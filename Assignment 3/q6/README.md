# Use of Loop Invariants in Sorting — DAA Lab Assignment

## Aim

To implement the selection-sort algorithm and use a **loop invariant** to prove that the algorithm is correct.

## Algorithm

The algorithm repeatedly finds the smallest element in the unsorted part of the array and places it at the beginning of that part.

For example:

```text
[ 5  2  8  1  6 ]

After first iteration:
[ 1  2  8  5  6 ]

After second iteration:
[ 1  2  8  5  6 ]

After third iteration:
[ 1  2  5  8  6 ]

After fourth iteration:
[ 1  2  5  6  8 ]
```

## Loop Invariant

At the beginning of iteration `i`:

> The first `i` elements are sorted and contain the `i` smallest elements of the array.

### Initialization

Before the first iteration, no elements are fixed, so the invariant is true.

### Maintenance

The algorithm finds the smallest element in the unsorted portion `A[i...n]` and exchanges it with `A[i]`.

Therefore one more smallest element is placed in its correct position, so the invariant remains true.

### Termination

After `n - 1` iterations, the first `n - 1` elements are in their correct positions.

The remaining element must also be correctly placed.

Therefore the entire array is sorted.

## Why n - 1 iterations?

There is no need to process the last element.

Once the smallest `n - 1` elements have been placed correctly, only one element remains. It must be the largest element and is automatically in its correct position.

## Complexity

The inner loop compares:

```text
n - 1
n - 2
n - 3
...
1
```

elements.

Therefore total comparisons are:

```text
(n - 1) + (n - 2) + ... + 1
```

which is:

```text
n(n - 1) / 2
```

Hence:

```text
Worst-case time = Theta(n^2)
Best-case time  = Theta(n^2)
```

The best case is **not asymptotically better**, because selection sort still searches the entire remaining portion even when the array is already sorted.

## Files

```text
loop-invariants-sorting-lab/
│
├── src/
│   ├── main.c
│   └── benchmark.c
│
├── docs/
│   └── pseudocode.md
│
├── results/
│   └── comparisons.csv
│
├── README.md
└── .gitignore
```

No graph is included.

## Run the Main Program

### Windows

```powershell
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o sort.exe
.\sort.exe
```

### Linux / macOS

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o sort
./sort
```

### Example

```text
========== SORTING USING LOOP INVARIANT ==========

Enter number of elements: 6
Enter 6 elements:
5 2 8 1 6 3

Sorted array:
1 2 3 5 6 8

Number of comparisons: 15
Worst-case time: Theta(n^2)
Best-case time: Theta(n^2)
```

## Run the Benchmark

### Windows

```powershell
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/benchmark.c -o benchmark.exe
.\benchmark.exe
```

### Linux / macOS

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/benchmark.c -o benchmark
./benchmark
```

The program creates:

```text
results/comparisons.csv
```

The theoretical comparison count is:

```text
n(n - 1) / 2
```

The benchmark validates that the implementation performs exactly that many comparisons.

## Conclusion

The selection-sort algorithm is correct because its loop invariant is maintained through every iteration and, at termination, implies that the complete array is sorted.

The algorithm performs:

```text
n(n - 1)/2
```

comparisons in the best and worst cases, so both are:

```text
Theta(n^2)
```
