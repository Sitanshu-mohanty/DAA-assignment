#include <stdio.h>

unsigned long long moveCount = 0;
int switches[100];

void display(int n)
{
    int i;

    for (i = n; i >= 1; i--)
        printf("%d", switches[i]);

    printf("\n");
}
void turnOff(int n, int total);
void turnOn(int n, int total);

void turnOff(int n, int total)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        switches[1] = 0;
        moveCount++;
        printf("Move %llu: Toggle S1 -> ", moveCount);
        display(total);
        return;
    }
    turnOff(n - 2, total);

    switches[n] = 0;
    moveCount++;
    printf("Move %llu: Toggle S%d -> ", moveCount, n);
    display(total);

    turnOn(n - 2, total);

    turnOff(n - 1, total);
}
void turnOn(int n, int total)
{
    if (n == 0)
        return;

    if (n == 1)
    {
        switches[1] = 1;
        moveCount++;
        printf("Move %llu: Toggle S1 -> ", moveCount);
        display(total);
        return;
    }

    turnOn(n - 1, total);

    turnOff(n - 2, total);

    switches[n] = 1;
    moveCount++;
    printf("Move %llu: Toggle S%d -> ", moveCount, n);
    display(total);
    turnOn(n - 2, total);
}
int main()
{
    int n, i;
    unsigned long long theoreticalMinimum;
    printf("Enter number of switches: ");

    if (scanf("%d", &n) != 1 || n < 1 || n > 20)
    {
        printf("Invalid input. Please enter a number between 1 and 20.\n");
        return 1;
    }

    for (i = 1; i <= n; i++)
        switches[i] = 1;

    printf("Initial state: ");
    display(n);
    printf("\n");

    turnOff(n, n);

    printf("Final state:   ");
    display(n);
    printf("Total Moves = %llu\n", moveCount);
    theoreticalMinimum = (1ULL << (n + 1)) / 3;

    printf("Theoretical minimum = %llu\n", theoreticalMinimum);

    return 0;
}