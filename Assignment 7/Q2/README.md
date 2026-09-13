### Problem Statement

Given `eggs` eggs and `floors` floors, determine the minimum number of egg droppings required in the worst case to find the critical floor from which an egg will break. The problem is solved using Dynamic Programming.

### Algorithm
*   Read the number of eggs and floors.
*   Create a DP table `dp[eggs+1][floors+1]`.
*   Initialize `dp[e][0] = 0` for all eggs.
*   Initialize `dp[e][1] = 1` for all eggs.
*   Initialize `dp[1][f] = f` for all floors.
*   For each number of eggs from 2 to `eggs`:
    *   For each number of floors from 2 to `floors`:
        *   Try dropping the egg from every floor `x`.
        *   Calculate the cases where the egg breaks and survives.
        *   Take the worst case using `max()`.
        *   Store the minimum number of drops.
*   Return `dp[eggs][floors]`.
*   Display the minimum number of droppings.

### Pseudocode

```text
ALGORITHM EggDrop(eggs, floors)

BEGIN
    Create dp[eggs + 1][floors + 1]

    FOR e = 0 TO eggs DO
        dp[e][0] = 0
    END FOR

    FOR e = 1 TO eggs DO
        dp[e][1] = 1
    END FOR

    FOR f = 0 TO floors DO
        dp[1][f] = f
    END FOR

    FOR e = 2 TO eggs DO
        FOR f = 2 TO floors DO
            dp[e][f] = ∞

            FOR x = 1 TO f DO
                breaks = dp[e-1][x-1]
                survives = dp[e][f-x]
                drops = 1 + max(breaks, survives)

                IF drops < dp[e][f] THEN
                    dp[e][f] = drops
                END IF
            END FOR
        END FOR
    END FOR

    RETURN dp[eggs][floors]
END ALGORITHM

```

### Sample Output

```text
Enter number of eggs: 2
Enter number of floors: 10

Minimum number of droppings = 4

```

### Time Complexity Calculation

Let:
*   $E$ = number of eggs
*   $F$ = number of floors

The main DP calculation contains three nested loops:

```c
for (e = 2; e <= eggs; e++)         
{
    for (f = 2; f <= floors; f++)   
    {
        for (x = 1; x <= f; x++)    
        {
            ...
        }
    }
}

```
*   Outer loop $\rightarrow O(E)$
*   Middle loop $\rightarrow O(F)$
*   Inner loop $\rightarrow O(F)$

Multiplying them:
$$T(E,F) = O(E) \times O(F) \times O(F)$$
$$T(E,F) = O(EF^2)$$

**Final Time Complexity:**
$$O(EF^2)$$

The initialization loops take only $O(E + F)$, which is dominated by the main DP calculation, so the overall complexity remains:
$$O(EF^2)$$

### Conclusion

The Super Egg Testing problem is successfully solved using Dynamic Programming. By considering both possible outcomes of each egg dropping and selecting the minimum number of drops required in the worst case, the program determines the optimal solution. The algorithm has a time complexity of $O(EF^2)$.
