# Candy Distribution Problem

## Problem Statement

Given $n$ children standing in a line, each assigned a rating value, the objective is to distribute candies to these children such that two conditions are met: every child receives at least one candy, and any child with a higher rating than an adjacent neighbor receives more candies than that neighbor. The program calculates and outputs the minimum total number of candies required to satisfy these rules. This is solved efficiently using a Greedy approach with a two-pass algorithm.

---

## Algorithm

* Read the number of children $n$ and validate that the input is greater than zero.
* Dynamically allocate memory for two integer arrays: `rating` to store the children's ratings, and `candy` to track the number of candies assigned to each child.
* Read the rating for each child into the `rating` array while simultaneously initializing every element in the `candy` array to $1$ (ensuring every child gets at least one candy).
* **Left-to-Right Pass:** Iterate through the array starting from the second child ($i = 1$) up to the last child ($n-1$). If the current child's rating is strictly greater than the left neighbor's rating (`rating[i] > rating[i - 1]`), assign the current child one more candy than the left neighbor (`candy[i] = candy[i - 1] + 1`).
* **Right-to-Left Pass:** Iterate backwards starting from the second-to-last child ($i = n - 2$) down to the first child ($0$). If the current child's rating is strictly greater than the right neighbor's rating (`rating[i] > rating[i + 1]`) and their currently assigned candies are less than or equal to the right neighbor's candies (`candy[i] <= candy[i + 1]`), update their candy count to be one more than the right neighbor's candy count (`candy[i] = candy[i + 1] + 1`).
* Iterate through the `candy` array one final time to compute the total sum of all candies distributed.
* Print the minimum number of candies required and free the allocated memory for both arrays.

---

## Pseudocode

```text
CANDY-DISTRIBUTION(rating, n)

1. Initialize candy array of size n.
2. For i = 0 to n - 1:
       candy[i] = 1

3. // Left-to-Right Pass
   For i = 1 to n - 1:
       If rating[i] > rating[i - 1]:
           candy[i] = candy[i - 1] + 1

4. // Right-to-Left Pass
   For i = n - 2 down to 0:
       If rating[i] > rating[i + 1] and candy[i] <= candy[i + 1]:
           candy[i] = candy[i + 1] + 1

5. total = 0
   For i = 0 to n - 1:
       total = total + candy[i]

6. Return total

```

## Sample Output

```text
Enter number of children: 3
Enter ratings:
1 0 2
Minimum number of candies = 5

```

## Time Complexity Analysis

To determine the overall time complexity, we analyze the sequential loops used in the algorithm:
* **Initialization Phase:** Reading the ratings and initializing the candy array to $1$ requires a single pass over $n$ elements, taking $O(n)$ time.
* **Left-to-Right Pass:** Comparing each child with their left neighbor requires a loop traversing $n-1$ elements, which takes $O(n)$ time.
* **Right-to-Left Pass:** Comparing each child with their right neighbor requires a loop traversing $n-1$ elements backward, which also takes $O(n)$ time.
* **Summation Phase:** A final loop to sum the $n$ elements in the candy array takes $O(n)$ time.

Since these are unnested, sequential operations, the total time is $O(n) + O(n) + O(n) + O(n) = O(n)$.

**Final Time Complexity:**
$$O(n)$$

---

## Conclusion

The Candy Distribution problem is solved elegantly using a two-pass Greedy strategy. By breaking the constraints into two separate local evaluations (one checking the left neighbor, the other checking the right), the algorithm prevents the need for nested comparisons or recalculations. This guarantees an optimal distribution with a highly efficient linear time complexity of $O(n)$.
