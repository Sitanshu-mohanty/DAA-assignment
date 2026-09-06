## Problem Statement

Given $n \times n$ square matrices, design a C program to implement, validate, and derive the worst-case computational complexity for seven key matrix operations: addition, multiplication, zero-matrix check, symmetry check, determinant computation, in-place transposition, and calculation of eigenvalues and eigenvectors.

### 1. Matrix Addition

**Algorithm**
*   Iterate through every row $i$ and column $j$.
*   Add the corresponding elements of matrix A and matrix B: $C[i][j] = A[i][j] + B[i][j]$.

### 2. Matrix Multiplication

**Algorithm**
*   Select a row $i$ of A and a column $j$ of B.
*   Initialize $C[i][j]$ to zero.
*   Multiply corresponding elements and add them to compute the dot product: $C[i][j] = \sum_{k=0}^{n-1} A[i][k] B[k][j]$.
*   Repeat for every element of C.

### 3. Checking for a Zero Matrix

**Algorithm**
*   Traverse every element of the matrix.
*   Check whether its absolute value is strictly greater than a small tolerance (EPS = 1e-10). If yes, return `FALSE`.
*   If all elements satisfy the condition, return `TRUE`.

### 4. Checking for a Symmetric Matrix

**Algorithm**
*   Traverse the rows $i$ from 0 to $n-1$.
*   For each row, traverse the columns $j$ starting from $i+1$ (checking only the upper triangular part).
*   Compare $A[i][j]$ and $A[j][i]$. If they differ by more than EPS, return `FALSE`.
*   If all pairs match, return `TRUE`.

### 5. Computing the Determinant

**Algorithm**
*   Copy the original matrix into a temporary matrix B to avoid modifying the input.
*   Initialize `det` to 1.
*   For each column $i$, find the row with the largest absolute pivot and swap rows if necessary (changing the sign of `det` upon swapping).
*   Multiply `det` by the pivot element.
*   Perform Gaussian elimination to eliminate elements below the pivot.
*   Return the final calculated determinant.

### 6. In-Place Matrix Transposition

**Algorithm**
*   Start from the first row and consider only elements above the main diagonal.
*   Swap $A[i][j]$ with $A[j][i]$.
*   Continue until the entire upper triangular portion is processed.

### 7. Finding Eigenvalues and Eigenvectors (QR Iteration)

**Algorithm**
*   Initialize matrix H as a copy of A and matrix V as an Identity Matrix.
*   Iteratively apply QR Decomposition on H ($H = Q \times R$).
*   Update H as $R \times Q$ and V as $V \times Q$.
*   Check for convergence (elements below the main diagonal are $\leq$ EPS).
*   Upon convergence, the diagonal entries of H represent the eigenvalues, and the columns of V represent the eigenvectors.

### Sample Output

```text
Enter order of square matrices: 2

Enter Matrix A:
1 2
3 4

Enter Matrix B:
5 6
7 8

1. MATRIX ADDITION

A + B:
    6.0000     8.0000 
   10.0000    12.0000 

2. MATRIX MULTIPLICATION

A * B:
   19.0000    22.0000 
   43.0000    50.0000 

3. ZERO MATRIX CHECK

Matrix A: A is not a zero matrix.
Matrix B: B is not a zero matrix.

4. SYMMETRIC MATRIX CHECK

Matrix A: A is not symmetric.
Matrix B: B is not symmetric.

5. DETERMINANT
det(A) = -2.000000
det(B) = -2.000000

6. TRANSPOSE IN-SITU

Transpose of A:
    1.0000     3.0000 
    2.0000     4.0000 

Transpose of B:
    5.0000     7.0000 
    6.0000     8.0000 

7. EIGENVALUES AND EIGENVECTORS

Matrix A:

Eigenvalues:
Lambda1 = 5.372281
Lambda2 = -0.372281

Eigenvectors:

For Lambda1 = 5.372281
v1 = 0.415974
v2 = 0.909377

For Lambda2 = -0.372281
v1 = -0.909377
v2 = 0.415974

Matrix B:

Eigenvalues:
Lambda1 = 13.152067
Lambda2 = -0.152067

Eigenvectors:

For Lambda1 = 13.152067
v1 = 0.592764
v2 = 0.805376

For Lambda2 = -0.152067
v1 = -0.805376
v2 = 0.592764

```

### Overall Time Complexity 

| Operation | Technique Used | Worst-Case Time |
| :--- | :--- | :--- |
| **Matrix Addition** | Two nested loops | $O(n^2)$ |
| **Matrix Multiplication** | Three nested loops | $O(n^3)$ |
| **Zero Matrix Check** | Matrix traversal | $O(n^2)$ |
| **Symmetric Matrix Check** | Upper-triangular comparison | $O(n^2)$ |
| **Determinant** | Gaussian elimination | $O(n^3)$ |
| **In-place Transpose** | Upper-triangular swaps | $O(n^2)$ |
| **Eigenvalues/Eigenvectors** | QR iteration | $O(n^3)$* |

*\*Note: The QR iteration is $O(k n^3)$ where $k$ is the number of iterations. Because the program enforces a fixed maximum iteration limit (`MAX_ITER = 5000`), $k$ is treated as a constant, resulting in an asymptotic complexity of $O(n^3)$.*

The operations are performed sequentially. The highest-order operations (multiplication, determinant, and eigenvalue calculation) dictate the overall computational bound.

*   **Overall Program Worst-Case Time Complexity:** $$O(n^3)$$
*   **Overall Program Space Complexity:** $$O(n^2)$$ *(Multiple $n \times n$ matrices are allocated, but the amount is constant with respect to $n$.)*


### Conclusion

The program successfully implements the seven square-matrix operations specified in the requirements. Matrix addition, zero-matrix checking, symmetric-matrix checking, and in-place transposition require $O(n^2)$ time. Standard matrix multiplication and Gaussian-elimination determinant calculation require $O(n^3)$ time. The QR-based eigenvalue and eigenvector calculation requires $O(k n^3)$ time for $k$ iterations, which reduces to $O(n^3)$ when the maximum iteration count is fixed. Thus, the overall worst-case time complexity of the implemented program is $O(n^3)$, and the space complexity is $O(n^2)$ due to the constant number of auxiliary matrices utilized.

### Pseudocode 

```text
ALGORITHM MATRIX-ADDITION(A, B, C, n)
    FOR i = 0 TO n-1
        FOR j = 0 TO n-1
            C[i][j] = A[i][j] + B[i][j]
    RETURN C
END ALGORITHM

ALGORITHM MATRIX-MULTIPLICATION(A, B, C, n)
    FOR i = 0 TO n-1
        FOR j = 0 TO n-1
            C[i][j] = 0
            FOR k = 0 TO n-1
                C[i][j] = C[i][j] + A[i][k] * B[k][j]
    RETURN C
END ALGORITHM

ALGORITHM IS-ZERO-MATRIX(A, n)
    FOR i = 0 TO n-1
        FOR j = 0 TO n-1
            IF |A[i][j]| > EPS
                RETURN FALSE
    RETURN TRUE
END ALGORITHM

ALGORITHM IS-SYMMETRIC(A, n)
    FOR i = 0 TO n-1
        FOR j = i+1 TO n-1
            IF |A[i][j] - A[j][i]| > EPS
                RETURN FALSE
    RETURN TRUE
END ALGORITHM

ALGORITHM DETERMINANT(A, n)
    B = copy of A
    det = 1
    
    FOR i = 0 TO n-1
        pivot = row having largest |B[row][i]|
        
        IF |B[pivot][i]| < EPS
            RETURN 0
            
        IF pivot != i
            SWAP rows i and pivot
            det = -det
            
        det = det * B[i][i]
        
        FOR j = i+1 TO n-1
            factor = B[j][i] / B[i][i]
            FOR k = i TO n-1
                B[j][k] = B[j][k] - factor * B[i][k]
                
    RETURN det
END ALGORITHM

ALGORITHM TRANSPOSE-IN-PLACE(A, n)
    FOR i = 0 TO n-1
        FOR j = i+1 TO n-1
            temp = A[i][j]
            A[i][j] = A[j][i]
            A[j][i] = temp
END ALGORITHM

ALGORITHM EIGEN-QR(A, n)
    H = A
    V = Identity Matrix
    
    FOR iter = 1 TO MAX_ITER
        Q, R = QR-DECOMPOSITION(H)
        
        T = R * Q
        H = T
        
        T = V * Q
        V = T
        
        IF H is converged
            BREAK
            
    FOR i = 0 TO n-1
        eigenvalue[i] = H[i][i]
        
    eigenvectors = columns of V
END ALGORITHM


