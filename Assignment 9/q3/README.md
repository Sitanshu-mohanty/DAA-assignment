## Minimum Refueling Stops

### Problem Statement

Given a target distance $D$, an initial amount of fuel $F$, and a list of $n$ gas stations along the route, determine the minimum number of refueling stops required to reach the target. Each station has a specific distance from the starting point and provides a specific amount of fuel. The vehicle uses one unit of fuel to travel one unit of distance. The algorithm utilizes a Greedy approach combined with a Max-Heap (Priority Queue) to always refuel optimally by retrospectively choosing the passed station with the maximum available fuel only when the vehicle runs out.

### Algorithm

* Read the target distance $D$, the initial fuel $F$, and the total number of stations $n$.
* Dynamically allocate memory and read the distance and fuel capacity for each of the $n$ stations.
* Sort the array of stations in ascending order based on their distance from the starting position.
* Initialize a max-heap array to track the fuel capacities of stations that have been passed.
* Initialize tracking variables: `currentFuel = F`, `currentPosition = 0`, and `stops = 0`.
* Iterate through each station, treating the target destination $D$ as the final $(n+1)$-th point:
  * Calculate the distance to travel from the `currentPosition` to the `nextPosition` (capping the `nextPosition` at $D$).
  * While the `currentFuel` is strictly less than the required distance to travel:
    * If the max-heap is empty, it means there are no reachable stations left to draw fuel from; return `-1` to indicate the target is unreachable.
    * Extract the maximum fuel capacity from the max-heap, add it to `currentFuel`, and increment the `stops` counter.
  * Deduct the traveled distance from `currentFuel` and update `currentPosition` to the `nextPosition`.
  * If the current iteration corresponds to a station (and is not past $D$), insert its fuel capacity into the max-heap.
  * If `currentPosition` reaches $D$, break out of the loop.
* Print the minimum number of refueling stops, or print an error message if the result is `-1`.
* Free the allocated heap and stations arrays.

### Pseudocode

```text
MINIMUM-REFUELING-STOPS(D, F, stations, n)

1. Sort stations by distance in ascending order.
2. Initialize an empty max_heap.
3. currentFuel = F
   currentPosition = 0
   stops = 0

4. For i = 0 to n:
       If i == n:
           nextPosition = D
       Else:
           nextPosition = min(stations[i].distance, D)

       distance_to_travel = nextPosition - currentPosition

       While currentFuel < distance_to_travel:
           If max_heap is empty:
               Return -1  // Target cannot be reached
           
           currentFuel = currentFuel + extractMax(max_heap)
           stops = stops + 1

       currentFuel = currentFuel - distance_to_travel
       currentPosition = nextPosition

       If i < n and stations[i].distance <= D:
           insertMaxHeap(max_heap, stations[i].fuel)

       If currentPosition == D:
           Break

5. Return stops

```
### Sample Output

```text
Enter target distance: 100
Enter initial fuel: 10
Enter number of stations: 4
Enter station distance and fuel:
10 60
20 30
30 30
60 40
Minimum refuelling stops = 2

```

### Time Complexity Analysis

To determine the overall time complexity, we analyze the primary operations executed in the algorithm:
* **Sorting phase:** Sorting the $n$ stations by their distance using `qsort` takes $O(n \log n)$ time.   
* **Iteration phase:** The main loop iterates through the stations $n + 1$ times, costing $O(n)$ operations.   
* **Heap Operations:** Inside the loop, the `insertMaxHeap` and `extractMax` functions are called. In the worst-case scenario, every station is pushed into the heap and later extracted. A single heap insertion or extraction operation takes $O(\log n)$ time, meaning $n$ operations will take $O(n \log n)$ time.   

Summing these independent parts, we get $O(n \log n) + O(n) + O(n \log n)$, which simplifies to the dominant term.

**Final Time Complexity:**
$$O(n \log n)$$

### Conclusion

The Minimum Refueling Stops problem is effectively solved using a Greedy algorithm optimized by a Max-Heap. By postponing the decision to refuel until the tank is entirely empty, and then retroactively choosing the highest-capacity station passed so far, the algorithm accurately guarantees the fewest possible stops. Using a priority queue efficiently manages the dynamic maximum fuel selection, maintaining a highly scalable time complexity of $O(n \log n)$.
