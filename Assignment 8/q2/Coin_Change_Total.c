#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V)
{
    long long *dp;
    int i, j;

    dp = (long long *)malloc((V + 1) * sizeof(long long));

    for (i = 0; i <= V; i++)
    {
        dp[i] = 0;
    }

    dp[0] = 1;

    for (i = 0; i < n; i++)
    {
        for (j = coins[i]; j <= V; j++)
        {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    long long result = dp[V];

    free(dp);

    return result;
}

int main()
{
    int n, V;
    int *coins;
    int i;
    long long result;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    coins = (int *)malloc(n * sizeof(int));

    printf("Enter the coin denominations:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &coins[i]);
    }

    printf("Enter target amount: ");
    scanf("%d", &V);

    result = countWays(coins, n, V);

    printf("Total number of ways = %lld\n", result);

    free(coins);

    return 0;
}