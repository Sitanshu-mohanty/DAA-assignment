#!/usr/bin/env python3

import argparse
from pathlib import Path

import matplotlib.pyplot as plt
import pandas as pd


def load_results(csv_path: Path) -> pd.DataFrame:
    data = pd.read_csv(csv_path)

    required_columns = {
        "k",
        "n",
        "sequential_seconds",
        "pairwise_seconds",
        "speedup",
    }

    missing = required_columns - set(data.columns)

    if missing:
        raise ValueError(
            f"Missing required columns: {', '.join(sorted(missing))}"
        )

    return data.sort_values("k")


def create_runtime_plot(data: pd.DataFrame, output_path: Path) -> None:
    plt.figure(figsize=(9, 5.5))

    plt.plot(
        data["k"],
        data["sequential_seconds"],
        marker="o",
        label="Sequential merging",
    )
    plt.plot(
        data["k"],
        data["pairwise_seconds"],
        marker="o",
        label="Pairwise merging",
    )

    plt.xscale("log", base=2)
    plt.yscale("log")

    plt.xlabel("Number of arrays (k)")
    plt.ylabel("Average runtime (seconds)")
    plt.title("Runtime comparison: merging k sorted arrays")
    plt.grid(True, which="both", linestyle="--", alpha=0.35)
    plt.legend()
    plt.tight_layout()

    plt.savefig(output_path, dpi=180)
    plt.close()


def create_speedup_plot(data: pd.DataFrame, output_path: Path) -> None:
    plt.figure(figsize=(9, 5.5))

    plt.plot(
        data["k"],
        data["speedup"],
        marker="o",
        label="Sequential / Pairwise",
    )

    plt.xscale("log", base=2)

    plt.xlabel("Number of arrays (k)")
    plt.ylabel("Speedup (times)")
    plt.title("Pairwise merging speedup")
    plt.grid(True, which="both", linestyle="--", alpha=0.35)
    plt.legend()
    plt.tight_layout()

    plt.savefig(output_path, dpi=180)
    plt.close()


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Generate graphs from the merge benchmark CSV."
    )
    parser.add_argument(
        "csv_file",
        type=Path,
        help="Path to the benchmark CSV file",
    )
    args = parser.parse_args()

    data = load_results(args.csv_file)

    output_directory = args.csv_file.parent
    output_directory.mkdir(parents=True, exist_ok=True)

    runtime_plot = output_directory / "runtime_vs_k.png"
    speedup_plot = output_directory / "speedup_vs_k.png"

    create_runtime_plot(data, runtime_plot)
    create_speedup_plot(data, speedup_plot)

    print(f"Created: {runtime_plot}")
    print(f"Created: {speedup_plot}")


if __name__ == "__main__":
    main()
