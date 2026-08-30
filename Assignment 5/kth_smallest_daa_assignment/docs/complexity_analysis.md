# Complexity Analysis

## 1. Partition

The partition operation scans the current subarray once.

If the current subarray contains `m` elements, partitioning costs:

`O(m)`

## 2. Quickselect Average Case

With reasonably balanced partitions, the amount of work is approximately:

`N + N/2 + N/4 + N/8 + ...`

This is a geometric series with total:

`O(N)`

Therefore:

**Average time complexity = O(N)**

## 3. Quickselect Worst Case

If the pivot is repeatedly the smallest or largest element, only one element is removed on each partition:

`N + (N-1) + (N-2) + ... + 1`

So:

`O(N^2)`

Therefore:

**Worst-case time complexity = O(N²)**

## 4. Space Complexity

The algorithm modifies the input array in place and uses only a constant number of variables.

Therefore:

**Auxiliary space complexity = O(1)**

The dynamically allocated input array itself requires `O(N)` storage.

## 5. Important Observation

Quickselect does perform swaps and partitions, so the array may become partially rearranged. However, it does **not fully sort the list**, which satisfies the requirement of the problem.
