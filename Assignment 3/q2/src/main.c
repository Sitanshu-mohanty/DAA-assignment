#include <stdio.h>
#include <stdlib.h>

/*
    Compare two groups of coins.

    -1 : left group is lighter
     0 : both groups are equal
     1 : right group is lighter
*/
int weigh(int a[], int left, int right, int size)
{
    int leftWeight = 0;
    int rightWeight = 0;

    for (int i = 0; i < size; i++)
    {
        leftWeight += a[left + i];
        rightWeight += a[right + i];
    }

    if (leftWeight < rightWeight)
        return -1;

    if (leftWeight > rightWeight)
        return 1;

    return 0;
}

/*
    Find one lighter coin, if it exists.

    At most one coin is lighter than the normal weight.
    The function returns the index of that coin, or -1.

    count = number of balance-scale weighings.
*/
int findCoin(int a[], int left, int right, int *count)
{
    int n = right - left + 1;

    /* Only one possible coin remains. */
    if (n == 1)
        return left;

    /* Two coins: weigh them directly. */
    if (n == 2)
    {
        (*count)++;

        if (a[left] < a[right])
            return left;

        if (a[right] < a[left])
            return right;

        return -1;
    }

    /* Divide the coins into two equal groups. */
    int size = n / 2;

    int result = weigh(a, left, left + size, size);
    (*count)++;

    /* Left group is lighter. */
    if (result == -1)
        return findCoin(a, left, left + size - 1, count);

    /* Right group is lighter. */
    if (result == 1)
        return findCoin(a, left + size,
                        left + 2 * size - 1, count);

    /*
        Both groups are equal.

        If n is even, there is no lighter coin.

        If n is odd, one coin was not weighed.
        That extra coin is the only possible defective coin.
    */
    if (n % 2 == 0)
        return -1;

    int extra = right;

    (*count)++;

    if (a[extra] < a[left])
        return extra;

    return -1;
}

int main(void)
{
    int n;

    printf("========== SEARCH THE DEFECTIVE COIN ==========\n\n");

    printf("Enter number of coins: ");
    scanf("%d", &n);

    if (n < 2)
    {
        printf("Number of coins must be at least 2.\n");
        return 1;
    }

    int *a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter the weights of %d coins:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int count = 0;
    int answer = findCoin(a, 0, n - 1, &count);

    printf("\n========== RESULT ==========\n");

    if (answer == -1)
        printf("No defective coin found.\n");
    else
        printf("Defective coin: Coin %d\n", answer + 1);

    printf("Number of weighings: %d\n", count);

    printf("\nTime Complexity (number of weighings): O(log2 n)\n");
    printf("Extra Space Complexity: O(log n) due to recursion.\n");

    free(a);

    return 0;
}
