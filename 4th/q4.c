#include <stdio.h>

int moves = 0;

void TOH(int n, char source, char auxiliary, char destination)
{
    if (n == 1)
    {
        printf("Move disk 1 from %c to %c\n", source, destination);
        moves++;
        return;
    }

    TOH(n - 1, source, destination, auxiliary);

    printf("Move disk %d from %c to %c\n", n, source, destination);
    moves++;

    TOH(n - 1, auxiliary, source, destination);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    TOH(n, 'A', 'B', 'C');

    printf("\nTotal moves = %d\n", moves);

    return 0;
}