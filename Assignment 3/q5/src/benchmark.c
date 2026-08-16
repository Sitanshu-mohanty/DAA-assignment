#include <stdio.h>
#include <stdlib.h>

long long operations = 0;

void add(int n, long long a[n][n], long long b[n][n],
         long long c[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] + b[i][j];
            operations++;
        }
}

void sub(int n, long long a[n][n], long long b[n][n],
         long long c[n][n])
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            c[i][j] = a[i][j] - b[i][j];
            operations++;
        }
}

void multiply(int n, long long a[n][n], long long b[n][n],
              long long c[n][n])
{
    if (n == 1)
    {
        c[0][0] = a[0][0] * b[0][0];
        operations++;
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

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
        {
            a1[i][j] = a[i][j];
            a2[i][j] = a[i][j + m];
            b1[i][j] = b[i][j];
            b2[i][j] = b[i][j + m];
        }

    add(m, a1, a2, x1);
    add(m, b1, b2, x2);
    multiply(m, x1, x2, x);

    sub(m, a1, a2, y1);
    sub(m, b1, b2, y2);
    multiply(m, y1, y2, y);

    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++)
        {
            /*
                The two assignments below represent
                the arithmetic needed to form P and Q.
            */
            long long p = (x[i][j] + y[i][j]) / 2;
            long long q = (x[i][j] - y[i][j]) / 2;

            operations += 2;

            c[i][j] = p;
            c[i][j + m] = q;
            c[i + m][j] = q;
            c[i + m][j + m] = p;
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

int main(void)
{
    int sizes[] = {2, 4, 8, 16, 32, 64, 128, 256};
    int total = sizeof(sizes) / sizeof(sizes[0]);

    FILE *file = fopen("results/complexity.csv", "w");

    if (file == NULL)
    {
        printf("Could not create results/complexity.csv\n");
        printf("Make sure the results folder exists.\n");
        return 1;
    }

    fprintf(file, "n,operations,n_squared\n");

    for (int s = 0; s < total; s++)
    {
        int n = sizes[s];

        long long (*a)[n] = malloc(n * sizeof(*a));
        long long (*b)[n] = malloc(n * sizeof(*b));
        long long (*c)[n] = malloc(n * sizeof(*c));

        if (!a || !b || !c)
        {
            printf("Memory allocation failed for n = %d\n", n);
            fclose(file);
            free(a);
            free(b);
            free(c);
            return 1;
        }

        /*
            Simple special-pattern matrices.
            A = [1 2; 2 1] recursively in block form.
            B = [2 1; 1 2] recursively in block form.
            Filling by parity also gives the required pattern.
        */
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if ((i % 2) == (j % 2))
                {
                    a[i][j] = 1;
                    b[i][j] = 2;
                }
                else
                {
                    a[i][j] = 2;
                    b[i][j] = 1;
                }
            }

        operations = 0;

        multiply(n, a, b, c);

        fprintf(file, "%d,%lld,%lld\n",
                n, operations, (long long)n * n);

        free(a);
        free(b);
        free(c);
    }

    fclose(file);

    printf("Complexity validation completed.\n");
    printf("File created: results/complexity.csv\n");

    return 0;
}
