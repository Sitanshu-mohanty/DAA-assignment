# Bidirectional BFS for Shortest Transformation Sequence in a Word Graph

A C11 implementation for finding the minimum number of single-character mutations required to transform a start word `A` into a target word `B`, using only dictionary words as intermediate steps.

## Problem definition

The dictionary contains `N` unique lowercase words of equal length `L` (`N <= 100000`, `L <= 10`). A valid mutation changes exactly one character and the resulting word must exist in dictionary `D`. The program returns the minimum number of mutations from `A` to `B`, or `-1` if no valid transformation exists.

- Start word `A` does not need to be in the dictionary.
- Target word `B` must be in the dictionary.
- The start word is included as the BFS source even when it is not in `D`.
- If `A == B`, the answer is `0` provided the target-word input constraints are satisfied.

## Repository structure

```text
bidirectional_word_ladder_bfs/
├── src/
│   └── main.c
├── tests/
│   ├── sample_input.txt
│   ├── expected_output.txt
│   └── edge_cases.txt
├── docs/
│   └── algorithm.md
├── Makefile
└── README.md
```

No graph visualization is included, as requested.

## Input format

```text
N L
A B
word1
word2
...
wordN
```

- `N`: number of dictionary words (`1 <= N <= 100000`)
- `L`: common word length (`1 <= L <= 10`)
- `A`: starting word of length `L`
- `B`: target word of length `L`
- Next `N` lines: unique lowercase dictionary words of length `L`; `B` must be in the dictionary.

## Build and run

Linux/macOS:

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src/main.c -o word_ladder
./word_ladder < tests/sample_input.txt
```

Windows PowerShell:

```powershell
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 src/main.c -o word_ladder.exe
Get-Content tests/sample_input.txt | .\word_ladder.exe
```

Or use `make`:

```sh
make
./word_ladder < tests/sample_input.txt
```

## Sample

Expected result for `tests/sample_input.txt`:

```text
Minimum mutations from hit to cog: 4
```

## Algorithm

Use bidirectional BFS: one search begins at `A`, and the other begins at `B`. At each iteration, expand one complete BFS layer from the smaller current frontier. For each word, generate its neighbors by changing each character to each of the other 25 lowercase letters. A generated word is a neighbor only if it exists in the dictionary (or is `A` for the source-side search). Hash-table lookup makes membership checks expected `O(1)`.

When the searches meet, the distance is the sum of the two distances at the meeting point. If a search frontier becomes empty before a meeting, no path exists.

## Complexity analysis

There are at most `N + 1` searchable words including `A`. For each expanded word, at most `25L` candidates are generated. With expected constant-time hash-table operations:

- **Expected time:** `O((N + 1) * L * 26)` = `O(NL)` for fixed alphabet size.
- **Space:** `O(NL)` to store words and the hash table, plus `O(N)` for distance arrays and frontiers.

The stated bounds `N <= 10^5`, `L <= 10` make this approach suitable for the assignment. Hash-table operations have worst-case linear probing behavior in pathological collision cases; the time bound is expected, not a deterministic worst-case guarantee.

## Correctness outline

Every generated edge joins words that differ in exactly one character, and dictionary membership is checked before a word is admitted. Thus the implicit graph contains exactly the valid mutation edges. BFS explores vertices in nondecreasing distance. Bidirectional BFS explores from both endpoints and, when the two explored regions meet, combines their shortest distances to obtain the shortest transformation length. If the frontiers exhaust without meeting, no path connects the endpoints.
