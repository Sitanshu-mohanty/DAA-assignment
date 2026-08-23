# Comparison

## Proposed Algorithm vs Conventional Sorting

The important condition in this problem is that the input is already sorted by number.

We only need to rearrange the items according to their color.

| Method | Main Idea | Time Complexity | Extra Space |
|---|---|---:|---:|
| Proposed grouping method | Count colors and place items in color sections | **O(n)** | **O(n)** |
| Comparison-based sorting | Sort using a general sorting algorithm and compare color values | O(n log n) | Depends on algorithm |
| Repeated scanning for each color | Scan the array separately for red, blue, and yellow | O(n) | O(1) or O(n), depending on implementation |

## Why the Proposed Method Is Suitable

There are only three possible colors. Therefore, it is unnecessary to use a general-purpose sorting algorithm.

The input is already sorted by number, so the only task is to group the items by color while preserving their order.

The proposed method:

- uses the fact that there are exactly three colors,
- does not compare numbers,
- preserves the order within each color,
- runs in linear time,
- is simple enough for a laboratory implementation.

## Important Observation

If the input were not already sorted by number, grouping by color alone would not guarantee that the numbers within each color were sorted.

For example:

```text
(30, Red), (10, Red)
```

would remain:

```text
(30, Red), (10, Red)
```

after grouping, which is not sorted by number.

Therefore, the given condition that the input is already sorted is essential to achieving the required result in `O(n)` time.

## Conclusion

The proposed counting-and-grouping algorithm is the most appropriate solution for this problem. It takes advantage of both important properties of the input:

1. There are only three colors.
2. The numbers are already sorted.

As a result, the required color ordering can be obtained in **O(n)** time without performing a conventional sorting operation.
