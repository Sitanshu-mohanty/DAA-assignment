#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
int minCoinChange(int coins[], int n, int V, int **usedCoins)
{
    int *dp;
    int i, j;
    int result;

    dp = (int *)malloc((V + 1) * sizeof(int));
    *usedCoins = (int *)malloc((V + 1) * sizeof(int));

    dp[0] = 0;
    (*usedCoins)[0] = -1;

    for (i = 1; i <= V; i++)
    {
        dp[i] = V + 1;
        (*usedCoins)[i] = -1;
    }

    for (i = 1; i <= V; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (coins[j] <= i)
            {
                if (dp[i - coins[j]] + 1 < dp[i])
                {
                    dp[i] = dp[i - coins[j]] + 1;
                    (*usedCoins)[i] = coins[j];
                }
            }
        }
    }
    if (dp[V] == V + 1)
    {
        free(dp);
        free(*usedCoins);
        *usedCoins = NULL;
        return -1;
    }
    result = dp[V];
    free(dp);
    return result;
}
int main()
{
    int n, V;
    int *coins;
    int *usedCoins;
    int i;
    int result;
    int amount;
    int first;

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
    result = minCoinChange(coins, n, V, &usedCoins);

    if (result == -1)
    {
        printf("Minimum number of coins = -1\n");
    }
    else
    {
        printf("Minimum number of coins = %d\n", result);
        printf("Coins used: ");

        amount = V;
        first = 1;
        while (amount > 0)
        {
            if (!first)
            {
                printf(" + ");
            }
            printf("%d", usedCoins[amount]);
            amount = amount - usedCoins[amount];
            first = 0;
        }
        printf(" = %d\n", V);
        free(usedCoins);
    }
    free(coins);

    return 0;
}