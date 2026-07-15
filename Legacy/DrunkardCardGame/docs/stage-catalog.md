# Stage Catalog

## Chronology

| Date (UTC) | Former name | Preserved location | Distinctive design |
| --- | --- | --- | --- |
| 2016-03-30 | `Архив/Drunk` | `original/Архив/Drunk` | 36-card deck in a manually managed dynamic-array `List`; game output could be appended to a text log |
| 2016-04-17 17:20 | `C++/Код C++/Drunk 3` | `original/C++/Код C++/Drunk 3` | Experimental circular linked queue and a reduced 16-card setup |
| 2016-04-17 17:32 | `C++/Код C++/Drunk 2` | `original/C++/Код C++/Drunk 2` | Split `Card`, `Deck`, `Queue`, rank, and suit types for a 36-card deck |
| 2016-04-27 | `Архив/Программы RC/for3(пьяница).cpp` | `../ProgrammingExercisesRC/original/for3(пьяница).cpp` | Single-file circular-queue rewrite |
| 2016-05-02 | `Архив/Программы RC/Пьяница RC` | `../ProgrammingExercisesRC/original/Пьяница RC` | Visual C++ project form of the RC rewrite |

The dates come from the preservation manifests, not from checkout timestamps.
The archive branch replays these states in this order so the original names and
development sequence remain inspectable in Git.

## Findings

### `Drunk`

- `List::pop()` indexes `-1` when called on an empty list.
- The copy constructor omits the last occupied element.
- Raw ownership is not assignment-safe.
- A tied battle can read from an exhausted player.
- The random deal uses modulo-biased `rand()` and global process state.

### `Drunk 3`

- Queue ownership relies on mutable raw-pointer rings with no clear lifetime.
- Empty and one-card edge cases can dereference null pointers.
- The implementation uses only part of a standard 36-card deck.
- The global round counter and console delays prevent deterministic tests.

### `Drunk 2`

- The class named `Queue` removes cards in stack order in key paths.
- Empty access returns invalid state instead of reporting failure.
- Several temporary objects allocated with `new` are leaked.
- Card comparison omits the earlier six-over-ace rule.

### RC stages

- They improve the circular queue but still leak helper nodes and assume that
  enough cards always exist during tied battles.
- `rand()`/`srand(time(...))`, Windows-only console calls, and unbounded play
  make behavior difficult to reproduce.
- The rank/suit encoding is inconsistent in places (`% 9` and `% 4` over a
  single integer), so display and identity are coupled unnecessarily.

## Refactoring Decision

The maintained engine uses value-type cards, `std::deque` for explicit FIFO
semantics, `std::mt19937` for seedable shuffling, and a bounded `play` method.
It preserves the historical six-over-ace rule while defining exhausted tie
behavior and retaining every card in either a hand or the unclaimed table.
