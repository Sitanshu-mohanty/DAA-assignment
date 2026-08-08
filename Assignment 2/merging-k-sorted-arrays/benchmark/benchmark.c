#ifdef _WIN32
#define _CRT_SECURE_NO_WARNINGS
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include "merge_arrays.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif

typedef struct {
    size_t k;
    size_t n;
    double sequential_seconds;
    double pairwise_seconds;
    double speedup;
} BenchmarkResult;

static double current_time_seconds(void)
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
    struct timespec time_value;

    if (clock_gettime(CLOCK_MONOTONIC, &time_value) != 0) {
        return 0.0;
    }

    return (double)time_value.tv_sec +
           (double)time_value.tv_nsec / 1000000000.0;
#endif
}

static size_t next_power_of_two(size_t value)
{
    size_t power = 1;

    while (power < value) {
        if (power > (size_t)-1 / 2) {
            return value;
        }
        power *= 2;
    }

    return power;
}

static IntArray *create_sorted_arrays(size_t k, size_t n)
{
    IntArray *arrays = calloc(k, sizeof(*arrays));

    if (arrays == NULL) {
        return NULL;
    }

    /*
     * Deterministic, overlapping sorted data.
     * Each array contains n elements and is independently sorted.
     */
    for (size_t i = 0; i < k; ++i) {
        arrays[i].size = n;

        if (n == 0) {
            continue;
        }

        arrays[i].data = malloc(n * sizeof(*arrays[i].data));

        if (arrays[i].data == NULL) {
            for (size_t j = 0; j <= i; ++j) {
                free_int_array(&arrays[j]);
            }
            free(arrays);
            return NULL;
        }

        for (size_t j = 0; j < n; ++j) {
            arrays[i].data[j] = (int)(j * 2 + (i % 3));
        }
    }

    return arrays;
}

static void free_input_arrays(IntArray *arrays, size_t k)
{
    if (arrays == NULL) {
        return;
    }

    for (size_t i = 0; i < k; ++i) {
        free_int_array(&arrays[i]);
    }

    free(arrays);
}

static int validate_result(const IntArray *result, size_t expected_size)
{
    return result != NULL &&
           result->size == expected_size &&
           is_sorted(result);
}

static BenchmarkResult benchmark_configuration(
    size_t k,
    size_t n,
    int repetitions)
{
    BenchmarkResult benchmark = {k, n, 0.0, 0.0, 0.0};

    IntArray *arrays = create_sorted_arrays(k, n);

    if (arrays == NULL) {
        fprintf(stderr, "Error: unable to allocate input arrays.\n");
        exit(EXIT_FAILURE);
    }

    IntArray sequential_result = {NULL, 0};
    IntArray pairwise_result = {NULL, 0};

    /* Correctness check before timing. */
    sequential_result = merge_sequential(arrays, k);
    pairwise_result = merge_pairwise(arrays, k);

    if (!validate_result(&sequential_result, k * n) ||
        !validate_result(&pairwise_result, k * n) ||
        !arrays_equal(&sequential_result, &pairwise_result)) {
        fprintf(stderr,
                "Error: correctness check failed for k=%zu, n=%zu.\n",
                k, n);

        free_int_array(&sequential_result);
        free_int_array(&pairwise_result);
        free_input_arrays(arrays, k);
        exit(EXIT_FAILURE);
    }

    free_int_array(&sequential_result);
    free_int_array(&pairwise_result);

    for (int repetition = 0; repetition < repetitions; ++repetition) {
        double start = current_time_seconds();
        sequential_result = merge_sequential(arrays, k);
        double end = current_time_seconds();

        if (!validate_result(&sequential_result, k * n)) {
            fprintf(stderr, "Error: sequential merge failed.\n");
            free_int_array(&sequential_result);
            free_input_arrays(arrays, k);
            exit(EXIT_FAILURE);
        }

        benchmark.sequential_seconds += end - start;
        free_int_array(&sequential_result);

        start = current_time_seconds();
        pairwise_result = merge_pairwise(arrays, k);
        end = current_time_seconds();

        if (!validate_result(&pairwise_result, k * n)) {
            fprintf(stderr, "Error: pairwise merge failed.\n");
            free_int_array(&pairwise_result);
            free_input_arrays(arrays, k);
            exit(EXIT_FAILURE);
        }

        benchmark.pairwise_seconds += end - start;
        free_int_array(&pairwise_result);
    }

    benchmark.sequential_seconds /= repetitions;
    benchmark.pairwise_seconds /= repetitions;

    if (benchmark.pairwise_seconds > 0.0) {
        benchmark.speedup =
            benchmark.sequential_seconds / benchmark.pairwise_seconds;
    }

    free_input_arrays(arrays, k);

    return benchmark;
}

static void print_usage(const char *program_name)
{
    printf("Usage: %s <output.csv> <n> <max_k> <repetitions>\n",
       program_name);
    printf("\n");
    printf("Arguments:\n");
    printf("  output.csv   CSV file for benchmark results\n");
    printf("  n            Elements in each sorted array\n");
    printf("  max_k        Largest k to test (minimum 2)\n");
    printf("  repetitions  Timed repetitions per configuration\n");
    printf("\n");
    printf("Example:\n");
    printf("  %s results/benchmark.csv 1000 512 5\n", program_name);
}

static int parse_positive_size(const char *text, size_t *value)
{
    char *end = NULL;
    unsigned long long parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    parsed = strtoull(text, &end, 10);

    if (*end != '\0' || parsed == 0 ||
        parsed > (unsigned long long)(size_t)-1) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_positive_int(const char *text, int *value)
{
    char *end = NULL;
    long parsed;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return 0;
    }

    parsed = strtol(text, &end, 10);

    if (*end != '\0' || parsed <= 0 || parsed > 1000000) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 5) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    const char *output_file = argv[1];
    size_t n;
    size_t max_k;
    int repetitions;

    if (!parse_positive_size(argv[2], &n) ||
        !parse_positive_size(argv[3], &max_k) ||
        !parse_positive_int(argv[4], &repetitions) ||
        max_k < 2) {
        fprintf(stderr,
                "Error: n, max_k, and repetitions must be positive; "
                "max_k must be at least 2.\n");
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(output_file, "w");

    if (file == NULL) {
        perror("Error opening output CSV");
        return EXIT_FAILURE;
    }

    fprintf(file,
            "k,n,sequential_seconds,pairwise_seconds,speedup\n");

    printf("Benchmarking k sorted arrays, n=%zu\n", n);
    printf("Results: %s\n\n", output_file);

    /*
     * Powers of two give a perfectly balanced pairwise merge tree.
     * If max_k is not a power of two, it is also benchmarked once.
     */
    size_t k = 2;

    while (k <= max_k) {
        BenchmarkResult result =
            benchmark_configuration(k, n, repetitions);

        fprintf(file, "%zu,%zu,%.9f,%.9f,%.6f\n",
                result.k,
                result.n,
                result.sequential_seconds,
                result.pairwise_seconds,
                result.speedup);

        printf("k=%-5zu  sequential=%10.6f s  pairwise=%10.6f s  speedup=%8.2fx\n",
               result.k,
               result.sequential_seconds,
               result.pairwise_seconds,
               result.speedup);

        if (k > max_k / 2) {
            break;
        }

        k *= 2;
    }

    if (max_k > 2 && max_k != next_power_of_two(max_k)) {
        BenchmarkResult result =
            benchmark_configuration(max_k, n, repetitions);

        fprintf(file, "%zu,%zu,%.9f,%.9f,%.6f\n",
                result.k,
                result.n,
                result.sequential_seconds,
                result.pairwise_seconds,
                result.speedup);

        printf("k=%-5zu  sequential=%10.6f s  pairwise=%10.6f s  speedup=%8.2fx\n",
               result.k,
               result.sequential_seconds,
               result.pairwise_seconds,
               result.speedup);
    }

    fclose(file);

    printf("\nBenchmark completed successfully.\n");
    return EXIT_SUCCESS;
}
