#include <stdio.h>
#include <stdlib.h>

struct Result
{
    int min;
    int max;
};

struct Result findMinMax(int a[], int left, int right, int *count)
{
    struct Result result;
    struct Result leftResult;
    struct Result rightResult;

    /* One element */
    if (left == right)
    {
        result.min = a[left];
        result.max = a[left];
        return result;
    }

    /* Two elements */
    if (right == left + 1)
    {
        (*count)++;

        if (a[left] < a[right])
        {
            result.min = a[left];
            result.max = a[right];
        }
        else
        {
            result.min = a[right];
            result.max = a[left];
        }

        return result;
    }

    int mid = left + (right - left) / 2;

    leftResult = findMinMax(a, left, mid, count);
    rightResult = findMinMax(a, mid + 1, right, count);

    /* Compare the two minimums */
    (*count)++;

    if (leftResult.min < rightResult.min)
        result.min = leftResult.min;
    else
        result.min = rightResult.min;

    /* Compare the two maximums */
    (*count)++;

    if (leftResult.max > rightResult.max)
        result.max = leftResult.max;
    else
        result.max = rightResult.max;

    return result;
}

int main(void)
{
    int n;

    printf("========== MAX AND MIN USING DIVIDE AND CONQUER ==========\n\n");

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Number of elements must be positive.\n");
        return 1;
    }

    int *a = malloc(n * sizeof(int));

    if (a == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int count = 0;

    struct Result result = findMinMax(a, 0, n - 1, &count);

    printf("\n========== RESULT ==========\n");
    printf("Minimum element: %d\n", result.min);
    printf("Maximum element: %d\n", result.max);
    printf("Number of comparisons: %d\n", count);

    printf("\nTheoretical upper bound: 3n/2 = %.1f\n",
           1.5 * n);

    if (count <= 1.5 * n)
        printf("The number of comparisons is within the required bound.\n");
    else
        printf("The number of comparisons exceeds the required bound.\n");

    printf("\nTime Complexity: O(n)\n");
    printf("Extra Space Complexity: O(log n) due to recursion.\n");

    free(a);

    return 0;
}
