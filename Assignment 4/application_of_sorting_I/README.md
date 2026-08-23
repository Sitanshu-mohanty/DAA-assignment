# Application of Sorting-I

## Question

Assume that we are given `n` pairs of items as input, where the first item is a number and the second item is one of three colours (red, blue, or yellow). Further assume that the items are sorted by number. Give an `O(n)` algorithm to sort the items by colour (all reds before all blues before all yellows) such that the numbers for identical colours stay sorted. By choosing the proper input representation, write a program in C to validate your algorithm.

## Idea

The input is already sorted by number. Therefore, we do **not** need to compare or sort the numbers again.

We represent every pair using a structure:

```c
typedef struct {
    int number;
    int color;
} Item;
```

The colors are represented as:

- `0` → Red
- `1` → Blue
- `2` → Yellow

The algorithm performs the following steps:

1. Count how many red, blue, and yellow items are present.
2. Use these counts to determine where each color starts in the result array.
3. Scan the input from left to right once.
4. Put each item into the next available position belonging to its color.
5. Copy the result back to the input array.

Because the input numbers are already sorted and we process the input from left to right, items having the same color remain in their original sorted order.

## Files

```text
application_of_sorting_I/
├── src/
│   └── main.c
├── docs/
│   ├── algorithm.md
│   └── comparison.md
├── tests/
│   └── sample_input.txt
├── .gitignore
└── README.md
```

## How to Compile

### GCC

```bash
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o sorting
```

### Windows PowerShell

```powershell
gcc -std=c11 -O2 -Wall -Wextra -pedantic src/main.c -o sorting.exe
.\sorting.exe
```

## Sample Input

```text
8
10 1
15 0
20 2
25 1
30 0
35 2
40 0
50 1
```

Here, the numbers are already sorted.

## Sample Output

```text
Items after sorting by color:
Number  Color
------  -----
15      Red
30      Red
40      Red
10      Blue
25      Blue
50      Blue
20      Yellow
35      Yellow
```

Notice that:

- all red items come first,
- all blue items come next,
- all yellow items come last,
- the numbers within each color remain sorted.

## Complexity

- Counting colors: `O(n)`
- Placing items: `O(n)`
- Copying the result: `O(n)`
- Total time: **O(n)**

## Conclusion

Since the input is already sorted by number, the problem can be solved without performing a conventional sorting algorithm. By grouping the items according to their color while scanning the sorted input, we obtain the required order in linear time. The important observation is that preserving the left-to-right order within each color automatically keeps the numbers of identical colors sorted.
