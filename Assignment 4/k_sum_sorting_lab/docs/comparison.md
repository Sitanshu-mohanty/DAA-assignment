# Approach Comparison

| Approach | Time Complexity | Main Idea | Suitable for This Lab? |
|---|---:|---|---|
| Brute Force | O(n^k) | Generate all k-element combinations | No |
| Sorting + Binary Search | O(n^(k-1) log n) | Choose k-1 elements and binary-search the last value | **Yes** |
| Sorting + Two Pointers | Depends on k | Useful mainly for smaller fixed k such as 2-sum or 3-sum | Not used |
| Hashing | O(n^(k-1)) average for this style | Use a hash table for the final lookup | Not used |

## Chosen Approach

The **sorting + binary search** method is used because it directly satisfies the required:

```text
O(n^(k-1) log n)
```

time complexity.

It is also easy to implement using:

- one sorting function,
- one recursive function,
- one binary-search function.

## Why Brute Force Is Not Used

A brute-force method checks every possible group of `k` elements.

This can take approximately:

```text
O(n^k)
```

which is slower than the required bound.

## Why Binary Search Is Used

After choosing `k - 1` elements, the value required to reach `T` is known.

For example:

```text
T = 30
selected values = 5, 8

remaining = 30 - 5 - 8
          = 17
```

Because the array has already been sorted, binary search can check for `17` in `O(log n)` time.

This is the key idea that gives the required complexity.
