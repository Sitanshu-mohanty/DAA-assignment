#include <stdio.h>
#include <math.h>
#include <complex.h>

#define MAX 20
#define EPS 1e-10
#define MAX_ITER 5000

typedef double complex cd;

void inputMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);
}

void printMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            printf("%10.4lf ", A[i][j]);

        printf("\n");
    }
}

void copyMatrix(double A[MAX][MAX], double B[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            B[i][j] = A[i][j];
}

void addMatrix(double A[MAX][MAX], double B[MAX][MAX],
               double C[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void multiplyMatrix(double A[MAX][MAX], double B[MAX][MAX],
                    double C[MAX][MAX], int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int isZeroMatrix(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (fabs(A[i][j]) > EPS)
                return 0;

    return 1;
}

int isSymmetric(double A[MAX][MAX], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
            if (fabs(A[i][j] - A[j][i]) > EPS)
                return 0;

    return 1;
}

double determinant(double A[MAX][MAX], int n)
{
    double B[MAX][MAX];
    double det = 1;
    double factor, temp;
    int i, j, k, pivot;

    copyMatrix(A, B, n);

    for (i = 0; i < n; i++)
    {
        pivot = i;

        for (j = i + 1; j < n; j++)
        {
            if (fabs(B[j][i]) > fabs(B[pivot][i]))
                pivot = j;
        }

        if (fabs(B[pivot][i]) < EPS)
            return 0;

        if (pivot != i)
        {
            for (k = 0; k < n; k++)
            {
                temp = B[i][k];
                B[i][k] = B[pivot][k];
                B[pivot][k] = temp;
            }

            det = -det;
        }

        det *= B[i][i];

        for (j = i + 1; j < n; j++)
        {
            factor = B[j][i] / B[i][i];

            for (k = i; k < n; k++)
                B[j][k] -= factor * B[i][k];
        }
    }

    return det;
}

void transposeInPlace(double A[MAX][MAX], int n)
{
    int i, j;
    double temp;

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}

void qrDecomposition(cd A[MAX][MAX],
                     cd Q[MAX][MAX],
                     cd R[MAX][MAX],
                     int n)
{
    cd v[MAX];
    cd dot;
    double norm;
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            Q[i][j] = 0;
            R[i][j] = 0;
        }
    }

    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n; i++)
            v[i] = A[i][j];

        for (k = 0; k < j; k++)
        {
            dot = 0;

            for (i = 0; i < n; i++)
                dot += conj(Q[i][k]) * A[i][j];

            R[k][j] = dot;

            for (i = 0; i < n; i++)
                v[i] -= dot * Q[i][k];
        }

        norm = 0;

        for (i = 0; i < n; i++)
            norm += pow(cabs(v[i]), 2);

        norm = sqrt(norm);

        if (norm < EPS)
            continue;

        R[j][j] = norm;

        for (i = 0; i < n; i++)
            Q[i][j] = v[i] / norm;
    }
}

void complexMultiply(cd A[MAX][MAX],
                     cd B[MAX][MAX],
                     cd C[MAX][MAX],
                     int n)
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}

int converged(cd A[MAX][MAX], int n)
{
    int i, j;

    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (cabs(A[i][j]) > EPS)
                return 0;
        }
    }

    return 1;
}

void printComplex(cd z)
{
    double real = creal(z);
    double imag = cimag(z);

    if (fabs(imag) < EPS)
        printf("%.6lf", real);
    else if (imag >= 0)
        printf("%.6lf + %.6lfi", real, imag);
    else
        printf("%.6lf - %.6lfi", real, -imag);
}

void eigenQR(double A[MAX][MAX], int n)
{
    cd H[MAX][MAX];
    cd Q[MAX][MAX];
    cd R[MAX][MAX];
    cd T[MAX][MAX];
    cd V[MAX][MAX];

    int i, j, iter;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            H[i][j] = A[i][j];

            if (i == j)
                V[i][j] = 1.0;
            else
                V[i][j] = 0.0;
        }
    }

    for (iter = 0; iter < MAX_ITER; iter++)
    {
        qrDecomposition(H, Q, R, n);

        complexMultiply(R, Q, T, n);

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                H[i][j] = T[i][j];

        complexMultiply(V, Q, T, n);

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                V[i][j] = T[i][j];

        if (converged(H, n))
            break;
    }

    printf("\nEigenvalues:\n");

    for (i = 0; i < n; i++)
    {
        printf("Lambda%d = ", i + 1);
        printComplex(H[i][i]);
        printf("\n");
    }

    printf("\nEigenvectors:\n");

    for (j = 0; j < n; j++)
    {
        printf("\nFor Lambda%d = ", j + 1);
        printComplex(H[j][j]);
        printf("\n");

        for (i = 0; i < n; i++)
        {
            printf("v%d = ", i + 1);
            printComplex(V[i][j]);
            printf("\n");
        }
    }
}

int main()
{
    int n;
    double A[MAX][MAX];
    double B[MAX][MAX];
    double C[MAX][MAX];
    double TA[MAX][MAX];
    double TB[MAX][MAX];

    double detA, detB;

    printf("Enter order of square matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid matrix size.\n");
        return 1;
    }

    printf("\nEnter Matrix A:\n");
    inputMatrix(A, n);

    printf("\nEnter Matrix B:\n");
    inputMatrix(B, n);

    printf("\n1. MATRIX ADDITION\n");

    addMatrix(A, B, C, n);

    printf("\nA + B:\n");
    printMatrix(C, n);

    printf("\n2. MATRIX MULTIPLICATION\n");

    multiplyMatrix(A, B, C, n);

    printf("\nA * B:\n");
    printMatrix(C, n);

    printf("\n3. ZERO MATRIX CHECK\n");

    printf("\nMatrix A: ");

    if (isZeroMatrix(A, n))
        printf("A is a zero matrix.\n");
    else
        printf("A is not a zero matrix.\n");

    printf("Matrix B: ");

    if (isZeroMatrix(B, n))
        printf("B is a zero matrix.\n");
    else
        printf("B is not a zero matrix.\n");

    printf("\n4. SYMMETRIC MATRIX CHECK\n");

    printf("\nMatrix A: ");

    if (isSymmetric(A, n))
        printf("A is symmetric.\n");
    else
        printf("A is not symmetric.\n");

    printf("Matrix B: ");

    if (isSymmetric(B, n))
        printf("B is symmetric.\n");
    else
        printf("B is not symmetric.\n");

    printf("\n5. DETERMINANT\n");

    detA = determinant(A, n);
    detB = determinant(B, n);

    printf("det(A) = %.6lf\n", detA);
    printf("det(B) = %.6lf\n", detB);

    printf("\n6. TRANSPOSE IN-SITU\n");

    copyMatrix(A, TA, n);
    copyMatrix(B, TB, n);

    transposeInPlace(TA, n);
    transposeInPlace(TB, n);

    printf("\nTranspose of A:\n");
    printMatrix(TA, n);

    printf("\nTranspose of B:\n");
    printMatrix(TB, n);

    printf("\n7. EIGENVALUES AND EIGENVECTORS\n");

    printf("\nMatrix A:\n");
    eigenQR(A, n);

    printf("\nMatrix B:\n");
    eigenQR(B, n);

    return 0;
}