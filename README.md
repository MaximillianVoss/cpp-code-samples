# C++ Coursework Exercises (2016-2018)

This module consolidates eight small Visual C++ projects formerly scattered
between `Архив` and `C++/Код C++`. The original names are intentionally kept in
`original`, including the misspelled names `Перестановка солбцов...`,
`C++ taine`, and the misleading `Практика Си` (which is C++ despite its `.c`
extension).

## What Was Recovered

| Original project | Historical behavior | Disposition |
| --- | --- | --- |
| `Перестановка солбцов и строк в матрице` | Transpose a rectangular matrix | Reuses the tested transpose implementation from `ProgrammingExercisesRC` |
| `За­да­ние_25_№_4703` | Several unfinished array and student exercises | Preserved as source; incomplete and unsafe branches were not invented anew |
| `Объединение статических массивов` | Concatenate arrays and order values by absolute magnitude | Reimplemented and tested |
| `C++ taine` | Queue, quicksort, allocation, and class experiments | Preserved; overlaps standard containers and existing repository sort samples |
| `Односвязный список  C++` | Append, pop from the tail, and reverse a list | Reimplemented with owned nodes and tested |
| `Бинарный поиск` | Count values in matrix rows and columns | Search bounds and duplicate counting were corrected and tested |
| `Бинарное дерево C++` | Insert values and measure subtree height | Reimplemented with deterministic ownership and tested |
| `Практика Си` | Pointer and matrix scratch code | Preserved only; the original writes beyond `m[10][10]` and has no complete result |

The early and later copies of the search, list, and tree projects are distinct
historical stages. Their sequence is described in
[`docs/stage-catalog.md`](docs/stage-catalog.md), rather than treating either
copy as disposable duplication.

## Layout

- `original`: 84 byte-exact source, solution, project, and template files under
  their former local paths;
- `preservation`: 309 original NTFS records with paths, dates, sizes, SHA-256
  values, and private-archive references;
- `modernized`: portable C++20 implementations and deterministic tests;
- `docs/stage-catalog.md`: old-name mapping, chronology, defects, and decisions.

Eight compiled executables remain only in the private archive. IDE databases,
precompiled headers, object files, and build logs are represented by metadata,
because they are reproducible and account for nearly all of the old disk use.

## Verification

```powershell
& '.\modernized\scripts\test.ps1'
```

The original payload must remain byte-exact. Refactoring is confined to
`modernized`; files below `original` are historical evidence.
