#!/usr/bin/env python3

import csv
import math
from pathlib import Path

import matplotlib.pyplot as plt

ROOT = Path(__file__).resolve().parents[1]
DATA = ROOT / "data" / "benchmark_results.csv"
GRAPHS = ROOT / "graphs"
GRAPHS.mkdir(exist_ok=True)

with DATA.open(newline="", encoding="utf-8") as f:
    rows = list(csv.DictReader(f))

n = [int(r["n"]) for r in rows]
merge = [float(r["merge_sort_seconds"]) for r in rows]
three = [float(r["merge_sort_3way_seconds"]) for r in rows]

# 1. Measured runtime.
plt.figure(figsize=(9, 5.5))
plt.plot(n, merge, marker="o", label="Standard Merge Sort")
plt.plot(n, three, marker="o", label="3-Way Merge Sort")
plt.xlabel("Input size, n")
plt.ylabel("Median execution time (seconds)")
plt.title("Measured Runtime: Merge Sort vs. 3-Way Merge Sort")
plt.grid(True, alpha=0.25)
plt.legend()
plt.tight_layout()
plt.savefig(GRAPHS / "runtime_comparison.png", dpi=180)
plt.close()

# 2. Correct recurrence-specific normalization.
# Standard: n log_2(n)
# 3-way:    n log_3(n)
merge_own = [
    t / (x * math.log2(x))
    for x, t in zip(n, merge)
]
three_own = [
    t / (x * math.log(x, 3))
    for x, t in zip(n, three)
]

plt.figure(figsize=(9, 5.5))
plt.plot(n, merge_own, marker="o", label=r"Standard: T(n) / [n log$_2$(n)]")
plt.plot(n, three_own, marker="o", label=r"3-Way: T(n) / [n log$_3$(n)]")
plt.xlabel("Input size, n")
plt.ylabel("Normalized time")
plt.title("Growth Validation Using Each Algorithm's Own Logarithm Base")
plt.grid(True, alpha=0.25)
plt.legend()
plt.tight_layout()
plt.savefig(GRAPHS / "normalized_own_base.png", dpi=180)
plt.close()

# 3. Common-base normalization.
# This is a secondary Big-Theta comparison. The different base
# contributes only a constant factor.
merge_common = [
    t / (x * math.log2(x))
    for x, t in zip(n, merge)
]
three_common = [
    t / (x * math.log2(x))
    for x, t in zip(n, three)
]

plt.figure(figsize=(9, 5.5))
plt.plot(n, merge_common, marker="o", label=r"Standard: T(n) / [n log$_2$(n)]")
plt.plot(n, three_common, marker="o", label=r"3-Way: T(n) / [n log$_2$(n)]")
plt.xlabel("Input size, n")
plt.ylabel("Normalized time")
plt.title(r"Common-Base Θ(n log n) Comparison")
plt.grid(True, alpha=0.25)
plt.legend()
plt.tight_layout()
plt.savefig(GRAPHS / "normalized_common_base.png", dpi=180)
plt.close()

# 4. Theoretical recursion depth.
# Use a smooth theoretical range rather than benchmark points.
x_values = [2 ** (k / 10) for k in range(1, 101)]
log2_values = [math.log2(x) for x in x_values]
log3_values = [math.log(x, 3) for x in x_values]

plt.figure(figsize=(9, 5.5))
plt.plot(x_values, log2_values, label=r"Standard depth: log$_2$(n)")
plt.plot(x_values, log3_values, label=r"3-Way depth: log$_3$(n)")
plt.xscale("log")
plt.xlabel("Input size, n (log scale)")
plt.ylabel("Recursion depth")
plt.title("Theoretical Recursion Depth")
plt.grid(True, alpha=0.25)
plt.legend()
plt.tight_layout()
plt.savefig(GRAPHS / "theoretical_recursion_depth.png", dpi=180)
plt.close()

print("Generated:")
for name in [
    "runtime_comparison.png",
    "normalized_own_base.png",
    "normalized_common_base.png",
    "theoretical_recursion_depth.png",
]:
    print(f"  graphs/{name}")
