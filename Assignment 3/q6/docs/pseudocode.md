# Pseudocode

## Selection Sort

```text
SELECTION-SORT(A, n)

for i = 1 to n - 1
    min = i

    for j = i + 1 to n
        if A[j] < A[min]
            min = j

    exchange A[i] with A[min]
```

## Loop Invariant

At the start of iteration `i`:

> The first `i` elements of `A` are already sorted and contain the `i` smallest elements of the array.

### Initialization

Before the first iteration, `i = 1`.

There are no elements before `A[1]`, so the invariant is true.

### Maintenance

During iteration `i`, the algorithm searches `A[i ... n]` and finds its smallest element.

It exchanges that element with `A[i]`.

Therefore, after the iteration, the first `i` elements are sorted and contain the `i` smallest elements.

So the invariant remains true.

### Termination

The loop stops after `n - 1` iterations.

At that point, the first `n - 1` elements are sorted and contain the `n - 1` smallest elements.

The last element must therefore be the largest element.

Hence the complete array is sorted.

## Why only n - 1 iterations?

After placing the smallest `n - 1` elements in the first `n - 1` positions, only one element remains.

That last element must already be in its correct position, so an additional iteration is unnecessary.
