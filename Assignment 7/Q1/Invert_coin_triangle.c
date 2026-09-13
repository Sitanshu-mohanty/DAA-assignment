#include <stdio.h>

long long minimumMoves(long long n)
{
    long long totalCoins = n * (n + 1) / 2;

    return totalCoins / 3;
}
int main()
{
    long long n;

    printf("Enter number of rows in the triangle: ");
    if (scanf("%lld", &n) != 1)
    {
        printf("Invalid input.\n");
        return 1;
    }
    if (n <= 0)
    {
        printf("Invalid input. Number of rows must be greater than 0.\n");
        return 1;
    }

    long long totalCoins = n * (n + 1) / 2;
    long long moves = minimumMoves(n);

    printf("Number of rows in the coin triangle = %lld\n", n);
    printf("Total number of coins = %lld\n", totalCoins);
    printf("Minimum moves for inverting the coin triangle = %lld\n", moves);

    return 0;
}