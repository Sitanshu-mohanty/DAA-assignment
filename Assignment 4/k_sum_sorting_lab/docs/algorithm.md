# Algorithm

## Sorting + Recursive Selection + Binary Search

### Step-by-Step

1. Read `n`, the elements of `S`, `k`, and `T`.
2. Sort `S` in ascending order.
3. Start a recursive function with:
   - current index = `0`
   - number of elements still to choose = `k - 1`
   - current sum = `0`
4. Select one element at a time in increasing index order.
5. After selecting `k - 1` elements:
   - Calculate `remaining = T - current_sum`.
   - Binary-search for `remaining` from the next valid index to the end of the array.
6. If binary search finds `remaining`, a valid set of `k` integers exists.
7. Otherwise, continue trying other combinations.
8. If all combinations are checked, report that no solution exists.

## Pseudocode

```text
sort(S)

function findSum(S, start, left, current_sum, T)

    if left == 0
        remaining = T - current_sum

        if binarySearch(S, start, n - 1, remaining)
            return true
        else
            return false

    for i = start to n - left
        if findSum(S, i + 1, left - 1,
                   current_sum + S[i], T)
            return true

    return false
```

The initial call is:

```text
findSum(S, 0, k - 1, 0, T)
```

## Why Sorting Helps

Sorting allows us to use binary search when the first `k - 1` values have been selected.

For example, if:

```text
T = 22
current sum = 11
```

then we only need to search for:

```text
22 - 11 = 11
```

in the remaining sorted part of the array.

## Correctness

At every recursive level, the algorithm chooses a different array position because the next recursive call starts at `i + 1`.

Therefore, an element is never selected more than once.

When `k - 1` elements have been selected, there is only one value required to reach `T`. Binary search checks whether that value exists in the remaining part of the sorted array.

Thus, if a valid set of `k` integers exists, the corresponding combination will eventually be considered and its final required value will be found.

If every possible combination of `k - 1` elements is checked and no required final value exists, then no set of `k` integers adds up to `T`.

## Complexity Analysis

There are `O(n^(k-1))` possible choices for the first `k - 1` elements.

For every such choice, binary search takes:

```text
O(log n)
```

Therefore:

```text
O(n^(k-1) log n)
```

The initial sorting takes:

```text
O(n log n)
```

So the required overall bound is:

```text
O(n^(k-1) log n)
```
             Start
               |
               ↓
          Sort S
               |
               ↓
       Choose k - 1 numbers
               |
               ↓
       Calculate remaining
       
       remaining = T - sum
               |
               ↓
       Binary search remaining
               |
          ┌────┴────┐
          ↓         ↓
       Found?     Not found
          |         |
         YES        ↓
          |    Try another
          |    combination
          ↓
       Solution
