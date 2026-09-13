#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, i, j, idx, seqLen;
    int *sequence;
    int *possible;
    int *next;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);
    if (n <= 1)
    {
        printf("Invalid input. n must be > 1.\n");
        return 0;
    }
    if (n == 2)
    {
        printf("Shooting sequence: 1 1\n");
        printf("Algorithm guarantees a hit for all starting positions.\n");
        return 0;
    }
    seqLen = 2 * n - 4;
    sequence = (int *)malloc(seqLen * sizeof(int));
    possible = (int *)calloc(n + 1, sizeof(int));
    next = (int *)calloc(n + 1, sizeof(int));

    if (sequence == NULL || possible == NULL || next == NULL)
    {
        printf("Memory allocation failed.\n");
        free(sequence);
        free(possible);
        free(next);
        return 0;
    }
    idx = 0;
    for (i = 2; i <= n - 1; i++)
        sequence[idx++] = i;
    for (i = n - 1; i >= 2; i--)
        sequence[idx++] = i;

    printf("Shooting sequence: ");
    for (i = 0; i < seqLen; i++)
        printf("%d ", sequence[i]);
    printf("\n");
    for (i = 1; i <= n; i++)
        possible[i] = 1;
    for (i = 0; i < seqLen; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (possible[j] && j == sequence[i])
                possible[j] = 0;
        }
        if (i == seqLen - 1)
            break;
        for (j = 1; j <= n; j++)
            next[j] = 0;

        for (j = 1; j <= n; j++)
        {
            if (possible[j])
            {
                if (j > 1)
                    next[j - 1] = 1;

                if (j < n)
                    next[j + 1] = 1;
            }
        }
        for (j = 1; j <= n; j++)
            possible[j] = next[j];
    }
    for (i = 1; i <= n; i++)
    {
        if (possible[i])
        {
            printf("The target is not guaranteed to be hit.\n");
            free(sequence);
            free(possible);
            free(next);
            return 0;
        }
    }
    printf("The target is guaranteed to be hit for all starting positions.\n");
    free(sequence);
    free(possible);
    free(next);

    return 0;
}