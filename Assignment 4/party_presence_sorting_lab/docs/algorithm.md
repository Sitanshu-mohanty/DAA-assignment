# Algorithm

## Sorting Event Times

For every person `i`, create two events:

```text
(a[i], +1)   Entry
(b[i], -1)   Exit
```

This gives `2n` events.

### Steps

1. Read the entry and exit time of every person.
2. Store each entry as an event with type `+1`.
3. Store each exit as an event with type `-1`.
4. Sort all `2n` events by time.
5. Set `count = 0`, `maxPeople = 0`, and `maxTime = 0`.
6. Scan the sorted events.
7. If the event is an entry, increase `count`.
8. If `count > maxPeople`, update `maxPeople` and store the current time in `maxTime`.
9. If the event is an exit, decrease `count`.
10. Print `maxPeople` and `maxTime`.

## Pseudocode

```text
for each person
    add (entry time, +1)
    add (exit time, -1)

sort all events by time

count = 0
maxPeople = 0
maxTime = 0

for each event
    if event is an entry
        count = count + 1

        if count > maxPeople
            maxPeople = count
            maxTime = event.time
    else
        count = count - 1

print maxPeople
print maxTime
```

## Correctness

After sorting, events are processed in chronological order.

An entry means one more person is present, so the count increases by one. An exit means one person has left, so the count decreases by one.

Therefore, while scanning the events, `count` always represents the number of people present immediately after the current event.

Whenever an entry makes `count` larger than the previous maximum, that event time is a time when the new maximum number of people are present. Hence the final stored `maxTime` is the required time.

Because all entry and exit times are distinct, there are no ties to handle.

## Complexity Analysis

There are `2n` events.

Sorting:

```text
O(2n log(2n)) = O(n log n)
```

Scanning:

```text
O(2n) = O(n)
```

Therefore:

```text
O(n log n) + O(n) = O(n log n)
```

