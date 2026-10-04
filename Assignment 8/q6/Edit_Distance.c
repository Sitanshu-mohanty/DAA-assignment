#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min3(int a, int b, int c)
{
    int result;
    result = a;

    if (b < result)
    {
        result = b;
    }

    if (c < result)
    {
        result = c;
    }
    return result;
}
int main()
{
    char A[1000];
    char B[1000];
    int m, n;
    int **dp;
    int i, j;
    int editDistance;

    printf("Enter first string: ");
    scanf("%s", A);

    printf("Enter second string: ");
    scanf("%s", B);

    m = strlen(A);
    n = strlen(B);

    dp = (int **)malloc((m + 1) * sizeof(int *));

    for (i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (i = 0; i <= m; i++)
    {
        dp[i][0] = i;
    }

    for (j = 0; j <= n; j++)
    {
        dp[0][j] = j;
    }

    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]
                );
            }
        }
    }
    editDistance = dp[m][n];
    printf("\nEdit Distance = %d\n", editDistance);
    printf("Traceback:\n");

    i = m;
    j = n;
    while (i > 0 || j > 0)
    {
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1])
        {
            printf("Match: %c\n", A[i - 1]);
            i--;
            j--;
        }
        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            printf("Substitute: %c -> %c\n", A[i - 1], B[j - 1]);
            i--;
            j--;
        }
        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1)
        {
            printf("Delete: %c\n", A[i - 1]);
            i--;
        }
        else
        {
            printf("Insert: %c\n", B[j - 1]);
            j--;
        }
    }
    for (i = 0; i <= m; i++)
    {
        free(dp[i]);
    }
    free(dp);
    return 0;
}