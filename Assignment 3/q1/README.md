# Binary vs Ternary Search — DAA Lab Assignment

## Aim

To implement **Binary Search** and **Ternary Search** on a sorted array and compare their performance.

## Question

In binary search, the array is divided into two nearly equal parts.  
In ternary search, the array is divided into three nearly equal parts.

Implement both methods and justify through experiments that binary search is better than ternary search.

## Files

```text
binary-vs-ternary-lab/
│
├── src/
│   └── main.c
│
├── scripts/
│   └── plot.py
│
├── results/
│   └── benchmark.csv
│
└── README.md
```

## How to Compile

### Windows

```powershell
gcc src/main.c -o search.exe
.\search.exe
```

## Generate the Graph

First run the C program. It creates:

```text
results/benchmark.csv
```

Then install matplotlib if required:

```bash
pip install matplotlib
```

Run:

```bash
python scripts/plot.py
```

The graph will be saved as:

```text
results/comparison.png
```

## Expected Result

Binary search uses approximately:

```text
log2(n)
```

comparisons.

Ternary search uses approximately:

```text
2 log3(n)
```

comparisons.

Although both algorithms have **O(log n)** time complexity, binary search normally performs fewer comparisons because each ternary-search step requires checking two middle positions.

Therefore, the experiment supports the conclusion that **binary search is generally better than ternary search for this problem**.

## Sample Output

```text
Binary vs Ternary Search

Array size: 100000

Binary Search:
Found at index: 99999
Comparisons: 17

Ternary Search:
Found at index: 99999
Comparisons: 34

Benchmark data written to results/benchmark.csv
```

## Time Complexity

| Algorithm | Best Case | Average Case | Worst Case |
|-----------|-----------|--------------|------------|
| Binary Search | O(1) | O(log n) | O(log n) |
| Ternary Search | O(1) | O(log n) | O(log n) |

Space complexity for the iterative implementations is **O(1)**.

## Conclusion

Both binary search and ternary search are logarithmic searching algorithms. However, ternary search performs two comparisons per iteration, while binary search generally needs only one comparison to decide which half to continue searching in. Experimental comparison counts therefore show that binary search is more efficient for searching a sorted array.
