# Refactoring Analysis

## Current Pass

This pass focuses on the shared `Common` helpers because they are reused by tests, graph samples, crypto samples, and the legacy application project.

Completed changes:

- `Common/Sorts.h`: quick sort now handles empty and single-item vectors explicitly and sorts the local copy in-place instead of copying vectors on each recursive step.
- `Common/BinarySearch.h`: binary search is iterative and keeps the legacy contract: `Find` returns the index in a sorted copy, not the original input vector.
- `Common/Graph.h`: node and edge lookup no longer depends on indexes returned from a sorted copy; ID lookup now searches the actual graph storage.
- `Common Tests`: deterministic unit coverage was extended for sorting, binary search, and graph ID lookup.

## Important Findings

- Existing tests were present, but the common test executable did not run them automatically and waited for a console pause.
- Several legacy types implement comparison operators without `const`; shared templates must stay compatible with that style until those types are modernized together.
- Some tests still perform interactive input, file dialogs, fixed-path writes, graph exports, or plotting. They should remain outside the default automated runner until isolated.
- There are still duplicated helper concepts between `Common` and the legacy `Code Samples C++` application project. They should be merged gradually with tests around each helper.

## Next Safe Targets

- Make `GraphItem`, `Node`, and `Edge` const-correct, then tighten `Sorts` and `BinarySearch` signatures.
- Split interactive tests from deterministic tests in `Common Tests` and `Crypto Tests`.
- Move fixed test artifacts to `build/` or a test output directory instead of writing into the source tree.
- Continue namespace migration from facade headers into source declarations once the public examples are covered by tests.
