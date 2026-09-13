### Problem Statement

Given the birth and death years of $n$ scientists, determine the year in which the maximum number of scientists were alive at the same time. The program uses a sweep-line/event-based approach. Each birth is treated as a $+1$ event and each death as a $-1$ event. The events are sorted by year, and the number of scientists alive is tracked to find the maximum.

### Algorithm
*   Read the number of scientists $n$.
*   Create an event array of size $2n$.
*   For each scientist:
    *   Store the birth year as a $+1$ event.
    *   Store the death year as a $-1$ event.
*   Sort all $2n$ events by year using `qsort()`.
*   Traverse the sorted events:
    *   Add the event type to `current`.
    *   If `current` is greater than `maximum`, update `maximum` and store the corresponding year.
*   Display the year with the maximum number of scientists alive and the maximum count.
*   Free the allocated memory.

### Pseudocode

```text
ALGORITHM BestTimeToBeAlive(n)

BEGIN
    Create an array events of size 2n

    FOR i = 0 TO n-1 DO
        READ birth, death

        events[2i].year = birth
        events[2i].type = +1

        events[2i+1].year = death
        events[2i+1].type = -1
    END FOR

    Sort events according to year

    current = 0
    maximum = 0
    bestYear = 0

    FOR i = 0 TO 2n-1 DO
        current = current + events[i].type

        IF current > maximum THEN
            maximum = current
            bestYear = events[i].year
        END IF
    END FOR

    PRINT bestYear
    PRINT maximum
END ALGORITHM

```

### Sample Output

```text
Enter number of scientists: 4
Enter birth and death year of scientist 1: 1900 1950
Enter birth and death year of scientist 2: 1910 1960
Enter birth and death year of scientist 3: 1920 1970
Enter birth and death year of scientist 4: 1930 1980

Best time to be alive: 1930
Maximum number of scientists alive: 4

```

### Time Complexity Analysis

To determine the precise time complexity, we analyze the algorithm in three distinct phases as a function of the number of scientists $n$:

**1. Event Creation Phase:**
The program processes $n$ scientists and creates 2 events (birth and death) for each.
*   Time taken: $O(n)$

**2. Sorting Phase:**
The program sorts the array of $2n$ events using a comparison-based sorting algorithm (`qsort`). The time complexity of sorting $k$ elements is $O(k \log k)$. Substituting $k = 2n$:
$$O(2n \log(2n)) = O(2n(\log n + \log 2))$$
Since constants and lower-order terms are ignored in asymptotic notation, this simplifies to:
*   Time taken: $O(n \log n)$

**3. Traversal Phase:**
The program linearly scans the sorted array of $2n$ events exactly once.
*   Time taken: $O(2n) = O(n)$

**Total Time Function $T(n)$:**
Summing the phases gives the total time function:
$$T(n) = O(n) + O(n \log n) + O(n)$$

Because the $n \log n$ term grows faster than the linear $n$ terms, it dominates the time complexity.

**Final Time Complexity:**
$$O(n \log n)$$

### Conclusion

The Best Time to Be Alive problem is successfully solved using an event-based (sweep-line) approach. Birth and death years are converted into discrete events, sorted chronologically, and sequentially processed to determine the year with the maximum number of scientists alive simultaneously. The algorithm has an optimal time complexity of $O(n \log n)$, which is primarily bounded by the sorting phase of the $2n$ events.

