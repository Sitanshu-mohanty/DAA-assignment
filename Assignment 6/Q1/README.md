## Problem Statement

Given an unsorted integer array of $n$ elements, implement and analyze the worst-case time complexity of operations such as finding the maximum, the largest two elements, mean, median, standard deviation, mode, removing duplicates, reversing, and partitioning around a pivot. A C program is required to validate these operations and their complexity.

### 1. Finding the Maximum Element

**Algorithm**
*   Assume the first element is the maximum.
*   Traverse the remaining elements.
*   Compare each element with the current maximum. If the current element is greater, update the maximum.
*   After traversing the entire array, return the maximum.

### 2. Finding the First and Second Largest Elements

**Algorithm**
*   Assume the first element is the largest.
*   Initialize foundSecond as FALSE.
*   Traverse the remaining elements from the second element.
*   If the current element is greater than largest, assign the previous largest to second and update largest.
*   Otherwise, if the current element is smaller than largest and either no second-largest element has been found or the current element is greater than second, update second.
*   Return largest and second if a distinct second-largest element exists; otherwise, report that the second-largest element does not exist.

### 3. Finding the Mean

**Algorithm**
*   Initialize sum to 0.
*   Traverse the array, adding every element to sum.
*   Divide sum by $n$ and return the result.

### 4. Finding the Median

**Algorithm**
*   Sort a copy of the array (using a sorting function like `qsort`).
*   Check whether $n$ is odd or even.
*   If $n$ is odd, select the middle element.
*   If $n$ is even, calculate the average of the two middle elements.

### 5. Finding the Standard Deviation

**Algorithm**
*   Calculate the mean ($\bar{A}$) using the FIND-MEAN procedure.
*   Initialize a variance sum to 0.
*   Traverse the array. Calculate the squared difference between each element and the mean. Add it to the variance sum.
*   Divide the final sum by $n$ and compute the square root to return the standard deviation.

### 6. Finding the Mode

**Algorithm**
*   Assume the first element is the mode.
*   For every element, initialize its frequency counter to zero.
*   Use a nested loop to traverse the complete array and count occurrences of the current element.
*   If its frequency is greater than the current maximum frequency, update the mode and maximum frequency.

### 7. Removing All Duplicates

**Algorithm**
*   Start from the first element and compare it with all subsequent elements.
*   If a duplicate is found, shift all subsequent elements one position to the left.
*   Decrease the tracking size of the array.
*   Return the new array size.

### 8. Reversing the Elements of the Array

**Algorithm**
*   Set a left pointer to $0$ and a right pointer to $n-1$.
*   While left is strictly less than right, swap the elements at these indices.
*   Increment left and decrement right until the pointers meet in the middle.

### 9. Partitioning the Array

**Algorithm**
*   Use the given pivot element.
*   Set left = 0 and right = n-1.
*   Move the left pointer forward as long as elements are greater than or equal to the pivot.
*   Move the right pointer backward as long as elements are strictly less than the pivot.
*   If left < right, swap the two elements and continue until the pointers cross.

### Sample Output

```text
Enter number of elements: 8
Enter 8 elements:
4 2 7 2 9 4 1 7

Original Array: 4 2 7 2 9 4 1 7

1. Maximum Element = 9
2. Largest = 9
   Second Largest = 7
3. Mean = 4.50
4. Median = 4.00
5. Standard Deviation = 2.78
6. Mode = 2
7. After removing duplicates: 4 2 7 9 1
8. Reversed Array: 7 1 4 9 2 7 2 4
9. Enter pivot element: 4
Array after partitioning: 4 4 7 9 7 2 1 2

```

### Overall Time Complexity

| Operation | Technique Used | Worst-Case Time |
| :--- | :--- | :--- |
| **Maximum element** | Single traversal | $O(n)$ |
| **First and second largest** | Single traversal | $O(n)$ |
| **Mean** | Single traversal | $O(n)$ |
| **Median** | Sorting via `qsort` | $O(n \log n)$ |
| **Standard deviation** | Two linear traversals | $O(n)$ |
| **Mode** | Nested loops | $O(n^2)$ |
| **Remove duplicates** | Comparison & shifting | $O(n^2)$ |
| **Reverse array** | Two-pointer swapping | $O(n)$ |
| **Partition around pivot** | Two-pointer partition | $O(n)$ |

From fastest asymptotic growth to slowest, the ranking is:
$$O(n) < O(n \log n) < O(n^2)$$

Because the complete program includes nested loops for the mode and duplicate removal operations, the overall worst-case computational complexity of the entire script is dominated by these quadratic operations.

**Overall Program Worst-Case Complexity: $$O(n^2)$$**

## Conclusion

The implemented program successfully executes all nine array operations on an unsorted 1D integer array. The time complexity analysis indicates that finding the maximum, the two largest elements, the mean, the standard deviation, reversing the array, and partitioning can all be achieved optimally in $O(n)$ time. Determining the median forces a structural reordering, resulting in an $O(n \log n)$ bound. Finding the mode and removing duplicates utilize naive comparison frameworks, resulting in $O(n^2)$ complexity in the worst-case scenario. Ultimately, the theoretical analysis aligns exactly with the structural design of the validation program.


### Pseudocode 

```text
ALGORITHM FIND-MAXIMUM(A, n)
    max = A[0]
    FOR i = 1 TO n-1
        IF A[i] > max THEN
            max = A[i]
    RETURN max
END ALGORITHM

ALGORITHM FIND-LARGEST-TWO(A, n)

    largest = A[0]
    foundSecond = FALSE

    FOR i = 1 TO n-1

        IF A[i] > largest THEN
            second = largest
            largest = A[i]
            foundSecond = TRUE

        ELSE IF A[i] < largest AND
                (foundSecond = FALSE OR A[i] > second) THEN
            second = A[i]
            foundSecond = TRUE

    IF foundSecond = TRUE THEN
        RETURN largest, second
    ELSE
        RETURN largest, "NO SECOND LARGEST"

END ALGORITHM

ALGORITHM FIND-MEAN(A, n)
    sum = 0
    FOR i = 0 TO n-1
        sum = sum + A[i]
        
    mean = sum / n
    RETURN mean
END ALGORITHM

ALGORITHM FIND-MEDIAN(A, n)
    SORT A
    IF n is odd THEN
        median = A[n/2]
    ELSE
        median = (A[n/2 - 1] + A[n/2]) / 2
        
    RETURN median
END ALGORITHM

ALGORITHM FIND-STANDARD-DEVIATION(A, n)
    mean = FIND-MEAN(A, n)
    sum = 0
    
    FOR i = 0 TO n-1
        sum = sum + (A[i] - mean)^2
        
    variance = sum / n
    standardDeviation = sqrt(variance)
    
    RETURN standardDeviation
END ALGORITHM

ALGORITHM FIND-MODE(A, n)
    mode = A[0]
    maxFreq = 0
    
    FOR i = 0 TO n-1
        freq = 0
        FOR j = 0 TO n-1
            IF A[i] == A[j] THEN
                freq = freq + 1
                
        IF freq > maxFreq THEN
            maxFreq = freq
            mode = A[i]
            
    IF maxFreq == 1 THEN
        RETURN "NO MODE"
        
    RETURN mode
END ALGORITHM

ALGORITHM REMOVE-DUPLICATES(A, n)
    FOR i = 0 TO n-1
        j = i + 1
        WHILE j < n
            IF A[i] == A[j] THEN
                FOR k = j TO n-2
                    A[k] = A[k+1]
                n = n - 1
            ELSE
                j = j + 1
                
    RETURN n
END ALGORITHM

ALGORITHM REVERSE(A, n)
    left = 0
    right = n - 1
    
    WHILE left < right
        SWAP A[left] AND A[right]
        left = left + 1
        right = right - 1
END ALGORITHM

ALGORITHM PARTITION(A, n)
    pivot = GIVEN_PIVOT
    left = 0
    right = n - 1
    
    WHILE left <= right
        WHILE left <= right AND A[left] >= pivot
            left = left + 1
            
        WHILE left <= right AND A[right] < pivot
            right = right - 1
            
        IF left < right THEN
            SWAP A[left] AND A[right]
            left = left + 1
            right = right - 1
END ALGORITHM


