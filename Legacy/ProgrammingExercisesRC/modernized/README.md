# Modernized Exercises

Portable C++20 versions of the reusable behavior recovered from `Программы RC`:

- rectangular matrix transposition with shape validation;
- bracket validation with a structured error and source offset;
- a bounded circular queue with explicit overflow and underflow errors.

Build and run the tests from this directory:

```powershell
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

The module uses only the C++ standard library. Original console I/O, Windows
headers, raw allocation, and fixed global buffers are intentionally outside the
refactored core.
