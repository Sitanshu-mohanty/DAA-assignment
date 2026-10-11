# Minimum Cost to Connect Sticks

## Problem Statement
Given $n$ sticks of various lengths, the objective is to connect them into a single stick with the minimum total cost. The cost of connecting two sticks is equal to the sum of their lengths. To minimize the cumulative cost, the optimal greedy strategy is to always connect the two shortest available sticks first. The program implements this strategy efficiently using a Min-Heap (Priority Queue) to continuously track and retrieve the smallest elements.

---

## Algorithm
* Read the number of sticks $n$ and ensure the input is valid (greater than zero).
* Dynamically allocate memory to store the stick lengths and read them into an array.
* Allocate a separate array of `long long` integers for the Min-Heap to prevent overflow during addition, and copy the initial stick lengths into it.
* Build the initial Min-Heap by calling `minHeapify` from the middle of the array down to the root.
* Initialize tracking variables: `size = n` and `total_cost = 0`.
* Loop while there is more than one stick in the heap (`size > 1`):
  * Extract the smallest stick `x` from the heap.
  * Extract the next smallest stick `y` from the heap.
  * Calculate the combined length: `sum = x + y`.
  * Add this sum to the running total cost.
  * Insert the newly formed stick (`sum`) back into the Min-Heap.
* Return the accumulated total cost.
* Print the result and free all dynamically allocated memory.

---

## Pseudocode

```text
MINIMUM-COST-STICKS(sticks, n)

1. Initialize heap of size n.
2. For i = 0 to n - 1:
       heap[i] = sticks[i]

3. For i = (n / 2) - 1 down to 0:
       minHeapify(heap, n, i)

4. size = n
   cost = 0

5. While size > 1:
       x = extractMin(heap, &size)
       y = extractMin(heap, &size)
       
       sum = x + y
       cost = cost + sum
       
       insert(heap, &size, sum)

6. Return cost

```

## Sample Output

```text
Enter number of sticks: 4
Enter stick lengths:
2 4 3 1
Minimum cost = 19

```

## Time Complexity Analysis

To determine the overall time complexity, we analyze the heap operations:
* **Heap Construction:** Building the initial Min-Heap from the array of size $n$ takes $O(n)$ time.   
* **Merging Phase:** The while loop runs exactly $n - 1$ times to merge all sticks into one.   
* **Heap Operations:** In each iteration, the algorithm performs two `extractMin` operations and one `insert` operation. Each of these individual heap operations takes $O(\log n)$ time in the worst case.   

Multiplying the loop iterations by the cost of the internal operations yields $(n - 1) \times O(\log n) = O(n \log n)$. Adding the initial heap construction gives $O(n) + O(n \log n)$, which simplifies to the dominant term.

**Final Time Complexity:**
$$O(n \log n)$$

---

## Conclusion

The Minimum Cost to Connect Sticks problem is solved optimally using a Greedy approach backed by a Min-Heap. By strictly merging the two smallest current sticks, the algorithm prevents larger lengths from being repeatedly added to the total cost. The use of a Min-Heap ensures that finding and inserting lengths remains highly efficient, resulting in an optimal time complexity of $O(n \log n)$.


