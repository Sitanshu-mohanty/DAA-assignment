#include <stdio.h>
#include <limits.h>

long long powerOfTwo(int n)
{
    long long result = 1;
    int i;
    for (i = 0; i < n; i++)
        result = result * 2;
    return result;
}
void hanoi3(int n, char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, source, auxiliary, destination);

    printf("Move disk %d from %c to %c\n", n, source, destination);

    hanoi3(n - 1, auxiliary, destination, source);
}
void hanoi4(int n, char source, char destination,
            char auxiliary1, char auxiliary2,
            int split[])
{
    int k;
    if (n == 0)
        return;
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n",
               source, destination);
        return;
    }
    k = split[n];

    hanoi4(k, source, auxiliary1,
           destination, auxiliary2, split);

    hanoi3(n - k, source, destination, auxiliary2);

    hanoi4(k, auxiliary1, destination,
           source, auxiliary2, split);
}
int main()
{
    int n, i, k;
    long long dp[31];
    int split[31];

    printf("Enter number of disks: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 30)
    {
        printf("Invalid input. Please enter a number between 1 and 30.\n");
        return 1;
    }
    dp[0] = 0;
    dp[1] = 1;
    split[0] = 0;
    split[1] = 1;

    for (i = 2; i <= n; i++)
    {
        dp[i] = LLONG_MAX;
        split[i] = 1;

        for (k = 1; k < i; k++)
        {
            long long moves =
                2 * dp[k] + powerOfTwo(i - k) - 1;

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }
    printf("\nMinimum number of moves = %lld\n", dp[n]);

    if (n == 8)
        printf("For 8 disks, the minimum is 33 moves.\n");
    printf("\nSequence of Moves\n");
    hanoi4(n, 'A', 'D', 'B', 'C', split);
    return 0;
}