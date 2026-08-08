#define _POSIX_C_SOURCE 200809L

#include "merge_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define DEFAULT_REPETITIONS 7

static double now_seconds(void)
{
#ifdef _WIN32
    static LARGE_INTEGER frequency;
    static int initialized = 0;
    LARGE_INTEGER counter;

    if (!initialized) {
        QueryPerformanceFrequency(&frequency);
        initialized = 1;
    }

    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart / (double)frequency.QuadPart;
#else
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
#endif
}

static unsigned int rng_state = 0xC0FFEEU;

static unsigned int next_random(void)
{
    rng_state = 1664525U * rng_state + 1013904223U;
    return rng_state;
}

static void fill_random(int *arr, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        arr[i] = (int)(next_random() % 1000000U);
    }
}

static int compare_doubles(const void *a, const void *b)
{
    const double x = *(const double *)a;
    const double y = *(const double *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

static double median(double *values, size_t count)
{
    qsort(values, count, sizeof(*values), compare_doubles);

    if (count % 2 != 0) {
        return values[count / 2];
    }

    return (values[count / 2 - 1] + values[count / 2]) / 2.0;
}

static double benchmark_algorithm(
    void (*sort_function)(int *, size_t),
    const int *input,
    int *working,
    size_t n,
    size_t repetitions)
{
    double *times = malloc(repetitions * sizeof(*times));

    if (times == NULL) {
        return -1.0;
    }

    for (size_t r = 0; r < repetitions; ++r) {
        memcpy(working, input, n * sizeof(*working));

        double start = now_seconds();
        sort_function(working, n);
        double end = now_seconds();

        if (!is_sorted(working, n)) {
            fprintf(stderr, "ERROR: sorting failed for n=%zu\n", n);
            free(times);
            return -1.0;
        }

        times[r] = end - start;
    }

    double result = median(times, repetitions);
    free(times);
    return result;
}

int main(int argc, char **argv)
{
    const char *output_path = "data/benchmark_results.csv";
    size_t repetitions = DEFAULT_REPETITIONS;

    if (argc >= 2) {
        output_path = argv[1];
    }

    if (argc >= 3) {
        char *end = NULL;
        unsigned long value = strtoul(argv[2], &end, 10);

        if (end == argv[2] || *end != '\0' || value == 0) {
            fprintf(stderr, "Invalid repetition count: %s\n", argv[2]);
            return EXIT_FAILURE;
        }

        repetitions = (size_t)value;
    }

    const size_t sizes[] = {
        1024, 2048, 4096, 8192, 16384,
        32768, 65536, 131072, 262144, 524288
    };
    const size_t count = sizeof(sizes) / sizeof(sizes[0]);

    int *input = NULL;
    int *working = NULL;

    FILE *out = fopen(output_path, "w");
    if (out == NULL) {
        perror("Could not open output CSV");
        return EXIT_FAILURE;
    }

    fprintf(out, "n,merge_sort_seconds,merge_sort_3way_seconds\n");

    printf("Benchmarking standard and three-way merge sort\n");
    printf("Repetitions per algorithm: %zu\n\n", repetitions);
    printf("%10s %18s %22s\n", "n", "Merge Sort (s)", "3-Way Merge Sort (s)");
    printf("---------------------------------------------------------------\n");

    for (size_t s = 0; s < count; ++s) {
        size_t n = sizes[s];

        int *new_input = realloc(input, n * sizeof(*input));
        int *new_working = realloc(working, n * sizeof(*working));

        if (new_input == NULL || new_working == NULL) {
            fprintf(stderr, "Memory allocation failed for n=%zu\n", n);
            free(new_input);
            free(new_working);
            free(input);
            free(working);
            fclose(out);
            return EXIT_FAILURE;
        }

        input = new_input;
        working = new_working;

        fill_random(input, n);

        double standard_time =
            benchmark_algorithm(merge_sort, input, working, n, repetitions);
        double three_way_time =
            benchmark_algorithm(merge_sort_3way, input, working, n, repetitions);

        if (standard_time < 0.0 || three_way_time < 0.0) {
            fclose(out);
            free(input);
            free(working);
            return EXIT_FAILURE;
        }

        fprintf(out, "%zu,%.9f,%.9f\n",
                n, standard_time, three_way_time);

        printf("%10zu %18.9f %22.9f\n",
               n, standard_time, three_way_time);
    }

    fclose(out);
    free(input);
    free(working);

    printf("\nResults written to: %s\n", output_path);
    return EXIT_SUCCESS;
}
