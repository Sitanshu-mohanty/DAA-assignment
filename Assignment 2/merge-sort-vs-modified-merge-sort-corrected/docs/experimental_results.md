# Experimental Results

The following results were generated locally on a Windows system using GCC. The benchmark was executed directly with the compiled executable rather than through `make`.

Each algorithm was benchmarked using the same input sizes and seven repetitions per measurement. The reported execution time is the median of the repetitions.

## Benchmark Results

| Input Size (n) | Standard Merge Sort (s) | 3-Way Merge Sort (s) |
|---------------:|------------------------:|----------------------:|
| 1,024          | 0.000030300             | 0.000023100           |
| 2,048          | 0.000076900             | 0.000071000           |
| 4,096          | 0.000182600             | 0.000177500           |
| 8,192          | 0.000415600             | 0.000381300           |
| 16,384         | 0.000909400             | 0.000855600           |
| 32,768         | 0.001915200             | 0.001755200           |
| 65,536         | 0.003731700             | 0.003540800           |
| 131,072        | 0.008000600             | 0.007609400           |
| 262,144        | 0.016714900             | 0.015881900           |
| 524,288        | 0.034916700             | 0.032952500           |

## Experimental Observations

The measured execution times increase as the input size increases, which is consistent with the expected \(O(n\log n)\) growth of both algorithms.

For this particular Windows test environment, the 3-Way Merge Sort implementation was slightly faster than the standard 2-Way Merge Sort implementation for the tested input sizes. This is an experimental observation and should not be interpreted as a universal theoretical advantage.

Actual execution times depend on hardware, operating-system load, compiler version, compiler optimization settings, memory hierarchy, and other system-level factors.

## Normalized Growth Analysis

The primary normalized analysis uses the logarithm base associated with each algorithm's recursion structure:

- Standard Merge Sort:

\[
\frac{T(n)}{n\log_2 n}
\]

- 3-Way Merge Sort:

\[
\frac{T(n)}{n\log_3 n}
\]

The purpose of this normalization is to compare the measured running time against the corresponding theoretical growth function.

### Why both algorithms are still \( \Theta(n\log n) \)

Standard Merge Sort satisfies the recurrence

\[
T_2(n)=2T_2(n/2)+\Theta(n),
\]

which gives

\[
T_2(n)=\Theta(n\log_2 n).
\]

The 3-Way version satisfies a recurrence of the form

\[
T_3(n)=3T_3(n/3)+\Theta(n),
\]

which gives

\[
T_3(n)=\Theta(n\log_3 n).
\]

Although the logarithm bases are different, logarithms with constant bases greater than 1 differ only by a constant multiplicative factor:

\[
\log_3 n=\frac{\log_2 n}{\log_2 3}.
\]

Therefore,

\[
n\log_3 n
=
\frac{1}{\log_2 3}n\log_2 n.
\]

Since \(1/\log_2 3\) is a constant,

\[
\boxed{\Theta(n\log_2 n)=\Theta(n\log_3 n)=\Theta(n\log n)}
\]

in asymptotic notation.

Thus, the different logarithm bases do not make the two algorithms belong to different Big-Theta complexity classes.

## Graphs

The generated graphs are stored in the `graphs/` directory:

1. `runtime_comparison.png` — measured execution-time comparison.
2. `normalized_own_base.png` — normalization using \(n\log_2 n\) for standard Merge Sort and \(n\log_3 n\) for 3-Way Merge Sort.
3. `normalized_common_base.png` — normalization using a common logarithm base to illustrate the equivalence of the asymptotic growth classes.
4. `theoretical_recursion_depth.png` — comparison of the theoretical recursion depths \(\log_2 n\) and \(\log_3 n\).

## Reproducibility on Windows
### 1. Compile the Benchmark

Run the following command from the project root:

```powershell
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src\merge_sort.c src\benchmark.c -o build\benchmark.exe
### 2. Compile the Correctness Tests

```powershell
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic -Iinclude src\merge_sort.c tests\test_merge_sort.c -o build\test_merge_sort.exe
### 3. Run the Correctness Tests

```powershell
.\build\test_merge_sort.exe
The tests produced:

```text
All Merge Sort tests passed.
## 4. Run the Benchmark

```bash
.\build\benchmark.exe
```

The resulting benchmark data was written to:data\benchmark_results.csv
## 5. Generate the Graphs

```bash
python scripts\plot_results.py
```

The generated graphs were saved in:graphs
The experiment can therefore be reproduced using GCC and Python without requiring GNU Make.
