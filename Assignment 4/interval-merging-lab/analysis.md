# Algorithm and Comparison

## 1. Algorithm

### Step 1: Sort

Sort all intervals in increasing order of their starting points.

For example:

```text
(2, 6), (1, 3), (8, 10), (7, 18)
```

becomes:

```text
(1, 3), (2, 6), (7, 18), (8, 10)
```

### Step 2: Merge

Keep the last merged interval and inspect the remaining intervals one at a time.

- If `current.start <= last.end`, the intervals overlap.
- Extend `last.end` if `current.end` is larger.
- Otherwise, start a new merged interval.

For the sample:

```text
(1, 3) and (2, 6)  -> (1, 6)
(1, 6) and (7, 18) -> no overlap
(7, 18) and (8, 10) -> already covered by (7, 18)
```

Final result:

```text
(1, 6), (7, 18)
```

## 2. Pseudocode

```text
mergeIntervals(intervals, n)
    if n <= 0
        return 0

    sort intervals by start, then by end

    mergedCount = 1

    for i = 1 to n - 1
        last = intervals[mergedCount - 1]
        current = intervals[i]

        if current.start <= last.end
            last.end = max(last.end, current.end)
        else
            intervals[mergedCount] = current
            mergedCount = mergedCount + 1

    return mergedCount
```

## 3. Why Sorting Is Useful

After sorting by the starting point, all intervals that could overlap the current interval appear next to it. This allows the intervals to be merged in one left-to-right scan.

## 4. Comparison of Possible Approaches

| Approach | Main idea | Time complexity | Space | Suitable for this question? |
|---|---|---:|---:|---|
| Brute-force comparison | Compare many pairs and repeatedly find overlaps | Can become `O(n^2)` or worse | `O(n)` | No, does not meet the required bound |
| Sorting + scan | Sort by start, then merge in one pass | `O(n log n)` | `O(n)` for input/storage | **Yes** |
| Sorting + separate result array | Sort, then copy merged intervals to a new array | `O(n log n)` | `O(n)` extra | Yes, but more memory is used |

The sorting + scan method is the simplest choice because it directly satisfies the required worst-case `O(n log n)` time complexity and can reuse the input array as the output storage.

## 5. Correctness Idea

After sorting, consider the intervals from left to right. The algorithm always keeps the correct merged interval for everything processed so far.

- When the next interval overlaps the current merged interval, it can be joined safely because there is no unprocessed interval that starts earlier than it.
- When it does not overlap, the next interval must begin a separate merged interval.

Therefore, after the scan finishes, every overlapping group has been merged and no non-overlapping groups have been joined.
