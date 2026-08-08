# Algorithm

## Optimized Bubble Sort

1. Generate a random array of size `n`.
2. Copy the same array into another array for fair comparison.
3. Repeat for each pass from `0` to `n - 2`:
   - Set a `swapped` flag to `0`.
   - Compare each pair of adjacent elements.
   - Increment the comparison counter.
   - If the elements are in the wrong order, swap them and set `swapped = 1`.
   - If no swaps occur in a pass, stop the algorithm because the array is already sorted.
4. Return the total number of comparisons.

---

## Normal Bubble Sort

1. Use the copied random array.
2. Perform exactly `n - 1` passes.
3. In each pass:
   - Compare every adjacent pair of elements.
   - Increment the comparison counter.
   - Swap the elements if they are in the wrong order.
4. Return the total number of comparisons.

---

## Simulation Steps

1. Define different input sizes: `100, 200, 300, 400, 500`.
2. Generate random numbers for each input size.
3. Copy the generated array for both sorting methods.
4. Execute the optimized bubble sort and record the number of comparisons.
5. Execute the normal bubble sort and record the number of comparisons.
6. Display the comparison counts in tabular form.
7. Plot the recorded values to compare the efficiency of both algorithms.

# Time Complexity

| Case | Optimized Bubble Sort | Normal Bubble Sort |
|------|------------------------|--------------------|
| Best Case | **O(n)** | **O(n²)** |
| Average Case | **O(n²)** | **O(n²)** |
| Worst Case | **O(n²)** | **O(n²)** |

**Space Complexity:** `O(1)` (for both versions)

# Conclusion

- The optimized bubble sort terminates early if the array becomes sorted before completing all passes, reducing the number of comparisons.
- The normal bubble sort always performs all `n - 1` passes, resulting in more comparisons even when the array is already sorted.
- For random data, both algorithms have an average time complexity of **O(n²)**, but the optimized version is generally more efficient due to early termination.
- <img width="1536" height="1024" alt="IMG-20260802-WA0003" src="https://github.com/user-attachments/assets/b861a478-e96b-4de5-9fc9-8bd992735350" />
