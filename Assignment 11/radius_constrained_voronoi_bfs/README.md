# Multi-Source BFS for Radius-Constrained Voronoi Cell Partitioning

DAA assignment implementation in C for assigning every vertex in an unweighted, undirected graph to its nearest designated hub, subject to a maximum service radius `R`.

## Problem

Input:
- An unweighted, undirected graph `G = (V, E)`.
- `K` distinct hub vertices, listed in numerical priority order `h1, h2, ..., hK`.
- A non-negative integer radius `R`.

For each vertex `v`, output:
- `owner[v]`: the index `i` of the closest hub `hi` if its distance is at most `R`; otherwise `-1`.
- `distance[v]`: the shortest distance to the assigned hub, or `-1` if unassigned.

If multiple hubs are equally close, the hub with the smallest index wins.

## Repository layout

```text
radius_constrained_voronoi_bfs/
├── src/
│   └── main.c
├── tests/
│   ├── sample_input.txt
│   └── expected_output.txt
├── docs/
│   └── algorithm.md
├── Makefile
└── README.md
```

No graph visualization is included, as requested.

## Input format

```text
n m
K R
h1 h2 ... hK
u1 v1
u2 v2
...
um vm
```

- Vertices are numbered `1` through `n`.
- `n` is the number of vertices and `m` is the number of undirected edges.
- `K` is the number of distinct hubs (`1 <= K <= n`).
- `R` is the maximum service distance (`R >= 0`).
- The hub list order defines hub indices `1` through `K`.
- Each edge `u v` is undirected.

## Build and run

With GCC or Clang:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src/main.c -o voronoi_bfs
./voronoi_bfs < tests/sample_input.txt
```

Or use Make:

```sh
make
./voronoi_bfs < tests/sample_input.txt
```

On Windows PowerShell:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src/main.c -o voronoi_bfs.exe
Get-Content tests/sample_input.txt | .\voronoi_bfs.exe
```

## Sample output

See `tests/expected_output.txt`.

The output lists every vertex as `Vertex v: owner = i, distance = d`. An owner and distance of `-1` mean the vertex is outside all hubs' radius coverage.

## Algorithm

Run one multi-source BFS. Insert all hubs into the queue in ascending hub-index order, with distance `0` and their corresponding owner labels. Explore each vertex's neighbors in BFS order, but only expand vertices whose distance is less than `R`. A vertex is assigned the first time it is discovered. Since the queue is initialized in hub-index order, BFS explores equal-distance candidates with the smaller hub index first; therefore the first assignment also enforces the required deterministic tie-breaking.

Vertices not reached within `R` remain unassigned (`owner = -1`, `distance = -1`).

## Complexity analysis

Using adjacency lists, each vertex is enqueued at most once and each undirected edge is examined at most twice. Therefore:

- **Time complexity:** `O(V + E + K)`; since `K <= V`, this is `O(V + E)`.
- **Space complexity:** `O(V + E)` for adjacency lists, queue, owner labels, and distances.

## Validation

The C program validates graph sizes, hub count, radius, hub uniqueness/ranges, and edge endpoints. It rejects self-loops and duplicate edges are allowed (they do not affect correctness).
