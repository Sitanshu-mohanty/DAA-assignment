#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VALUE (ULLONG_MAX)

unsigned long long collatz_next(unsigned long long n, int *overflow)
{
    if (n % 2 == 0)
    {
        return n / 2;
    }
    else
    {
        if (n > (MAX_VALUE - 1) / 3)
        {
            *overflow = 1;
            return 0;
        }

        return 3 * n + 1;
    }
}

void analyze_single_trajectory(unsigned long long n)
{
    unsigned long long current = n;
    unsigned long long maximum = n;

    unsigned long long capacity = 10;
    unsigned long long steps = 0;
    int overflow = 0;

    unsigned long long *trajectory =
        (unsigned long long *)malloc(capacity * sizeof(unsigned long long));

    if (trajectory == NULL)
    {
        printf("Memory allocation failed.\n");
        return;
    }

    while (current != 1)
    {
        trajectory[steps++] = current;

        if (steps >= capacity)
        {
            capacity *= 2;

            unsigned long long *temp =
                (unsigned long long *)realloc(
                    trajectory,
                    capacity * sizeof(unsigned long long)
                );

            if (temp == NULL)
            {
                printf("Memory reallocation failed.\n");
                free(trajectory);
                return;
            }

            trajectory = temp;
        }

        current = collatz_next(current, &overflow);

        if (overflow)
        {
            printf("Overflow detected at step %llu\n", steps);
            free(trajectory);
            return;
        }

        if (current > maximum)
        {
            maximum = current;
        }
    }

    trajectory[steps++] = 1;

    printf("\nStarting value: %llu\n", n);
    printf("Trajectory: ");

    for (unsigned long long i = 0; i < steps; i++)
    {
        printf("%llu", trajectory[i]);

        if (i < steps - 1)
        {
            printf(" -> ");
        }
    }

    printf("\nSteps: %llu\n", steps - 1);
    printf("Maximum value: %llu\n", maximum);

    free(trajectory);
}

void analyze_interval(unsigned long long a, unsigned long long b)
{
    unsigned long long max_steps = 0;
    unsigned long long start_max_steps = a;

    unsigned long long absolute_max_val = 0;
    unsigned long long start_max_val = a;

    printf("\nAnalyzing interval [%llu, %llu]...\n", a, b);

    for (unsigned long long n = a; ; n++)
    {
        unsigned long long current = n;
        unsigned long long steps = 0;
        unsigned long long peak = current;
        int overflow = 0;

        while (current != 1)
        {
            current = collatz_next(current, &overflow);

            if (overflow)
            {
                break;
            }

            if (current > peak)
            {
                peak = current;
            }

            steps++;
        }

        if (!overflow)
        {
            if (steps > max_steps)
            {
                max_steps = steps;
                start_max_steps = n;
            }

            if (peak > absolute_max_val)
            {
                absolute_max_val = peak;
                start_max_val = n;
            }
        }

        if (n == b)
        {
            break;
        }
    }

    printf("\nInterval Summary:\n");
    printf("- Longest sequence: %llu steps (Started at %llu)\n",
           max_steps, start_max_steps);

    printf("- Highest value reached: %llu (Started at %llu)\n",
           absolute_max_val, start_max_val);
}

int main()
{
    unsigned long long n, a, b;

    printf("Enter a single starting value (n >= 1) to view its full trajectory: ");
    scanf("%llu", &n);

    if (n >= 1)
    {
        analyze_single_trajectory(n);
    }
    else
    {
        printf("Invalid starting value.\n");
    }

    printf("\nEnter the interval [a, b] for summary analysis: ");
    scanf("%llu %llu", &a, &b);

    if (a < 1 || b < 1 || a > b)
    {
        printf("Invalid interval.\n");
        return 0;
    }

    analyze_interval(a, b);

    return 0;
}