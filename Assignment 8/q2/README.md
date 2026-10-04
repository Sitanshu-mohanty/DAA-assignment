## Q2. Coin Change Combinations

### Problem Statement
Given an array of $n$ distinct coin denominations and a target amount $V$, find the total number of distinct combinations of coins that can be used to obtain the target amount. An unlimited number of coins of each denomination is available, and the order of coins does not matter. The program uses Dynamic Programming to calculate the total number of possible combinations.

### Algorithm
*   Read the number of coin denominations $n$, the coin values, and the target amount $V$.
*   Create a DP array `dp` of size $V + 1$ and initialize all elements to $0$.
*   Set `dp[0] = 1`, since there is exactly one way to make the amount 0 (by choosing no coins).
*   Iterate through each coin denomination from $0$ to $n - 1$:
    *   For each coin, iterate through all amounts $j$ from the coin's value up to the target amount $V$.
    *   Update the number of ways to form amount $j$ by adding the number of ways to form $j - \text{coin}$ (`dp[j] = dp[j] + dp[j - coins[i]]`).
*   Retrieve the result stored in `dp[V]`.
*   Display the total number of distinct combinations.

### Pseudocode

```text
COUNT-WAYS(coins, n, V)

1. Create an array dp[0...V].
2. Initialize all elements of dp to 0.
3. Set dp[0] = 1.

4. For i = 0 to n - 1:
       For j = coins[i] to V:
           dp[j] = dp[j] + dp[j - coins[i]]

5. Set result = dp[V].

6. Return result.

```

### Sample Output

```text
Enter number of coin denominations: 3
Enter coin denominations: 1 2 3
Enter target amount V: 4

Total number of distinct combinations = 4

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the Dynamic Programming formulation:
*   **Outer Loop:** Iterates through each of the $n$ coin denominations, running $n$ times.
*   **Inner Loop:** Iterates from the coin value up to the target amount $V$, running up to $V$ times for each coin.

Multiplying the iterations of the two nested loops:
$$T(n, V) = O(n \times V)$$

**Final Time Complexity:**
$$O(n \times V)$$

### Conclusion

The Coin Change Combinations problem is successfully solved using a bottom-up Dynamic Programming approach. By building up the solution iteratively for each coin denomination, the algorithm avoids overcounting permutations and accurately computes the total number of distinct combinations to form the target amount $V$. The time complexity of the algorithm is $O(n \times V)$.



