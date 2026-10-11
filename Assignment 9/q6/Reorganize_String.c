#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

typedef struct
{
    char ch;
    int freq;
} Element;

typedef struct
{
    int size;
    Element array[MAX_CHARS];
} MaxHeap;

void swap(Element *a, Element *b)
{
    Element temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(MaxHeap *heap, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heap->size &&
        heap->array[left].freq > heap->array[largest].freq)
        largest = left;

    if (right < heap->size &&
        heap->array[right].freq > heap->array[largest].freq)
        largest = right;

    if (largest != i)
    {
        swap(&heap->array[i], &heap->array[largest]);
        maxHeapify(heap, largest);
    }
}

void insert(MaxHeap *heap, Element e)
{
    int i = heap->size++;

    while (i > 0 && e.freq > heap->array[(i - 1) / 2].freq)
    {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    heap->array[i] = e;
}

Element extractMax(MaxHeap *heap)
{
    Element max = heap->array[0];

    heap->array[0] = heap->array[--heap->size];

    if (heap->size > 0)
        maxHeapify(heap, 0);

    return max;
}

char *reorganize(char *s, int k)
{
    int n = strlen(s);
    int freq[MAX_CHARS] = {0};
    int i;

    char *result = malloc((n + 1) * sizeof(char));
    Element *queue = NULL;
    MaxHeap heap;

    heap.size = 0;

    if (result == NULL)
        return NULL;

    if (k <= 1)
    {
        strcpy(result, s);
        return result;
    }

    queue = calloc(k, sizeof(Element));

    if (queue == NULL)
    {
        free(result);
        return NULL;
    }

    for (i = 0; i < n; i++)
        freq[(unsigned char)s[i]]++;

    for (i = 0; i < MAX_CHARS; i++)
    {
        if (freq[i] > 0)
            insert(&heap, (Element){(char)i, freq[i]});
    }

    for (i = 0; i < n; i++)
    {
        int index = i % k;

        if (queue[index].freq > 0)
        {
            insert(&heap, queue[index]);
            queue[index].freq = 0;
        }

        if (heap.size == 0)
        {
            result[0] = '\0';
            free(queue);
            return result;
        }

        Element current = extractMax(&heap);

        result[i] = current.ch;
        current.freq--;

        queue[index] = current;
    }

    result[n] = '\0';

    free(queue);

    return result;
}

int main()
{
    char s[1000];
    int k;

    printf("Enter the string S: ");
    scanf("%s", s);

    printf("Enter distance K: ");
    scanf("%d", &k);

    if (k < 0)
    {
        printf("Invalid K.\n");
        return 1;
    }

    char *result = reorganize(s, k);

    if (result == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (strlen(result) == 0)
        printf("Reorganized String: Empty String - Impossible\n");
    else
        printf("Reorganized String: %s\n", result);

    free(result);

    return 0;
}