# Maximum Component Weight with Size Threshold

## Problem Statement

Given a graph with $V$ vertices, where each vertex has an initial weight, the objective is to dynamically connect vertices via a stream of $E$ edges and report the maximum component weight after each insertion. The weight of a component is the sum of the weights of all its vertices, but the algorithm must only consider components whose total number of vertices does not exceed a given size threshold $K$. The problem is solved using an augmented Disjoint Set Union (DSU) data structure that independently tracks both the size and the sum of weights for each connected component as they are merged.

---

## Algorithm

* Read the number of vertices $V$ and the size threshold $K$, and validate the inputs.
* Dynamically allocate memory for four arrays of size $V + 1$: `parent`, `rank`, `size`, and `sum`.
* Initialize the DSU structure for each vertex $i$: set its parent to itself (`parent[i] = i`), its rank to $0$, its size to $1$, and its sum to the inputted vertex weight.
* Read the number of edges $E$ to be processed.
* For each edge connecting vertex $u$ and $v$, perform the `Unite` operation:
  * Find the root of $u$ and the root of $v$ using the `Find` function, which applies path compression.
  * If the roots differ, merge the components using union by rank (attaching the shallower tree to the deeper one).
  * Update the new root's size by adding the sizes of both merging components (`size[rv] += size[ru]`).
  * Update the new root's sum by adding the weight sums of both merging components (`sum[rv] += sum[ru]`).
* After each edge is added, call the `GetMaximum` function to scan for the valid maximum weight:
  * Iterate through all vertices from $1$ to $V$.
  * Filter for vertices that are component roots (`parent[i] == i`) and whose component size is within the threshold (`size[i] <= K`).
  * Track and return the highest `sum[i]` among these valid components.
* Print the maximum valid component weight after every edge insertion, returning $0$ if no components satisfy the threshold.
* Free the dynamically allocated memory arrays.

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
       size[rv] = size[rv] + size[ru]
       sum[rv] = sum[rv] + sum[ru]
   Else If rank[ru] > rank[rv]:
       parent[rv] = ru
       size[ru] = size[ru] + size[rv]
       sum[ru] = sum[ru] + sum[rv]
   Else:
       parent[rv] = ru
       size[ru] = size[ru] + size[rv]
       sum[ru] = sum[ru] + sum[rv]
       rank[ru] = rank[ru] + 1

GET-MAXIMUM(V, K)
1. maximum = 0
2. found = 0
3. For i = 1 to V:
       If parent[i] == i and size[i] <= K:
           If found == 0 or sum[i] > maximum:
               maximum = sum[i]
               found = 1
4. If found == 0:
       Return 0
5. Return maximum

MAIN:
1. Read V, K
2. Initialize parent, rank, size, and sum arrays
3. For i = 1 to V:
       Read weight
       parent[i] = i
       rank[i] = 0
       size[i] = 1
       sum[i] = weight
4. Read E
5. For i = 1 to E:
       Read u, v
       UNITE(u, v)
       max_weight = GET-MAXIMUM(V, K)
       Print "Maximum weight component after edge i: max_weight"

```

## Sample Output

```text
Enter number of vertices: 4
Enter size threshold K: 2
Enter vertex weights:
10
20
30
40
Enter number of edges: 3
Enter edges (u v):
1 2
Maximum weight component after edge 1: 40
3 4
Maximum weight component after edge 2: 70
2 3
Maximum weight component after edge 3: 0

```

## Time Complexity Analysis

To determine the overall time complexity, we evaluate the DSU operations and the maximum weight search per edge:
* **DSU Operations:** Each edge insertion performs `Find` and `Unite` operations which run in nearly constant amortized time, $O(\alpha(V))$, thanks to path compression and union by rank.
* **Component Scan (`GetMaximum`):** After each of the $E$ edge insertions, the algorithm scans all $V$ vertices to find the maximum weight root satisfying the size constraint $\le K$, which takes $O(V)$ time per query.
* **Total Time Complexity:** With $E$ edge queries, the total time spent across all queries is $O(E \cdot (V + \alpha(V))) = O(E \cdot V)$.

**Final Time Complexity:**
$$O(E \cdot V)$$
*(where $E$ is the number of edges and $V$ is the number of vertices)*

---

## Conclusion

The Maximum Component Weight with Size Threshold problem is effectively solved by augmenting the Disjoint Set Union data structure to track component properties like size and weight sums dynamically. While the linear scan required to find the constrained maximum adds an $O(V)$ factor per edge insertion, the approach maintains clean modular updates and efficiently handles online connectivity queries under structural limitations.
