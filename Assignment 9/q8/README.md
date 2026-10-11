# Minimum Meeting Rooms

## Problem Statement
Given $n$ meetings, each defined by a start time and an end time, the objective is to determine the minimum number of conference rooms required to accommodate all meetings without overlap. The problem is solved efficiently by separating the start and end times, sorting them chronologically, and using a two-pointer Greedy approach to simulate the allocation and freeing of rooms over time.

---

## Algorithm
* Read the number of meetings $n$ and validate that it is greater than zero.
* Dynamically allocate memory for two separate arrays: one for the start times and one for the end times.
* Iterate $n$ times to read the start and end times of each meeting into their respective arrays.
* Sort the start time array in ascending order using `qsort`.
* Sort the end time array in ascending order using `qsort`.
* Initialize two pointers, `i = 0` and `j = 0`, to traverse the start and end arrays respectively.
* Initialize tracking counters `rooms = 0` (current active rooms) and `maxRooms = 0` (peak rooms needed).
* Loop while there are still start times to process (`i < n`):
  * If the current meeting starts before the earliest scheduled meeting ends (`start[i] < end[j]`), a new room is required. Increment `rooms`, update `maxRooms` if the current rooms count exceeds it, and move to the next start time (`i++`).
  * Otherwise, a meeting has finished before or exactly when the next one starts. A room is freed, so decrement `rooms` and move to the next end time (`j++`).
* Print the peak number of rooms required (`maxRooms`) and free the dynamically allocated arrays.

---

## Pseudocode

```text
MIN-MEETING-ROOMS(start, end, n)

1. Sort the start array in ascending order.
2. Sort the end array in ascending order.
3. Initialize pointers and counters:
       i = 0
       j = 0
       rooms = 0
       maxRooms = 0

4. While i < n:
       If start[i] < end[j]:
           rooms = rooms + 1
           If rooms > maxRooms:
               maxRooms = rooms
           i = i + 1
       Else:
           rooms = rooms - 1
           j = j + 1

5. Return maxRooms

```

## Sample Output

```text
Enter number of meetings: 3
Enter start and end time of each meeting:
Meeting 1: 0 30
Meeting 2: 5 10
Meeting 3: 15 20

Minimum number of meeting rooms required = 2

```

## Time Complexity Analysis

To determine the overall time complexity, we evaluate the sorting and traversal phases:
* **Sorting Phase:** Sorting the start array takes $O(n \log n)$ time, and sorting the end array takes $O(n \log n)$ time.   
* **Traversal Phase:** The while loop iterates through the elements. In the worst case, both pointers `i` and `j` traverse their respective arrays of size $n$, resulting in a maximum of $2n$ operations. This takes $O(n)$ time.   

Combining these phases gives $O(n \log n) + O(n \log n) + O(n)$, which simplifies to the dominant logarithmic term.

**Final Time Complexity:**
$$O(n \log n)$$

---

## Conclusion

The Minimum Meeting Rooms problem is effectively solved using a Greedy algorithm based on a chronological sweep. By decoupling the start and end times and treating them as independent timeline events, the algorithm avoids the need for complex interval trees or nested loops. The two-pointer simulation accurately tracks the peak overlap, achieving an optimal and scalable time complexity of $O(n \log n)$.
