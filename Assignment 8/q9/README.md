## Q9.Collatz Sequence Analysis

### Problem Statement
Given a positive integer $n$, generate its Collatz trajectory using the following rules:
* If $n$ is even, divide it by 2.
* If $n$ is odd, calculate $3n + 1$.
* Continue until the value becomes 1.

The program should display the complete trajectory, number of steps, and maximum value reached. It should also analyze an interval $[a, b]$ to find the number having the longest sequence and the highest value reached. Overflow during the $3n + 1$ operation must also be detected.

### Algorithm

A. Collatz Next Value
* Check whether the current number is even. If it is even, calculate:
  $$n = \frac{n}{2}$$
* If it is odd, check whether calculating $3n + 1$ will cause an unsigned integer overflow using the condition:
  $$n > \frac{\text{ULLONG\_MAX} - 1}{3}$$
* If overflow is possible, set the overflow flag. Otherwise, calculate:
  $$n = 3n + 1$$

B. Single Trajectory Analysis
* Initialize the current value and maximum value with the starting number.
* Dynamically allocate memory for storing the trajectory.
* Continue generating Collatz values until $1$ is reached, expanding capacity using `realloc()` as needed.
* Track the maximum value encountered and safely terminate if overflow occurs.
* Display the starting value, complete trajectory, number of steps, and peak value.

C. Interval Analysis
* Iterate through every starting value from $a$ to $b$.
* For each value, generate its sequence, count steps, and track the highest peak reached.
* Record the values producing the longest sequence and the highest peak, then display the interval summary.

### Pseudocode

```text
COLLATZ-NEXT(n)

1. If n is even:
      Return n / 2

2. Otherwise:
      If 3n + 1 will exceed maximum unsigned long long value:
          Set overflow = 1
          Return 0

      Return 3n + 1

ANALYZE-SINGLE-TRAJECTORY(n)

1. Set current = n
2. Set maximum = n
3. Set steps = 0
4. Create a dynamic array trajectory.

5. While current != 1:
      Store current in trajectory.
      Increase steps.

      If trajectory is full:
          Double its capacity using realloc.

      Calculate the next Collatz value.

      If overflow occurs:
          Display overflow message and stop.

      If current > maximum:
          Update maximum.

6. Store 1 in trajectory.

7. Display:
      Starting value
      Complete trajectory
      Number of steps
      Maximum value reached

ANALYZE-INTERVAL(a, b)

1. Set max_steps = 0
2. Set absolute_max_val = 0

3. For every n from a to b:
      Set current = n
      Set steps = 0
      Set peak = n

      While current != 1:
          Calculate next Collatz value.

          If overflow occurs:
              Skip this value.

          If current > peak:
              Update peak.

          Increase steps.

      If steps > max_steps:
          Update max_steps and starting value.

      If peak > absolute_max_val:
          Update absolute_max_val and starting value.

4. Display:
      Longest sequence and its starting value.
      Highest value reached and its starting value.

```

### Sample Output

```text

Enter a single starting value (n >= 1) to view its full trajectory: 6
Starting value: 6
Trajectory: 6 -> 3 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
Steps: 8
Maximum value: 16

Enter the interval [a, b] for summary analysis: 1 10
Analyzing interval [1, 10]...

Interval Summary:
- Longest sequence: 19 steps (Started at 9)
- Highest value reached: 52 (Started at 9)

```

### Time Complexity Analysis

* **Single Starting Value:** Let $T(n)$ be the number of steps required for the sequence to reach $1$. Each step takes constant time $O(1)$, resulting in:
  $$T(n) = O(T(n))$$
  *(Note: The exact upper bound for Collatz steps remains an open mathematical problem).*

* **Interval Analysis:** For an interval $[a, b]$, summing the steps across all elements yields:
  $$T_{\text{interval}} = O\left(\sum_{k=a}^{b} T(k)\right)$$
  Using the maximum number of steps $T_{\max}$ in the interval, this can be upper-bounded by:
  $$T_{\text{interval}} = O((b - a + 1)T_{\max})$$

**Final Time Complexity:**
$$O\left(\sum_{k=a}^{b} T(k)\right)$$

### Conclusion

The Collatz Sequence Analysis program is successfully implemented by repeatedly applying the even and odd rules until the value reaches $1$. It dynamically manages memory to store trajectories, tracks step counts and peak values, and includes safety checks for integer overflow during the $3n + 1$ operation. Additionally, interval analysis efficiently scans ranges to identify starting values with the longest sequences and highest peaks. 

However, it is important to note that the Collatz conjecture remains a famous unsolved problem in mathematics. Because it has not been proven mathematically whether every positive integer eventually reaches $1$, this computational approach cannot guarantee termination for all possible values beyond tested intervals or arbitrarily large integers.

