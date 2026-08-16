import csv
import matplotlib.pyplot as plt

n = []
binary = []
ternary = []

with open("results/benchmark.csv", "r") as file:
    data = csv.DictReader(file)

    for row in data:
        n.append(int(row["n"]))
        binary.append(int(row["binary_comparisons"]))
        ternary.append(int(row["ternary_comparisons"]))

plt.plot(n, binary, marker="o", label="Binary Search")
plt.plot(n, ternary, marker="o", label="Ternary Search")

plt.xlabel("Array Size")
plt.ylabel("Average Comparisons")
plt.title("Binary Search vs Ternary Search")
plt.xscale("log")
plt.legend()
plt.grid(True)

plt.savefig("results/comparison.png")
plt.show()
