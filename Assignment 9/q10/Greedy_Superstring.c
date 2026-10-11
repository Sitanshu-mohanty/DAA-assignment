#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int overlap(char *a, char *b)
{
    int la = strlen(a);
    int lb = strlen(b);
    int max;

    if (la < lb)
        max = la;
    else
        max = lb;

    for (int k = max; k > 0; k--)
    {
        int match = 1;

        for (int i = 0; i < k; i++)
        {
            if (a[la - k + i] != b[i])
            {
                match = 0;
                break;
            }
        }

        if (match)
            return k;
    }

    return 0;
}

char *mergeStrings(char *a, char *b, int ov)
{
    int la = strlen(a);
    int lb = strlen(b);

    char *result = (char *)malloc((la + lb - ov + 1) * sizeof(char));

    if (!result)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    strcpy(result, a);
    strcat(result, b + ov);

    return result;
}

int main()
{
    int n;

    printf("Enter number of strings: ");

    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid input for number of strings.\n");
        return 1;
    }

    while (getchar() != '\n');

    char **s = (char **)malloc(n * sizeof(char *));

    if (!s)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        s[i] = (char *)malloc(256 * sizeof(char));

        if (!s[i])
        {
            printf("Memory allocation failed.\n");
            return 1;
        }

        printf("Enter string %d: ", i + 1);

        if (fgets(s[i], 256, stdin) == NULL)
        {
            printf("Invalid input.\n");
            return 1;
        }

        int len = strlen(s[i]);

        if (len > 0 && s[i][len - 1] == '\n')
            s[i][len - 1] = '\0';
    }

    while (n > 1)
    {
        int maxOverlap = -1;
        int bestI = 0;
        int bestJ = 1;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    continue;

                int ov = overlap(s[i], s[j]);

                if (ov > maxOverlap)
                {
                    maxOverlap = ov;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        char *merged = mergeStrings(s[bestI], s[bestJ], maxOverlap);

        printf("\nMerging: \"%s\" + \"%s\"", s[bestI], s[bestJ]);
        printf(" (Overlap: %d)\n", maxOverlap);
        printf("Merged String: \"%s\"\n", merged);

        char **newS = (char **)malloc((n - 1) * sizeof(char *));

        if (!newS)
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        int index = 0;

        for (int i = 0; i < n; i++)
        {
            if (i != bestI && i != bestJ)
            {
                newS[index] = s[i];
                index++;
            }
        }

        newS[index] = merged;

        free(s[bestI]);
        free(s[bestJ]);
        free(s);

        s = newS;
        n--;
    }

    printf("\nFinal Greedy Superstring: %s\n", s[0]);
    printf("Length: %lu\n", strlen(s[0]));

    free(s[0]);
    free(s);

    return 0;
}