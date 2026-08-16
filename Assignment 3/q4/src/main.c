#include <stdio.h>
#include <stdlib.h>

void add(int n, int a[n][n], int b[n][n], int c[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
}

void sub(int n, int a[n][n], int b[n][n], int c[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] - b[i][j];
}

void strassen(int n, int a[n][n], int b[n][n], int c[n][n])
{
    if (n == 1)
    {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    int size = n / 2;

    int (*a11)[size] = malloc(size * sizeof(*a11));
    int (*a12)[size] = malloc(size * sizeof(*a12));
    int (*a21)[size] = malloc(size * sizeof(*a21));
    int (*a22)[size] = malloc(size * sizeof(*a22));

    int (*b11)[size] = malloc(size * sizeof(*b11));
    int (*b12)[size] = malloc(size * sizeof(*b12));
    int (*b21)[size] = malloc(size * sizeof(*b21));
    int (*b22)[size] = malloc(size * sizeof(*b22));

    int (*m1)[size] = malloc(size * sizeof(*m1));
    int (*m2)[size] = malloc(size * sizeof(*m2));
    int (*m3)[size] = malloc(size * sizeof(*m3));
    int (*m4)[size] = malloc(size * sizeof(*m4));
    int (*m5)[size] = malloc(size * sizeof(*m5));
    int (*m6)[size] = malloc(size * sizeof(*m6));
    int (*m7)[size] = malloc(size * sizeof(*m7));

    int (*x)[size] = malloc(size * sizeof(*x));
    int (*y)[size] = malloc(size * sizeof(*y));
    int (*p1)[size] = malloc(size * sizeof(*p1));
    int (*p2)[size] = malloc(size * sizeof(*p2));

    if (a11 == NULL || a12 == NULL || a21 == NULL || a22 == NULL ||
        b11 == NULL || b12 == NULL || b21 == NULL || b22 == NULL ||
        m1 == NULL || m2 == NULL || m3 == NULL || m4 == NULL ||
        m5 == NULL || m6 == NULL || m7 == NULL ||
        x == NULL || y == NULL || p1 == NULL || p2 == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            a11[i][j] = a[i][j];
            a12[i][j] = a[i][j + size];
            a21[i][j] = a[i + size][j];
            a22[i][j] = a[i + size][j + size];

            b11[i][j] = b[i][j];
            b12[i][j] = b[i][j + size];
            b21[i][j] = b[i + size][j];
            b22[i][j] = b[i + size][j + size];
        }
    }

    add(size, a11, a22, x);
    add(size, b11, b22, y);
    strassen(size, x, y, m1);

    add(size, a21, a22, x);
    strassen(size, x, b11, m2);

    sub(size, b12, b22, y);
    strassen(size, a11, y, m3);

    sub(size, b21, b11, y);
    strassen(size, a22, y, m4);

    add(size, a11, a12, x);
    strassen(size, x, b22, m5);

    sub(size, a21, a11, x);
    add(size, b11, b12, y);
    strassen(size, x, y, m6);

    sub(size, a12, a22, x);
    add(size, b21, b22, y);
    strassen(size, x, y, m7);

    /*
        C11 = M1 + M4 - M5 + M7
        C12 = M3 + M5
        C21 = M2 + M4
        C22 = M1 - M2 + M3 + M6
    */

    add(size, m1, m4, p1);
    sub(size, p1, m5, p2);
    add(size, p2, m7, p1);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            c[i][j] = p1[i][j];

    add(size, m3, m5, p1);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            c[i][j + size] = p1[i][j];

    add(size, m2, m4, p1);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            c[i + size][j] = p1[i][j];

    sub(size, m1, m2, p1);
    add(size, p1, m3, p2);
    add(size, p2, m6, p1);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            c[i + size][j + size] = p1[i][j];

    free(a11);
    free(a12);
    free(a21);
    free(a22);
    free(b11);
    free(b12);
    free(b21);
    free(b22);
    free(m1);
    free(m2);
    free(m3);
    free(m4);
    free(m5);
    free(m6);
    free(m7);
    free(x);
    free(y);
    free(p1);
    free(p2);
}

int isPowerOfTwo(int n)
{
    if (n <= 0)
        return 0;

    while (n > 1)
    {
        if (n % 2 != 0)
            return 0;

        n /= 2;
    }

    return 1;
}

void printMatrix(int n, int a[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", a[i][j]);

        printf("\n");
    }
}

int main(void)
{
    int n;

    printf("========== STRASSEN MATRIX MULTIPLICATION ==========\n\n");

    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    if (!isPowerOfTwo(n))
    {
        printf("For this lab implementation, n must be a power of 2.\n");
        printf("Try n = 2, 4, 8, 16, ...\n");
        return 1;
    }

    int (*a)[n] = malloc(n * sizeof(*a));
    int (*b)[n] = malloc(n * sizeof(*b));
    int (*c)[n] = malloc(n * sizeof(*c));

    if (a == NULL || b == NULL || c == NULL)
    {
        printf("Memory allocation failed.\n");
        free(a);
        free(b);
        free(c);
        return 1;
    }

    printf("\nEnter elements of Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    printf("\nEnter elements of Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &b[i][j]);

    strassen(n, a, b, c);

    printf("\n========== RESULT ==========\n");
    printf("Matrix A:\n");
    printMatrix(n, a);

    printf("\nMatrix B:\n");
    printMatrix(n, b);

    printf("\nA x B using Strassen's method:\n");
    printMatrix(n, c);

    printf("\nTime Complexity: O(n^log2(7)) ≈ O(n^2.81)\n");

    free(a);
    free(b);
    free(c);

    return 0;
}
