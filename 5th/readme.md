## Algorithm

1. Start the program.
2. Read the size of the array `n`.
3. Input the array elements containing consecutive `0`s followed by consecutive `1`s.
4. Initialize two variables:
   - `low = 0`
   - `high = n - 1`
5. Repeat while `low <= high`:
   - Calculate the middle index:
     ```
     mid = (low + high) / 2
     ```
   - If `A[mid] == 0`:
     - If `mid` is the last index or `A[mid + 1] == 1`, then the transition point is found. Return `mid + 1`.
     - Otherwise, search the right half by setting `low = mid + 1`.
   - Otherwise (`A[mid] == 1`):
     - Search the left half by setting `high = mid - 1`.
6. If no transition point is found, return `-1`.
7. Display the transition index if found; otherwise, print "No transition found."
8. End the program.

---

## Time Complexity

- **Best Case:**
  ```
  O(1)
  ```
  The transition is found in the first comparison.

- **Worst Case:**
  ```
  O(log n)
  ```
  Binary Search halves the search space in every iteration.

- **Average Case:**
  ```
  O(log n)
  ```
