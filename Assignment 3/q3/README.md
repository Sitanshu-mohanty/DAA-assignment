# Max and Min Using Divide and Conquer — DAA Lab Assignment

## Aim

To find the maximum and minimum elements in an array using the **divide and conquer** approach, while keeping the number of comparisons within the required bound:

```text
3n/2
```

## Basic Idea

The array is divided into two smaller parts.

For each part, recursively find:

- minimum
- maximum

Then combine the two results using only two comparisons:

```text
minimum = smaller of the two minimums
maximum = larger of the two maximums
```

For two elements, only **one comparison** is needed.

Therefore, for an array of `n` elements, the total number of comparisons is bounded by:

```text
3n/2
```

## Files

```text
max-min-divide-conquer-lab/
│
├── src/
│   ├── main.c
│   └── benchmark.c
│
├── results/
│   └── comparisons.csv
│
├── README.md
└── .gitignore
```

There is **no graph**, as requested.

## Run the Main Program

### Windows

```powershell
gcc src/main.c -o maxmin.exe
.\maxmin.exe
```

### Linux / macOS

```bash
gcc src/main.c -o maxmin
./maxmin
```

### Example

```text
========== MAX AND MIN USING DIVIDE AND CONQUER ==========

Enter number of elements: 6
Enter 6 elements:
12 5 8 2 19 7

========== RESULT ==========
Minimum element: 2
Maximum element: 19
Number of comparisons: 8

Theoretical upper bound: 3n/2 = 9.0
The number of comparisons is within the required bound.

Time Complexity: O(n)
Extra Space Complexity: O(log n) due to recursion.
```

## Run the Benchmark

### Windows

```powershell
gcc src/benchmark.c -o benchmark.exe
.\benchmark.exe
```

### Linux / macOS

```bash
gcc src/benchmark.c -o benchmark
./benchmark
```

The benchmark creates:

```text
results/comparisons.csv
```

The CSV contains:

```text
n,actual,theoretical_bound
```

The benchmark is used only to validate the comparison bound experimentally.

## Comparison Analysis

The divide and conquer recurrence is:

```text
T(n) = 2T(n/2) + 2
```

For two elements:

```text
T(2) = 1
```

For even `n`, this gives:

```text
T(n) = 3n/2 - 2
```

which is clearly less than:

```text
3n/2
```

For odd `n`, the same divide-and-conquer idea also stays within the required `3n/2` bound.

Thus the algorithm satisfies the assignment requirement.

## Complexity

### Time Complexity

```text
O(n)
```

because every element is considered and the total number of comparisons grows linearly.

### Extra Space Complexity

```text
O(log n)
```

because the recursive calls form a logarithmic-depth recursion tree.

## Conclusion

The divide-and-conquer method successfully finds both the minimum and maximum elements while using no more than `3n/2` comparisons. The benchmark confirms that the actual number of comparisons remains below the required theoretical upper bound.
