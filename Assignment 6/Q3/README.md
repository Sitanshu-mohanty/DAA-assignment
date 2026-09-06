## Problem Statement

Given two vectors $A$ and $B$ of sizes $m$ and $n$, where $n \ge m$, compute their convolution:
$$C[k] = \sum_{j=0}^{m-1} A[j] B[k-j]$$

Design an $O(n \log n)$ divide and conquer algorithm for this operation and implement a C program to validate your algorithm. 

---

## Algorithm

To achieve the required $O(n \log n)$ time complexity, the algorithm uses the Fast Fourier Transform (FFT) rather than direct calculation (which takes $O(mn)$ time). The convolution theorem states that convolution in the time domain is equivalent to pointwise multiplication in the frequency domain.

1.  **Determine Size:** Find the smallest power of two size, $N$, such that $N \ge m + n - 1$.
2.  **Zero-Pad Vectors:** Place both vectors $A$ and $B$ into arrays of size $N$, initializing the unused positions to zero to prevent circular wrap-around.
3.  **Forward FFT:** Compute the forward Fast Fourier Transform of both padded vectors to convert them into the frequency domain.
4.  **Pointwise Multiplication:** Multiply the transformed complex vectors pointwise: $FC[i] = FA[i] \times FB[i]$.
5.  **Inverse FFT:** Compute the Inverse Fast Fourier Transform (IFFT) of the resulting product vector to convert it back to the time domain.
6.  **Normalize:** Divide each element of the resulting vector by $N$ and extract the real parts to yield the final convolution coefficients.

### Sample Output

```text
Enter size of vector A: 3
Enter size of vector B: 4

Enter elements of vector A:
1 2 3

Enter elements of vector B:
4 5 6 7

Convolution C:
C[0] = 4.000000
C[1] = 13.000000
C[2] = 28.000000
C[3] = 34.000000
C[4] = 32.000000
C[5] = 21.000000

```

## Time Complexity

The FFT-based divide-and-conquer strategy optimizes the sequence of operations significantly. Let $N$ be the padded power-of-two size, where $N < 4n$. Therefore, $N = O(n)$.

| Operation | Worst-Case Time |
| :--- | :--- |
| **Finding FFT size and Padding** | $O(n)$ |
| **FFT of Vector A** | $O(n \log n)$ |
| **FFT of Vector B** | $O(n \log n)$ |
| **Pointwise multiplication** | $O(n)$ |
| **Inverse FFT** | $O(n \log n)$ |
| **Normalization/Output** | $O(n)$ |

Summing these steps:
$T(n) = O(n \log n) + O(n \log n) + O(n) + O(n \log n) + O(n)$

**Overall Time Complexity: $$O(n \log n)$$**

*(Note: Dynamic allocation for recursive temporary complex arrays requires an overall $O(n \log n)$ auxiliary space for this specific implementation.)*

## Conclusion

The FFT-based divide-and-conquer algorithm successfully computes the linear convolution of two vectors of sizes $m$ and $n$. By utilizing zero-padding and transforming the input vectors into the frequency domain, the algorithm circumvents the inefficient $O(mn)$ operations required by direct calculation. The recursive implementation strictly achieves the target $O(n \log n)$ time complexity bound specified in the requirements, validating the mathematical efficiency of Fourier-based convolution.


## Pseudocode

```text
ALGORITHM FFT(A, n, invert)
    IF n == 1 THEN
        RETURN
        
    Create arrays A_even and A_odd of size n/2
    
    FOR i = 0 TO n/2 - 1
        A_even[i] = A[2i]
        A_odd[i] = A[2i+1]
        
    FFT(A_even, n/2, invert)
    FFT(A_odd, n/2, invert)
    
    angle = 2 * PI / n
    IF invert THEN angle = -angle
    
    w = 1
    wn = cos(angle) + i * sin(angle)
    
    FOR i = 0 TO n/2 - 1
        A[i] = A_even[i] + w * A_odd[i]
        A[i + n/2] = A_even[i] - w * A_odd[i]
        w = w * wn
END ALGORITHM

ALGORITHM CONVOLUTION(A, m, B, n)
    size = 1
    WHILE size < m + n - 1
        size = size * 2
        
    Create complex arrays FA and FB of size 'size', padded with 0s
    Copy A into FA and B into FB
    
    FA = FFT(FA, size, FALSE)
    FB = FFT(FB, size, FALSE)
    
    FOR i = 0 TO size - 1
        FA[i] = FA[i] * FB[i]
        
    FA = FFT(FA, size, TRUE)
    
    FOR i = 0 TO m + n - 2
        C[i] = Real(FA[i]) / size
        
    RETURN C
END ALGORITHM

