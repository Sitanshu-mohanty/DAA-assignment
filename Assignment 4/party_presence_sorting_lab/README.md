# Application of Sorting-IV - Party Presence

## Lab Assignment

A camera at the door records the entry time `a[i]` and exit time `b[i]` for each of `n` people attending a party, where `b[i] > a[i]`.

All entry and exit times are distinct. The task is to determine the **time when the maximum number of people were simultaneously present** at the party.

The required time complexity is **O(n log n)**.

## Approach

The solution uses **sorting of entry/exit events**.

For every person, create two events:

- Entry time → `+1`
- Exit time → `-1`

There are `2n` events in total.

Then:

1. Sort all events by time.
2. Start `count = 0`.
3. Process the events from earliest to latest.
4. At an entry, increase `count`.
5. At an exit, decrease `count`.
6. Whenever `count` becomes greater than the previous maximum, store that event's time.

Because all times are distinct, no tie handling is required.

## Example

Input:

```text
5
1 10
2 7
3 8
5 12
9 11
```

The sorted events are:

```text
1  Entry
2  Entry
3  Entry
5  Entry
7  Exit
8  Exit
9  Entry
10 Exit
11 Exit
12 Exit
```

The number of people reaches 4 at time 5.

Output:

```text
Maximum people present: 4
Time when maximum was reached: 5
```

## Complexity

There are `2n` events.

Sorting:

`O(2n log(2n)) = O(n log n)`

Scanning the events:

`O(2n) = O(n)`

Therefore the overall time complexity is:

**O(n log n)**

The event array uses **O(n)** extra space.

## Project Structure

```text
party_presence_sorting_lab/
├── docs/
│   ├── algorithm.md
│   └── comparison.md
├── src/
│   └── sorting.c
├── tests/
│   └── test_cases.txt
├── .gitignore
└── README.md
```

## Compile on Windows PowerShell

From the project folder:

```powershell
gcc src\sorting.c -o sorting.exe
.\sorting.exe
```

## Compile on Linux/macOS

```bash
gcc src/sorting.c -o sorting
./sorting
```

## Note

If the maximum number is reached more than once, the program reports the **first time** that maximum is reached.
