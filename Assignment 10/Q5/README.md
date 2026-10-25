# Lexicographically Smallest Permutation with Allowed Swaps

## Problem Statement

Given an array containing a permutation of $n$ elements and a list of $m$ allowed swap pairs (edges) between indices, the objective is to find the lexicographically smallest permutation that can be formed by applying the allowed swaps any number of times. If two indices are connected directly or indirectly through a series of allowed swaps, their values can be rearranged into any arbitrary order within those indices. The problem is solved using a Disjoint Set Union (DSU) data structure to group connected indices into independent components, followed by sorting the values within each component to ensure the smallest possible elements are placed at the earliest possible indices.

---

## Algorithm

* Read the number of elements $n$ and dynamically allocate memory for the permutation array `A`.
* Read the initial permutation values into array `A`.
* Initialize the DSU structure by allocating `parent` and `rank` arrays of size $n + 1$, setting each element to be its own parent with a rank of $0$.
* Read the number of edges $m$, then iteratively read each allowed swap pair `(u, v)` and merge their respective components using the `Unite` function.
* Count the number of elements in each connected component by finding the root of every index and tallying it in a `count` array.
* Dynamically allocate 2D arrays (arrays of pointers) named `positions` and `values` to group the indices and their corresponding values based on their DSU root.
* Iterate through all indices from $1$ to $n$, pushing each index and its corresponding value `A[i]` into the respective component's `positions` and `values` arrays.
* For each independent connected component (where `count[i] > 0`):
  * Sort the `positions` array in ascending order.
  * Sort the `values` array in ascending order using `qsort`.
  * Map the sorted values back into the original array `A` by placing the $j$-th smallest value into the $j$-th smallest position of that component (`A[positions[i][j]] = values[i][j]`).
* Print the fully reorganized, lexicographically smallest permutation.
* Iterate through the components to free the nested `positions` and `values` arrays, then free all remaining dynamically allocated memory.

---

## Pseudocode

```text
FIND(x)
1. If parent[x] != x:
       parent[x] = FIND(parent[x])
2. Return parent[x]

UNITE(u, v)
1. ru = FIND(u)
2. rv = FIND(v)
3. If ru == rv:
       Return
4. If rank[ru] < rank[rv]:
       parent[ru] = rv
   Else If rank[ru] > rank[rv]:
       parent[rv] = ru
   Else:
       parent[rv] = ru
       rank[ru] = rank[ru] + 1

LEXICOGRAPHICALLY-SMALLEST(A, n, edges, m)
1. Initialize parent and rank arrays of size n + 1.
2. For i = 1 to n:
       parent[i] = i
       rank[i] = 0

3. For each edge (u, v) in edges:
       UNITE(u, v)

4. count = array of size n + 1 initialized to 0
5. For i = 1 to n:
       root = FIND(i)
       count[root] = count[root] + 1

6. Initialize positions and values as arrays of arrays.
7. For i = 1 to n:
       If count[i] > 0:
           Allocate positions[i] and values[i] of size count[i]

8. index = array of size n + 1 initialized to 0
9. For i = 1 to n:
       root = FIND(i)
       positions[root][index[root]] = i
       values[root][index[root]] = A[i]
       index[root] = index[root] + 1

10. For i = 1 to n:
        If count[i] > 0:
            Sort positions[i] in ascending order.
            Sort values[i] in ascending order.
            
            For j = 0 to count[i] - 1:
                A[positions[i][j]] = values[i][j]

11. Return A

```

## Sample Output

```text
Enter number of elements: 4
Enter permutation:
4 3 2 1
Enter number of edges: 2
Enter edges (u v):
1 2
3 4
Lexicographically smallest permutation:
3 4 1 2

```

## Time Complexity Analysis

To determine the overall time complexity, we evaluate the DSU construction, component grouping, and sorting phases:
* **DSU Construction:** Initializing the arrays takes $O(n)$ time. Processing the $m$ edges using `unite` and `find` (with path compression and union by rank) takes amortized $O(m \times \alpha(n))$ time.   
* **Component Grouping:** Finding the root for each element and populating the positions and values arrays requires iterating through the $n$ elements, running in $O(n \times \alpha(n))$ time.   
* **Sorting Phase:** Let $k_i$ be the number of elements in the $i$-th connected component. Sorting the positions and values arrays for each component takes $O(k_i \log k_i)$ time. The sum of all component sizes equals $n$ ($\sum k_i = n$). In the worst-case scenario (a single fully connected graph), sorting takes $O(n \log n)$ time.   

Combining the phases yields $O(n) + O(m \alpha(n)) + O(n \alpha(n)) + O(n \log n)$. The sorting operation strictly bounds the asymptotic behavior for the vertices, alongside the edge processing.

**Final Time Complexity:**
$$O(n \log n + m \alpha(n))$$

---

## Conclusion

The Lexicographically Smallest Connected Component problem is efficiently resolved by recognizing that transitive swap operations form independent connected components. By utilizing a Union-Find structure, the algorithm perfectly maps out these isolated sub-graphs. It then applies a greedy sorting strategy within each isolated component, ensuring the absolute minimum values drift to the earliest possible indices, yielding the optimal permutation in $O(n \log n + m \alpha(n))$ time.
