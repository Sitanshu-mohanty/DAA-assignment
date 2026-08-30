# Heap Sort Complexity Analysis

## 1. Building the Heap

The algorithm builds a max heap from the input array.

Although `heapify` for one node can take O(log N), building the complete heap takes:

**O(N)**

This is because most nodes are near the bottom of the heap and require very little work.

## 2. Heapify

After moving the maximum element to the end, the root is restored using `heapify`.

For a heap containing N elements, the height is O(log N), so one heapify operation takes:

**O(log N)**

## 3. Sorting Phase

The maximum element is removed from the heap N-1 times.

Therefore:

**O(N) × O(log N) = O(N log N)**

## Overall Time Complexity

| Case | Complexity |
|---|---:|
| Best | O(N log N) |
| Average | O(N log N) |
| Worst | O(N log N) |

Heap Sort has the same asymptotic time complexity in all three cases.

## Space Complexity

Heap Sort rearranges the elements inside the same array.

Therefore:

**Auxiliary space = O(1)**

The recursive `heapify` function can use O(log N) call-stack space in the worst case because the implementation is recursive. If strict constant auxiliary stack space is required, `heapify` can instead be implemented iteratively.

## File Operations

Generating and writing N values requires O(N) time. Reading N values from the input file and writing N sorted values to the output file also require O(N) time.

These linear file operations do not change the overall sorting complexity of O(N log N).
