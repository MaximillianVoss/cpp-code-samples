# Stage Catalog

## Chronology

| Date of meaningful source state | Former local path | Git stage |
| --- | --- | --- |
| 2016-04-10 | `Архив/Бинарный поиск` | Initial matrix-search implementation |
| 2016-04-12 | `C++/Код C++/Бинарный поиск` | Later sequence-search revision |
| 2016-04-13 | `Архив/Перестановка солбцов и строк в матрице` | Matrix transposition exercise |
| 2016-04-17 | `Архив/C++ taine` | Queue, sorting, and class experiments |
| 2016-04-19 | `Архив/За­да­ние_25_№_4703` | Numbered exercise scratchpad |
| 2016-04-20 | `Архив/Объединение статических массивов` | Concatenation and absolute-value ordering |
| 2016-04-25 | `Архив/Практика Си` | Misnamed C++ pointer scratchpad |
| 2016-04-26 | `Архив/Односвязный список  C++` | Initial list implementation |
| 2016-04-28 | `Архив/Бинарное дерево C++` | Initial binary-search-tree implementation |
| 2017-01-27 | `C++/Код C++/Односвязный список  C++` | Later list experiment |
| 2018-08-03 | `C++/Код C++/Бинарное дерево C++` | Later height-calculation revision |

The 2019 dates found in Visual Studio databases are IDE state, not new source
stages. They remain in the preservation register but do not create artificial
source commits.

## Refactoring Findings

- The original list leaves `next` uninitialized, leaks nodes during reversal,
  and transfers ownership through raw pointers. The modern list uses
  `std::unique_ptr`, initializes every link, and has defined empty-list errors.
- The old binary-search helper starts the right bound at `size()`, which can
  index one element past the vector. The modern function validates sorted input
  and uses `std::equal_range` to count duplicates safely.
- The old tree never initializes `root`, leaks duplicate insertions, and uses
  integer division for an average reported as `double`. The modern tree owns
  nodes, ignores duplicates explicitly, and preserves fractional averages.
- The array-ordering function was described as insertion sort but actually used
  a shrinking-gap exchange pass. The modern function states and tests the real
  requirement: stable ordering by absolute magnitude.
- Matrix transposition duplicated behavior already recovered from `Программы
  RC`; the module links to that implementation instead of adding another copy.
- `За­да­ние_25_№_4703` contains several mutually exclusive exercises, an XOR
  expression where exponentiation was intended, uninitialized averages, and
  unchecked fixed buffers. It is retained as history rather than presented as
  production-ready code.

## Preservation Boundary

The public source snapshots contain only human-authored source/project files.
The private repositories `legacy-programming-projects-archive` and
`legacy-native-projects-archive` retain the approved binary payloads. Generated
and IDE-only files remain reproducible from their path, size, timestamps, and
SHA-256 values in `preservation/file-metadata.csv`.
