#include <stdio.h>
#include <stdlib.h>

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

int longestIncreasingSubsequence(int A[], int n)
{
    int *dp;
    int *parent;
    int *LIS;
    int i, j;
    int result;
    int maxIndex;
    int length;
    int index;

    dp = (int *)malloc(n * sizeof(int));
    parent = (int *)malloc(n * sizeof(int));
    LIS = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        dp[i] = 1;
        parent[i] = -1;
    }

    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
    }

    result = dp[0];
    maxIndex = 0;

    for (i = 1; i < n; i++)
    {
        if (dp[i] > result)
        {
            result = dp[i];
            maxIndex = i;
        }
    }

    length = result;
    index = maxIndex;

    for (i = length - 1; i >= 0; i--)
    {
        LIS[i] = A[index];
        index = parent[index];
    }

    printf("Length of Longest Increasing Subsequence = %d\n", result);
    printf("Longest Increasing Subsequence: ");

    for (i = 0; i < length; i++)
    {
        printf("%d", LIS[i]);

        if (i < length - 1)
        {
            printf(" ");
        }
    }

    printf("\n");

    free(dp);
    free(parent);
    free(LIS);

    return result;
}

int main()
{
    int n;
    int *A;
    int i;
    int result;

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    A = (int *)malloc(n * sizeof(int));

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    result = longestIncreasingSubsequence(A, n);

    free(A);

    return 0;
}