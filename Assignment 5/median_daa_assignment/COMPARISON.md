# Algorithm Comparison

| Feature | Quickselect | Sorting-Based Method |
|---|---|---|
| Main idea | Select required rank using partitioning | Sort all elements first |
| Full list sorted? | No | Yes |
| Average time | O(N) | O(N^2) with the included insertion sort |
| Worst time | O(N^2) | O(N^2) with the included insertion sort |
| Extra working space | O(1) | O(1) |
| Best suited for this problem | Yes | Mainly for comparison |

## Result

Quickselect is more appropriate for the given question because it finds the median without sorting the complete list. Its expected running time is linear, `O(N)`.

The sorting program is intentionally simple and is included only as a baseline comparison. It is not the primary solution.
