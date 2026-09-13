### Problem Statement

Given $n$ matrices, find the minimum number of scalar multiplications required to multiply all the matrices. The program uses Dynamic Programming to find the optimal multiplication order and prints the corresponding parenthesization.

### Algorithm
*   Read the number of matrices $n$.
*   Read $n + 1$ dimensions into array $p$.
*   Initialize $m[i][i] = 0$ for every matrix.
*   Consider matrix chains of length from 2 to $n$.
*   For every chain $A_i$ to $A_j$, try every possible split position $k$.
*   Calculate the multiplication cost:
    $$m[i][k] + m[k+1][j] + p[i-1] \times p[k] \times p[j]$$
*   Store the minimum cost in $m[i][j]$ and the corresponding split position in $s[i][j]$.
*   Print $m[1][n]$ as the minimum number of scalar multiplications.
*   Use `printOrder()` and the $s$ table to print the optimal multiplication order.

### Pseudocode

```text
ALGORITHM MatrixChainOrder(p, n)
BEGIN
    IF n <= 0 OR n >= MAX THEN
        PRINT "Invalid number of matrices"
        STOP
    END IF

    FOR i = 1 TO n DO
        m[i][i] = 0
    END FOR

    FOR length = 2 TO n DO
        FOR i = 1 TO n - length + 1 DO
            j = i + length - 1
            k = i

            -- Calculate initial cost and store in m[i][j] and s[i][j]
            m[i][j] = infinity
            
            FOR k = i TO j - 1 DO
                cost = m[i][k] + m[k+1][j] + p[i-1] * p[k] * p[j]

                IF cost < m[i][j] THEN
                    m[i][j] = cost
                    s[i][j] = k
                END IF
            END FOR
        END FOR
    END FOR

    PRINT m[1][n]
    PRINT optimal multiplication order using printOrder()
END ALGORITHM

```

### Sample Output

```text
Enter number of matrices: 4
Enter 5 dimensions: 10 20 30 40 30

Minimum number of scalar multiplications = 30000
Optimal multiplication order = (((A1A2)A3)A4)

```

### Time Complexity Analysis

To establish a rigorous mathematical upper bound, we analyze the exact number of operations executed across the nested loops of the Dynamic Programming table construction for $n$ matrices.

**1. Loop Iteration Breakdown:**
*   **Outer Loop (`length`):** Iterates over the chain lengths from $2$ to $n$, running approximately $n$ times.
*   **Middle Loop (`i`):** Represents the starting index of the matrix chain, running $n - \text{length} + 1$ times for each chain length.
*   **Inner Loop (`k`):** Represents the split position within the current chain from $i$ to $j-1$, running roughly proportional to the current chain length.

**2. Summation Derivation:**
The total number of scalar multiplication cost evaluations is modeled by the triple summation:
$$T(n) = \sum_{\text{length}=2}^{n} \sum_{i=1}^{n-\text{length}+1} \sum_{k=i}^{i+\text{length}-2} 1$$

Evaluating this from the inside out:
*   The inner loop executes $\text{length} - 1$ times.
*   Summing this over the middle loop bounds yields a quadratic growth factor for each chain length.
*   Summing the outer loop from $2$ to $n$ evaluates to a cubic polynomial:
$$T(n) = \frac{n^3 - n}{6} = O(n^3)$$

**3. Additional Operations:**
*   The `printOrder()` function recursively traverses the optimal split table $s$ to reconstruct the parenthesization, requiring linear time $O(n)$.
*   This auxiliary reconstruction routine is completely dominated by the $O(n^3)$ cost matrix calculation.

**Final Time Complexity:**
$$O(n^3)$$

### Conclusion

The Matrix Chain Multiplication problem is successfully solved using Dynamic Programming. The program finds the minimum number of scalar multiplications by checking all possible split positions and displays the optimal parenthesization order. Through rigorous summation analysis, the time complexity of the algorithm is proven to be $O(n^3)$.
