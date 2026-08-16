#include <stdio.h>

long long strassenMultiplications(int n)
{
    if (n == 1)
        return 1;

    return 7 * strassenMultiplications(n / 2);
}

long long normalMultiplications(int n)
{
    return (long long)n * n * n;
}

int main(void)
{
    int sizes[] = {2, 4, 8, 16, 32, 64, 128};
    int total = sizeof(sizes) / sizeof(sizes[0]);

    FILE *file = fopen("results/comparisons.csv", "w");

    if (file == NULL)
    {
        printf("Could not create results/comparisons.csv\n");
        printf("Make sure the results folder exists.\n");
        return 1;
    }

    fprintf(file, "n,normal_multiplications,strassen_multiplications\n");

    for (int i = 0; i < total; i++)
    {
        int n = sizes[i];

        long long normal = normalMultiplications(n);
        long long strassen = strassenMultiplications(n);

        fprintf(file, "%d,%lld,%lld\n",
                n, normal, strassen);
    }

    fclose(file);

    printf("Comparison completed.\n");
    printf("File created: results/comparisons.csv\n");

    return 0;
}
