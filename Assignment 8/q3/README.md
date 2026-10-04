## Q3. Longest Common Subsequence

### Problem Statement
Given two sequences $X$ and $Y$ of lengths $m$ and $n$, find the Longest Common Subsequence (LCS) between them. The program should find the length of the LCS and reconstruct and print the actual LCS string. A subsequence maintains the relative order of elements but does not require them to be consecutive. This is implemented using Dynamic Programming.

### Algorithm
*   Read the two sequences $X$ and $Y$.
*   Find their lengths $m$ and $n$.
*   Dynamically create a two-dimensional DP table of size $(m + 1) \times (n + 1)$.
*   Initialize the first row and first column to 0.
*   Compare each character of $X$ with each character of $Y$.
*   If the characters are equal, set:
    $$dp[i][j] = dp[i-1][j-1] + 1$$
*   If the characters are different, take the maximum of the two possible previous values:
    $$dp[i][j] = \max(dp[i-1][j], dp[i][j-1])$$
*   After filling the table, $dp[m][n]$ gives the length of the LCS.
*   Start from $dp[m][n]$ and move backwards through the table.
*   If the current characters match, add the character to the LCS and move diagonally.
*   Otherwise, move to the cell having the larger value.
*   Continue until either sequence reaches its beginning.
*   Print the LCS length and the reconstructed LCS.

### Pseudocode

```text
LCS(X, Y, m, n)

1. Create a DP table dp[0...m][0...n].

2. Initialize:
       dp[i][0] = 0 for all i
       dp[0][j] = 0 for all j

3. For i = 1 to m:
       For j = 1 to n:
           If X[i-1] == Y[j-1]:
               dp[i][j] = dp[i-1][j-1] + 1
           Else:
               dp[i][j] = max(dp[i-1][j], dp[i][j-1])

4. Create an array lcs of size dp[m][n] + 1.

5. Set index = dp[m][n].
   Set lcs[index] = '\0'.

6. Set i = m and j = n.

7. While i > 0 and j > 0:
       If X[i-1] == Y[j-1]:
           lcs[index-1] = X[i-1]
           index = index - 1
           i = i - 1
           j = j - 1
       Else if dp[i-1][j] > dp[i][j-1]:
           i = i - 1
       Else:
           j = j - 1

8. Print dp[m][n] as the length of LCS.

9. Print lcs as the actual LCS.

```

### Sample Output

```text
Enter sequence X: ABCBDAB
Enter sequence Y: BDCABA

Length of Longest Common Subsequence = 4
Longest Common Subsequence = BCAB

```

### Time Complexity Analysis

To determine the time complexity, we analyze the nested loops used in the Dynamic Programming table construction:
*   **Outer Loop:** Iterates through sequence $X$ of length $m$, running $m$ times.
*   **Inner Loop:** Iterates through sequence $Y$ of length $n$, running $n$ times.

Multiplying the iterations of the two nested loops for the table filling phase:
$$T(m, n) = O(m \times n)$$

*   **Traceback Phase:** The reconstruction loop walks backwards from $(m, n)$ to $(0, 0)$, taking at most $O(m + n)$ time, which is strictly dominated by the $O(m \times n)$ DP table construction.

**Final Time Complexity:**
$$O(m \times n)$$

### Conclusion

The Longest Common Subsequence problem is successfully solved using a bottom-up Dynamic Programming approach. The algorithm constructs a 2D DP table to find the maximum matching subsequence length and subsequently backtracks through the table to reconstruct the actual sequence. The time complexity of the algorithm is $O(m \times n)$.
