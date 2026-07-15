# Inclined-Plane Friction Study (2016)

This module consolidates three stages of one mechanics exercise formerly stored
below `C++/Код C++`:

- `Трение`;
- `Windows Forms C++`;
- `Windows forms C++ RC`.

The console sketch introduced the equations. The two C++/CLI Windows Forms
folders are successive visualizations of the same coupled-mass experiment, not
independent applications. Original names and bytes remain available under
`original`; chronology and review findings are in
[`docs/stage-catalog.md`](docs/stage-catalog.md).

## Layout

- `original`: 41 byte-exact source, project, resource, icon, and draft files;
- `preservation`: metadata for all 140 historical files, including original
  NTFS timestamps, sizes, SHA-256 values, and private-archive references;
- `modernized`: a portable C++20 mechanics model and deterministic tests;
- `docs/stage-catalog.md`: lineage, duplicate analysis, defects, and decisions.

Three compiled executables and all IDE databases, object files, precompiled
headers, symbols, and build logs are represented by metadata only. These
reproducible files account for nearly all of the 310.4 MB historical footprint.

## Modernized Model

The maintained implementation models an incline mass connected over a pulley
to a hanging mass. Positive acceleration means that the hanging mass moves
down. The friction coefficient is used as both the static limit and kinetic
coefficient, matching the single-coefficient scope of the original exercise.

The solver reports direction, signed acceleration, rope tension, normal force,
friction magnitude, and the friction-free driving force. It also provides
validated angle/friction sweeps for the plots and a separate resultant-force
calculation for two equal rope tensions at a supplied included angle.

## Verification

```powershell
& '.\modernized\scripts\test.ps1'
```

Files below `original` are historical evidence and must remain byte-exact.
Refactoring belongs only in `modernized`.
