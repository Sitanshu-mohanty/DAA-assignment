# Complexity Comparison

Let `n` be the number of dictionary items.

| Data structure | Search | Insert | Delete | Maximum | Minimum | Predecessor | Successor |
|---|---:|---:|---:|---:|---:|---:|---:|
| Unsorted array | O(n) | O(1) | O(1) | O(n) | O(n) | O(n) | O(n) |
| Sorted array | O(log n) | O(n) | O(n) | O(1) | O(1) | O(1) | O(1) |
| Singly linked unsorted | O(n) | O(1) | O(n) | O(n) | O(n) | O(n) | O(1) |
| Singly linked sorted | O(n) | O(n) | O(n) | O(n) | O(1) | O(n) | O(1) |
| Doubly linked unsorted | O(n) | O(1) | O(1) | O(n) | O(n) | O(1) | O(1) |
| Doubly linked sorted | O(n) | O(n) | O(1) | O(n) | O(1) | O(1) | O(1) |

## Important assumptions

- `Delete(D, x)` is interpreted literally: a pointer/reference to `x` is already available.
- Unsorted-array deletion replaces the deleted element with the last element, so order is not preserved and deletion is O(1).
- Linked lists do not maintain a tail pointer, so maximum is O(n).
- Sorted arrays use binary search.
- Linked lists do not support random access, so sorted-list search remains O(n).
- Predecessor/successor mean the immediately smaller/larger **key**, not necessarily the physical neighbor in an unsorted structure.

## Why these results occur

**Unsorted array:** no ordering exists, so search/min/max/predecessor/successor may scan all elements. Appending is O(1), and unordered deletion is O(1).

**Sorted array:** binary search gives O(log n), but insertion/deletion can shift O(n) elements. Endpoints and neighboring positions are directly accessible.

**Singly linked unsorted list:** traversal operations are O(n). Head insertion is O(1). Given `x`, deletion may need to find its predecessor, making the worst case O(n). `x->next` makes successor O(1).

**Singly linked sorted list:** minimum is the head and successor is `x->next`, but search, insertion, deletion, predecessor and maximum can require traversal.

**Doubly linked unsorted list:** given a node pointer, `x->prev` and `x->next` make predecessor, successor and deletion O(1). Search/min/max remain O(n).

**Doubly linked sorted list:** minimum is the head; given a node pointer, deletion, predecessor and successor are O(1). Search/insertion/max remain O(n) under the no-tail-pointer assumption.

### Important variation

If a tail pointer is maintained, maximum for a sorted linked list becomes O(1). If an unsorted array must preserve element order during deletion, deletion becomes O(n).
