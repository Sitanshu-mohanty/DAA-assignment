# Algorithm Comparison

## Quick Sort vs Simple Sorting Approach

For this assignment, Quick Sort is the required algorithm. A comparison with common sorting algorithms is useful for understanding its performance.

| Algorithm | Best | Average | Worst | Extra Space |
|---|---:|---:|---:|---:|
| Quick Sort | O(N log N) | O(N log N) | O(N^2) | O(log N) average |
| Merge Sort | O(N log N) | O(N log N) | O(N log N) | O(N) |
| Insertion Sort | O(N) | O(N^2) | O(N^2) | O(1) |

Quick Sort is usually fast in practice because partitioning is done in-place and it needs relatively little extra memory. Its worst case occurs when the chosen pivot repeatedly creates very unbalanced partitions.
