#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void computeOBST(double p[], double q[], int n)
{
    double **e = (double **)malloc((n + 2) * sizeof(double *));
    double **w = (double **)malloc((n + 2) * sizeof(double *));
    int **root = (int **)malloc((n + 2) * sizeof(int *));

    int i, j, L, r;

    for (i = 0; i <= n + 1; i++)
    {
        e[i] = (double *)malloc((n + 1) * sizeof(double));
        w[i] = (double *)malloc((n + 1) * sizeof(double));
        root[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (i = 1; i <= n + 1; i++)
    {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    for (L = 1; L <= n; L++)
    {
        for (i = 1; i <= n - L + 1; i++)
        {
            j = i + L - 1;
            e[i][j] = DBL_MAX;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (r = i; r <= j; r++)
            {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];

                if (t < e[i][j])
                {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\nMinimum expected search cost: %.4lf\n", e[1][n]);
    printf("Optimal Root = Key %d\n", root[1][n]);

    for (i = 0; i <= n + 1; i++)
    {
        free(e[i]);
        free(w[i]);
        free(root[i]);
    }

    free(e);
    free(w);
    free(root);
}

int main()
{
    int n, i;
    double *p, *q;

    printf("Enter the number of distinct keys (n): ");
    scanf("%d", &n);

    p = (double *)malloc((n + 1) * sizeof(double));
    q = (double *)malloc((n + 1) * sizeof(double));

    printf("Enter the search probabilities for %d keys (p_1 to p_%d):\n", n, n);

    for (i = 1; i <= n; i++)
    {
        scanf("%lf", &p[i]);
    }

    printf("Enter the search probabilities for %d dummy keys (q_0 to q_%d):\n", n + 1, n);

    for (i = 0; i <= n; i++)
    {
        scanf("%lf", &q[i]);
    }

    computeOBST(p, q, n);

    free(p);
    free(q);

    return 0;
}