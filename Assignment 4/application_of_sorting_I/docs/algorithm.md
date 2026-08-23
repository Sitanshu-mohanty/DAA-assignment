# Algorithm

## Representation

Each pair is stored using:

```text
Item = (number, color)
```

The color is encoded as an integer:

```text
0 = Red
1 = Blue
2 = Yellow
```

The complete input is stored in an array of `Item`.

## Algorithm Steps

1. Create an array `count[3]` and initialize it to zero.
2. Traverse the input array and count red, blue, and yellow items.
3. Calculate the starting position of each color:
   - Red starts at index `0`.
   - Blue starts after all red items.
   - Yellow starts after all red and blue items.
4. Create an array `next[3]` containing the next free position for each color.
5. Traverse the original array from left to right.
6. For every item:
   - Find its color.
   - Place it at `result[next[color]]`.
   - Increment `next[color]`.
7. Copy the result array back to the input array.
8. Print the final array.

## Why Does It Preserve Sorted Order?

The original input is sorted by number.

Suppose two items have the same color and appear as:

```text
(10, Blue), (25, Blue), (50, Blue)
```

They are encountered in exactly this order. The algorithm places them into consecutive blue positions in the same order:

```text
(10, Blue), (25, Blue), (50, Blue)
```

Therefore, the numbers belonging to each color remain sorted.

## Pseudocode

```text
SORT_BY_COLOR(items, n)

    count[0] = count[1] = count[2] = 0

    for i = 0 to n - 1
        count[items[i].color]++

    start[0] = 0
    start[1] = count[0]
    start[2] = count[0] + count[1]

    next = start

    for i = 0 to n - 1
        color = items[i].color
        result[next[color]] = items[i]
        next[color]++

    copy result into items
```

## Correctness

After counting, the result array is divided into three sections:

```text
[ Red section ][ Blue section ][ Yellow section ]
```

During the second traversal, every item is placed in the section belonging to its color.

Since items are processed from left to right and the original array is sorted by number, the relative order of items having the same color is preserved. Hence, the numbers within each color remain sorted.

Therefore, the final array satisfies all requirements.

## Time Complexity

There are three linear traversals:

```text
Counting       = O(n)
Placing        = O(n)
Copying        = O(n)
```

Therefore:

```text
O(n) + O(n) + O(n) = O(n)
```

Final time complexity:

**O(n)**

## Space Complexity

The algorithm uses a result array of `n` items.

Therefore, the extra space complexity is:

**O(n)**
