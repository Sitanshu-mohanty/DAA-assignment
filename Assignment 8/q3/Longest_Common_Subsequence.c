#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    char X[1000], Y[1000];
    int m, n;
    int i, j;
    int **dp;
    char *lcs;
    int index;

    printf("Enter first sequence: ");
    scanf("%s", X);

    printf("Enter second sequence: ");
    scanf("%s", Y);

    m = strlen(X);
    n = strlen(Y);

    dp = (int **)malloc((m + 1) * sizeof(int *));

    for (i = 0; i <= m; i++)
    {
        dp[i] = (int *)malloc((n + 1) * sizeof(int));
    }

    for (i = 0; i <= m; i++)
    {
        dp[i][0] = 0;
    }

    for (j = 0; j <= n; j++)
    {
        dp[0][j] = 0;
    }

    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    lcs = (char *)malloc((dp[m][n] + 1) * sizeof(char));

    index = dp[m][n];
    lcs[index] = '\0';

    i = m;
    j = n;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];
            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("Length of LCS = %d\n", dp[m][n]);
    printf("LCS = %s\n", lcs);

    free(lcs);

    for (i = 0; i <= m; i++)
    {
        free(dp[i]);
    }

    free(dp);

    return 0;
}