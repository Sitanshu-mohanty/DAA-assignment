# Shortest Common Superstring (Greedy Approach)

## Problem Statement
Given a set of $n$ strings, the objective is to find a single string (the shortest common superstring) that contains every given string as a substring. Because the general problem is NP-hard, a common heuristic is the greedy approach: it repeatedly selects the pair of strings with the maximum overlap (where a suffix of one string matches a prefix of another), merges them, and repeats the process until only a single string remains. While efficient, the greedy strategy provides an approximation guarantee rather than an absolute optimal solution.

---

## Algorithm
* Read the number of strings $n$ and validate that the input is greater than zero.
* Read all $n$ strings into memory.
* Loop while there is more than one string remaining in the collection ($n > 1$):
  * Initialize `maxOverlap = -1` to track the best overlap found in the current iteration.
  * Iterate through every ordered pair of distinct strings $(i, j)$.
  * Calculate the maximum overlap between the suffix of string $i$ and the prefix of string $j$.
  * If the calculated overlap exceeds `maxOverlap`, update `maxOverlap`, `bestI`, and `bestJ`.
  * Merge the strings at `bestI` and `bestJ` using the found overlap.
  * Remove the two original strings from the set and insert the newly merged string.
  * Decrease the active string count $n$ by $1$.
* Display the final greedy superstring and its total length.

---

## Pseudocode

```text
START

Read n

Read n strings

WHILE n > 1

    maxOverlap = -1

    FOR every ordered pair (i, j)

        IF i is not equal to j

            Find overlap between string i and string j

            IF overlap > maxOverlap
                maxOverlap = overlap
                bestI = i
                bestJ = j

    Merge bestI and bestJ using maxOverlap

    Remove bestI and bestJ

    Insert merged string

    Decrease n by 1

Display final superstring
Display its length

STOP

```

## Sample Output

```text
Enter number of strings: 4
Enter string 1: ABC
Enter string 2: BCADE
Enter string 3: DEFG
Enter string 4: FGHI

Merging: "ABC" + "BCADE" (Overlap: 2)
Merged String: "ABCADE"

Merging: "ABCADE" + "DEFG" (Overlap: 2)
Merged String: "ABCADEFG"

Merging: "ABCADEFG" + "FGHI" (Overlap: 2)
Merged String: "ABCADEFGHI"

Final Greedy Superstring: ABCADEFGHI
Length: 11

```

## Time Complexity Analysis

To determine the overall time complexity, we analyze the pair-wise comparisons and merge iterations:
* **Reduction Loop:** The main loop runs $n - 1$ times, as one string is eliminated in each iteration.
* **Pair Evaluation:** In each iteration, the algorithm compares all ordered pairs of strings. With $n$ strings, there are $O(n^2)$ pairs to check.
* **Overlap Calculation:** Computing the maximum overlap between two strings of maximum length $L$ takes $O(L^2)$ time.
* Combining these operations, each iteration takes $O(n^2 \cdot L^2)$ time, leading to a total time complexity of $O(n^3 \cdot L^2)$.

**Final Time Complexity:**
$$O(n^3 \cdot L^2)$$
*(where $n$ is the number of strings and $L$ is the maximum length of a string)*

---

## Conclusion

The Greedy approach to the Shortest Common Superstring problem provides a practical heuristic for combining multiple substrings into a unified superstring by iteratively merging the pair with the highest overlap. While it executes efficiently in polynomial time compared to exponential exact algorithms, it does not always yield the absolute shortest possible superstring. Nonetheless, it serves as a powerful approximation technique in applications like DNA sequence assembly.
