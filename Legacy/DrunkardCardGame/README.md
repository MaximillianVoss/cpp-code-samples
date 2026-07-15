# Drunkard Card Game (2016)

This module consolidates five successive implementations of the card game
commonly called `Пьяница`. They were previously scattered between `Архив`,
`C++/Код C++`, and `Архив/Программы RC` under the names `Drunk`, `Drunk 3`,
`Drunk 2`, `for3(пьяница).cpp`, and `Пьяница RC`.

The numbering is misleading: file dates show that `Drunk 3` predates
`Drunk 2`. The recovered order and the defects found in each stage are recorded
in [`docs/stage-catalog.md`](docs/stage-catalog.md).

## Layout

- `original`: 33 byte-exact source, solution, project, and template files from
  the first three stages, retained below their former local paths;
- `preservation`: metadata for all 99 historical files, including original
  NTFS timestamps, sizes, SHA-256 values, and private-archive references;
- `modernized`: a portable C++20 implementation with deterministic tests;
- `docs/stage-catalog.md`: chronology, old-name mapping, defects, and decisions.

The two later stages are already preserved byte-for-byte in the sibling
[`ProgrammingExercisesRC`](../ProgrammingExercisesRC/README.md) module. They
are referenced instead of copied again.

Compiled executables, IDE databases, object files, precompiled headers, and a
2.2 MB generated play log remain in the private archive or as metadata only.
They are not useful source history and can be reproduced from the code.

## Modernized Rules

The maintained implementation uses a 36-card deck, FIFO player queues, and the
historical special rule that a six beats an ace. Equal ranks continue the same
battle. If one player cannot continue a tied battle, the other receives the
table; simultaneous exhaustion is a draw. Game execution is explicitly
bounded so cyclic deals cannot run forever.

## Verification

```powershell
& '.\modernized\scripts\test.ps1'
```

Files below `original` are historical evidence and must remain byte-exact.
Refactoring belongs only in `modernized`.
