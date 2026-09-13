### Problem Statement

Given an equilateral triangle formed by closely packed identical coins, with the centers of the coins positioned on an equilateral triangular lattice, the triangle consists of $n$ rows of coins. The task is to invert the triangle (turn it upside down) using the minimum possible number of moves. 

In each move, only one coin can be slid from its current position to a new position. Design an algorithm to determine the minimum number of moves required to invert the coin triangle, derive a compact formula for the minimum number of moves, and implement the algorithm in C to analyze its complexity.

### Compact Formula

For $n$ rows, the total number of coins is the sum of the first $n$ natural numbers:
$$\text{Total Coins}=1+2+3+\dots+n=\frac{n(n+1)}{2}$$

The program calculates the minimum number of moves by dividing the total number of coins by 3:
$$\text{Minimum Moves}=\left\lfloor\frac{\text{Total Coins}}{3}\right\rfloor$$

Substituting the total coins formula gives the final compact equation:
$$\text{Minimum Moves}=\left\lfloor\frac{n(n+1)}{6}\right\rfloor$$

*Note: In C, standard integer division performs this floor operation automatically.*

## Algorithm: Invert the Coin Triangle

*   **Start.**
*   Read the number of rows $n$.
*   Check whether the input is a valid integer. If $n \le 0$, display an invalid-input message and stop.
*   Calculate the total number of coins using:
    $$\text{totalCoins} = \frac{n(n+1)}{2}$$
*   Calculate the minimum number of moves using integer division:
    $$\text{moves} = \frac{\text{totalCoins}}{3}$$
*   Display $n$, total number of coins, and minimum number of moves.
*   **Stop.**

## Pseudocode

```text
ALGORITHM MinimumMoves(n)
BEGIN
    totalCoins = n * (n + 1) / 2
    moves = totalCoins / 3
    RETURN moves
END

```
### Sample Output

```text
Enter number of rows in the triangle: 6
Number of rows in the coin triangle = 6
Total number of coins = 21
Minimum moves for inverting the coin triangle = 7

```

### Time Complexity

| Operation | Time Complexity |
| :--- | :--- |
| **Read input $n$** | $O(1)$ |
| **Calculate total number of coins** | $O(1)$ |
| **Calculate minimum moves** | $O(1)$ |
| **Display the results** | $O(1)$ |

**Overall Time Complexity: $$O(1)$$**

### Conclusion

The program successfully determines the minimum number of moves required to invert an $n$-row coin triangle using the compact mathematical formula. It calculates the total number of coins as $\frac{n(n+1)}{2}$ and then determines the minimum moves by dividing the total number of coins by $3$. The algorithm is efficient, requiring $O(1)$ time complexity.




