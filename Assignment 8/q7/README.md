## Q7. Rod Cutting

### Problem Statement
Given a rod of length $n$ and an array of prices where $P[i]$ represents the price of a rod piece of length $i+1$, determine the maximum revenue obtainable by cutting the rod into pieces. Also display the optimal rod pieces used to obtain the maximum revenue. This is implemented using Dynamic Programming.

### Algorithm
*   Read the length $n$ of the rod and the prices of pieces of lengths 1 to $n$.
*   Create a DP array `dp` where `dp[i]` stores the maximum revenue obtainable from a rod of length $i$.
*   Initialize `dp[0] = 0` because a rod of length zero gives zero revenue.
*   For every rod length $i$ from 1 to $n$, consider every possible first cut $j$ from 1 to $i$.
*   Calculate the revenue as:
    $$P[j-1] + dp[i-j]$$
*   Select the maximum value among all possible cuts and store it in `dp[i]`.
*   Store the cut length in `cuts[i]` whenever a better revenue is found.
*   After calculating `dp[n]`, trace the `cuts` array to determine the optimal rod pieces.
*   Display the maximum revenue and the optimal cutting combination.

### Pseudocode

```text
ROD-CUTTING(P, n)

1. Create arrays dp[0...n] and cuts[0...n].
2. Set dp[0] = 0 and cuts[0] = 0.

3. For i = 1 to n:
      max_val = -1

      For j = 1 to i:
          current_value = P[j-1] + dp[i-j]

          If current_value > max_val:
              max_val = current_value
              cuts[i] = j

      dp[i] = max_val

4. Print dp[n] as the maximum revenue.

5. Set remaining_length = n.

6. While remaining_length > 0:
      Print cuts[remaining_length].
      remaining_length = 
          remaining_length - cuts[remaining_length].

7. Stop.

```

### Sample Output

```text
Enter rod length n: 8
Enter prices for pieces of length 1 to 8: 1 5 8 9 10 17 17 20

Maximum revenue = 22
Optimal piece lengths: 2 6

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the Dynamic Programming table construction:
*   **Outer Loop:** Iterates through rod length from $1$ to $n$, running $n$ times.
*   **Inner Loop:** Iterates through every possible cut from $1$ to $i$, taking on average $O(n)$ steps.

Multiplying the iterations of the two nested loops:
$$T(n) = \sum_{i=1}^{n} O(i) = O(1 + 2 + 3 + \cdots + n) = O\left(\frac{n(n+1)}{2}\right) = O(n^2)$$

*   **Reconstruction Phase:** The traceback loop takes $O(n)$ in the worst case, which does not change the overall complexity.

**Final Time Complexity:**
$$O(n^2)$$

### Conclusion

The Rod Cutting problem is solved efficiently using a bottom-up Dynamic Programming approach by storing the maximum revenue for every smaller rod length. The `cuts` array is additionally used to reconstruct and display the optimal cutting combination. The algorithm has a time complexity of $O(n^2)$.


