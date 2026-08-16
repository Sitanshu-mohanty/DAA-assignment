# Search the Defective Coin — DAA Lab Assignment

## Aim

To use a divide-and-conquer algorithm with a balance weighing scale to find one coin that is lighter than all the other coins, or report that no defective coin exists.

## Problem

There are `n` coins. All normal coins have the same weight. At most one coin may be lighter.

Using a balance scale, find the lighter coin if it exists.

The required running time is:

```text
log2(n) + c
```

for some constant `c`.

## Simple Idea

Divide the possible coins into two equal groups.

```text
             n coins
             /    \
           n/2    n/2
```

### Case 1: Left side is lighter

The defective coin must be in the left group.

### Case 2: Right side is lighter

The defective coin must be in the right group.

### Case 3: Both sides are equal

If `n` is even, there is no defective coin.

If `n` is odd, one coin was not weighed. That extra coin is the only possible defective coin, so compare it with one normal coin.

The problem size is approximately halved after every weighing.

Therefore:

```text
T(n) = T(n/2) + 1
```

and:

```text
T(n) = O(log2 n)
```

## Project Structure

```text
search-defective-coin-lab/
│
├── src/
│   ├── main.c
│   └── benchmark.c
│
├── scripts/
│   └── plot.py
│
├── results/
│   └── benchmark.csv
│
├── README.md
└── .gitignore
```

## 1. Run the Interactive Program

### Windows

```powershell
gcc src/main.c -o coin.exe
.\coin.exe
```

### Linux / macOS

```bash
gcc src/main.c -o coin
./coin
```

Example:

```text
========== SEARCH THE DEFECTIVE COIN ==========

Enter number of coins: 8
Enter the weights of 8 coins:
10 10 10 9 10 10 10 10

========== RESULT ==========

Defective coin: Coin 4
Number of weighings: 3

Time Complexity (number of weighings): O(log2 n)
Extra Space Complexity: O(log n) due to recursion.
```

No defective coin:

```text
Enter number of coins: 8
Enter the weights of 8 coins:
10 10 10 10 10 10 10 10

========== RESULT ==========

No defective coin found.
Number of weighings: 1
```

## 2. Generate Benchmark Data

### Windows

```powershell
gcc src/benchmark.c -o benchmark.exe
.\benchmark.exe
```

### Linux / macOS

```bash
gcc src/benchmark.c -o benchmark
./benchmark
```

The program creates:

```text
results/benchmark.csv
```

## 3. Generate the Graph

Install matplotlib:

```powershell
pip install matplotlib
```

Then run:

```powershell
python scripts/plot.py
```

The graph will be saved as:

```text
results/weighings.png
```

## Benchmark

The benchmark uses:

```text
n = 10
n = 100
n = 1,000
n = 10,000
n = 100,000
n = 1,000,000
```

The defective coin is placed at the beginning so that the algorithm repeatedly follows the lighter half.

The CSV contains:

```text
n,weighings,theoretical
```

The theoretical value is:

```text
ceil(log2(n))
```

which is an upper bound on the number of weighings for this implementation.

## Complexity

Each balance weighing reduces the possible set of coins to approximately half.

```text
n → n/2 → n/4 → n/8 → ...
```

Therefore:

```text
T(n) = T(n/2) + O(1)
```

So the number of balance-scale operations is:

```text
O(log2 n)
```

The recursive implementation uses:

```text
O(log n)
```

stack space.

### Important Note

The C function `weigh()` loops through the coins in the two groups to simulate a physical balance scale. In the algorithm analysis, one physical weighing is treated as one operation, as required by the problem statement. The benchmark therefore measures **number of weighings**, not CPU execution time.

## Conclusion

The experiment shows that the number of balance-scale operations grows logarithmically as the number of coins increases. Since each step approximately halves the set of possible defective coins, the divide-and-conquer solution satisfies the required `log2(n) + c` bound.
