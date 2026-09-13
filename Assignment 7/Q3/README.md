### Problem Statement

Given $n$ disks and four pegs, move all the disks from the source peg to the destination peg using the minimum number of moves, following the rules of the Tower of Hanoi. The program uses Dynamic Programming to determine the optimal split of disks and recursively generates the sequence of moves.

### Algorithm

*   Read the number of disks $n$.
*   Initialize $dp[0] = 0$ and $dp[1] = 1$.
*   For every number of disks $i$ from 2 to $n$:
    *   Set $dp[i]$ to a very large value.
    *   Try every possible split $k$ from 1 to $i-1$.
    *   Calculate: $\text{moves} = 2(dp[k]) + 2^{(i-k)} - 1$
    *   If this value is smaller than the current $dp[i]$, update $dp[i]$ and store $k$ in $split[i]$.
*   The value $dp[n]$ gives the minimum number of moves.
*   Use `hanoi4()` recursively to generate the sequence of moves.
*   Use `hanoi3()` to solve the required three-peg subproblem.
*   Display the minimum number of moves and the sequence of moves.

### Pseudocode

```text
ALGORITHM RevePuzzle(n)

BEGIN
    dp[0] = 0
    dp[1] = 1

    FOR i = 2 TO n DO
        dp[i] = ∞
        split[i] = 1

        FOR k = 1 TO i-1 DO
            moves = 2 * dp[k] + 2^(i-k) - 1

            IF moves < dp[i] THEN
                dp[i] = moves
                split[i] = k
            END IF
        END FOR
    END FOR

    RETURN dp[n]
END ALGORITHM

```

### Sample Output

```text
Enter number of disks: 5

Minimum number of moves = 13

Sequence of Moves
Move disk 1 from A to D
Move disk 1 from A to B
Move disk 1 from D to B
Move disk 1 from A to D
Move disk 2 from A to C
Move disk 1 from D to C
Move disk 3 from A to D
Move disk 1 from C to A
Move disk 2 from C to D
Move disk 1 from A to D
Move disk 1 from B to A
Move disk 1 from B to D
Move disk 1 from A to D

```

### Time Complexity Calculation

The main DP section contains two nested loops:

```c
for (i = 2; i <= n; i++)
{
    for (k = 1; k < i; k++)
    {
        ...
    }
}

```
*   Outer loop $\rightarrow O(n)$
*   Inner loop $\rightarrow O(n)$

Therefore:
$$T(n) = O(n) \times O(n)$$
$$T(n) = O(n^2)$$

However, each iteration also calls `powerOfTwo(i - k)`, and `powerOfTwo()` itself takes $O(i-k)$ time because it contains a loop. 
Thus, the actual time complexity of the given code is:
$$O\left(\sum_{i=2}^{n}\sum_{k=1}^{i-1}(i-k)\right) = O(n^3)$$

**Final Time Complexity:**
$$O(n^3)$$

### Conclusion

The Reve’s Puzzle is successfully solved using Dynamic Programming and recursion. The program determines the optimal number of disks to split at each stage and then uses recursive functions to generate the minimum sequence of moves. For the given implementation, the DP calculation has a time complexity of $O(n^3)$ because the `powerOfTwo()` function itself takes $O(n)$ time. The program correctly computes the minimum moves and dynamically generates the sequence of steps for valid input values between 1 and 30 disks.
