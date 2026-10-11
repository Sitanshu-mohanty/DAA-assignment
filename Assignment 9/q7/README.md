# Minimize Deviation in Array

## Problem Statement
Given an array of $n$ elements, the goal is to minimize the deviation, which is defined as the difference between the maximum and minimum elements in the array. You are allowed to perform two operations any number of times: multiply an odd element by $2$, or divide an even element by $2$. To simplify the problem, the algorithm first maximizes all odd numbers by multiplying them by $2$, converting the problem into a one-way reduction where elements can only be divided by $2$. The algorithm then uses a Max-Heap to repeatedly extract the maximum even element, divide it by $2$, and update the minimum deviation.

---

## Algorithm
* Read the number of elements $n$ and validate the input.
* Dynamically allocate memory for an array to act as the Max-Heap.
* Initialize `minValue` to the maximum possible long long integer (`LLONG_MAX`).
* Read each element of the array:
  * If the element is odd, multiply it by $2$ (this ensures we only need to decrease values from this point forward).
  * Insert the element into the heap array.
  * Update the global `minValue` if the current element is smaller.
* Build a valid Max-Heap from the array by calling `maxHeapify` from the middle of the array down to the root.
* Initialize `minDeviation` as the difference between the maximum element (`heap[0]`) and the current `minValue`.
* Loop while the maximum element in the heap (`heap[0]`) is even:
  * Extract the maximum element from the heap and divide it by $2$.
  * Update the `minValue` if this newly halved value is smaller than the current `minValue`.
  * Insert the halved value back into the Max-Heap.
  * Calculate the `currentDeviation` as `heap[0] - minValue`.
  * Update `minDeviation` if the `currentDeviation` is smaller.
* Print the minimized deviation and free the allocated memory.

---

## Pseudocode

```text
MINIMIZE-DEVIATION(arr, n)

1. Initialize heap of size n.
2. minValue = infinity

3. For i = 0 to n - 1:
       value = arr[i]
       If value is odd:
           value = value * 2
       
       heap[i] = value
       
       If value < minValue:
           minValue = value

4. For i = (n / 2) - 1 down to 0:
       maxHeapify(heap, n, i)

5. minDeviation = heap[0] - minValue

6. While heap[0] % 2 == 0:
       maxValue = extractMax(heap, &n)
       value = maxValue / 2
       
       If value < minValue:
           minValue = value
           
       insert(heap, &n, value)
       
       currentDeviation = heap[0] - minValue
       If currentDeviation < minDeviation:
           minDeviation = currentDeviation

7. Return minDeviation

```

## Sample Output

```text
Enter number of elements: 4
Enter elements:
1 2 3 4
Minimum deviation = 1

```

## Time Complexity Analysis

To determine the time complexity, we analyze the heap operations and division limits:
* **Initialization Phase:** Multiplying odd numbers by $2$, tracking the minimum value, and building the Max-Heap takes $O(n)$ time.
* **Reduction Loop:** Each even number in the heap can be divided by $2$ at most $\log M$ times (where $M$ is the maximum value in the array). Across $n$ elements, the maximum number of divisions is bounded by $O(n \log M)$.
* **Heap Operations:** In each iteration of the while loop, an element is extracted and re-inserted, taking $O(\log n)$ time per operation.
* Combining these bounds, the total time spent in the reduction loop is $O(n \log M \log n)$.
* **Space Complexity:** $O(n)$ auxiliary space is required for the heap array.

**Final Time Complexity:**
$$O(n \log M \log n)$$
*(where $M$ is the maximum value in the array)*

---

## Conclusion

The Minimize Deviation in Array problem is efficiently solved using a Greedy approach combined with a Max-Heap. By transforming odd numbers through multiplication and restricting the problem to a one-way division reduction, the algorithm systematically narrows the gap between the maximum and minimum elements. The time complexity is $O(n \log M \log n)$ and the space complexity is $O(n)$.
