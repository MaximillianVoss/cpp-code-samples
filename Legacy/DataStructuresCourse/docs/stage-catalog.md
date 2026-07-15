# Recovered stage catalog

The order below follows recovered last-write timestamps, not assignment
numbers. Several files were edited again while later stages were in progress.

| Original folder | Recovered purpose | Notes |
| --- | --- | --- |
| `5 лаба` | Console geometry and shape inheritance | Extends the earlier shape hierarchy and keeps its report/screenshots. |
| `3 лаба` | Hash-backed `Set` implementation | Includes an original standalone file and a Visual Studio project revision. |
| `6 лаба` | Set experiment in a C# project shell | Contains C++ source beside `Program.cs`; the recovered project is not a valid modern mixed-language build. |
| `1 лаба` | Hash-table/set exercise | Includes source, Visual Studio project files, report, and screenshots. |
| `2 лаба` | AVL-tree exercise | Includes several historical reference documents copied into the lab folder. |
| `4 лаба` | Console geometry and shape hierarchy | Root-level headers and project-level headers are different revisions. |
| `6 lab` | Later revision of the lab-3 set project | Reuses reports/screenshots but changes the project implementation source. |
| `Lab 6  RC` | AVL/tree revision | Adds tree operations and visual output. |
| `Курсовая` | Tree coursework with file I/O | Extends the previous tree revision with file loading and benchmark-style runs. |
| `Lab 2 RC` | Alternate AVL revision | Smaller branch of the AVL implementation. |
| `Lab 3 RC` | Final recovered AVL/file-I/O revision | Latest modified stage in the recovered folder. |

## Duplicate policy

Shared Visual Studio scaffolding remains inside each historical project because
removing it would make the original solutions incomplete. Compiled outputs,
databases, PDB/OBJ/IPCH/TLOG files, and user-state files are not duplicated
here. Their original names, dates, sizes, and SHA-256 hashes remain in the
archive manifest.
