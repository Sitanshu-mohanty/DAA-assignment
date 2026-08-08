# Submission Report

## Title

**Dictionary ADT: Worst-Case Complexity Comparison of Arrays and Linked Lists**

## Objective

To implement the seven primary Dictionary ADT operations using six data structures and compare their theoretical worst-case complexities with experimentally measured running times.

## Operations

- Search
- Insert
- Delete
- Maximum
- Minimum
- Predecessor
- Successor

## Data structures

1. Unsorted array
2. Sorted array
3. Singly linked unsorted list
4. Singly linked sorted list
5. Doubly linked unsorted list
6. Doubly linked sorted list

## Theoretical result

| Data structure | Search | Insert | Delete | Max | Min | Pred | Succ |
|---|---:|---:|---:|---:|---:|---:|---:|
| Unsorted array | O(n) | O(1) | O(1) | O(n) | O(n) | O(n) | O(n) |
| Sorted array | O(log n) | O(n) | O(n) | O(1) | O(1) | O(1) | O(1) |
| Singly linked unsorted | O(n) | O(1) | O(n) | O(n) | O(n) | O(n) | O(1) |
| Singly linked sorted | O(n) | O(n) | O(n) | O(n) | O(1) | O(n) | O(1) |
| Doubly linked unsorted | O(n) | O(1) | O(1) | O(n) | O(n) | O(1) | O(1) |
| Doubly linked sorted | O(n) | O(n) | O(1) | O(n) | O(1) | O(1) | O(1) |

## Conclusion

The experiment is consistent with the theoretical analysis:

- Sorting an array greatly improves search from O(n) to O(log n), but insertion and deletion become O(n).
- Sorting a linked list does not produce O(log n) search because linked lists do not provide random access.
- Doubly linked lists provide O(1) predecessor, successor and deletion when a node pointer is already available.
- Sorted structures provide O(1) minimum, while maximum remains O(n) in this project because no tail pointer is maintained.
- Constant-time operations produce approximately flat curves, while linear operations show increasing time as `n` grows.

The exact measured times are machine-dependent; the important evidence is the growth trend.
