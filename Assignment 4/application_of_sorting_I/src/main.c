#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    int color;  // 0 = red, 1 = blue, 2 = yellow
} Item;

const char *getColorName(int color) {
    if (color == 0) return "Red";
    if (color == 1) return "Blue";
    return "Yellow";
}

void sortByColor(Item items[], int n) {
    int count[3] = {0, 0, 0};
    int start[3];
    int next[3];
    Item *result;

    /* Count the number of items of each color. */
    for (int i = 0; i < n; i++) {
        count[items[i].color]++;
    }

    /* Find the starting position of each color in the result. */
    start[0] = 0;
    start[1] = count[0];
    start[2] = count[0] + count[1];

    next[0] = start[0];
    next[1] = start[1];
    next[2] = start[2];

    result = (Item *)malloc(n * sizeof(Item));
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Insert each item at the next available position of its color.
     * Because the input is already sorted by number, this keeps
     * numbers of the same color in sorted order.
     */
    for (int i = 0; i < n; i++) {
        int color = items[i].color;
        result[next[color]] = items[i];
        next[color]++;
    }

    /* Copy the result back to the original array. */
    for (int i = 0; i < n; i++) {
        items[i] = result[i];
    }

    free(result);
}

void printItems(const Item items[], int n) {
    printf("\nItems after sorting by color:\n");
    printf("Number\tColor\n");
    printf("------\t-----\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%s\n", items[i].number, getColorName(items[i].color));
    }
}

int main(void) {
    int n;
    Item *items;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of items must be positive.\n");
        return 1;
    }

    items = (Item *)malloc(n * sizeof(Item));
    if (items == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("\nEnter each pair as: number color\n");
    printf("Color: 0 = Red, 1 = Blue, 2 = Yellow\n");
    printf("Numbers must be entered in sorted order.\n\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);
        scanf("%d %d", &items[i].number, &items[i].color);

        if (items[i].color < 0 || items[i].color > 2) {
            printf("Invalid color. Use 0, 1, or 2.\n");
            free(items);
            return 1;
        }

        if (i > 0 && items[i].number < items[i - 1].number) {
            printf("Numbers must be entered in sorted order.\n");
            free(items);
            return 1;
        }
    }

    sortByColor(items, n);
    printItems(items, n);

    free(items);
    return 0;
}
