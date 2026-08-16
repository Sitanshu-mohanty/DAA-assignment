# Matrix Multiplication using Strassen's Method — DAA Lab Assignment

## Aim

To multiply two square matrices of size `n x n` using **Strassen's divide-and-conquer method**.

## Important Note

This lab implementation accepts matrix sizes that are powers of 2:

```text
2, 4, 8, 16, 32, ...
```

This keeps the code simple and makes the divide-and-conquer splitting easy to understand.

## Basic Idea

For two matrices:

```text
A = | A11 A12 |
    | A21 A22 |

B = | B11 B12 |
    | B21 B22 |
```

Normal multiplication uses 8 recursive multiplications.

Strassen's method reduces these to 7:

```text
M1 = (A11 + A22)(B11 + B22)
M2 = (A21 + A22)B11
M3 = A11(B12 - B22)
M4 = A22(B21 - B11)
M5 = (A11 + A12)B22
M6 = (A21 - A11)(B11 + B12)
M7 = (A12 - A22)(B21 + B22)
```

Then:

```text
C11 = M1 + M4 - M5 + M7
C12 = M3 + M5
C21 = M2 + M4
C22 = M1 - M2 + M3 + M6
```

This reduces the number of multiplications from 8 to 7 at every recursive level.

## Files

```text
matrix-multiplication-strassen-lab/
│
├── src/
│   ├── main.c
│   └── benchmark.c
│
├── results/
│   └── comparisons.csv
│
├── README.md
├── comparison.md
└── .gitignore
```

There is no graph because this lab does not require one.

## Run the Main Program

### Windows

```powershell
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o strassen.exe
.\strassen.exe
```

### Linux / macOS

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o strassen
./strassen
```

### Example

```text
========== STRASSEN MATRIX MULTIPLICATION ==========

Enter matrix size (power of 2): 2

Enter elements of Matrix A:
1 2
3 4

Enter elements of Matrix B:
5 6
7 8

========== RESULT ==========

Matrix A:
1 2
3 4

Matrix B:
5 6
7 8

A x B using Strassen's method:
19 22
43 50

Time Complexity: O(n^log2(7)) ≈ O(n^2.81)
```

## Run the Comparison Program

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

It creates:

```text
results/comparisons.csv
```

The file compares the number of scalar multiplications used by normal matrix multiplication and Strassen's method.

## Complexity

### Normal Matrix Multiplication

```text
T(n) = 8T(n/2) + O(n²)
```

Therefore:

```text
O(n³)
```

### Strassen's Method

```text
T(n) = 7T(n/2) + O(n²)
```

Therefore:

```text
O(n^log2(7))
```

and:

```text
log2(7) ≈ 2.81
```

So Strassen's method has a better asymptotic multiplication complexity than the usual `O(n³)` method.

## Conclusion

Strassen's matrix multiplication uses 7 recursive matrix multiplications instead of 8. This gives the recurrence:

```text
T(n) = 7T(n/2) + O(n²)
```

and results in:

```text
O(n^2.81)
```

time complexity, which is asymptotically better than the conventional `O(n³)` matrix multiplication method.
