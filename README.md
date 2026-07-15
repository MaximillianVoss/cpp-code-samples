# C++ Code Samples

<!-- repository-metadata:start -->
Target repository name: `cpp-code-samples`

Current GitHub repository: `MaximillianVoss/cpp-code-samples`

Previous GitHub repository: `MaximillianVoss/Code-Samples-C-`

RU description: Набор учебных и прикладных заготовок на C++: алгоритмы, структуры данных, консольные игры, простые тестовые каркасы и криптографические эксперименты.

EN description: A collection of C++ learning and utility samples: algorithms, data structures, console games, lightweight test scaffolding, and cryptography experiments.

Topics: `cpp`, `type-sample`, `learning`

Lifecycle/status: active refactoring
<!-- repository-metadata:end -->

## Назначение

Этот репозиторий сохраняется как набор заготовок для учебных и небольших C++ проектов. История старого проекта не переписывается: исходное состояние перед текущим рефакторингом сохранено отдельным git-тегом и bundle-архивом.

Текущий этап приводит проект к воспроизводимой сборке, единому стилю и понятной навигации в Visual Studio, не удаляя учебные примеры только потому, что они устарели.

## Purpose

This repository is kept as a collection of templates and examples for learning and small C++ projects. The old project history is preserved: the state before the current refactoring pass is saved as a git tag and as a bundle archive.

The current pass focuses on reproducible builds, consistent style, and clear Visual Studio navigation while keeping legacy educational examples available.

## Структура решения

- `Applications`: исполняемые учебные приложения and console entry points.
- `Libraries`: reusable libraries such as `Common`, `Crypto`, `Constants`, and `UnitTest`.
- `Tests`: simple sample/test projects.
- `Samples`: standalone snippets and experiments.
- `Legacy`: documented historical exercises with pre-refactor snapshots, including
  `ShamirSecretConsole`, the 2014 `FileParsingExperiments` sequence, and the
  recovered 2016 [data-structures course](Legacy/DataStructuresCourse/README.md).

Key namespace facade headers:

- `Common/Namespaces.h` -> `code_samples::common`
- `Crypto/Namespaces.h` -> `code_samples::crypto`
- `Code Samples C++/Namespaces.h` -> `code_samples::samples`

The facade headers provide a migration path toward namespaced code without breaking the original global-class samples immediately.

## Build

Recommended local build uses the latest Visual Studio/MSBuild instance installed on the machine:

```powershell
$vs = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
$msbuild = Join-Path $vs 'MSBuild\Current\Bin\MSBuild.exe'
& $msbuild 'Code Samples C++.sln' /t:Build /p:Configuration=Debug /p:Platform=x64 /m
```

The solution is aligned with Visual Studio 2026 / MSBuild 18 and C++ `PlatformToolset` `v145`. `WindowsTargetPlatformVersion` is kept as `10.0` so MSBuild selects the latest installed Windows SDK. Build outputs are redirected by `Directory.Build.props` into `build/<Platform>/<Configuration>/`.

## Unit Tests

The deterministic common helper tests are wired through the `Common Tests` project. After building `Debug|x64`, run:

```powershell
& '.\build\x64\Debug\bin\Common Tests.exe'
```

The test runner returns a non-zero exit code when any unit test fails.

## Refactoring Notes

Current analysis notes and next refactoring targets are tracked in `docs/refactoring-analysis.md`.

## Preservation

Pre-refactor preservation points:

- Git tag: `codex/pre-refactor-head-2026-06-09`
- Local preservation bundle: `C:\Users\FossW\OneDrive\Документы\Проекты GitHub\codex-preservation\code-samples-cpp-2026-06-09\committed-history.bundle`
- Recovered course branch: `archive/data-structures-course-2016`
- Byte-exact recovered source tag: `original-data-structures-course-2016`
- Original file names, timestamps, sizes, and hashes:
  [`Legacy/DataStructuresCourse/preservation/file-metadata.csv`](Legacy/DataStructuresCourse/preservation/file-metadata.csv)

The canonical GitHub repository is `MaximillianVoss/cpp-code-samples`.
