import csv
import matplotlib.pyplot as plt

n = []
actual = []
theoretical = []

with open("results/benchmark.csv", "r") as file:
    data = csv.DictReader(file)

    for row in data:
        n.append(int(row["n"]))
        actual.append(int(row["weighings"]))
        theoretical.append(int(row["theoretical"]))

plt.figure(figsize=(9, 6))

plt.plot(n, actual, marker="o", label="Actual Weighings")
plt.plot(n, theoretical, marker="o", label="Theoretical Upper Bound")

plt.xscale("log")
plt.xlabel("Number of Coins (n)")
plt.ylabel("Number of Weighings")
plt.title("Defective Coin: Weighings vs Input Size")
plt.grid(True)
plt.legend()

plt.tight_layout()
plt.savefig("results/weighings.png", dpi=150)
plt.show()
