#include <stdio.h>
#include <stdlib.h>

int maxSumIncreasingSubsequence(int A[], int n)
{
    int *dp;
    int *prev; 
    int i, j;
    int max_sum;
    int max_idx = 0;
    int *sequence;
    int seq_count = 0;

    dp = (int *)malloc(n * sizeof(int));
    prev = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        dp[i] = A[i];
        prev[i] = -1; 
    }
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (A[j] < A[i] && dp[i] < dp[j] + A[i])
            {
                dp[i] = dp[j] + A[i];
                prev[i] = j; 
            }
        }
    }
    max_sum = dp[0];
    for (i = 1; i < n; i++)
    {
        if (dp[i] > max_sum)
        {
            max_sum = dp[i];
            max_idx = i;
        }
    }
    sequence = (int *)malloc(n * sizeof(int));
    int curr = max_idx;
    while (curr != -1)
    {
        sequence[seq_count++] = A[curr];
        curr = prev[curr];
    }
    printf("Maximum Sum Increasing Subsequence:");
    for (i = seq_count - 1; i >= 0; i--)
    {
        printf("%d", sequence[i]);
        if (i > 0)
        {
            printf(" + ");
        }
    }
    printf(" = %d\n", max_sum);

    free(dp);
    free(prev);
    free(sequence);

    return max_sum;
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

    printf("Enter the positive integer elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }
    result = maxSumIncreasingSubsequence(A, n);
    free(A);
    return 0;
}