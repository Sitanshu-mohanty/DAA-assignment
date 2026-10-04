## Q4. Longest Increasing Subsequence

### Problem Statement
Given an integer array $A$ containing $n$ elements, find the Longest Increasing Subsequence (LIS) such that every element of the subsequence is strictly greater than the previous element. The program should determine the length of the LIS and the actual Longest Increasing Subsequence. This is implemented using Dynamic Programming.

### Algorithm
*   Read the number of elements $n$ and the array $A$.
*   Create three arrays: `dp` to store LIS lengths, `parent` to store the previous index in the LIS, and `LIS` to store the reconstructed subsequence.
*   Initialize every `dp[i]` to $1$, because every individual element forms an increasing subsequence of length $1$.
*   Initialize `parent[i]` to $-1$.
*   For every element $A[i]$, compare it with all previous elements $A[j]$.
*   If $A[j] < A[i]$, then $A[i]$ can extend the increasing subsequence ending at $A[j]$.
*   If extending that subsequence produces a longer sequence, update:
    $$dp[i] = dp[j] + 1$$
    and store:
    $$parent[i] = j$$
*   Find the maximum value in `dp[]` and its corresponding index.
*   Starting from this index, use the `parent` array to trace the LIS backwards.
*   Store the elements in reverse order in the `LIS` array.
*   Print the length and the actual LIS.

### Pseudocode

```text
LONGEST-INCREASING-SUBSEQUENCE(A, n)

1. Create arrays dp[0...n-1], parent[0...n-1] and LIS[0...n-1].

2. For i = 0 to n-1:
       dp[i] = 1
       parent[i] = -1

3. For i = 1 to n-1:
       For j = 0 to i-1:
           If A[j] < A[i]:
               If dp[j] + 1 > dp[i]:
                   dp[i] = dp[j] + 1
                   parent[i] = j

4. Set result = dp[0]
   Set maxIndex = 0

5. For i = 1 to n-1:
       If dp[i] > result:
           result = dp[i]
           maxIndex = i

6. Set length = result
   Set index = maxIndex

7. For i = length-1 down to 0:
       LIS[i] = A[index]
       index = parent[index]

8. Print result as the length of LIS.

9. Print LIS as the Longest Increasing Subsequence.

10. Return result.

```

### Sample Output

```text
Enter number of elements n: 8
Enter elements: 10 22 9 33 21 50 41 60

Length of Longest Increasing Subsequence = 5
Longest Increasing Subsequence = 10 22 33 50 60

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the Dynamic Programming table construction:
*   **Outer Loop:** Iterates through each element from index $1$ to $n-1$, running $n$ times.
*   **Inner Loop:** Iterates through all previous elements from $0$ to $i-1$, taking on average $O(n)$ steps for each outer iteration.

Multiplying the iterations of the two nested loops:
$$T(n) = O(n^2)$$

*   **Traceback Phase:** The reconstruction loop walks backwards using the `parent` array, taking at most $O(n)$ time, which is dominated by the $O(n^2)$ table calculation.

**Final Time Complexity:**
$$O(n^2)$$

### Conclusion

The Longest Increasing Subsequence problem is successfully solved using a bottom-up Dynamic Programming approach. The algorithm computes optimal substructures by evaluating preceding elements to build up the longest increasing chain lengths and tracks path indices for full subsequence reconstruction. The time complexity of the algorithm is $O(n^2)$.


