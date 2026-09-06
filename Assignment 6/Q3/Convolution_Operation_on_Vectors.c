#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846

typedef double complex cd;

void fft(cd a[], int n, int invert)
{
    if (n == 1)
        return;

    cd *a0 = (cd *)malloc((n / 2) * sizeof(cd));
    cd *a1 = (cd *)malloc((n / 2) * sizeof(cd));

    for (int i = 0; i < n / 2; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }

    fft(a0, n / 2, invert);
    fft(a1, n / 2, invert);

    double angle = 2 * PI / n * (invert ? -1 : 1);
    cd w = 1;
    cd wn = cos(angle) + I * sin(angle);

    for (int i = 0; i < n / 2; i++)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }

    free(a0);
    free(a1);
}

void convolution(double A[], int m, double B[], int n)
{
    int size = 1;

    while (size < m + n - 1)
        size <<= 1;

    cd *FA = (cd *)calloc(size, sizeof(cd));
    cd *FB = (cd *)calloc(size, sizeof(cd));

    for (int i = 0; i < m; i++)
        FA[i] = A[i];

    for (int i = 0; i < n; i++)
        FB[i] = B[i];

    fft(FA, size, 0);
    fft(FB, size, 0);

    for (int i = 0; i < size; i++)
        FA[i] *= FB[i];

    fft(FA, size, 1);

    printf("\nConvolution C:\n");

    for (int i = 0; i < m + n - 1; i++)
    {
        FA[i] /= size;
        printf("C[%d] = %.6lf\n", i, creal(FA[i]));
    }

    free(FA);
    free(FB);
}

int main()
{
    int m, n;
    double *A, *B;

    printf("Enter size of vector A: ");
    scanf("%d", &m);

    printf("Enter size of vector B: ");
    scanf("%d", &n);

    if (m <= 0 || n <= 0 || n < m)
    {
        printf("Invalid input. Ensure n >= m.\n");
        return 1;
    }

    A = (double *)malloc(m * sizeof(double));
    B = (double *)malloc(n * sizeof(double));

    printf("\nEnter elements of vector A:\n");
    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("\nEnter elements of vector B:\n");
    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    convolution(A, m, B, n);

    free(A);
    free(B);

    return 0;
}