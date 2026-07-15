# Programming Exercises RC (2016)

This directory preserves the original folder `Программы RC` as a chronological
source-only history. The recovered branch contains 15 commits dated from
2016-04-27 through 2016-05-02; the tag
`original-programming-exercises-rc-2016` points to the last unmodified source
snapshot.

## Contents

- `original`: byte-exact C/C++ source, Visual Studio project files, and template
  readme files under their original names;
- `preservation`: original NTFS paths, sizes, timestamps, SHA-256 values, and
  records for excluded IDE/build files;
- `modernized`: a portable C++20 extraction of the completed reusable ideas;
- `docs/stage-catalog.md`: chronology and disposition of each exercise.

The original implementations are retained for historical review. They are not
part of the active Visual Studio solution because they rely on manual memory
management, fixed-size buffers, deprecated project formats, and interactive
console behavior that is difficult to test.

## Refactoring Boundary

The initial refactor covers matrix transposition, bracket validation, and a
bounded circular queue. These behaviors were complete enough to identify and
test without inventing new requirements. The custom string and both versions
of the card game remain historical source: replacing them safely would be a
separate implementation rather than a small refactor.

## Verification

All 39 public source/project files match the original SHA-256 register. The
remaining 79 records describe four preserved executables and generated or IDE
state; their paths, sizes, hashes, and original dates remain in
`preservation/file-metadata.csv` and in the private archive.
