# Alexandra C++ Assignments (2015)

This module consolidates four Visual C++ exercises formerly stored below
`C++/Код C++/Задания Александры`:

- `Быстрая сортировка`;
- `Вектор C++`;
- `Пересечение прямых`;
- `Пересечение отрезков`.

The original folder name is retained as historical provenance. The exercises
are independent assignments, not four copies of one project. Their chronology
and the defects found during review are documented in
[`docs/assignment-catalog.md`](docs/assignment-catalog.md).

## Layout

- `original`: 33 byte-exact source, solution, project, template, and draft
  files under their former local path;
- `preservation`: metadata for all 111 historical files, including original
  NTFS timestamps, sizes, SHA-256 values, and private-archive references;
- `modernized`: portable C++20 implementations and deterministic tests;
- `docs/assignment-catalog.md`: old-name mapping, chronology, defects, and
  refactoring decisions.

Four compiled executables and all IDE databases, object files, precompiled
headers, symbols, and build logs are represented by metadata only. They are
reproducible and account for nearly all of the 236.9 MB historical footprint.

## Modernized Scope

The maintained code provides a bounds-checked dynamic-array exercise, a
three-way quicksort that handles duplicate values, robust line classification,
and segment intersection including endpoint and collinear-overlap cases.
Production code would normally use `std::vector` and `std::sort`; the wrappers
remain here because ownership and partitioning were the subjects of the
original assignments.

## Verification

```powershell
& '.\modernized\scripts\test.ps1'
```

Files below `original` are historical evidence and must remain byte-exact.
Refactoring belongs only in `modernized`.
