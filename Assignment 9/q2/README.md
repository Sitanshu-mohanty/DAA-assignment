## Canonical Huffman Codebook Generation

### Problem Statement

Given a set of $n$ symbols and their positive frequencies, generate a Canonical Huffman Codebook to achieve an optimal prefix-free binary encoding. The program uses a min-heap to construct a Huffman tree to determine the optimal code length for each symbol. After determining the lengths, the symbols are sorted by length and lexicographically to generate canonical prefix codes. Finally, the program calculates and outputs the total weighted code length and the expected code length in bits per symbol.

### Algorithm

* Read the number of symbols $n$ and ensure it is greater than zero.
* Dynamically allocate memory to store the symbols, their frequencies, and the resulting code details.
* Read each symbol alongside its frequency, verifying that the frequency is positive, and compute the total cumulative frequency.
* Construct a Min-Heap of size $n$ and initialize it with single-node trees for each symbol.
* Build the Huffman Tree by looping while the heap size is greater than $1$:
  * Extract the two nodes with the lowest frequencies from the min-heap.
  * Create a new internal parent node with a frequency equal to the sum of the two extracted nodes.
  * Assign the extracted nodes as the left and right children of this new parent node.
  * Insert the parent node back into the min-heap.
* Traverse the completed Huffman Tree recursively to find the depth (code length) for each leaf node (symbol).
* Sort the extracted symbols first by their code length in ascending order, and then alphabetically by their character value to satisfy canonical properties.
* Generate the canonical binary codes:
  * Initialize an integer `code = 0` for the first symbol.
  * For subsequent symbols, increment the previous code by $1$.
  * If the current symbol's length is greater than the previous symbol's length, bitwise left-shift the code by the difference in their lengths.
  * Convert the resulting integer into a binary string representation for storage.
* Print the generated symbol, frequency, length, and code for each entry.
* Calculate the total cost by summing the product of frequency and length for all symbols, and compute the expected bits per symbol.
* Free the allocated tree nodes and arrays.

### Pseudocode

```text
CANONICAL-HUFFMAN-CODING(symbols, freq, n)

1. Total_Frequency = 0
2. For i = 0 to n - 1:
       Read symbols[i] and freq[i]
       Total_Frequency += freq[i]

3. h = createMinHeap(n)
4. For i = 0 to n - 1:
       Insert createNode(symbols[i], freq[i]) into h

5. While h.size > 1:
       left = extractMin(h)
       right = extractMin(h)
       parent = createNode('\0', left.frequency + right.frequency)
       parent.left = left
       parent.right = right
       insert(h, parent)

6. root = extractMin(h)
7. codes = array to store lengths
8. count = 0
9. getLengths(root, 0, codes, &count)

10. Sort codes array by:
        a. Code length (ascending)
        b. Symbol character (alphabetical)

11. code = 0
    previous_length = codes[0].length
    
    For i = 0 to n - 1:
        If i > 0:
            code = code + 1
            If codes[i].length > previous_length:
                code = code << (codes[i].length - previous_length)
                
        Convert integer 'code' to binary string in codes[i].code
        previous_length = codes[i].length

12. cost = 0
13. For each symbol in codes:
        Print symbol, frequency, length, code
        cost += frequency * length

14. Print cost
15. Print cost / Total_Frequency as Expected code length

```

### Sample Output

```text
Enter number of symbols: 4
Enter symbol and frequency:
A 5
B 1
C 2
D 2

Canonical Huffman Codebook:
Symbol	Frequency	Length	Code
A	5		1	0
D	2		2	10
B	1		3	110
C	2		3	111

Total weighted code length = 17
Expected code length = 1.70 bits/symbol

```

### Time Complexity Analysis

To determine the time complexity, we analyze the distinct phases of the codebook generation:
* **Heap Construction:** Building the initial min-heap of $n$ elements takes $O(n)$ time.
* **Tree Building:** The while loop runs $n - 1$ times to merge nodes. Each extraction and insertion operation in the min-heap takes $O(\log n)$ time. Thus, building the tree takes $O(n \log n)$ time.
* **Tree Traversal:** Traversing the tree to calculate node depths visits each node exactly once, taking $O(n)$ time.
* **Sorting:** Using qsort to sort the $n$ symbols by length and alphabetical order takes $O(n \log n)$ time.
* **Code Generation:** Iterating through the sorted array to assign canonical codes via bitwise operations takes $O(n)$ time.
* Summing these phases, the $O(n \log n)$ terms dominate the polynomial $O(n)$ operations.

**Final Time Complexity:**
$$O(n \log n)$$

### Conclusion

The Canonical Huffman Coding problem is effectively solved using a Greedy approach facilitated by a Min-Heap data structure to build the optimal tree. By separating the length calculation from the code generation, the algorithm ensures that the resulting binary encodings are predictable, prefix-free, and mathematically optimal for the given frequencies, yielding an overall time complexity of $O(n \log n)$.
