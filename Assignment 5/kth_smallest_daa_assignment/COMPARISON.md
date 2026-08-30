# Algorithm Comparison

The assignment specifically asks for the K-th smallest element **without sorting the list**. The main solution therefore uses Quickselect.

| Method | Main Idea | Average Time | Worst Time | Extra Space |
|---|---|---:|---:|---:|
| Quickselect | Partition and continue only on the required side | O(N) | O(N²) | O(1)* |
| Sorting + indexing | Sort all values, then take position K-1 | O(N²)** | O(N²)** | O(1) |

\* The Quickselect implementation works in-place, so its auxiliary space is O(1) apart from the input array.

\*\* The comparison program intentionally uses simple Bubble Sort so the difference is easy to understand in a DAA lab. A library or efficient comparison sort would normally take O(N log N) time.

## Conclusion

Quickselect is more suitable for this assignment because it avoids sorting the complete list and has **O(N) average time**. It is especially useful when only one K-th smallest position is required.
