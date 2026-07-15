# Stage Catalog

| Date (UTC) | Original item | Recovered meaning |
| --- | --- | --- |
| 2016-04-27 20:02:37 | `dz3.cpp` | First bracket-checking draft. |
| 2016-04-27 20:02:41 | `dz3_final_version.cpp` | Expanded bracket validator with diagnostics. |
| 2016-04-27 20:02:46 | `dz4_final_version.cpp` | Fourth standalone homework exercise. |
| 2016-04-27 20:02:49 | `dz5_1.cpp` | Fixed-capacity circular queue. |
| 2016-04-27 20:02:54 | `for3(пьяница).cpp` | First card-game implementation. |
| 2016-04-27 20:22:05 | `dz1.c` | Dynamic-array resize exercise. |
| 2016-04-29 17:27:49 | `Класс String` | Visual Studio project skeleton. |
| 2016-04-29 17:39:45 | `Очерель RC` | Visual Studio queue project skeleton; typo retained. |
| 2016-05-02 11:55:15 | `Класс String.cpp` | Custom string implementation. |
| 2016-05-02 12:06:15 | `Очерель RC.cpp` | Queue implementation in the project. |
| 2016-05-02 12:43:03 | `dz2(транспонирование).cpp` | Standalone matrix transposition. |
| 2016-05-02 12:44:22 | `Транспонирование` | Visual Studio project skeleton. |
| 2016-05-02 12:50:17 | `Транспонирование.cpp` | Project form of matrix transposition. |
| 2016-05-02 19:06:17 | `Пьяница RC` | Visual Studio card-game project skeleton. |
| 2016-05-02 20:04:19 | `Пьяница RC.cpp` | Second card-game implementation. |

## Duplicate Review

The standalone and Visual Studio forms of transposition and the card game are
related revisions, not byte-identical copies. They are retained as separate
chronological stages. Common Visual Studio template headers are exact copies
already seen elsewhere in `cpp-code-samples`; Git object storage deduplicates
their blobs.

The active repository already contains stronger binary-search, binary-tree,
linked-list, and matrix abstractions. This import therefore keeps the original
exercise context under `Legacy` and promotes only independently testable
behavior in `modernized`.
