### Problem Statement

Given $n$ switches initially in the ON state, turn all the switches OFF using the minimum number of moves, where each move toggles a switch according to the rules of the problem. The program uses recursive functions `turnOff()` and `turnOn()` to generate the sequence of moves and counts the total number of moves.

### Algorithm
*   Read the number of switches $n$.
*   Validate that $n$ is between 1 and 20.
*   Initialize all $n$ switches to 1 (ON).
*   Display the initial state.
*   Call `turnOff(n, n)` to recursively turn the switches OFF.
*   In `turnOff()`:
    *   Recursively process smaller switch groups.
    *   Toggle switch $n$ OFF.
    *   Use `turnOn()` to restore required switches.
    *   Continue recursively until all required switches are OFF.
*   Count every toggle using `moveCount`.
*   Display the final state and total number of moves.
*   Calculate and display the theoretical minimum.
*   Stop.

### Pseudocode

```text
ALGORITHM TurnOff(n, total)
BEGIN
    IF n = 0 THEN
        RETURN
    END IF

    IF n = 1 THEN
        switch[1] = OFF
        moveCount = moveCount + 1
        RETURN
    END IF

    TurnOff(n - 2, total)

    switch[n] = OFF
    moveCount = moveCount + 1

    TurnOn(n - 2, total)

    TurnOff(n - 1, total)
END ALGORITHM

```

```text
ALGORITHM TurnOn(n, total)
BEGIN
    IF n = 0 THEN
        RETURN
    END IF

    IF n = 1 THEN
        switch[1] = ON
        moveCount = moveCount + 1
        RETURN
    END IF

    TurnOn(n - 1, total)

    TurnOff(n - 2, total)

    switch[n] = ON
    moveCount = moveCount + 1

    TurnOn(n - 2, total)
END ALGORITHM

```

### Sample Output

```text
Enter number of switches: 4
Initial state: 1111

Move 1: Toggle S2 -> 1101
Move 2: Toggle S1 -> 1100
Move 3: Toggle S4 -> 0100
Move 4: Toggle S1 -> 0101
Move 5: Toggle S2 -> 0111
Move 6: Toggle S1 -> 0110
Move 7: Toggle S3 -> 0010
Move 8: Toggle S1 -> 0011
Move 9: Toggle S2 -> 0001
Move 10: Toggle S1 -> 0000
Final state:   0000

Total Moves = 10
Theoretical minimum = 10

```

### Time Complexity Analysis

Let $T(n)$ represent the total number of moves required to process $n$ switches. 
By analyzing the pseudocode for `TurnOff(n)`, we can break down the operations:
1. `TurnOff(n - 2)` requires $T(n-2)$ moves.
2. Toggling switch $n$ requires $1$ move.
3. `TurnOn(n - 2)` requires $T(n-2)$ moves (by symmetry, turning switches on takes the same number of moves as turning them off).
4. `TurnOff(n - 1)` requires $T(n-1)$ moves.

Summing these together gives the following linear recurrence relation:
$$T(n) = T(n-1) + 2T(n-2) + 1$$

To find the asymptotic time complexity, we solve the characteristic equation of the homogeneous recurrence relation $T(n) - T(n-1) - 2T(n-2) = 0$:
$$r^2 - r - 2 = 0$$

Factoring the polynomial yields:
$$(r - 2)(r + 1) = 0$$

The roots of the characteristic equation are $r_1 = 2$ and $r_2 = -1$. 
The general solution takes the form:
$$T(n) = A(2^n) + B(-1)^n + C$$

Because the dominant term in this closed-form expression is $2^n$, the number of recursive operations grows exponentially based on powers of 2.

**Final Time Complexity:**
$$O(2^n)$$

### Conclusion

The Security Switches problem is successfully solved using recursive functions. The program starts with all switches ON and systematically toggles them according to the problem's rules to reach the final state where all switches are OFF. It accurately tracks the total number of moves and validates them against the theoretical minimum. Through mathematical analysis of the recurrence relation, the recursive approach is proven to have an exponential time complexity of $O(2^n)$.

