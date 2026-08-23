# Approach Comparison

| Approach | Time Complexity | Main Idea |
|---|---:|---|
| Brute Force | O(n²) | Check every possible pair |
| Binary Search | O(n log n) | Sort one array and binary-search complements |
| Sorting + Two Pointers | O(n log n) | Sort both arrays and move two pointers |
| Hash Table | O(n) average | Store values and search for complements |

## Chosen Approach

The **sorting + two-pointer approach** is used in this lab.

### Why?

- It satisfies the required `O(n log n)` complexity.
- It directly demonstrates an application of sorting.
- The logic is simple and easy to understand.
- It does not require a complicated data structure.

## Why Not Brute Force?

Brute force checks `n × n` possible pairs, so its complexity is:

```text
O(n²)
```

This does not satisfy the assignment requirement.

## Why Not Hashing?

Hashing can provide `O(n)` average time, but the main purpose of this assignment is to demonstrate how sorting can be applied to solve a problem. Therefore, sorting with two pointers is more appropriate.
