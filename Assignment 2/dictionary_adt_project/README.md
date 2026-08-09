# Dictionary ADT — Empirical Complexity Comparison in C

This project solves the **Dictionary Operations** question by implementing the same seven Dictionary ADT operations using six different data structures and experimentally measuring their running time.

## Operations

1. Search
2. Insert
3. Delete
4. Maximum
5. Minimum
6. Predecessor
7. Successor

## Data structures

- Unsorted array
- Sorted array
- Singly linked unsorted list
- Singly linked sorted list
- Doubly linked unsorted list
- Doubly linked sorted list

## Repository structure

```text
dictionary-adt-project/
├── README.md
├── Makefile
├── .gitignore
├── src/
│   └── dictionary_benchmark.c
├── scripts/
│   └── plot_graphs.py
├── results/
│   └── benchmark.csv
├── graphs/
│   ├── search.png
│   ├── insert.png
│   ├── delete.png
│   ├── maximum.png
│   ├── minimum.png
│   ├── predecessor.png
│   └── successor.png
└── docs/
    ├── complexity_comparison.md
    ├── benchmark_methodology.md
    └── submission_report.md
```

## Theoretical worst-case complexities

| Data structure | Search | Insert | Delete | Max | Min | Predecessor | Successor |
|---|---:|---:|---:|---:|---:|---:|---:|
| Unsorted array | O(n) | O(1) | O(1) | O(n) | O(n) | O(n) | O(n) |
| Sorted array | O(log n) | O(n) | O(n) | O(1) | O(1) | O(1) | O(1) |
| Singly linked unsorted | O(n) | O(1) | O(n) | O(n) | O(n) | O(n) | O(1) |
| Singly linked sorted | O(n) | O(n) | O(n) | O(n) | O(1) | O(n) | O(1) |
| Doubly linked unsorted | O(n) | O(1) | O(1) | O(n) | O(n) | O(1) | O(1) |
| Doubly linked sorted | O(n) | O(n) | O(1) | O(n) | O(1) | O(1) | O(1) |

### Important assumptions

- `Delete(D, x)` is interpreted literally: **a pointer/reference to the item `x` is already available**.
- For an unsorted array, deletion does **not preserve element order**; the deleted item is replaced by the last item. Therefore deletion is O(1).
- The sorted linked lists do not maintain a tail pointer. Therefore `Maximum` is O(n).
- A basic singly linked list has only `next`; a doubly linked list has both `prev` and `next`.
- A sorted array uses binary search for `Search`.
- A linked list does not support efficient random access, so sorting does not turn linked-list search into O(log n).
- `Predecessor(x)` and `Successor(x)` mean the immediately smaller/larger key in sorted key order, not necessarily the physical previous/next element in an unsorted structure.

If an implementation maintains extra information such as a tail pointer, the complexity can change. For example, a sorted linked list with a maintained tail pointer has O(1) maximum.

## Why the complexities occur

### Unsorted array

There is no ordering, so search, min, max, predecessor and successor may require scanning all `n` elements.

Insertion can append at the end in O(1). Deletion is O(1) because order is not preserved.

### Sorted array

Binary search gives O(log n) search.

However, insertion and deletion may require shifting O(n) elements. Minimum, maximum, predecessor and successor are directly available from array positions and are O(1) once the item pointer/index is known.

### Singly linked unsorted list

Search, min, max and predecessor require traversal and are O(n). Insertion at the head is O(1).

Deletion is O(n) in the worst case because, even when a pointer to `x` is supplied, a singly linked list does not provide `x`'s predecessor.

Successor is simply `x->next`, so it is O(1).

### Singly linked sorted list

Sorting makes minimum O(1) and successor O(1), but the list still has no random access, so search remains O(n).

Insertion requires finding the correct position: O(n). Deletion and predecessor can require finding the previous node: O(n). Maximum is O(n) without a tail pointer.

### Doubly linked unsorted list

Search, min and max remain O(n).

Insertion at the head is O(1). Given a node pointer, deletion is O(1) because the node has both `prev` and `next`.

Predecessor and successor are directly available through `prev` and `next`, so both are O(1).

### Doubly linked sorted list

Search and insertion remain O(n) because we must traverse the list to find a position.

Minimum is O(1). Without a tail pointer, maximum is O(n).

Given a node pointer, deletion, predecessor and successor are all O(1).

## Running the benchmark

### Linux / macOS

```bash
make
make benchmark
make graphs
```

Equivalent commands:

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/dictionary_benchmark.c -o dictionary_benchmark
./dictionary_benchmark
python3 scripts/plot_graphs.py
```

The C program is responsible for implementing and timing all six data structures. The plotting step is intentionally separated into Python so the measured CSV data can be regenerated and visualized cleanly.

The benchmark writes:

```text
results/benchmark.csv
```

and the plotting script creates eight PNG graphs in:

```text
graphs/
```

### Windows

Using MinGW/MSYS2, compile with:

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/dictionary_benchmark.c -o dictionary_benchmark.exe
dictionary_benchmark.exe
```

Then run:

```bash
python scripts/plot_graphs.py
```

## What the benchmark measures

The C program measures average elapsed time per operation for:

```text
n = 100, 500, 1,000, 5,000, 10,000, 50,000, 100,000
```

The benchmark deliberately chooses worst-case-style inputs:

- Search: absent key for sequential structures.
- Sorted-array insertion: smallest key, forcing maximum shifting.
- Sorted-list insertion: largest key, forcing traversal to the tail.
- Linked-list deletion: tail node for singly linked lists.
- Min/max: full scan where required.
- Predecessor/successor: a valid node is supplied.
- Constant-time operations are repeated many times to improve timing resolution.

Preparation and cleanup needed to restore the data structure between mutating operations are kept outside the timed operation itself.

## Interpreting the graphs

The graphs use logarithmic axes. This is useful because the measured times can differ by several orders of magnitude.

The goal is **not** to prove Big-O mathematically from hardware timings. The graphs are empirical validation that the measured growth is consistent with the theoretical analysis.

For example:

- Nearly horizontal → approximately O(1)
- Approximately proportional growth → approximately O(n)
- Slowly increasing search curve for sorted array → consistent with O(log n)

Actual nanosecond values depend on CPU, compiler, operating system, cache behavior and system load. Therefore, the **growth trend**, rather than the absolute time, is the important result.

## Submission note

- `src/dictionary_benchmark.c` — C implementation and benchmark
- `results/benchmark.csv` — measured data
- `graphs/*.png` — generated plots
- `docs/complexity_comparison.md` — theoretical analysis
- `README.md` — project documentation

