#include <stdio.h>

int findTransition(int A[], int n) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (A[mid] == 0) {
            if (mid == n - 1 || A[mid + 1] == 1)
                return mid + 1;   // Index of first 1
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return -1;   // No transition
}

int main() {
    int n, i;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int A[n];

    printf("Enter %d elements (0s followed by 1s):\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
    }

    int index = findTransition(A, n);

    if (index == -1)
        printf("No transition found.\n");
    else
        printf("Transition occurs at index %d\n", index);

    return 0;
}