# Element Uniqueness

## Algorithm
1. Read the number of elements `n`.
2. Input the `n` elements into an array.
3. Compare each element with every element that comes after it:
   - For each index `i` from `0` to `n-2`:
     - For each index `j` from `i+1` to `n-1`:
       - If `a[i] == a[j]`, a duplicate is found.
       - Print the duplicate element and terminate the program.
4. If no duplicate is found after all comparisons, print **"No duplicates found."**

---

## Time Complexity
- **Best Case:** `O(1)` (Duplicate found in the first comparison)
- **Worst Case:** `O(n²)` (No duplicates or duplicate found at the end)
- **Average Case:** `O(n²)`

**Conclusion:**  
This brute-force approach works well for small input sizes. However, for sufficiently large values of `n`, its quadratic time complexity (`O(n²)`) makes it inefficient because the number of comparisons increases rapidly.