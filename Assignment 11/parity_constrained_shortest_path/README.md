# Shortest Path on Parity-Constrained Graphs via 0-1 BFS

DAA assignment implementation in C. The project computes the minimum effective cost from a source vertex to every vertex in a directed graph whose edge weights are either `0` or `1`.

## Problem definition

For a path `P`, let `W(P)` be the sum of edge weights and let `k1(P)` be the number of weight-1 edges. Its effective cost is

\[
\operatorname{Cost}(P)=W(P)+
\begin{cases}
0 & \text{if } k_1(P)\text{ is even},\\
C & \text{if } k_1(P)\text{ is odd}.
\end{cases}
\]

For each vertex `v`, the program reports the minimum effective cost of any path from source `S` to `v`, or `UNREACHABLE` if no path exists.

## Repository layout

```text
parity_constrained_shortest_path/
├── src/
│   └── main.c
├── tests/
│   └── sample_input.txt
├── docs/
│   └── algorithm.md
├── Makefile
└── README.md
```

## Build and run

Requires a C compiler such as GCC or Clang.

```sh
make
./parity_shortest_path < tests/sample_input.txt
```

Or compile directly:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src/main.c -o parity_shortest_path
./parity_shortest_path < tests/sample_input.txt
```

## Input format

```text
n m
S C
u1 v1 w1
u2 v2 w2
...
um vm wm
```

- `n`: number of vertices, numbered `1` through `n`
- `m`: number of directed edges
- `S`: source vertex
- `C`: non-negative penalty for an odd number of weight-1 edges
- Each edge line contains `u v w`, representing `u -> v` with `w` equal to `0` or `1`.

The program validates input ranges and edge weights. `C` is read as a non-negative `long long`.

## Sample

Input file: `tests/sample_input.txt`

Expected output:

```text
Minimum effective costs from source 1 (penalty C = 3):
Vertex 1: 0
Vertex 2: 0
Vertex 3: 4
Vertex 4: 2
Vertex 5: 2
Vertex 6: UNREACHABLE
```

## Algorithm overview

Each original vertex `v` is represented by two states:

- `(v, 0)`: reached using an even number of weight-1 edges
- `(v, 1)`: reached using an odd number of weight-1 edges

For an original edge `u -> v` with weight `w`, add a state transition from `(u, p)` to `(v, p XOR w)` with edge cost `w`. Run 0-1 BFS from `(S, 0)`. The answer for `v` is

`min(dist[v][0], dist[v][1] + C)`.

This correctly applies the penalty only after the path parity is known.

## Complexity

There are `2n` states and `2m` transitions in the expanded graph. 0-1 BFS processes this graph in `O(V' + E') = O(n + m)` time and uses `O(n + m)` memory, including the graph representation. The final scan over vertices is `O(n)`. Thus the total time complexity is **O(n + m)** and space complexity is **O(n + m)**.

## Notes

- No graph plotting is included, as requested.
- This is a standalone C implementation suitable for a DAA assignment repository.
