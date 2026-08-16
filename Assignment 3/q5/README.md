# Special-Pattern Matrix Multiplication — DAA Lab Assignment

## Aim

To multiply two special-pattern `n x n` matrices using a divide-and-conquer approach and obtain an `O(n^2)` algorithm.

Here:

```text
n = 2^k
```

Each matrix has the form:

```text
M = | M1  M2 |
    | M2  M1 |
```

and each block has the same recursive structure until single elements are reached.

## Basic Idea

Let:

```text
A = | A1  A2 |
    | A2  A1 |

B = | B1  B2 |
    | B2  B1 |
```

Instead of doing four block multiplications, use:

```text
X = (A1 + A2)(B1 + B2)
Y = (A1 - A2)(B1 - B2)
```

Then:

```text
P = (X + Y) / 2
Q = (X - Y) / 2
```

The result is:

```text
AB = | P  Q |
     | Q  P |
```

So only **two recursive multiplications** are needed.

## Complexity

At each level:

- 2 recursive multiplications are performed.
- The additions and subtractions operate on `(n/2) x (n/2)` blocks, so their total cost is `O(n^2)`.

Therefore:

```text
T(n) = 2T(n/2) + O(n^2)
```

By the Master Theorem:

```text
T(n) = O(n^2)
```

This is the required complexity.

## Project Structure

```text
special-pattern-matrix-lab/
│
├── src/
│   ├── main.c
│   └── benchmark.c
│
├── results/
│   └── complexity.csv
│
├── README.md
└── .gitignore
```

There is **no graph**, as requested.

## Run the Main Program

### Windows

```powershell
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o special.exe
.\special.exe
```

### Linux / macOS

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o special
./special
```

## Example

For:

```text
A =
1 2
2 1

B =
2 1
1 2
```

the result is:

```text
5 4
4 5
```

## Run the Complexity Validation

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
results/complexity.csv
```

The columns are:

```text
n,operations,n_squared
```

The `operations` column counts the scalar arithmetic operations performed by the implementation, while `n_squared` provides an `n^2` reference.

The number of operations grows proportionally to `n^2`, which validates the `O(n^2)` complexity.

## Important Input Restriction

For this simple lab implementation:

```text
n = 1, 2, 4, 8, 16, ...
```

The input matrices must follow the special recursive pattern described in the question.

For example, a 4 x 4 matrix must have the form:

```text
A11 A12
A12 A11
```

where `A11` and `A12` are themselves 2 x 2 blocks with the same recursive structure.

The program checks the required pattern before multiplication.

## Conclusion

By using the special block structure, the multiplication can be reduced to two recursive matrix multiplications instead of four.

The recurrence:

```text
T(n) = 2T(n/2) + O(n^2)
```

gives:

```text
O(n^2)
```

Thus the divide-and-conquer algorithm satisfies the required `O(n^2)` complexity.
