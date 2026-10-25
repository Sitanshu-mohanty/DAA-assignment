# Number of Islands II (Dynamic Island Counting with DSU)

## Problem Statement

Given an $R \times C$ grid initially entirely filled with water, dynamically process $K$ operations where each operation turns a specific cell into land. After each addition, determine the total number of connected islands. Islands are connected horizontally and vertically. This is solved using a Disjoint Set Union (DSU) or Union-Find data structure representing a 1D flattened grid to efficiently merge newly adjacent landmasses and track the component count.

---

## Algorithm

* Read the dimensions $R$ and $C$ of the grid, followed by the number of land additions $K$, and validate the inputs.
* Calculate the total number of cells as $R \times C$.
* Dynamically allocate memory for the `parent`, `rank`, and `land` arrays of size `total`.
* Initialize the DSU structure: set each cell to be its own parent (`parent[i] = i`), its rank to $0$, and its land status to $0$ (water).
* Initialize the active components count to $0$.
* Define coordinate modifiers `dr` and `dc` to easily check the $4$ adjacent directional neighbors (up, down, left, right).
* Iterate through the $K$ operations:
  * Read the row and column coordinates and convert them to $0$-indexed values.
  * Calculate the 1D flattened index for the current cell as `id = r * C + c`.
  * If the cell is currently water (`land[id] == 0`), mark it as land (`1`) and tentatively increment the components count.
  * Iterate through the $4$ adjacent neighbors. If a neighbor is within the grid boundaries and is already marked as land, find the DSU roots of the current cell and the neighbor.
  * If the roots differ, the new land bridges two previously disconnected islands. Call `Unite` to merge them and decrement the components count.
  * Print the updated number of islands after evaluating the operation.
* Free the dynamically allocated memory.

---

## Pseudocode

```text
FIND(x)
1. If parent[x] != x:
       parent[x] = FIND(parent[x])
2. Return parent[x]

UNITE(a, b)
1. ra = FIND(a)
2. rb = FIND(b)
3. If ra == rb:
       Return
4. If rank[ra] < rank[rb]:
       parent[ra] = rb
   Else If rank[ra] > rank[rb]:
       parent[rb] = ra
   Else:
       parent[rb] = ra
       rank[ra] = rank[ra] + 1

MAIN:
1. Read R, C, K
2. total = R * C
3. Initialize parent, rank, and land arrays of size total
4. For i = 0 to total - 1:
       parent[i] = i
       rank[i] = 0
       land[i] = 0

5. components = 0
6. dr = {-1, 1, 0, 0}
   dc = {0, 0, -1, 1}

7. For i = 1 to K:
       Read r, c
       r = r - 1
       c = c - 1
       id = r * C + c

       If land[id] == 0:
           land[id] = 1
           components = components + 1

           For j = 0 to 3:
               nr = r + dr[j]
               nc = c + dc[j]

               If nr >= 0 and nr < R and nc >= 0 and nc < C:
                   nid = nr * C + nc
                   If land[nid] == 1:
                       root1 = FIND(id)
                       root2 = FIND(nid)
                       
                       If root1 != root2:
                           UNITE(root1, root2)
                           components = components - 1

       Print components

```

## Sample Output

```text
Enter number of rows: 3
Enter number of columns: 3
Enter number of land additions: 4
Enter land positions (row column):
1 1
Number of islands after operation 1: 1
1 3
Number of islands after operation 2: 2
1 2
Number of islands after operation 3: 1
2 2
Number of islands after operation 4: 1

```

## Time Complexity Analysis

To determine the overall time complexity, we analyze the DSU operations across $K$ land additions:
* **Grid Initialization:** Allocating and initializing the DSU arrays takes $O(R \times C)$ time.
* **Operation Processing:** For each of the $K$ operations, we check up to $4$ orthogonal neighbors and perform constant numbers of `Find` and `Unite` operations. With path compression and union by rank optimizations, each DSU operation runs in nearly constant amortized time, $O(\alpha(R \times C))$, where $\alpha$ is the inverse Ackermann function.
* **Total Processing Time:** $O(R \times C + K \alpha(R \times C))$.

**Final Time Complexity:**
$$O(R \times C + K \alpha(R \times C))$$
*(where $R$ and $C$ are grid dimensions and $K$ is the number of land additions)*

---

## Conclusion

The Number of Islands II problem demonstrates the power of the Disjoint Set Union (DSU) data structure in handling dynamic graph connectivity problems efficiently. By mapping a 2D grid into a 1D flattened index space and incrementally merging adjacent land cells, the algorithm tracks island counts online without re-scanning the grid at each step. The amortized time complexity of $O(R \times C + K \alpha(R \times C))$ makes it highly optimal and scalable compared to repeated BFS/DFS traversals.


