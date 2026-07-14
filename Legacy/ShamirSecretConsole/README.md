# Shamir Secret Console

RU: историческая консольная учебная работа 2019 года, демонстрирующая пороговое разделение секрета Шамира и визуализацию полиномов.

EN: a preserved and minimally refactored 2019 console exercise for Shamir secret sharing and polynomial visualization.

## Safety status

This is an educational arithmetic demonstration, not a cryptographic library. It uses `rand()`, accepts small integer moduli, keeps values in process memory, and does not implement authenticated storage or transport. Do not use it for real secrets.

## Current version

The runnable copy is under `app/`. The first refactoring pass:

- validates the threshold, prime modulus, and participant count;
- uses 64-bit intermediates for modular multiplication;
- ensures the highest polynomial coefficient is non-zero;
- replaces the unbounded session loop with one explicit run;
- removes automatic `system("python Main.py")` execution;
- limits visualization output to 25 series;
- adds a deterministic `--self-test` regression check;
- normalizes the runnable C++ sources from Windows-1251 to UTF-8 while keeping the original bytes in `preservation/`;
- fixes const access to points, an accidental infinite recursion in `Split`, and empty-vector output handling;
- updates the standalone project to the Visual Studio 2026 `v145` toolset.

Build from this repository with the latest Visual Studio/MSBuild:

```powershell
$msbuild = 'C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\amd64\MSBuild.exe'
& $msbuild '.\Legacy\ShamirSecretConsole\app\Shamir_Secret.sln' /t:Build /p:Configuration=Debug /p:Platform=x64 /m
& '.\Legacy\ShamirSecretConsole\app\build\x64\Debug\bin\Shamir_Secret.exe' --self-test
```

Run the console without arguments for an interactive demonstration. It writes `data.txt` to the current directory. The optional chart requires Python 3 and Matplotlib, then can be opened from `app/Shamir_Secret` with `python Main.py`.

## Preservation

The duplicate source trees originally lived at `C++/Shamir_Secret` and `C++/Код C++/Шифрование и криптография/Shamir_Secret`. Their 15 authored source/project files are byte-identical; the generated `data.txt` differs and both variants are retained.

- `preservation/original-source` is the unchanged source snapshot used for the import.
- `preservation/alternate-generated-data` retains the second `data.txt` variant.
- `preservation/file-metadata.csv` records all 84 original files, including generated IDE output, with SHA-256 and Windows timestamps.
- Commit `72dc2fcb4163e68fd795dd7c454055f9b84c5bd4` is the pre-refactor union import in this repository.
- The complete private snapshot is in [`legacy-native-projects-archive`](https://github.com/MaximillianVoss/legacy-native-projects-archive) at commit `54a7410ae04822b5e609059ecaf0f4d56f729b8c`.

Git commit dates describe import/refactoring work. The metadata CSV is authoritative for original filesystem dates, and the private archive is authoritative for exact pre-cleanup bytes.

## Provenance

The original source comments cite [`developer512/Shamir-s-Secret-Sharing`](https://github.com/developer512/Shamir-s-Secret-Sharing) as a reference. This retained exercise has not been audited for compatibility or security equivalence with that project.
