#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    int *P;
    int *dp;
    int *cuts;
    int i, j;
    int max_val;
    int remaining_length;

    printf("Enter the length of the rod (n): ");
    scanf("%d", &n);

    P = (int *)malloc(n * sizeof(int));
    dp = (int *)malloc((n + 1) * sizeof(int));
    cuts = (int *)malloc((n + 1) * sizeof(int));

    printf("Enter the prices for piece lengths 1 to %d:\n", n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &P[i]);
    }
    dp[0] = 0;
    cuts[0] = 0;

    for (i = 1; i <= n; i++)
    {
        max_val = -1;

        for (j = 1; j <= i; j++)
        {
            if (max_val < P[j - 1] + dp[i - j])
            {
                max_val = P[j - 1] + dp[i - j];
                cuts[i] = j;
            }
        }
        dp[i] = max_val;
    }
    printf("\nMaximum Revenue = %d\n", dp[n]);
    printf("Optimal Rod Pieces(positions): ");

    remaining_length = n;

    while (remaining_length > 0)
    {
        printf("%d", cuts[remaining_length]);
        remaining_length = remaining_length - cuts[remaining_length];

        if (remaining_length > 0)
        {
            printf(" + ");
        }
    }
    printf("\n");

    free(P);
    free(dp);
    free(cuts);

    return 0;
}