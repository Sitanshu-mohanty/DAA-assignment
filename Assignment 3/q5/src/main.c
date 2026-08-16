#include <stdio.h>
#include <stdlib.h>

void add(int n, long long a[n][n], long long b[n][n],
         long long c[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] + b[i][j];
}

void sub(int n, long long a[n][n], long long b[n][n],
         long long c[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            c[i][j] = a[i][j] - b[i][j];
}

/*
    Multiply two special-pattern matrices.

    A = [A1 A2]
        [A2 A1]

    B = [B1 B2]
        [B2 B1]

    Use:
        X = (A1 + A2)(B1 + B2)
        Y = (A1 - A2)(B1 - B2)

    Then:
        P = (X + Y) / 2
        Q = (X - Y) / 2

    Result:
        C = [P Q]
            [Q P]
*/
void multiply(int n, long long a[n][n], long long b[n][n],
              long long c[n][n])
{
    if (n == 1)
    {
        c[0][0] = a[0][0] * b[0][0];
        return;
    }

    int m = n / 2;

    long long (*a1)[m] = malloc(m * sizeof(*a1));
    long long (*a2)[m] = malloc(m * sizeof(*a2));
    long long (*b1)[m] = malloc(m * sizeof(*b1));
    long long (*b2)[m] = malloc(m * sizeof(*b2));

    long long (*x1)[m] = malloc(m * sizeof(*x1));
    long long (*x2)[m] = malloc(m * sizeof(*x2));
    long long (*y1)[m] = malloc(m * sizeof(*y1));
    long long (*y2)[m] = malloc(m * sizeof(*y2));

    long long (*x)[m] = malloc(m * sizeof(*x));
    long long (*y)[m] = malloc(m * sizeof(*y));

    if (!a1 || !a2 || !b1 || !b2 ||
        !x1 || !x2 || !y1 || !y2 || !x || !y)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    /*
        Because the matrix has the special form,
        we only need the two different blocks.
    */
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            a1[i][j] = a[i][j];
            a2[i][j] = a[i][j + m];

            b1[i][j] = b[i][j];
            b2[i][j] = b[i][j + m];
        }
    }

    add(m, a1, a2, x1);
    add(m, b1, b2, x2);
    multiply(m, x1, x2, x);

    sub(m, a1, a2, y1);
    sub(m, b1, b2, y2);
    multiply(m, y1, y2, y);

    /*
        Build P = (X + Y) / 2
        and   Q = (X - Y) / 2.
    */
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            long long p = (x[i][j] + y[i][j]) / 2;
            long long q = (x[i][j] - y[i][j]) / 2;

            c[i][j] = p;
            c[i][j + m] = q;
            c[i + m][j] = q;
            c[i + m][j + m] = p;
        }
    }

    free(a1);
    free(a2);
    free(b1);
    free(b2);
    free(x1);
    free(x2);
    free(y1);
    free(y2);
    free(x);
    free(y);
}

int powerOfTwo(int n)
{
    if (n < 1)
        return 0;

    while (n > 1)
    {
        if (n % 2 != 0)
            return 0;
        n /= 2;
    }

    return 1;
}

int isSpecial(int n, long long a[n][n])
{
    if (n == 1)
        return 1;

    int m = n / 2;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (a[i + m][j] != a[i][j + m])
                return 0;

            if (a[i + m][j + m] != a[i][j])
                return 0;
        }
    }

    /* The two different blocks must also be special recursively. */
    long long (*a1)[m] = malloc(m * sizeof(*a1));
    long long (*a2)[m] = malloc(m * sizeof(*a2));

    if (!a1 || !a2)
    {
        free(a1);
        free(a2);
        return 0;
    }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
        {
            a1[i][j] = a[i][j];
            a2[i][j] = a[i][j + m];
        }

    int ok = isSpecial(m, a1) && isSpecial(m, a2);

    free(a1);
    free(a2);

    return ok;
}

void printMatrix(int n, long long a[n][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%lld ", a[i][j]);

        printf("\n");
    }
}

int main(void)
{
    int n;

    printf("========== SPECIAL-PATTERN MATRIX MULTIPLICATION ==========\n\n");

    printf("Enter matrix size (power of 2): ");
    scanf("%d", &n);

    if (!powerOfTwo(n))
    {
        printf("Matrix size must be a power of 2.\n");
        printf("Use 1, 2, 4, 8, 16, ...\n");
        return 1;
    }

    long long (*a)[n] = malloc(n * sizeof(*a));
    long long (*b)[n] = malloc(n * sizeof(*b));
    long long (*c)[n] = malloc(n * sizeof(*c));

    if (!a || !b || !c)
    {
        printf("Memory allocation failed.\n");
        free(a);
        free(b);
        free(c);
        return 1;
    }

    printf("\nEnter Matrix A (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &a[i][j]);

    printf("\nEnter Matrix B (%d x %d):\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lld", &b[i][j]);

    if (!isSpecial(n, a) || !isSpecial(n, b))
    {
        printf("\nError: Both matrices must have the required special pattern.\n");
        printf("For example, a 4 x 4 matrix must be of the form:\n\n");
        printf("[ A1 A2 ]\n");
        printf("[ A2 A1 ]\n");
        printf("\nwhere A1 and A2 are 2 x 2 blocks.\n");

        free(a);
        free(b);
        free(c);
        return 1;
    }

    multiply(n, a, b, c);

    printf("\n========== RESULT ==========\n");
    printf("A x B:\n");
    printMatrix(n, c);

    printf("\nTime Complexity: O(n^2)\n");
    printf("Extra Space Complexity: O(n^2)\n");

    free(a);
    free(b);
    free(c);

    return 0;
}
