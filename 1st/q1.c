#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *name;
    double growth_score;
} Function;

int compare(const void *a, const void *b) {
    double score_a = ((Function *)a)->growth_score;
    double score_b = ((Function *)b)->growth_score;
    
    if (score_a > score_b) return 1;
    if (score_a < score_b) return -1;
    return 0;
}

int main() {
    
    Function funcs[] = {
        {"1/n",           -1.0},   // Negative score because it shrinks as n grows
        {"log_2 n",        0.1},   // Logarithms grow slower than any fractional power
        {"12*sqrt(n)",     0.501}, // sqrt is power of 0.5 (constant 12 is lower)
        {"50n^0.5",        0.502}, // power of 0.5 (constant 50 is higher)
        {"n^0.51",         0.510}, // 0.51 strictly beats 0.5, regardless of constants
        {"2^32 * n",       1.0},   // Linear function (n^1)
        {"n log_2 n",      1.1},   // Slightly faster than linear
        {"n^2 - 324",      2.001}, // Quadratic (n^2). -324 doesn't matter for large n
        {"100n^2 + 6n",    2.002}, // Quadratic, but coefficient 100 makes it larger
        {"2n^3",           3.0},   // Cubic (n^3)
        {"n^(log_2 n)",    4.0},   // Quasipolynomial (grows faster than normal powers)
        {"3^n",            5.0}    // Exponential (grows the fastest of all)
    };

    int num_funcs = sizeof(funcs) / sizeof(funcs[0]);

    qsort(funcs, num_funcs, sizeof(Function), compare);

    printf("Functions ordered by growth rate:\n");
    printf("---------------------------------\n");
    for (int i = 0; i < num_funcs; i++) {
        printf("%d. %s\n", i + 1, funcs[i].name);
    }

    return 0;
}