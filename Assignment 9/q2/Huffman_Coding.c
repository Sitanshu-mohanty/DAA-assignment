#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    char symbol;
    int frequency;
    struct Node *left, *right;
} Node;

typedef struct
{
    char symbol;
    int frequency;
    int length;
    char code[256];
} Code;

typedef struct
{
    int size;
    Node **array;
} MinHeap;

Node *createNode(char s, int f)
{
    Node *n = malloc(sizeof(Node));
    n->symbol = s;
    n->frequency = f;
    n->left = n->right = NULL;
    return n;
}

MinHeap *createHeap(int n)
{
    MinHeap *h = malloc(sizeof(MinHeap));
    h->size = 0;
    h->array = malloc(n * sizeof(Node *));
    return h;
}

void swap(Node **a, Node **b)
{
    Node *t = *a;
    *a = *b;
    *b = t;
}

void heapify(MinHeap *h, int i)
{
    int s = i, l = 2 * i + 1, r = 2 * i + 2;

    if (l < h->size &&
        h->array[l]->frequency < h->array[s]->frequency)
        s = l;

    if (r < h->size &&
        h->array[r]->frequency < h->array[s]->frequency)
        s = r;

    if (s != i)
    {
        swap(&h->array[i], &h->array[s]);
        heapify(h, s);
    }
}

void insert(MinHeap *h, Node *n)
{
    int i = h->size++;

    while (i > 0 &&
           n->frequency < h->array[(i - 1) / 2]->frequency)
    {
        h->array[i] = h->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    h->array[i] = n;
}

Node *extractMin(MinHeap *h)
{
    Node *n = h->array[0];
    h->array[0] = h->array[--h->size];

    if (h->size)
        heapify(h, 0);

    return n;
}

Node *buildTree(char symbols[], int freq[], int n)
{
    MinHeap *h = createHeap(n);
    Node *left, *right, *parent;
    int i;

    for (i = 0; i < n; i++)
        h->array[i] = createNode(symbols[i], freq[i]);

    h->size = n;

    for (i = n / 2 - 1; i >= 0; i--)
        heapify(h, i);

    while (h->size > 1)
    {
        left = extractMin(h);
        right = extractMin(h);

        parent = createNode('\0',
                            left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        insert(h, parent);
    }

    parent = extractMin(h);
    free(h->array);
    free(h);

    return parent;
}

void getLengths(Node *root, int depth, Code codes[], int *count)
{
    if (!root)
        return;

    if (!root->left && !root->right)
    {
        codes[*count].symbol = root->symbol;
        codes[*count].frequency = root->frequency;
        codes[*count].length = depth ? depth : 1;
        (*count)++;
        return;
    }

    getLengths(root->left, depth + 1, codes, count);
    getLengths(root->right, depth + 1, codes, count);
}

int compare(const void *a, const void *b)
{
    Code *x = (Code *)a;
    Code *y = (Code *)b;

    if (x->length != y->length)
        return x->length - y->length;

    return x->symbol - y->symbol;
}

void canonicalCodes(Code codes[], int n)
{
    unsigned int code = 0;
    int previous = codes[0].length;
    int i, j;

    qsort(codes, n, sizeof(Code), compare);

    for (i = 0; i < n; i++)
    {
        if (i)
        {
            code++;

            if (codes[i].length > previous)
                code <<= codes[i].length - previous;
        }

        for (j = codes[i].length - 1; j >= 0; j--)
            codes[i].code[codes[i].length - 1 - j] =
                ((code >> j) & 1) + '0';

        codes[i].code[codes[i].length] = '\0';
        previous = codes[i].length;
    }
}

void freeTree(Node *root)
{
    if (!root)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main()
{
    int n, i, count = 0, total = 0, cost = 0;
    char *symbols;
    int *freq;
    Code *codes;
    Node *root;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    symbols = malloc(n * sizeof(char));
    freq = malloc(n * sizeof(int));
    codes = malloc(n * sizeof(Code));

    printf("Enter symbol and frequency:\n");

    for (i = 0; i < n; i++)
    {
        scanf(" %c %d", &symbols[i], &freq[i]);

        if (freq[i] <= 0)
        {
            printf("Frequency must be positive.\n");
            return 1;
        }

        total += freq[i];
    }

    root = buildTree(symbols, freq, n);
    getLengths(root, 0, codes, &count);
    canonicalCodes(codes, count);

    printf("\nCanonical Huffman Codebook:\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    for (i = 0; i < count; i++)
    {
        printf("%c\t%d\t\t%d\t%s\n",
               codes[i].symbol, codes[i].frequency,
               codes[i].length, codes[i].code);

        cost += codes[i].frequency * codes[i].length;
    }

    printf("\nTotal weighted code length = %d\n", cost);
    printf("Expected code length = %.2f bits/symbol\n",
           (double)cost / total);

    freeTree(root);
    free(symbols);
    free(freq);
    free(codes);

    return 0;
}