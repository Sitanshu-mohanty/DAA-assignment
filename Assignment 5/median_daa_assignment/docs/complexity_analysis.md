# Complexity Analysis

## 1. Quickselect

The algorithm partitions the array around a pivot and then continues only in the subarray that can contain the required median.

### Average Case

With reasonably balanced partitions, the recurrence is approximately:

`T(N) = T(N/2) + O(N)`

Therefore:

`T(N) = O(N)`

### Worst Case

If the pivot is always the smallest or largest element, only one element is removed at each step:

`T(N) = T(N-1) + O(N)`

Therefore:

`T(N) = O(N^2)`

### Space Complexity

The selection loop is iterative and uses only a constant amount of extra working memory:

`O(1)` auxiliary space.

The array itself requires `O(N)` storage.

## 2. Even Number of Elements

For even `N`, two middle ranks are needed:

- `N/2 - 1`
- `N/2`

The average of these two values is the median.

The implementation performs two Quickselect operations. Since each operation is expected `O(N)`, the total remains:

`O(N) + O(N) = O(N)`

The constant factor is larger than for the odd case, but the asymptotic complexity is unchanged.

## 3. Why It Does Not Sort the List

A sorting algorithm tries to arrange every element in increasing order. Quickselect only partitions enough of the array to locate the required ranked element(s). Elements that are irrelevant to the median are not fully ordered.

## 4. Comparison

| Method | Average Time | Worst Time | Extra Space | Full Sorting? |
|---|---:|---:|---:|---|
| Quickselect | O(N) | O(N^2) | O(1) | No |
| Insertion Sort + Median | O(N^2) | O(N^2) | O(1) | Yes |
| Merge Sort + Median | O(N log N) | O(N log N) | O(N) | Yes |

For this assignment, Quickselect is preferred because the problem asks for the median **without sorting the list**.
