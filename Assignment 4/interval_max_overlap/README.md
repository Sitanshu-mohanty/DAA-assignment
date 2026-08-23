# Application of Sorting - VI

## Problem

Given `n` intervals `(l_i, r_i)` on a line, find a point `p` that belongs to the largest possible number of intervals.

Endpoints are included. Therefore, if `p = l_i` or `p = r_i`, the point is considered to be inside the interval.

### Example

For:

```text
(10, 40)
(20, 60)
(50, 90)
(15, 70)
```

The point `50` belongs to three intervals:

```text
(20, 60), (50, 90), (15, 70)
```

So an answer is:

```text
Point with maximum overlap: 50
Maximum number of intervals: 3
```

## Approach Used

The algorithm uses **sorting of interval endpoints**.

For every interval `(l, r)` we create two events:

- `+1` at `l` because one interval starts.
- `-1` at `r` because one interval ends.

All events are then sorted by coordinate.

Because the problem says that endpoints count as being inside an interval, a start event must be processed **before** an end event when both have the same coordinate.

While scanning the sorted events:

- Start event: increase the current overlap count.
- End event: decrease the current overlap count.
- Whenever the current count becomes larger than the previous maximum, store that coordinate as the best point.

## Complexity

There are `2n` events.

- Creating events: `O(n)`
- Sorting events: `O(n log n)`
- Scanning events: `O(n)`
- Extra space: `O(n)`

Therefore, the total time complexity is:

```text
O(n log n)
```

## Files

```text
interval_max_overlap/
├── main.c
├── README.md
├── algorithm.md
├── comparison.md
```

## How to Compile

### Using GCC directly

```bash
gcc -Wall -Wextra -std=c11 main.c -o interval_max_overlap
```

Then:

```bash
./interval_max_overlap
```

## Sample Run

Input:

```text
4
10 40
20 60
50 90
15 70
```

Output:

```text
Point with maximum overlap: 50
Maximum number of intervals: 3
```

## Notes

- The program assumes each interval is given as `left right` with `left <= right`.
- If more than one point gives the same maximum overlap, the program keeps updating on a tie, so it returns the rightmost such point in the sorted scan.
- No graph is required for this solution.
