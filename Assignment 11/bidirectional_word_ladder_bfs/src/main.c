#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define ALPHABET 26
#define MAX_WORD_LEN 10

typedef struct {
    char *key;
    int value;
} HashEntry;

typedef struct {
    HashEntry *entries;
    size_t capacity;
    size_t size;
} HashTable;

static uint64_t hash_word(const char *s) {
    uint64_t hash = UINT64_C(1469598103934665603);
    while (*s) {
        hash ^= (unsigned char)*s++;
        hash *= UINT64_C(1099511628211);
    }
    return hash;
}

static int hash_init(HashTable *table, size_t capacity) {
    table->entries = calloc(capacity, sizeof(*table->entries));
    if (!table->entries) return 0;
    table->capacity = capacity;
    table->size = 0;
    return 1;
}

static int hash_find(const HashTable *table, const char *key) {
    size_t index = (size_t)(hash_word(key) % table->capacity);
    while (table->entries[index].key != NULL) {
        if (strcmp(table->entries[index].key, key) == 0)
            return table->entries[index].value;
        index = (index + 1) % table->capacity;
    }
    return -1;
}

static int hash_insert(HashTable *table, char *key, int value) {
    size_t index = (size_t)(hash_word(key) % table->capacity);
    while (table->entries[index].key != NULL) {
        if (strcmp(table->entries[index].key, key) == 0)
            return 0; /* duplicate */
        index = (index + 1) % table->capacity;
    }
    table->entries[index].key = key;
    table->entries[index].value = value;
    table->size++;
    return 1;
}

static int valid_word(const char *word, int length) {
    if ((int)strlen(word) != length) return 0;
    for (int i = 0; i < length; ++i)
        if (word[i] < 'a' || word[i] > 'z') return 0;
    return 1;
}

static int bidirectional_bfs(char **words, int n, int length,
                             int start_id, int target_id, int start_is_dict) {
    int total = n + (start_is_dict ? 0 : 1);
    int *dist_a = malloc((size_t)total * sizeof(*dist_a));
    int *dist_b = malloc((size_t)total * sizeof(*dist_b));
    int *front_a = malloc((size_t)total * sizeof(*front_a));
    int *front_b = malloc((size_t)total * sizeof(*front_b));
    int *next_front = malloc((size_t)total * sizeof(*next_front));
    char *candidate = malloc((size_t)(length + 1));

    if (!dist_a || !dist_b || !front_a || !front_b || !next_front || !candidate) {
        free(dist_a); free(dist_b); free(front_a); free(front_b);
        free(next_front); free(candidate);
        return -2;
    }

    for (int i = 0; i < total; ++i) dist_a[i] = dist_b[i] = -1;

    /* Dictionary lookup table is built by caller; IDs are stored in it. */
    HashTable lookup;
    if (!hash_init(&lookup, (size_t)(2 * total + 1))) {
        free(dist_a); free(dist_b); free(front_a); free(front_b);
        free(next_front); free(candidate);
        return -2;
    }
    for (int i = 0; i < n; ++i) {
        if (!hash_insert(&lookup, words[i], i)) {
            free(lookup.entries); free(dist_a); free(dist_b); free(front_a);
            free(front_b); free(next_front); free(candidate);
            return -3;
        }
    }
    if (!start_is_dict) {
        if (!hash_insert(&lookup, words[start_id], start_id)) {
            free(lookup.entries); free(dist_a); free(dist_b); free(front_a);
            free(front_b); free(next_front); free(candidate);
            return -3;
        }
    }

    int size_a = 1, size_b = 1;
    front_a[0] = start_id;
    front_b[0] = target_id;
    dist_a[start_id] = 0;
    dist_b[target_id] = 0;

    int answer = -1;
    while (size_a > 0 && size_b > 0 && answer == -1) {
        int expand_a = size_a <= size_b;
        int *front = expand_a ? front_a : front_b;
        int *other_dist = expand_a ? dist_b : dist_a;
        int *this_dist = expand_a ? dist_a : dist_b;
        int front_size = expand_a ? size_a : size_b;
        int next_size = 0;

        for (int fi = 0; fi < front_size && answer == -1; ++fi) {
            int id = front[fi];
            memcpy(candidate, words[id], (size_t)length + 1);

            for (int pos = 0; pos < length && answer == -1; ++pos) {
                char original = candidate[pos];
                for (char ch = 'a'; ch <= 'z'; ++ch) {
                    if (ch == original) continue;
                    candidate[pos] = ch;
                    int neighbor = hash_find(&lookup, candidate);
                    if (neighbor < 0) continue;

                    if (this_dist[neighbor] == -1) {
                        this_dist[neighbor] = this_dist[id] + 1;
                        next_front[next_size++] = neighbor;
                    }
                    if (other_dist[neighbor] != -1) {
                        answer = this_dist[neighbor] + other_dist[neighbor];
                        break;
                    }
                }
                candidate[pos] = original;
            }
        }

        if (expand_a) {
            memcpy(front_a, next_front, (size_t)next_size * sizeof(*front_a));
            size_a = next_size;
        } else {
            memcpy(front_b, next_front, (size_t)next_size * sizeof(*front_b));
            size_b = next_size;
        }
    }

    free(lookup.entries);
    free(dist_a); free(dist_b); free(front_a); free(front_b);
    free(next_front); free(candidate);
    return answer;
}

int main(void) {
    int n, length;
    char start[ MAX_WORD_LEN + 2 ], target[ MAX_WORD_LEN + 2 ];

    if (scanf("%d %d", &n, &length) != 2 ||
        n <= 0 || n > 100000 || length <= 0 || length > MAX_WORD_LEN) {
        fprintf(stderr, "Error: N must be 1..100000 and L must be 1..10.\n");
        return EXIT_FAILURE;
    }
    if (scanf("%11s %11s", start, target) != 2 ||
        !valid_word(start, length) || !valid_word(target, length)) {
        fprintf(stderr, "Error: start and target must be lowercase words of length L.\n");
        return EXIT_FAILURE;
    }

    char **words = malloc((size_t)(n + 1) * sizeof(*words));
    if (!words) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    HashTable dictionary;
    if (!hash_init(&dictionary, (size_t)(2 * n + 1))) {
        fprintf(stderr, "Error: memory allocation failed.\n");
        free(words);
        return EXIT_FAILURE;
    }

    int start_id = -1, target_id = -1;
    for (int i = 0; i < n; ++i) {
        char buffer[MAX_WORD_LEN + 2];
        if (scanf("%11s", buffer) != 1 || !valid_word(buffer, length)) {
            fprintf(stderr, "Error: dictionary word %d is invalid.\n", i + 1);
            for (int j = 0; j < i; ++j) free(words[j]);
            free(words); free(dictionary.entries);
            return EXIT_FAILURE;
        }
        words[i] = malloc((size_t)length + 1);
        if (!words[i]) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            for (int j = 0; j < i; ++j) free(words[j]);
            free(words); free(dictionary.entries);
            return EXIT_FAILURE;
        }
        memcpy(words[i], buffer, (size_t)length + 1);

        if (!hash_insert(&dictionary, words[i], i)) {
            fprintf(stderr, "Error: dictionary words must be unique.\n");
            for (int j = 0; j <= i; ++j) free(words[j]);
            free(words); free(dictionary.entries);
            return EXIT_FAILURE;
        }
        if (strcmp(words[i], start) == 0) start_id = i;
        if (strcmp(words[i], target) == 0) target_id = i;
    }

    if (target_id == -1) {
        fprintf(stderr, "Error: target word B must be present in dictionary D.\n");
        for (int i = 0; i < n; ++i) free(words[i]);
        free(words); free(dictionary.entries);
        return EXIT_FAILURE;
    }

    int start_is_dict = start_id != -1;
    if (!start_is_dict) {
        start_id = n;
        words[n] = malloc((size_t)length + 1);
        if (!words[n]) {
            fprintf(stderr, "Error: memory allocation failed.\n");
            for (int i = 0; i < n; ++i) free(words[i]);
            free(words); free(dictionary.entries);
            return EXIT_FAILURE;
        }
        memcpy(words[n], start, (size_t)length + 1);
    }

    int result = (strcmp(start, target) == 0) ? 0 :
        bidirectional_bfs(words, n, length, start_id, target_id, start_is_dict);

    if (result == -2) {
        fprintf(stderr, "Error: memory allocation failed during BFS.\n");
    } else if (result == -3) {
        fprintf(stderr, "Error: duplicate word encountered in search table.\n");
    } else {
        printf("Minimum mutations from %s to %s: %d\n", start, target, result);
    }

    for (int i = 0; i < n + (start_is_dict ? 0 : 1); ++i) free(words[i]);
    free(words);
    free(dictionary.entries);
    return result == -2 || result == -3 ? EXIT_FAILURE : EXIT_SUCCESS;
}
