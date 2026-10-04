## Q8. Optimal Binary Search Tree (OBST)

### Problem Statement
Given $n$ distinct keys with their successful search probabilities $p$ and unsuccessful search probabilities $q$ for dummy keys, construct an Optimal Binary Search Tree (OBST) having the minimum expected search cost. Also determine the optimal root key. This is implemented using Dynamic Programming.

### Algorithm
*   Read the number of distinct keys $n$.
*   Read the successful search probabilities $p[1...n]$ and unsuccessful search probabilities $q[0...n]$.
*   Create three tables:
    *   `e[i][j]` – minimum expected search cost.
    *   `w[i][j]` – total probability weight.
    *   `root[i][j]` – stores the optimal root key.
*   Initialize the empty subtrees using the dummy-key probabilities:
    $$e[i][i-1] = q[i-1], \quad w[i][i-1] = q[i-1]$$
*   Consider subtrees in increasing order of their length $L$.
*   For each interval $[i, j]$, calculate its total weight:
    $$w[i][j] = w[i][j-1] + p[j] + q[j]$$
*   Try every key $r$ from $i$ to $j$ as the root.
*   Calculate the cost for each possible root:
    $$t = e[i][r-1] + e[r+1][j] + w[i][j]$$
*   Select the root giving the minimum cost and store it in `root[i][j]`.
*   Finally, $e[1][n]$ gives the minimum expected search cost and `root[1][n]` gives the optimal root key.

### Pseudocode

```text
OPTIMAL-BST(p, q, n)

1. Create tables e, w, and root.

2. For i = 1 to n + 1:
      e[i][i-1] = q[i-1]
      w[i][i-1] = q[i-1]

3. For L = 1 to n:
      For i = 1 to n-L+1:
          j = i + L - 1
          e[i][j] = ∞
          w[i][j] = w[i][j-1] + p[j] + q[j]

          For r = i to j:
              t = e[i][r-1] + e[r+1][j] + w[i][j]

              If t < e[i][j]:
                  e[i][j] = t
                  root[i][j] = r

4. Print e[1][n] as the minimum expected search cost.

5. Print root[1][n] as the optimal root key.

6. Stop.

```

### Sample Output

```text
Enter number of keys n: 4
Enter successful search probabilities p[1...4]: 0.1 0.2 0.4 0.3
Enter unsuccessful search probabilities q[0...4]: 0.05 0.1 0.05 0.05 0.1

Minimum expected search cost = 2.15
Optimal root key index = 3

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the Dynamic Programming table construction:
*   **Outer Loop:** Iterates through subtree length $L$ from $1$ to $n$, running $n$ times.
*   **Middle Loop:** Iterates through starting index $i$ up to $n$ times.
*   **Inner Loop:** Iterates through each candidate root $r$ from $i$ to $j$, running up to $n$ times.

Multiplying the iterations of the three nested loops:
$$T(n) = O(n) \times O(n) \times O(n) = O(n^3)$$

**Final Time Complexity:**
$$O(n^3)$$

### Conclusion

The Optimal Binary Search Tree problem is solved using a dynamic programming approach by considering all possible roots for every subtree and selecting the one with the minimum expected search cost. The `root` table stores the optimal root for each subproblem, while `e` stores the corresponding minimum cost. The algorithm has a time complexity of $O(n^3)$.


