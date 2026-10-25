# Dynamic Connectivity with Vertex Deletions (Reverse Time DSU)

## Problem Statement

Given a graph with $V$ vertices (each possessing a specific weight) and $E$ edges, a sequence of vertex deletions is performed. The goal is to determine the maximum weight of any connected component after each deletion. Because dynamically splitting components in a Disjoint Set Union (DSU) data structure is computationally expensive and complex, the problem is solved offline by reversing the flow of time. The algorithm starts with an empty graph and adds the vertices back in the exact reverse order of their deletion, utilizing the DSU to efficiently merge components and track the maximum weight incrementally.

---

## Algorithm

* Read the number of vertices $V$ and edges $E$, and dynamically allocate memory for the DSU arrays, vertex tracking arrays, and the adjacency list.
* Read the initial weights for all vertices and populate the graph's adjacency list using `head`, `to`, and `next` arrays.
* Read the exact sequence of vertex deletions into the `order` array.
* Iterate through the `order` array in reverse, starting from $V - 1$ down to $0$:
  * Retrieve the current vertex to be "added" back into the graph.
  * Mark this vertex as active in the graph.
  * Initialize its DSU properties: set its parent to itself (`parent[u] = u`), rank to $0$, and its component sum to its initial vertex weight (`sum[u] = weight[u]`).
  * Compare its solitary weight against the global maximum and update the maximum if it is greater.
  * Iterate through all adjacent neighbors of this newly active vertex using the adjacency list.
  * If a neighbor is also currently active, use the `Find` function to get the root of both vertices.
  * If they belong to different components, merge them using the `Unite` function (which applies union by rank and accumulates the component sum).
  * Check the total sum of the newly merged component's root and update the global maximum if it has grown larger.
  * Store the current maximum in the `answer` array at the current reverse index `i`.
* Iterate forward through the $V$ deletions to print the results chronologically. The maximum weight after deleting the vertex at `order[i]` corresponds to the graph state computed at `answer[i + 1]`. For the final deletion ($V - 1$), manually output $0$ as the graph is entirely empty.
* Free all dynamically allocated arrays.

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
       sum[rv] = sum[rv] + sum[ru]
   Else If rank[ru] > rank[rv]:
       parent[rv] = ru
       sum[ru] = sum[ru] + sum[ru]  // Note: sum[ru] = sum[ru] + sum[rv]
   Else:
       parent[rv] = ru
       sum[ru] = sum[ru] + sum[rv]
       rank[ru] = rank[ru] + 1

MAIN:
1. Read V, E
2. Initialize DSU arrays (parent, rank, sum) and Graph arrays (head, to, next, active)
3. Read vertex weights
4. Read E edges and populate the adjacency list
5. Read vertex deletion order into order array
6. maximum = 0

7. For i = V - 1 down to 0:
       u = order[i]
       active[u] = 1
       parent[u] = u
       rank[u] = 0
       sum[u] = weight[u]
       
       If sum[u] > maximum:
           maximum = sum[u]
           
       For each neighbor v of u:
           If active[v] == 1:
               ru = FIND(u)
               rv = FIND(v)
               If ru != rv:
                   UNITE(ru, rv)
                   root = FIND(u)
                   If sum[root] > maximum:
                       maximum = sum[root]
                       
       answer[i] = maximum

8. For i = 0 to V - 1:
       If i == V - 1:
           Print "After deleting order[i]: 0"
       Else:
           Print "After deleting order[i]: answer[i + 1]"

```

## Sample Output

```text
Enter number of vertices: 3
Enter number of edges: 2
Enter vertex weights:
10 20 30
Enter edges (u v):
1 2
2 3
Enter deletion order:
2 1 3

Maximum component weight after each deletion:
After deleting 2: 30
After deleting 1: 30
After deleting 3: 0

```

## Time Complexity Analysis

To determine the overall time complexity, we analyze the reverse-time simulation steps:
* **Graph and DSU Initialization:** Initializing arrays and building the adjacency list takes $O(V + E)$ time.
* **Reverse Processing:** We iterate through all $V$ vertices in reverse order. For each vertex, we examine all its incident edges (totaling $2E$ across the entire loop) and perform DSU operations (`Find` and `Unite`). With path compression and union by rank optimizations, each DSU operation runs in nearly constant amortized time, $O(\alpha(V))$.
* **Total Processing Time:** $O(V + E \alpha(V))$.

**Final Time Complexity:**
$$O(V + E \alpha(V))$$
*(where $V$ is the number of vertices and $E$ is the number of edges)*

---

## Conclusion

Processing vertex deletions by reversing time transforms an intractable dynamic splitting problem into an efficient incremental construction problem. By starting with an empty graph and adding vertices back in reverse order, the Disjoint Set Union (DSU) structure merges components and tracks weight sums in nearly constant amortized time per edge. This offline technique achieves an optimal time complexity of $O(V + E \alpha(V))$, making it highly effective for dynamic graph problems.
