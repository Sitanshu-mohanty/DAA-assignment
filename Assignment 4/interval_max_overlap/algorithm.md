# Algorithm

## Step-by-step Algorithm

1. Read `n` intervals.
2. For every interval `(l, r)`:
   - Create a start event `(l, START)`.
   - Create an end event `(r, END)`.
3. Sort all `2n` events:
   - First by coordinate.
   - If two events have the same coordinate, put `START` before `END`.
4. Set:
   - `count = 0`
   - `maxCount = 0`
5. Scan the events from left to right.
6. If the event is `START`, increase `count`.
7. If `count > maxCount`, update:
   - `maxCount = count`
   - `bestPoint = current coordinate`
8. If the event is `END`, decrease `count`.
9. Print `bestPoint` and `maxCount`.

## Why does START come before END?

Suppose one interval is `[10, 20]` and another is `[20, 30]`.

At point `20`, both intervals contain the point because endpoints are included.

Therefore, at coordinate `20`, the start event must be processed before the end event. This makes the overlap count temporarily include both intervals, which is exactly what the problem requires.

## Pseudocode

```text
read n
create an empty event array

for every interval (l, r)
    add (l, START)
    add (r, END)

sort events by:
    coordinate ascending
    START before END for equal coordinates

count = 0
maxCount = 0
bestPoint = first event coordinate

for every event
    if event is START
        count = count + 1
        if count > maxCount
            maxCount = count
            bestPoint = event.coordinate
    else
        count = count - 1

print bestPoint
print maxCount
```
