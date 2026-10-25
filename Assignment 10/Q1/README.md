# Online Bipartite Graph Checking using Augmented DSU

## Problem Statement

Given a graph with $V$ vertices, process a stream of $E$ edges one by one (online) and determine if each new edge can be added without violating the graph's bipartiteness. A graph is bipartite if its vertices can be divided into two disjoint sets such that every edge connects a vertex in one set to a vertex in the other (i.e., it contains no odd-length cycles). The algorithm utilizes an augmented Disjoint Set Union (DSU) or Union-Find data structure. Alongside the standard parent and rank arrays, it maintains a parity array to track the bipartite set assignment of each vertex relative to the root of its component.

---

## Algorithm

* Read the number of vertices $V$ and edges $E$, and validate the inputs.
* Dynamically allocate memory for `parent`, `rank`, and `parity` arrays of size $V + 1$.
* Initialize the DSU structure: for each vertex $i$, set its root parent to itself (`parent[i] = i`), its rank to $0$, and its parity to $0$.
* For each of the $E$ edges, read the endpoints $u$ and $v$ and process them using the `AddEdge` function:
  * Find the root of $u$ and the root of $v$ using the `Find` function.
  * The `Find` function recursively traces up to the root while applying path compression. During this traceback, it updates the parity of the current node by XORing it with the parity of its parent (`parity[x] ^= parity[p]`).
  * If $u$ and $v$ belong to the same component (their roots are identical), check their relative parities. If `parity[u] ^ parity[v] == 1`, they are in different bipartite sets, so the edge is accepted. If the XOR result is $0$, they belong to the same set, meaning the new edge forms an odd-length cycle, so the edge is rejected.
  * If $u$ and $v$ belong to different components, the edge is accepted, and the components are merged using the `Unite` function.
* The `Unite` function attaches the root of the shallower tree to the root of the deeper tree (Union by Rank) to maintain a balanced structure. It then assigns a parity to the attached root such that $u$ and $v$ end up with opposite parities (`pu ^ pv ^ 1`).
* Print whether each edge is accepted or rejected based on the bipartiteness check.
* Free the dynamically allocated arrays.

---

## Pseudocode

```text
FIND(x)
1. If parent[x] != x:
       p = parent[x]
       parent[x] = FIND(parent[x])
       parity[x] = parity[x] XOR parity[p]
2. Return parent[x]

UNITE(u, v)
1. ru = FIND(u)
2. rv = FIND(v)
3. pu = parity[u]
4. pv = parity[v]
5. If ru == rv:
       Return
6. If rank[ru] < rank[rv]:
       parent[ru] = rv
       parity[ru] = pu XOR pv XOR 1
   Else If rank[ru] > rank[rv]:
       parent[rv] = ru
       parity[rv] = pu XOR pv XOR 1
   Else:
       parent[rv] = ru
       parity[rv] = pu XOR pv XOR 1
       rank[ru] = rank[ru] + 1

ADD-EDGE(u, v)
1. ru = FIND(u)
2. rv = FIND(v)
3. If ru == rv:
       If (parity[u] XOR parity[v]) == 1:
           Return 1  
       Else:
           Return 0  
4. UNITE(u, v)
5. Return 1 // Accepted

MAIN:
1. Read V, E
2. Initialize parent, rank, parity arrays of size V + 1
3. For i = 0 to V:
       parent[i] = i
       rank[i] = 0
       parity[i] = 0
4. For i = 1 to E:
       Read u, v
       If ADD-EDGE(u, v) == 1:
           Print "Edge (u, v) accepted"
       Else:
           Print "Edge (u, v) rejected - violates bipartiteness"

```

## Sample Output

```text
Enter number of vertices: 3
Enter number of edges: 3
Enter edges (u v):
1 2
Edge (1, 2) accepted
2 3
Edge (2, 3) accepted
1 3
Edge (1, 3) rejected - violates bipartiteness

```

## Time Complexity Analysis

To determine the overall time complexity, we analyze the DSU operations across $E$ edge queries:
* **Find Operations:** With path compression and union by rank optimizations, the amortized time complexity for each `Find` operation is nearly constant, denoted as $O(\alpha(V))$, where $\alpha$ is the inverse Ackermann function.
* **Edge Processing:** For each of the $E$ edges, we perform constant numbers of `Find` and `Unite` operations. Thus, processing all $E$ edges takes $O(E \alpha(V))$ time.

**Final Time Complexity:**
$$O(E \alpha(V))$$
*(where $E$ is the number of edges and $V$ is the number of vertices)*

---

## Conclusion

Checking graph bipartiteness online using an augmented Disjoint Set Union (DSU) structure provides an exceptionally efficient solution. By tracking node parities relative to component roots alongside standard path compression and union-by-rank heuristics, the algorithm processes edge streams dynamically without rebuilding component trees. The amortized time complexity of $O(E \alpha(V))$ makes it highly scalable for large, dynamic graphs.
