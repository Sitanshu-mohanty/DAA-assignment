## Time-Decaying Fractional Knapsack Problem

### Problem Statement
Given $n$ items, each with a value, weight, and decay rate, and a knapsack of capacity $W$, maximize the total effective value. Unlike the standard fractional knapsack problem, the effective value per unit weight (density) of an item decreases dynamically over time. The current density of an item is calculated as its initial density minus the product of its decay rate and the elapsed time ($\text{value} / \text{weight} - \text{decay} \times \text{time}$). As items are placed in the knapsack, the elapsed time advances by the amount of weight taken. The program should output the selection sequence, weight taken, and the maximum effective value. This is solved using a Greedy approach.

### Algorithm

* Read the number of items $n$ and dynamically allocate memory to store their properties.
* For each item, read its value, weight, and decay rate.
* Read the total knapsack capacity $W$.
* Initialize tracking variables: `time = 0.0`, `remaining = W`, and `totalValue = 0.0`.
* Loop while the remaining capacity is greater than $0$ (specifically, $> 1e-9$):
  * Initialize variables to find the best available item (`best = -1`, `bestDensity = -1e100`).
  * Iterate through all items that still have available weight (`weight > 1e-9`).
  * Calculate the current effective density for each item: `(value / weight) - (decay * time)`.
  * Identify the item with the highest current effective density.
  * If no valid item is found, break the loop.
  * Determine the weight to take, which is the minimum of the selected item's remaining weight and the knapsack's `remaining` capacity.
  * Calculate the fraction of the item taken and its value contribution (`taken * bestDensity`).
  * Print the selection metrics for the current step.
  * Update the overall state: increase `totalValue` by the contribution, advance `time` by the weight taken, decrease the remaining knapsack capacity, and deduct the taken weight from the selected item's available weight.
* Print the maximum effective value and free the allocated memory.

### Pseudocode

```text

FRACTIONAL-KNAPSACK-DETERIORATION(items, n, W)

1. Read n items (value, weight, decay rate).
2. Read capacity W.
3. Initialize:
      time = 0.0
      remaining = W
      totalValue = 0.0

4. While remaining > 1e-9:
      best_item_index = -1
      best_density = -infinity

      For i = 0 to n - 1:
          If items[i].weight > 1e-9:
              current_density = (items[i].value / items[i].weight) - (items[i].decay * time)
              
              If current_density > best_density:
                  best_density = current_density
                  best_item_index = i

      If best_item_index == -1:
          Break

      If items[best_item_index].weight <= remaining:
          taken = items[best_item_index].weight
      Else:
          taken = remaining

      fraction = taken / items[best_item_index].weight
      contribution = taken * best_density

      Print Item, Fraction, Weight Taken, Time, Density, Value

      totalValue = totalValue + contribution
      time = time + taken
      remaining = remaining - taken
      items[best_item_index].weight = items[best_item_index].weight - taken

5. Print totalValue

```

### Sample Output

```text

Enter number of items: 3
Enter value, weight and decay rate for each item:
Item 1: 60 10 0.1
Item 2: 100 20 0.2
Item 3: 120 30 0.1
Enter knapsack capacity: 50

Selected items:
Item    Fraction        Weight Taken    Time            Density         Value
1       1.0000          10.0000         0.0000          6.0000          60.0000
2       1.0000          20.0000         10.0000         3.0000          60.0000
3       0.6667          20.0000         30.0000         1.0000          20.0000

Maximum effective value = 140.0000

```

### Time Complexity Analysis

To determine the time complexity, we analyze the repeated selection process:
* **Selection Phase:** In each iteration, the program scans all $n$ items to find the item with the highest current effective density. This scan takes $O(n)$ time.
* In the worst case, items may be processed or partially processed across multiple iterations.
* Therefore, if the selection process requires up to $n$ iterations, the total time complexity is:
  $$T(n) = O(n \times n)$$
  $$O(n^2)$$
* The effective density calculation itself takes constant time, $O(1)$, for each item.

**Final Time Complexity:**
$$O(n^2)$$

### Conclusion

The Fractional Knapsack problem with deterioration rate is successfully solved using a greedy approach. At each step, the item with the highest current effective density is selected, allowing either the complete item or a fraction of it to be placed in the knapsack. Since the effective density changes with time according to the deterioration rate, it is recalculated before every selection. The overall time complexity of the implemented approach is $O(n^2)$.
