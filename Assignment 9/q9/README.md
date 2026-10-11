# Optimal Alphabetic Binary Tree (Hu-Tucker Algorithm)

## Problem Statement
Given a sequence of $n$ weights, the objective is to construct an optimal alphabetic binary tree that minimizes the total weighted path length. Unlike standard Huffman coding, an alphabetic tree must strictly maintain the left-to-right order of the given sequence at its leaf nodes. The provided code implements the combination phase of the Hu-Tucker algorithm using a Greedy approach. It selectively merges "compatible" pairs of nodes—two nodes are considered compatible if no unmerged leaf nodes exist between them in the active sequence. By iteratively merging the compatible pair with the minimum combined weight, the algorithm determines the optimal structural depths for the leaves and computes the minimal weighted path cost.

---

## Algorithm
* Read the number of weights $n$ and validate the input.
* Dynamically allocate memory for an array of nodes (size $2n - 1$) and a `seq` array (size $n$) to track the actively available nodes.
* Initialize the first $n$ elements in the `nodes` array as leaf nodes (`is_leaf = 1`), assign their read weights, set their parent to `-1`, and initialize the `seq` array with their starting indices.
* Loop while there is more than one active node left in the sequence (`count > 1`):
  * Iterate through all possible pairs of indices `(a, b)` in the current active sequence.
  * Check for compatibility: a pair is compatible if all nodes situated between `a` and `b` in the sequence are internal nodes (`is_leaf == 0`).
  * Identify the compatible pair that produces the minimum combined weight.
  * Create a new internal node representing the merged pair: assign the combined weight, set `is_leaf = 0`, and set it as the parent for the two merged nodes.
  * Update the active sequence: replace the node at index `best_a` with the new internal node, and remove the node at `best_b` by shifting all subsequent elements to the left.
  * Decrement the active count.
* Once reduced to a single root, calculate the depth of each original leaf node by traversing its parent pointers upward.
* Compute the total weighted path length by summing the product of each leaf's weight and its computed depth.
* Print the calculated depths and the final minimum cost, then free the allocated memory.

---

## Pseudocode

```text
OPTIMAL-ALPHABETIC-TREE(weights, n)

1. max_nodes = 2 * n - 1
2. Initialize nodes array of size max_nodes.
3. Initialize seq array of size n with values 0 to n - 1.
4. count = n
   total_nodes = n

5. While count > 1:
       best_cost = infinity
       best_a = -1
       best_b = -1

       For a = 0 to count - 1:
           For b = a + 1 to count - 1:
               compatible = true

               For k = a + 1 to b - 1:
                   If nodes[seq[k]].is_leaf == true:
                       compatible = false
                       Break
               
               If compatible:
                   cost = nodes[seq[a]].weight + nodes[seq[b]].weight
                   If cost < best_cost:
                       best_cost = cost
                       best_a = a
                       best_b = b

       new_node_index = total_nodes
       total_nodes = total_nodes + 1
       
       Initialize nodes[new_node_index] with best_cost, is_leaf = false
       nodes[seq[best_a]].parent = new_node_index
       nodes[seq[best_b]].parent = new_node_index

       seq[best_a] = new_node_index
       
       For i = best_b to count - 2:
           seq[i] = seq[i + 1]
           
       count = count - 1

6. total_weighted_path = 0
7. For i = 0 to n - 1:
       depth = 0
       current = i
       While nodes[current].parent != -1:
           depth = depth + 1
           current = nodes[current].parent
           
       nodes[i].depth = depth
       total_weighted_path += nodes[i].weight * depth
       Print i + 1, nodes[i].weight, nodes[i].depth

8. Print total_weighted_path

```

## Sample Output

```text
Enter number of weights: 3
Enter the weights in order:
10 20 30
Merge 10 and 20 -> 30
Merge 30 and 30 -> 60

Final Leaf Depths:
Index    Weight  Depth
------------------------
1       10      2
2       20      2
3       30      1

Total Weighted Path Length: 90

```

## Time Complexity Analysis

To determine the overall time complexity, we evaluate the merging loops and the depth calculations:
* **Merge Loop:** The outer `while` loop executes exactly $n - 1$ times to reduce the sequence to a single root node.   
* **Pair Evaluation:** Inside the loop, finding the optimal pair requires checking all $O(n^2)$ combinations of `a` and `b`. For each pair, validating the compatibility iterates through the elements between them, which takes $O(n)$ time. Therefore, a single iteration of the `while` loop takes $O(n^3)$ operations.   
* **Total Merge Phase:** $(n - 1) \times O(n^3) = O(n^4)$.   
* **Depth Traversal:** Traversing up the tree to find the depth of each of the $n$ leaves takes a maximum of $O(n)$ steps per leaf, totaling $O(n^2)$ time.   

Summing these phases, the $O(n^4)$ term strictly dominates.

**Final Time Complexity:**
$$O(n^4)$$

---

## Conclusion

The code implements the combination phase of the Hu-Tucker algorithm using a brute-force Greedy selection process. By strictly enforcing compatibility constraints during each merge, it successfully calculates the optimal depths and minimum weighted path length required for a valid alphabetic binary tree. While functionally correct, the unoptimized sequential array scans result in an $O(n^4)$ time complexity, which is best suited for smaller datasets but could be heavily optimized by using priority queues and doubly linked lists for larger inputs.
