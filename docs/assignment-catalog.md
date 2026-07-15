# Assignment Catalog

## Chronology

| Last source update (UTC) | Former name | Subject |
| --- | --- | --- |
| 2015-10-16 22:25 | `Пересечение отрезков` | Find the intersection point of two supporting lines and test whether it belongs to both segments |
| 2015-10-23 18:03 | `Быстрая сортировка` | Sort a user-supplied integer array with recursive quicksort |
| 2015-10-29 08:09 | `Пересечение прямых` | Classify and intersect two lines given by `a*x + b*y = c` |
| 2015-11-28 12:54 | `Вектор C++` | Add, insert, remove, and print values in a manually resized integer buffer |

The archive branch follows last source-write timestamps. Original creation and
access dates remain available in `preservation/file-metadata.csv`.

## Findings

### `Быстрая сортировка`

- The recursive partition is valid for typical input but exposes raw pointers
  and an inclusive end index, making empty input easy to misuse.
- Allocation is never released by the console entry point.
- Windows-only headers and `system("pause")` are unrelated to the algorithm.
- The repository already contains a tested general quicksort in `Common`; the
  recovered version is preserved as lineage rather than replacing it.

### `Вектор C++`

- Memory allocated with `new[]` is passed to `realloc`, which is undefined
  behavior, and no destructor releases the final buffer.
- `pop` and `remove` underflow on an empty vector.
- Negative indexes pass the `index < size` check and can write before the
  allocation.
- Recursive menu calls grow the call stack for every user action.

### `Пересечение прямых`

- The formula divides by `a`, so a vertical first line fails even when the
  determinant proves that a unique intersection exists.
- Exact floating-point equality is used for parallel/coincident decisions.
- Coincidence is detected only when coefficients are identical, not merely
  proportional.

### `Пересечение отрезков`

- The bounding-box check compares `xPoint` to Y bounds and never uses
  `yPoint`, producing false positives and negatives.
- Intersection coordinates are truncated to integers before membership tests.
- Parallel, collinear-overlap, endpoint, vertical-line, and degenerate-segment
  cases are incomplete.
- `Code.txt` contains abandoned alternatives, including returning a pointer to
  a local array and a second entry point; it is preserved as a draft, not built.

## Refactoring Decision

The maintained layer uses value types, explicit exceptions for invalid
operations, epsilon-aware determinant tests, and complete collinear segment
handling. Tests cover the defects above while leaving every original byte
untouched.
