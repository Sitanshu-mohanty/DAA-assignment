# Complexity Validation

The algorithm uses two recursive multiplications:

```text
X = (A1 + A2)(B1 + B2)
Y = (A1 - A2)(B1 - B2)
```

At every level, the matrix additions/subtractions involve a total of `O(n²)` element operations.

Therefore:

```text
T(n) = 2T(n/2) + O(n²)
```

The recursion tree has:

```text
2^k
```

subproblems at level `k`, each with work proportional to:

```text
(n / 2^k)²
```

So the work per level decreases geometrically:

```text
n²
n²/2
n²/4
...
```

The total is bounded by a constant multiple of `n²`.

Therefore:

```text
T(n) = O(n²)
```

The benchmark file `results/complexity.csv` records the arithmetic operations performed by the implementation for several powers of 2 and compares them with `n²`.
