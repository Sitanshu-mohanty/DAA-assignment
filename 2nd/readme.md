# Coin Toss Simulation

## Algorithm

### Main Process
1. **Initialize:** Seed the random number generator using the system's current time.
2. **Setup:** Define the total number of tosses to perform per experiment (e.g., 1,000,000).
3. **Experiment 1 (Fair Coin):**
    * Pass the total tosses and a bias of `0.50` to the simulation function.
    * Print the returned simulated probability.
4. **Experiment 2 (Biased Coin - Heads Heavy):**
    * Pass the total tosses and a bias of `0.75` to the simulation function.
    * Print the returned simulated probability.
5. **Experiment 3 (Biased Coin - Tails Heavy):**
    * Pass the total tosses and a bias of `0.10` to the simulation function.
    * Print the returned simulated probability.
6. **Terminate:** Exit the program.

### Simulation Function
1. **Initialize Counter:** Create a variable `heads_count` and set it to `0`.
2. **Execute Loop:** Start a loop that repeats $n$ times (where $n$ is `num_tosses`).
3. **During Each Iteration:**
    * Generate a random floating-point number between `0.0` and `1.0`.
    * Compare the random number to the provided `bias`.
    * If the random number is strictly less than the `bias`, increment `heads_count` by 1.
4. **Calculate Ratio:** Once the loop finishes, divide `heads_count` by `num_tosses` to find the ratio.
5. **Return Result:** Return this final calculated probability.

---

## Time Complexity

* **Overall Time Complexity:** $O(n)$
    
**Explanation:** 
The `simulate_coin` function runs a single loop $n$ times (where $n$ represents the `num_tosses` variable). Inside the loop, the fundamental operations—generating the random number, performing the division, and evaluating the `if` condition—all execute in constant time, or $O(1)$. 
    
Because the function is called three separate times in the `main` program, the strict mathematical time complexity is $O(3n)$. In Big-O notation, constant multipliers are dropped, simplifying the final worst-case time complexity to linear time, or $O(n)$.