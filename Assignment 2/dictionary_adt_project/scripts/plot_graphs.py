#!/usr/bin/env python3
"""
Plot benchmark results produced by dictionary_benchmark.c.

Usage:
    python3 scripts/plot_graphs.py

The script creates one PNG per operation in graphs/.
The y-axis is logarithmic because measured times span several orders
of magnitude. The x-axis is logarithmic to make growth rates easier
to compare visually.
"""
from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt

ROOT = Path(__file__).resolve().parents[1]
CSV = ROOT / "results" / "benchmark.csv"
OUT = ROOT / "graphs"
OUT.mkdir(exist_ok=True)

df = pd.read_csv(CSV)

labels = {
    "unsorted_array": "Unsorted array",
    "sorted_array": "Sorted array",
    "singly_unsorted": "Singly linked unsorted",
    "singly_sorted": "Singly linked sorted",
    "doubly_unsorted": "Doubly linked unsorted",
    "doubly_sorted": "Doubly linked sorted",
}
operations = ["search", "insert", "delete", "maximum", "minimum",
              "predecessor", "successor"]

for op in operations:
    sub = df[df["operation"] == op]
    plt.figure(figsize=(10, 6))
    for ds in labels:
        d = sub[sub["data_structure"] == ds]
        plt.plot(d["n"], d["time_ns"], marker="o", linewidth=1.8,
                 label=labels[ds])
    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("Number of elements (n)")
    plt.ylabel("Average time per operation (ns)")
    plt.title(f"Dictionary {op.capitalize()} — empirical growth")
    plt.grid(True, which="both", alpha=0.25)
    plt.legend(fontsize=8)
    plt.tight_layout()
    plt.savefig(OUT / f"{op}.png", dpi=180)
    plt.close()

# Reference growth curves (normalized at n=100) for the three main orders
# appearing in this assignment: O(1), O(log n), and O(n).
import numpy as np
x = np.logspace(2, 5, 200)
base_n = 100.0
plt.figure(figsize=(10, 6))
plt.plot(x, np.ones_like(x), linewidth=2, label="O(1)")
plt.plot(x, np.log2(x) / np.log2(base_n), linewidth=2, label="O(log n)")
plt.plot(x, x / base_n, linewidth=2, label="O(n)")
plt.xscale("log")
plt.yscale("log")
plt.xlabel("n (normalized at n = 100)")
plt.ylabel("Relative growth")
plt.title("Reference asymptotic growth")
plt.grid(True, which="both", alpha=0.25)
plt.legend()
plt.tight_layout()
plt.savefig(OUT / "theoretical_growth.png", dpi=180)
plt.close()

print(f"Created {len(operations) + 1} graphs in {OUT}")
