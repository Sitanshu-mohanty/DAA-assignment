#include <stdio.h>
#include <limits.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}
int min(int a, int b)
{
    if (a < b)
        return a;
    else
        return b;
}
int eggDrop(int eggs, int floors)
{
    int dp[eggs + 1][floors + 1];
    int e, f, x;

    for (e = 0; e <= eggs; e++)
        dp[e][0] = 0;

    for (e = 1; e <= eggs; e++)
        dp[e][1] = 1;

    for (f = 0; f <= floors; f++)
        dp[1][f] = f;

    for (e = 2; e <= eggs; e++)
    {
        for (f = 2; f <= floors; f++)
        {
            dp[e][f] = INT_MAX;
            for (x = 1; x <= f; x++)
            {
                int breaks = dp[e - 1][x - 1];
                int survives = dp[e][f - x];
                int drops = 1 + max(breaks, survives);

                if (drops < dp[e][f])
                    dp[e][f] = drops;
            }
        }
    }
    return dp[eggs][floors];
}
int main()
{
    int eggs, floors;
    printf("Enter number of eggs: ");
    scanf("%d", &eggs);

    printf("Enter number of floors: ");
    scanf("%d", &floors);

    if (eggs <= 0 || floors < 0)
    {
        printf("Invalid input.\n");
        return 1;
    }
     else
    {
        printf("Minimum number of droppings = %d\n",
               eggDrop(eggs, floors));
    }

    return 0;
}