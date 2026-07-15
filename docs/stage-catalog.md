# Stage Catalog

## Chronology

| Last source update (UTC) | Former name | Role |
| --- | --- | --- |
| 2016-04-12 18:38 | `Трение` | Console formula sketch with no interactive behavior |
| 2016-04-30 07:28 | `Windows Forms C++` | First C++/CLI WinForms input and hand-drawn plot |
| 2016-06-02 23:58 | `Windows forms C++ RC` | Later revision using WinForms chart controls |

The archive branch follows the last source-write timestamps. Original creation
and access dates remain available in `preservation/file-metadata.csv`.

## Duplicate Analysis

The WinForms folders share the same project GUID and 12 byte-identical public
payload files. The later `RC` stage changes the solution, form, entry point, and
results implementation and adds `Code2.txt`. It is therefore a revision, not a
duplicate to retain as a second maintained application.

## Findings

### Console sketch

- The program computes nothing in `main`; only free functions contain the
  proposed equations.
- Macros, `float`, Windows-only headers, and an integer point type obscure an
  otherwise portable numerical exercise.
- Direction and the physical meaning of the pulley-force angle are implicit.

### First WinForms stage

- `plotOffsetY` is read from the `offsetX` setting.
- The form's string conversion leaves every `StringToHGlobalAnsi` allocation
  unreleased because `FreeHGlobal` is commented out.
- Numerical parsing silently maps malformed input to zero through `atof`.
- Paint events allocate `Results` with `new` and never release it.
- Model values are mixed with pixel scaling and axis offsets, so calculations
  cannot be tested independently from rendering.

### `RC` WinForms stage

- The acceleration branch tests the constructor's member angle while formulas
  may be evaluating a different supplied angle, corrupting angle sweeps.
- Several expressions add masses or a bare cosine to forces, which is
  dimensionally inconsistent.
- Force-sweep calls interchange angle and friction arguments.
- Acceleration and force functions can reach the end without returning a value.
- The force overload ignores its acceleration argument.
- Static arrays are only partially initialized and therefore inject zeros into
  the remaining plotted points.
- The form retains the unmanaged string-conversion leak from the first stage.

## Refactoring Decision

The maintained layer separates physical values from presentation coordinates,
uses `double`, validates every input, and defines one sign convention. The
friction-free drive determines motion direction; friction either holds the
system at rest or reduces the drive in that direction. Tests cover equilibrium,
both motion directions, friction hold, tension, pulley resultant force, sweeps,
and invalid inputs. The legacy C++/CLI interfaces remain evidence only.
