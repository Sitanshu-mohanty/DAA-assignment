# Merge Sort vs. Modified 3-Way Merge Sort

A reproducible, GitHub-ready solution to the assignment:

> Divide the input array into thirds rather than halves, recursively
> sort each third, and finally combine the results using a three-way
> merge subroutine. What is the worst-case running time? Write a C
> program to validate the claim by plotting the order of growth for
> standard Merge Sort and the modified Merge Sort.

## Main Result

Both algorithms have the same asymptotic worst-case complexity:

  -----------------------------------------------------------------------------------
  Algorithm       Recurrence                     Recursion Depth           Worst-Case
  --------------- ------------------------- -------------------- --------------------
  Standard Merge  `T(n) = 2T(n/2) + Θ(n)`               `log₂ n`       **Θ(n log n)**
  Sort                                                           

  3-Way Merge     `T(n) = 3T(n/3) + Θ(n)`               `log₃ n`       **Θ(n log n)**
  Sort                                                           
  -----------------------------------------------------------------------------------

The logarithm bases are genuinely different. They are still in the same
Big-Theta class because:

``` text
log₃(n) = log₂(n) / log₂(3)
```

and `1 / log₂(3)` is a constant.

Therefore:

``` text
Θ(n log₂ n) = Θ(n log₃ n) = Θ(n log n)
```

## Important Point About the Logarithm Bases

The two algorithms do **not** have identical exact growth expressions.

Standard Merge Sort has:

``` text
T₂(n) = Θ(n log₂ n)
```

while the 3-Way version has:

``` text
T₃(n) = Θ(n log₃ n)
```

Since:

``` text
log₃(n) = log₂(n) / log₂(3)
```

we obtain:

``` text
n log₃(n)
= [1 / log₂(3)] n log₂(n)
```

The factor `1 / log₂(3) ≈ 0.63093` is a constant.

Big-Theta notation ignores constant multiplicative factors. Therefore
both algorithms belong to:

``` text
Θ(n log n)
```

even though their logarithm bases and recursion depths are different.

## Repository Structure

``` text
merge-sort-vs-modified-merge-sort/
├── README.md
├── .gitignore
│
├── include/
│   └── merge_sort.h
│
├── src/
│   ├── merge_sort.c
│   └── benchmark.c
│
├── tests/
│   └── test_merge_sort.c
│
├── scripts/
│   └── plot_results.py
│
├── data/
│   └── benchmark_results.csv
│
├── graphs/
│   ├── runtime_comparison.png
│   ├── normalized_own_base.png
│   ├── normalized_common_base.png
│   └── theoretical_recursion_depth.png
│
└── docs/
    ├── analysis.md
    └── experimental_results.md
```

The `build/` directory is used locally for compiled Windows executables
and does not need to be committed to GitHub.

# Requirements

The experiment was reproduced on Windows using:

-   GCC
-   Python 3
-   Matplotlib

No GNU Make is required.

# Windows Reproducibility Procedure

The complete experiment can be reproduced using:

``` text
GCC
 ↓
Compile
 ↓
Correctness Tests
 ↓
Benchmark
 ↓
CSV
 ↓
Python
 ↓
Graphs
```

## 1. Create the Build Directory

From the repository root, open PowerShell and run:

``` powershell
New-Item -ItemType Directory -Force build
```

## 2. Compile the Benchmark Program

``` powershell
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src\merge_sort.c src\benchmark.c -o build\benchmark.exe
```

This creates:

``` text
build\benchmark.exe
```

## 3. Compile the Correctness Tests

``` powershell
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src\merge_sort.c tests\test_merge_sort.c -o build\test_merge_sort.exe
```

This creates:

``` text
build\test_merge_sort.exe
```

## 4. Run the Correctness Tests

``` powershell
.\build\test_merge_sort.exe
```

The tests should produce:

``` text
All Merge Sort tests passed.
```

The test suite checks multiple types of input, including:

-   Empty arrays
-   One-element arrays
-   Already-sorted arrays
-   Reverse-sorted arrays
-   Arrays containing duplicates
-   Random data
-   Non-power-of-two input sizes

## 5. Run the Benchmark

``` powershell
.\build\benchmark.exe
```

The benchmark compares Standard two-way Merge Sort and Modified
three-way Merge Sort.

The benchmark uses the same input data for both algorithms and performs
multiple repetitions to reduce the effect of timing noise.

The resulting benchmark data is written to:

``` text
data\benchmark_results.csv
```

## 6. Generate the Graphs

``` powershell
python scripts\plot_results.py
```

The generated graphs are saved in:

``` text
graphs\
```

The experiment can therefore be reproduced using GCC and Python without
requiring GNU Make.

# Experimental Graphs

The repository contains four graphs.

### 1. Runtime Comparison

``` text
graphs/runtime_comparison.png
```

This graph compares the measured execution time of Standard Merge Sort
and 3-Way Merge Sort against the input size `n`.

### 2. Own-Base Normalization

``` text
graphs/normalized_own_base.png
```

This graph uses the logarithm base corresponding to each algorithm's
recurrence:

``` text
Standard Merge Sort:
T(n) / [n log₂(n)]

3-Way Merge Sort:
T(n) / [n log₃(n)]
```

This is the primary recurrence-specific normalization.

### 3. Common-Base Normalization

``` text
graphs/normalized_common_base.png
```

This graph uses:

``` text
T(n) / [n log₂(n)]
```

for both algorithms.

This is mathematically valid because changing the logarithm base only
introduces a constant multiplicative factor.

The graph provides a common scale for comparing the asymptotic growth of
the two algorithms.

### 4. Theoretical Recursion Depth

``` text
graphs/theoretical_recursion_depth.png
```

This graph compares `log₂(n)` for standard Merge Sort with `log₃(n)` for
3-Way Merge Sort.

It makes the difference in recursion depth visually explicit.

# Theoretical Analysis

## 1. Standard Merge Sort

Standard Merge Sort divides an array into two approximately equal parts.

For an input of size `n`:

-   2 recursive calls are made.
-   Each recursive call receives approximately `n/2` elements.
-   The two sorted halves are combined using a linear-time merge.

Therefore:

``` text
T₂(n) = 2T₂(n/2) + Θ(n)
```

Using the Master Theorem:

``` text
a = 2
b = 2
f(n) = Θ(n)

n^(log_b a)
= n^(log₂ 2)
= n
```

Therefore:

``` text
T₂(n) = Θ(n log₂ n)
```

and hence:

``` text
T₂(n) = Θ(n log n)
```

## 2. Modified 3-Way Merge Sort

The modified algorithm divides the array into three approximately equal
parts.

For an input of size `n`:

-   3 recursive calls are made.
-   Each recursive call receives approximately `n/3` elements.
-   The three sorted portions are combined using a three-way merge.

Therefore:

``` text
T₃(n) = 3T₃(n/3) + Θ(n)
```

Using the Master Theorem:

``` text
a = 3
b = 3
f(n) = Θ(n)

n^(log_b a)
= n^(log₃ 3)
= n
```

Therefore:

``` text
T₃(n) = Θ(n log₃ n)
```

and hence:

``` text
T₃(n) = Θ(n log n)
```

# Three-Way Merge Cost

The three sorted subarrays must be combined into one sorted array.

At each step, the algorithm considers the current elements of the
non-empty subarrays and selects the smallest one.

Because there are at most three current elements to compare, only a
constant number of comparisons is required per output element.

Every element is processed during the merge.

Therefore, the three-way merge requires:

``` text
Θ(n)
```

time.

This gives the recurrence:

``` text
T₃(n) = 3T₃(n/3) + Θ(n)
```

rather than a recurrence with a superlinear merge cost.

# Recursion Depth

The recursion depth of standard Merge Sort is approximately:

``` text
log₂(n)
```

while the recursion depth of the three-way version is approximately:

``` text
log₃(n)
```

Ignoring constant and base-case effects:

``` text
log₃(n) < log₂(n)
```

for `n > 1`.

Therefore, the 3-Way algorithm has fewer recursion levels.

However, fewer recursion levels alone do not guarantee better practical
performance.

# Practical Performance

Although both algorithms have the same asymptotic complexity, their
constant factors can differ.

The three-way version may have fewer recursion levels, but its merge
operation must select the smallest element among up to three current
elements instead of two.

Actual execution time can also be affected by:

-   Memory access patterns
-   Cache behavior
-   Compiler optimization
-   CPU architecture
-   Function-call overhead
-   Implementation details

Therefore, the theoretical result `Θ(n log n)` does not imply that the
two implementations will have identical measured execution times.

# Space Complexity

Both algorithms require an auxiliary array for merging.

Therefore:

``` text
Auxiliary merge space = Θ(n)
```

The recursion depth is logarithmic, but the auxiliary merge buffer
dominates the asymptotic auxiliary space.

Thus both implementations require:

``` text
Θ(n)
```

auxiliary space.

# Experimental Results

The benchmark results stored in:

``` text
data\benchmark_results.csv
```

are generated by the repository's benchmark program.

Execution times are machine-dependent and may vary depending on:

-   Processor
-   Operating system
-   Compiler version
-   Compiler optimization
-   Background processes
-   Memory subsystem

Therefore, the numerical execution times should be interpreted as
experimental observations rather than universal constants.

The important experimental observation is that both runtime curves
exhibit approximately `n log n` growth.

# Final Conclusion

Standard Merge Sort has the recurrence:

``` text
T₂(n) = 2T₂(n/2) + Θ(n)
```

which gives:

``` text
T₂(n) = Θ(n log₂ n)
```

The modified 3-Way Merge Sort has the recurrence:

``` text
T₃(n) = 3T₃(n/3) + Θ(n)
```

which gives:

``` text
T₃(n) = Θ(n log₃ n)
```

Since:

``` text
log₃(n) = log₂(n) / log₂(3)
```

the two expressions differ only by a constant factor.

Therefore:

``` text
Θ(n log₂ n)
=
Θ(n log₃ n)
=
Θ(n log n)
```

### Final Answer

> **The worst-case running time of the modified three-way Merge Sort is
> Θ(n log n), the same asymptotic complexity as standard Merge Sort. The
> two algorithms have different logarithm bases and different recursion
> depths, but those differences affect only constant factors, not the
> Big-Theta classification.**

# Reproducibility Summary

The complete experiment can be reproduced on Windows using:

``` powershell
# Create build directory
New-Item -ItemType Directory -Force build

# Compile benchmark
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src\merge_sort.c src\benchmark.c -o build\benchmark.exe

# Compile tests
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src\merge_sort.c tests\test_merge_sort.c -o build\test_merge_sort.exe

# Run tests
.\build\test_merge_sort.exe

# Run benchmark
.\build\benchmark.exe

# Generate graphs
python scripts\plot_results.py
```

The resulting workflow is:

``` text
C Source Code
     │
     ▼
   GCC
     │
     ▼
Correctness Tests
     │
     ▼
Benchmark Program
     │
     ▼
benchmark_results.csv
     │
     ▼
Python + Matplotlib
     │
     ▼
Four Graphs
```

No GNU Make is required.

# Author

**Sitanshu Sekhar Mohanty**
