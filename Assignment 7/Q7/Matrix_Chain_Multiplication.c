#include <stdio.h>

#define MAX 20

long long m[MAX][MAX];
int s[MAX][MAX];

void printOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }
    printf("(");
    printOrder(i, s[i][j]);
    printOrder(s[i][j] + 1, j);
    printf(")");
}
int main()
{
    int n, i, j, k, length;
    int p[MAX];
    long long cost;

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n <= 0 || n >= MAX)
    {
        printf("Invalid number of matrices.\n");
        return 1;
    }
    printf("Enter %d dimensions: ", n + 1);
    for (i = 0; i <= n; i++)
        scanf("%d", &p[i]);

    for (i = 1; i <= n; i++)
        m[i][i] = 0;

    for (length = 2; length <= n; length++)
    {
        for (i = 1; i <= n - length + 1; i++)
        {
            j = i + length - 1;
            k = i;

            m[i][j] = m[i][k] +
                      m[k + 1][j] +
                      (long long)p[i - 1] * p[k] * p[j];

            s[i][j] = k;
            for (k = i + 1; k < j; k++)
            {
                cost = m[i][k] +
                       m[k + 1][j] +
                       (long long)p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
    printf("\nMinimum number of scalar multiplications = %lld\n", m[1][n]);

    printf("Optimal multiplication order = ");
    printOrder(1, n);
    printf("\n");
    return 0;
}