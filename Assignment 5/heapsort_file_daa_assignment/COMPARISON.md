# Sorting Algorithm Comparison

Heap Sort can be compared with Quick Sort and Merge Sort.

| Algorithm | Best | Average | Worst | Extra Space |
|---|---:|---:|---:|---:|
| Heap Sort | O(N log N) | O(N log N) | O(N log N) | O(1) |
| Quick Sort | O(N log N) | O(N log N) | O(N²) | O(log N) average |
| Merge Sort | O(N log N) | O(N log N) | O(N log N) | O(N) |

## Observation

Heap Sort guarantees O(N log N) time even in the worst case and sorts the array in-place. Its main advantage for this assignment is the predictable worst-case performance and constant auxiliary array space.
