## Q5. Maximum Sum Increasing Subsequence

### Problem Statement
Given an array $A$ of $n$ positive integers, find the maximum possible sum of a strictly increasing subsequence. The program should determine the maximum sum obtainable from a strictly increasing subsequence and the actual increasing subsequence that produces this maximum sum. This is implemented using Dynamic Programming.

### Algorithm
*   Read the number of elements $n$ and the positive integer array $A$.
*   Create the arrays `dp` and `prev`.
*   Set `dp[i] = A[i]` for every element, because a single element itself forms an increasing subsequence.
*   Set `prev[i] = -1`.
*   For every element $A[i]$, compare it with all previous elements $A[j]$.
*   If $A[j] < A[i]$, then $A[i]$ can be added to the increasing subsequence ending at $A[j]$.
*   If the resulting sum is greater than the current `dp[i]`, update:
    $$dp[i] = dp[j] + A[i]$$
    and store:
    $$prev[i] = j$$
*   Find the largest value in `dp[]`. This gives the maximum sum and its ending index.
*   Starting from this index, use the `prev` array to trace the selected elements backwards.
*   Store these elements in the sequence array.
*   Print the sequence in reverse order to obtain the correct increasing order.
*   Print the maximum sum.

### Pseudocode

```text
MAX-SUM-INCREASING-SUBSEQUENCE(A, n)

1. Create arrays dp[0...n-1] and prev[0...n-1].

2. For i = 0 to n-1:
       dp[i] = A[i]
       prev[i] = -1

3. For i = 1 to n-1:
       For j = 0 to i-1:
           If A[j] < A[i] AND
              dp[i] < dp[j] + A[i]:
                   dp[i] = dp[j] + A[i]
                   prev[i] = j

4. Set max_sum = dp[0]
   Set max_idx = 0

5. For i = 1 to n-1:
       If dp[i] > max_sum:
           max_sum = dp[i]
           max_idx = i

6. Create sequence array.

7. Set curr = max_idx.

8. While curr != -1:
       Store A[curr] in sequence
       curr = prev[curr]

9. Print the sequence in reverse order.

10. Print max_sum.

11. Return max_sum.

```

### Sample Output

```text
Enter number of elements n: 7
Enter elements: 1 101 2 3 100 4 5

Maximum sum increasing subsequence = 1 2 3 100
Maximum sum = 106

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the Dynamic Programming table construction:
*   **Outer Loop:** Iterates through each element from index $1$ to $n-1$, running $n$ times.
*   **Inner Loop:** Iterates through all previous elements from $0$ to $i-1$, taking on average $O(n)$ steps for each outer iteration.

Multiplying the iterations of the two nested loops:
$$T(n) = O(n^2)$$

*   **Traceback Phase:** The reconstruction loop walks backwards using the `prev` array, taking at most $O(n)$ time, which is dominated by the $O(n^2)$ table calculation.

**Final Time Complexity:**
$$O(n^2)$$

### Conclusion

The Maximum Sum Increasing Subsequence problem is successfully solved using a bottom-up Dynamic Programming approach. The algorithm computes optimal substructures by evaluating preceding elements to maximize cumulative sums along increasing paths, while tracking indices to reconstruct the exact subsequence. The algorithm has a time complexity of $O(n^2)$.



