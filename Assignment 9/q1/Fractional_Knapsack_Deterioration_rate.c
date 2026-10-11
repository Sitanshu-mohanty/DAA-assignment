#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    double value;
    double weight;
    double decay;
    int index;
} Item;

int main()
{
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item *items = (Item *)malloc(n * sizeof(Item));

    printf("Enter value, weight and decay rate for each item:\n");

    for (int i = 0; i < n; i++)
    {
        items[i].index = i + 1;

        printf("Item %d: ", i + 1);
        scanf("%lf %lf %lf",
              &items[i].value,
              &items[i].weight,
              &items[i].decay);
    }                                                                              
    printf("Enter knapsack capacity: ");
    scanf("%lf", &W);

    double time = 0.0;
    double remaining = W;
    double totalValue = 0.0;

    printf("\nSelected items:\n");
    printf("Item\tFraction\tWeight Taken\tTime\t\tDensity\t\tValue\n");

    while (remaining > 1e-9)
    {
        int best = -1;
        double bestDensity = -1e100;

        for (int i = 0; i < n; i++)
        {
            if (items[i].weight > 1e-9)
            {
                double density =
                    items[i].value / items[i].weight
                    - items[i].decay * time;

                if (density > bestDensity)
                {
                    bestDensity = density;
                    best = i;
                }
            }
        }
        if (best == -1)
            break;

        double taken;

        if (items[best].weight <= remaining)
            taken = items[best].weight;
        else
            taken = remaining;

        double fraction =
            taken / items[best].weight;

        double contribution =
            taken * bestDensity;


    printf("%-4d\t%-8.4f\t%-12.4f\t%-10.4f\t%-12.4f\t%-12.4f\n",
            items[best].index,
            fraction,
            taken,
            time,
            bestDensity,
            contribution);

        totalValue += contribution;
        time += taken;
        remaining -= taken;

        items[best].weight -= taken;
    }
    printf("\nMaximum effective value = %.4f\n", totalValue);
    free(items);

    return 0;
}