# Merging k Sorted Arrays

DAA implementation and benchmark for merging `k` sorted arrays, each containing `n` elements.

## Methods

1. **Sequential merging** — Θ(`nk²`)
2. **Pairwise merging** — Θ(`nk log k`)

The project validates that both methods produce the same sorted output and benchmarks their running times.

---

## Project structure

```text
merging-k-sorted-arrays/
├── include/
│   └── merge_arrays.h
├── src/
│   └── merge_arrays.c
├── benchmark/
│   └── benchmark.c
├── scripts/
│   └── plot_results.py
├── docs/
│   └── complexity.md
├── results/
│   └── .gitkeep
├── .gitignore
├── Makefile
├── requirements.txt
└── README.md
```

The `results` folder is intentionally empty. You will generate the CSV and graphs on your own Windows machine.

---

# Windows setup
## Quick Run on Windows

A precompiled Windows executable is included:

```powershell
.\benchmark.exe results\benchmark.csv 1000 512 5

## 1. Install a C compiler

If you already have GCC/MinGW, check:

```powershell
gcc --version
```

If this command works, continue.

You also need Python:

```powershell
python --version
```

---

## 2. Open the project folder

In PowerShell:

```powershell
cd path\to\merging-k-sorted-arrays
```

For example:

```powershell
cd C:\Users\YourName\Desktop\merging-k-sorted-arrays
```

---

# 3. Compile the C program

### PowerShell / MinGW GCC

Run:

```powershell
gcc -std=c11 -O2 -Wall -Wextra -pedantic -Iinclude src\merge_arrays.c benchmark\benchmark.c -o benchmark.exe
```

If compilation succeeds, you should see no error messages and:

```text
benchmark.exe
```

will be created.

You can check:

```powershell
dir benchmark.exe
```

---

# 4. Run a small test first

Before doing a large benchmark, use:

```powershell
.\benchmark.exe results\benchmark.csv 100 64 3
```

Meaning:

```text
results\benchmark.csv → output CSV file
100                    → n = 100 elements per array
64                     → maximum k
3                      → 3 repetitions
```

You should see output similar to:

```text
Benchmarking k sorted arrays, n=100
Results: results\benchmark.csv

k=2      sequential=... s  pairwise=... s  speedup=...x
k=4      sequential=... s  pairwise=... s  speedup=...x
k=8      sequential=... s  pairwise=... s  speedup=...x
...
k=64     sequential=... s  pairwise=... s  speedup=...x

Benchmark completed successfully.
```

The exact timings will be different on every computer.

---

# 5. Check the generated CSV

Run:

```powershell
dir results
```

You should now have:

```text
results/
└── benchmark.csv
```

You can open `benchmark.csv` in Excel or VS Code.

It will contain:

```text
k,n,sequential_seconds,pairwise_seconds,speedup
```

---

# 6. Install Python dependencies

Run:

```powershell
python -m pip install -r requirements.txt
```

If `python` is not recognized but `py` works, use:

```powershell
py -m pip install -r requirements.txt
```

---

# 7. Generate the graphs

Run:

```powershell
python scripts\plot_results.py results\benchmark.csv
```

Or:

```powershell
py scripts\plot_results.py results\benchmark.csv
```

You should now get:

```text
results/
├── benchmark.csv
├── runtime_vs_k.png
└── speedup_vs_k.png
```

---

# 8. Run a larger experiment

Once the small test works, use:

```powershell
.\benchmark.exe results\benchmark.csv 1000 512 5
```

This tests:

```text
n = 1000
k = 2, 4, 8, ..., 512
5 repetitions
```

Then regenerate the graphs:

```powershell
python scripts\plot_results.py results\benchmark.csv
```

---

# 9. What you should observe

The theoretical complexities are:

```text
Sequential merging : Θ(nk²)
Pairwise merging   : Θ(nk log k)
```

As `k` increases, pairwise merging should generally become much faster than sequential merging.

For very small inputs, the measured results may look noisy because of:

- timer resolution
- memory allocation
- CPU scheduling
- cache effects
- compiler optimizations

This is normal.

---

# 10. Files to commit to GitHub

After you generate your own results, your repository can contain:

```text
merging-k-sorted-arrays/
├── include/
│   └── merge_arrays.h
├── src/
│   └── merge_arrays.c
├── benchmark/
│   └── benchmark.c
├── scripts/
│   └── plot_results.py
├── docs/
│   └── complexity.md
├── results/
│   ├── benchmark.csv
│   ├── runtime_vs_k.png
│   └── speedup_vs_k.png
├── .gitignore
├── Makefile
├── requirements.txt
└── README.md
```

Do **not** commit:

```text
benchmark.exe
```

because `.gitignore` excludes executable build artifacts.

---

# 11. Git commands

After confirming everything works:

```powershell
git add .
git status
git commit -m "Implement and benchmark merging k sorted arrays"
git push
```

## Final theoretical result

```text
Method 1: Θ(nk²)
Method 2: Θ(nk log k)
```

Pairwise merging is asymptotically more efficient.
