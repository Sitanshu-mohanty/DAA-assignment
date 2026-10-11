# Reorganize String at Distance $K$

## Problem Statement
Given a string $S$ and an integer $K$, reorganize the string such that any two identical characters are placed at least $K$ distance apart from each other. If no such reorganization is possible, the program returns an empty string to indicate failure. The problem is solved using a Greedy algorithm combined with a Max-Heap (Priority Queue) to always place the most frequent available character, and a waiting queue to enforce the minimum distance constraint.

---

## Algorithm
* Calculate the length of the string $n$.
* If the required distance $K \le 1$, return the original string immediately as no reorganization is necessary.
* Calculate the frequency of each character in the string using a frequency array of size $256$.
* Initialize a Max-Heap and insert all unique characters along with their frequencies.
* Allocate a queue array of size $K$ to act as a "cooling period" buffer for characters that have just been used.
* Iterate $n$ times to build the reorganized string:
  * Calculate the current cooldown index as `i % k`.
  * If the queue at this index holds a character with a remaining frequency greater than $0$, its cooling period is over; reinsert it into the Max-Heap.
  * If the Max-Heap is empty at this point, a valid character cannot be placed without violating the distance rule. Return an empty string (impossible).
  * Extract the character with the highest frequency from the Max-Heap.
  * Append this character to the result string, decrement its frequency, and store it in the queue at the current `i % k` index to start its cooling period.
* Null-terminate the result string, free the allocated queue memory, and return the reorganized string.

---

## Pseudocode

```text
REORGANIZE-STRING(s, k)

1. n = length of s
2. If k <= 1:
       Return s

3. Count frequencies of all characters in s.
4. Initialize an empty Max-Heap.
5. For each unique character ch:
       Insert (ch, freq) into Max-Heap.

6. queue = array of size k, initialized to empty elements
7. result = empty string of size n

8. For i = 0 to n - 1:
       index = i % k

       If queue[index].freq > 0:
           Insert queue[index] into Max-Heap
           queue[index].freq = 0

       If Max-Heap is empty:
           Return ""  

       current = extractMax(Max-Heap)
       result[i] = current.ch
       current.freq = current.freq - 1

       queue[index] = current

9. Return result

```

## Sample Output

```text
Enter the string S: aabbcc
Enter distance K: 3
Reorganized String: abcabc

```

## Time Complexity Analysis

To determine the time complexity, we evaluate the distinct phases of the algorithm:
* **Frequency Counting:** Iterating through the string of length $n$ takes $O(n)$ time.
* **Heap Initialization:** Inserting at most $256$ unique ASCII characters into the Max-Heap takes $O(C \log C)$ time, where $C \le 256$. Since $C$ is a constant, this takes $O(1)$ time.
* **String Construction:** The main loop runs $n$ times. Inside the loop, elements are inserted and extracted from the Max-Heap. The maximum size of the heap is $C$ ($256$). Each heap operation takes $O(\log C)$ time. Therefore, the loop takes $n \times O(\log C)$ time. Because $C$ is bound to a constant maximum of $256$, $O(\log C)$ is effectively $O(1)$.

Adding these together gives $O(n) + O(1) + O(n \log C)$, which simplifies linearly based on the length of the string.

**Final Time Complexity:**
$$O(n \log C) \approx O(n)$$
*(where $C$ is the size of the character set)*

---

## Conclusion

The Reorganize String problem is solved optimally using a Greedy approach augmented by a Max-Heap and a fixed-size circular queue. By prioritizing the most frequent characters and temporarily quarantining used characters based on distance $K$, the algorithm ensures a valid arrangement if one exists. The constant bound on the character set size ensures the heap operations do not degrade performance, maintaining an efficient overall time complexity of $O(n)$.

