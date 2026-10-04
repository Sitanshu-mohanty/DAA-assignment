## Q1. Minimum Coin Change

### Problem Statement
Given an array of $n$ coin denominations and a target amount $V$, find the minimum number of coins required to make the target amount. An unlimited number of coins of each denomination is available. If the target amount cannot be formed using the given denominations, return $-1$. The program also identifies the coins used to obtain the minimum number of coins. This is implemented using Dynamic Programming.

### Algorithm
*   Read the number of coin denominations $n$, the coin values, and the target amount $V$.
*   Allocate the `dp` and `usedCoins` arrays dynamically.
*   Initialize `dp[0] = 0`, since zero coins are needed to form amount 0.
*   Initialize all other `dp` values to $V + 1$, which acts as an unreachable/infinite value.
*   For every amount from 1 to $V$, check every coin denomination.
*   If a coin can be used for the current amount, compare the current solution with `dp[i - coin] + 1`.
*   Store the smaller value in `dp[i]` and record that coin in `usedCoins[i]`.
*   After filling the table, check `dp[V]`.
*   If it is still $V + 1$, the target cannot be formed, so return -1.
*   Otherwise, reconstruct the selected coins by repeatedly subtracting `usedCoins[amount]` from the current amount.
*   Display the minimum number of coins and the coins used.

### Pseudocode

```text
MIN-COIN-CHANGE(coins, n, V)

1. Create arrays dp[0...V] and usedCoins[0...V].
2. Set dp[0] = 0.
3. Set usedCoins[0] = -1.

4. For i = 1 to V:
       dp[i] = V + 1
       usedCoins[i] = -1

5. For i = 1 to V:
       For j = 0 to n - 1:
           If coins[j] <= i:
               If dp[i - coins[j]] + 1 < dp[i]:
                   dp[i] = dp[i - coins[j]] + 1
                   usedCoins[i] = coins[j]

6. If dp[V] = V + 1:
       Return -1.

7. Otherwise:
       result = dp[V]

8. Set amount = V.

9. While amount > 0:
       Print usedCoins[amount]
       amount = amount - usedCoins[amount]

10. Return result.

```

### Sample Output

```text
Enter number of coin denominations: 3
Enter coin denominations: 1 5 6
Enter target amount V: 11

Minimum number of coins required = 2
Coins used: 5 6

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the bottom-up Dynamic Programming formulation:
*   **Outer Loop:** Iterates through every amount from $1$ to $V$, running $V$ times.
*   **Inner Loop:** Iterates through each of the $n$ coin denominations for every amount, running $n$ times.

Multiplying the iterations of the two nested loops:
$$T(n, V) = O(n \times V)$$

**Final Time Complexity:**
$$O(n \times V)$$

### Conclusion

The Minimum Coin Change problem is successfully solved using a bottom-up Dynamic Programming approach. The algorithm computes the optimal substructure by building up solutions for smaller amounts to determine the minimum coins needed for the target amount $V$, while successfully tracking the component coins. The time complexity of the algorithm is $O(n \times V)$.


