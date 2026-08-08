# Theoretical Analysis

## 1. Standard Merge Sort

Standard Merge Sort divides an array into two approximately equal parts.

For input size `n`:

- 2 recursive calls
- each of size approximately `n/2`
- one linear-time merge

Therefore:

```text
T₂(n) = 2T₂(n/2) + Θ(n)
```

By the Master Theorem:

```text
a = 2
b = 2
f(n) = Θ(n)

n^(log_b a)
= n^(log₂ 2)
= n
```

Thus:

```text
T₂(n) = Θ(n log₂ n)
```

and therefore:

```text
T₂(n) = Θ(n log n)
```

---

## 2. Modified 3-Way Merge Sort

The modified algorithm divides the array into three approximately equal parts.

For input size `n`:

- 3 recursive calls
- each of size approximately `n/3`
- one linear-time three-way merge

Therefore:

```text
T₃(n) = 3T₃(n/3) + Θ(n)
```

By the Master Theorem:

```text
a = 3
b = 3
f(n) = Θ(n)

n^(log_b a)
= n^(log₃ 3)
= n
```

Thus:

```text
T₃(n) = Θ(n log₃ n)
```

and therefore:

```text
T₃(n) = Θ(n log n)
```

---

## 3. Why the different bases do not contradict the same Big-Theta result

The exact logarithmic functions are different:

```text
log₂(n) ≠ log₃(n)
```

For example:

```text
log₂(27) = 4.7549...
log₃(27) = 3
```

However, by change of base:

```text
log₃(n) = log₂(n) / log₂(3)
```

Therefore:

```text
n log₃(n)
= [1 / log₂(3)] n log₂(n)
```

Since:

```text
1 / log₂(3) ≈ 0.63093
```

the difference is only a constant multiplicative factor.

Big-Theta notation ignores constant factors, so:

```text
Θ(n log₂ n)
=
Θ(n log₃ n)
=
Θ(n log n)
```

This is why both algorithms have the same asymptotic classification.

---

## 4. Three-way merge cost

At every merge step, the algorithm chooses the smallest current element among up to three sorted subarrays.

Only a constant number of comparisons is required per output element. Every element is copied into the temporary array and then copied back.

Therefore the three-way merge takes:

```text
Θ(n)
```

time.

This gives the recurrence:

```text
T₃(n) = 3T₃(n/3) + Θ(n)
```

rather than a larger asymptotic merge term.

---

## 5. Recursion depth

The standard algorithm has approximately:

```text
log₂(n)
```

levels.

The modified algorithm has approximately:

```text
log₃(n)
```

levels.

Therefore:

```text
log₃(n) < log₂(n)
```

for `n > 1`.

The three-way algorithm has fewer recursion levels, but that alone does not establish that it is faster. Its merge step has different constant costs.

---

## 6. Experimental normalization

The primary normalized graph uses each algorithm's own theoretical logarithm:

```text
Standard:
T₂(n) / [n log₂(n)]

3-Way:
T₃(n) / [n log₃(n)]
```

This is the most direct experimental correspondence to the two recurrences.

A second graph uses a common base:

```text
T(n) / [n log₂(n)]
```

for both algorithms.

That second graph is also mathematically legitimate as a Big-Theta comparison because replacing `log₃(n)` with `log₂(n)` multiplies the theoretical term by only a constant.

The repository deliberately includes both plots so that the distinction between **exact log bases** and **asymptotic equivalence** is visible.

---

## 7. Space complexity

Both algorithms use an auxiliary temporary array of size `n`.

Therefore:

```text
Auxiliary space = Θ(n)
```

The recursion depth is logarithmic, but the temporary merge buffer dominates the auxiliary space.

---

## 8. Final conclusion

The modified merge sort has:

```text
T₃(n) = 3T₃(n/3) + Θ(n)
       = Θ(n log₃ n)
       = Θ(n log n)
```

Standard Merge Sort has:

```text
T₂(n) = 2T₂(n/2) + Θ(n)
       = Θ(n log₂ n)
       = Θ(n log n)
```

Therefore the correct answer is:

> **The modified three-way Merge Sort has a worst-case running time of Θ(n log n), the same asymptotic complexity as standard Merge Sort. The recursion depths differ because one uses log₂(n) and the other uses log₃(n), but those logarithms differ only by a constant factor.**
