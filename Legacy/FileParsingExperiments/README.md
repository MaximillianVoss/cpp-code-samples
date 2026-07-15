# File Parsing Experiments (2014)

RU: четыре последовательные учебные заготовки C++/CX и консольного C++,
сохранённые из прежней папки `Архив`. Они объединены как одно семейство,
поскольку используют один шаблон и отражают шаги одной незавершённой идеи.

EN: four sequential C++/CX and console C++ learning stubs preserved from the
former `Архив` folder. They share one template lineage and represent stages of
the same unfinished file-processing experiment.

## Chronology

| Stage | Original name | Last meaningful source change | What existed |
| --- | --- | --- | --- |
| 1 | `Binary Checker` | 2014-02-10 | Windows Store `.bin` multi-file picker and an empty MD5 function |
| 2 | `Binary Checker Console` | 2014-02-10 | Empty Visual C++ console entry point |
| 3 | `Xparse(console)` | 2014-02-23 | File open/append draft with a non-terminating `while (!eof())` loop |
| 4 | `Xparser` | 2014-02-23 | Windows Store `.txt` picker, text display, and a commented parser-table draft |

The exact source-only bytes are under `preservation/original-source`, ordered by
stage. These projects are not added to the active solution because none contains
a complete reusable algorithm:

- the MD5 function has no body;
- both console applications contain no completed parsing behavior;
- `Xparse(console)` can loop forever because the stream is never consumed;
- `Xparser` defines a token header table but does not tokenize input;
- the C++/CX UI depends on the obsolete Windows 8.1 Store toolchain;
- generated XAML C++ files dominate the old build output but are reproducible.

## Preservation

The metadata register covers 254 original records (621,151,316 bytes). The
source-only snapshots contain 48 exact files (83,157 bytes), all verified by
SHA-256. The other 206 records describe generated XAML, IDE databases,
precompiled headers, debug output, and local state; they remain metadata-only
here and are retained in the private archive.

`preservation/file-metadata.csv` is authoritative for original paths, SHA-256,
NTFS timestamps, and inclusion decisions. Git commit dates describe the import,
not the original filesystem chronology.

## Disposition

No modern implementation was created because a new parser would not be a
refactoring of the surviving code. The useful historical lesson is documented;
future delimiter-separated parsing should use a tested parser library rather
than these stubs.
