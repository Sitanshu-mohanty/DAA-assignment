# Complexity Analysis

## Method 1 — Sequential merging

Suppose there are `k` arrays and every array contains `n` elements.

The first merge processes:

```text
2n elements
```

The second merge processes:

```text
3n elements
```

The third merge processes:

```text
4n elements
```

Therefore:

```text
T(k, n) = 2n + 3n + 4n + ... + kn
```

Factor out `n`:

```text
T(k, n) = n(2 + 3 + ... + k)
```

Since:

```text
2 + 3 + ... + k = Θ(k²)
```

we get:

```text
T(k, n) = Θ(nk²)
```

## Method 2 — Pairwise merging

At every round, the arrays are merged in pairs.

For example:

```text
k arrays
↓
k/2 arrays
↓
k/4 arrays
↓
...
↓
1 array
```

The number of rounds is:

```text
Θ(log k)
```

At each round, every one of the original `kn` elements is processed once.

Therefore the work per round is:

```text
Θ(kn)
```

and:

```text
T(k, n) = Θ(kn) × Θ(log k)
        = Θ(nk log k)
```

## Space complexity

The final result contains `kn` elements, so output space is:

```text
Θ(kn)
```

The implementation uses temporary arrays while merging. Peak memory is proportional to the total number of elements:

```text
Θ(kn)
```

## Why Method 2 wins

Compare:

```text
Method 1: nk²
Method 2: nk log k
```

The factor `n` is common, so the important difference is:

```text
k²  versus  k log k
```

As `k` becomes large:

```text
k log k << k²
```

Therefore pairwise merging scales much better.
