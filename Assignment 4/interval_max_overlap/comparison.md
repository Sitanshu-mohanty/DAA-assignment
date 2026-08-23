# Comparison of Methods

The following methods can be used to solve the problem.

| Method | Main idea | Time Complexity | Extra Space | Suitable for this problem? |
|---|---|---:|---:|---|
| Brute Force over possible points | Check many points and count how many intervals contain each point | Can be `O(n^2)` or worse depending on the point set | `O(1)` | No, slower |
| Check every interval endpoint | For every endpoint, count the intervals containing it | `O(n^2)` | `O(1)` | Simple but inefficient |
| Sorting / Sweep Line | Convert endpoints to start/end events, sort them, then scan once | `O(n log n)` | `O(n)` | **Yes** |

## Why the sorting method is selected

The question specifically asks for an `O(n log n)` algorithm. Sorting the `2n` endpoint events gives the required complexity.

The scan after sorting is linear, so the sorting step dominates the running time.

This method is also easy to implement in C using the standard `qsort()` function.
