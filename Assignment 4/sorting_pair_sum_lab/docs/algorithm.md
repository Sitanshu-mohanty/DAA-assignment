# Algorithm

## Sorting + Two-Pointer Method

### Step-by-Step Algorithm

1. Read the size `n`.
2. Read all elements of `S1`.
3. Read all elements of `S2`.
4. Read the value `x`.
5. Sort both arrays in ascending order.
6. Set pointer `i` to the first element of `S1`.
7. Set pointer `j` to the last element of `S2`.
8. Calculate `S1[i] + S2[j]`.
9. If the sum is equal to `x`, a required pair exists.
10. If the sum is less than `x`, increase `i`.
11. If the sum is greater than `x`, decrease `j`.
12. Continue until a pair is found or the pointers cross the valid range.
13. If no pair is found, report that no pair exists.

## Pseudocode

```text
sort(S1)
sort(S2)

i = 0
j = n - 1

while i < n and j >= 0

    sum = S1[i] + S2[j]

    if sum == x
        return pair found

    else if sum < x
        i = i + 1

    else
        j = j - 1

return no pair
```

## Correctness

Both arrays are sorted before the search.

If the current sum is smaller than `x`, moving `j` backward would make the sum smaller. Therefore, `i` is increased.

If the current sum is greater than `x`, moving `i` forward would make the sum greater. Therefore, `j` is decreased.

Thus, each pointer movement removes only impossible candidates. If the algorithm finds a sum equal to `x`, the pair is valid. If the search finishes without finding one, no valid pair exists.

## Complexity

Sorting each array takes `O(n log n)`.

The two-pointer search takes `O(n)` because each pointer moves only in one direction.

Therefore:

```text
O(n log n) + O(n log n) + O(n)
= O(n log n)
```

The arrays require `O(n)` memory, while the search itself uses `O(1)` extra space.
