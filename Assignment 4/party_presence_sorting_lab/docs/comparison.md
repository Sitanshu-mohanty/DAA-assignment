# Approach Comparison

| Approach | Time Complexity | Main Idea | Suitable? |
|---|---:|---|---|
| Brute Force | O(n^2) | Repeatedly count how many intervals contain a time | No |
| Sort Events | O(n log n) | Convert entries/exits into events and sort them | **Yes - used here** |
| Sort Entry/Exit Arrays | O(n log n) | Sort both arrays and scan with two pointers | Yes |

## Chosen Approach

The **sort events** method is used because the assignment is an application of sorting and it directly satisfies the required `O(n log n)` complexity.

It is also simple to implement and easy to explain in a lab viva.

## Why Events?

Each person produces only two important changes:

```text
Entry -> +1 person
Exit  -> -1 person
```

After sorting these changes by time, a single running count gives the number of people present.

## Why Not Brute Force?

Checking every possible time against every person's interval can require `O(n^2)` work, which does not satisfy the required `O(n log n)` bound.

## Alternative Approach

A second valid solution is to put all entry times in one sorted array and all exit times in another sorted array, then use two pointers. That also runs in `O(n log n)`.

The event-array approach is chosen here because it keeps the complete chronological order in one simple array.
