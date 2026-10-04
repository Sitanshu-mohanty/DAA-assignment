## Q6. Edit Distance

### Problem Statement
Given two strings $A$ and $B$ of lengths $m$ and $n$, find the minimum number of operations required to transform string $A$ into string $B$. The allowed operations are insertion, deletion, and substitution of a character. The program should also print the traceback information showing the sequence of matches, substitutions, deletions, and insertions used to transform $A$ into $B$. This is implemented using Dynamic Programming.

### Algorithm
*   Read the two strings $A$ and $B$.
*   Find their lengths $m$ and $n$.
*   Create a two-dimensional DP table of size $(m + 1) \times (n + 1)$.
*   Initialize the first column: $dp[i][0] = i$, because converting the first $i$ characters of $A$ into an empty string requires $i$ deletions.
*   Initialize the first row: $dp[0][j] = j$, because converting an empty string into the first $j$ characters of $B$ requires $j$ insertions.
*   Compare every character of $A$ with every character of $B$.
*   If the characters are equal, copy the diagonal value:
    $$dp[i][j] = dp[i-1][j-1]$$
*   If the characters are different, consider insertion, deletion, and substitution:
    $$dp[i][j] = 1 + \min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])$$
*   After filling the table, $dp[m][n]$ gives the minimum edit distance.
*   Start from $dp[m][n]$ and trace backwards through the table.
*   If the characters match, record a Match and move diagonally.
*   If the diagonal value represents a substitution, record Substitute and move diagonally.
*   If the upper value represents a deletion, record Delete and move upward.
*   Otherwise, record Insert and move left.
*   Print the edit distance and traceback operations.

### Pseudocode

```text
EDIT-DISTANCE(A, B, m, n)

1. Create a DP table dp[0...m][0...n].

2. Initialize:
       dp[i][0] = i for i = 0 to m
       dp[0][j] = j for j = 0 to n

3. For i = 1 to m:
       For j = 1 to n:

           If A[i-1] == B[j-1]:
               dp[i][j] = dp[i-1][j-1]

           Else:
               dp[i][j] = 
                   1 + min(
                       dp[i-1][j],
                       dp[i][j-1],
                       dp[i-1][j-1]
                   )

4. Set editDistance = dp[m][n].

5. Set i = m and j = n.

6. While i > 0 OR j > 0:

       If i > 0 AND j > 0 AND A[i-1] == B[j-1]:
           Print Match
           i = i - 1
           j = j - 1

       Else if i > 0 AND j > 0 AND 
               dp[i][j] = dp[i-1][j-1] + 1:
           Print Substitute
           i = i - 1
           j = j - 1

       Else if i > 0 AND 
               dp[i][j] = dp[i-1][j] + 1:
           Print Delete
           i = i - 1

       Else:
           Print Insert
           j = j - 1

7. Print editDistance.

```

### Sample Output

```text
Enter string A: kitten
Enter string B: sitting

Minimum Edit Distance = 3
Traceback Operations:
Substitute 'k' with 's'
Match 'i'
Match 't'
Match 't'
Substitute 'e' with 'i'
Match 'n'
Insert 'g'

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the Dynamic Programming table construction:
*   **Outer Loop:** Iterates through string $A$ of length $m$, running $m$ times.
*   **Inner Loop:** Iterates through string $B$ of length $n$, running $n$ times.

Multiplying the iterations of the two nested loops for table filling:
$$T(m, n) = O(m \times n)$$

*   **Traceback Phase:** The reconstruction loop walks backwards from $(m, n)$ to $(0, 0)$, taking at most $O(m + n)$ time, which is strictly dominated by the $O(m \times n)$ DP table construction.

**Final Time Complexity:**
$$O(m \times n)$$

### Conclusion

The Edit Distance problem is successfully solved using a bottom-up Dynamic Programming approach. The algorithm constructs a 2D DP table to find the minimum cost of transformation through insertions, deletions, and substitutions, while tracking path operations for full sequence reconstruction. The time complexity of the algorithm is $O(m \times n)$.


