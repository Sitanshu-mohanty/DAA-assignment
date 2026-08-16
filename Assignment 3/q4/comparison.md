# Comparison: Normal Matrix Multiplication vs Strassen

## Number of Scalar Multiplications

For an `n x n` matrix:

### Normal Method

The conventional method performs:

```text
n³
```

scalar multiplications.

### Strassen Method

For powers of 2:

```text
M(n) = 7M(n/2)
```

with:

```text
M(1) = 1
```

Therefore:

```text
M(n) = n^log2(7)
```

approximately:

```text
n^2.81
```

## Example

For `n = 8`:

```text
Normal:
8³ = 512 multiplications

Strassen:
7³ = 343 multiplications
```

For `n = 128`:

```text
Normal:
128³ = 2,097,152 multiplications

Strassen:
7^7 = 823,543 multiplications
```

The benchmark CSV contains these values for several input sizes.

## Important Practical Note

Strassen reduces the number of recursive multiplications, but it performs additional matrix additions and subtractions and requires extra memory. Therefore, the asymptotically better complexity does not automatically mean it is faster for every small matrix.

For this lab, the main purpose is to implement and understand the divide-and-conquer algorithm and its complexity.
