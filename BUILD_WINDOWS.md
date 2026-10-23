# Building Smina on Windows

This guide provides instructions for compiling native 64-bit Windows executables (`smina.exe`, `tosmina.exe`, `fromsmina.exe`, `server.exe`).

Two build options are provided:
- **Option 1: MSYS2 / MinGW-w64 (Recommended for Performance)** — Uses GCC `g++ -O3 -march=native -flto` via MSYS2 UCRT64. Delivers highest runtime performance for docking and minimization calculations and easiest dependency setup.
- **Option 2: CMake + Visual Studio 2022 (MSVC)** — Generates standard Visual Studio project solutions using Microsoft Visual C++ and `vcpkg`.

---

## Option 1: MSYS2 / MinGW-w64 (UCRT64) [Recommended]

### 1. Install MSYS2
If you do not already have MSYS2 installed:
1. Download and install MSYS2 from [msys2.org](https://www.msys2.org/).
2. Launch the **MSYS2 UCRT64** terminal (from Start Menu).

### 2. Install Required Dependencies
In the MSYS2 UCRT64 terminal, run:
```bash
pacman -Syu
pacman -S --needed \
    mingw-w64-ucrt-x86_64-gcc \
    mingw-w64-ucrt-x86_64-make \
    mingw-w64-ucrt-x86_64-boost \
    mingw-w64-ucrt-x86_64-zlib \
    mingw-w64-ucrt-x86_64-eigen3 \
    mingw-w64-ucrt-x86_64-openbabel
```

### 3. Build Smina
Navigate to the repository and the Windows release build folder:
```bash
# Navigate to the repo (example for E: drive)
cd {smina root directory}/smina/build/windows/release

# Compile using all available CPU cores
make -j$(nproc)
```

The resulting binaries (`smina.exe`, `tosmina.exe`, `fromsmina.exe`, `libsmina.a`) will be generated in `build/windows/release/`, and OpenBabel `.obf` format plugins are automatically deployed alongside them.

---

## Option 2: Visual Studio 2022 (MSVC) + CMake

### 1. Prerequisites
- **Visual Studio 2022** (Community, Professional, or Enterprise) with the "Desktop development with C++" workload installed.
- **CMake** (v3.15 or newer).
- **vcpkg** (Microsoft C++ package manager):
  ```cmd
  git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
  cd C:\vcpkg
  .\bootstrap-vcpkg.bat
  ```

### 2. Install Dependencies via vcpkg
Open a command prompt / PowerShell:
```powershell
C:\vcpkg\vcpkg install boost-program-options boost-filesystem boost-thread boost-system `
    boost-iostreams boost-regex boost-serialization boost-date-time boost-timer `
    boost-chrono boost-asio boost-ptr-container boost-assign boost-math `
    zlib eigen3 --triplet x64-windows
```

### 3. OpenBabel (MSVC 2022)
Because C++ standard library types (`std::string`, `std::vector`) must match MSVC runtime ABIs, OpenBabel must be compiled with MSVC 2022 (v143).
To build OpenBabel 3 with MSVC:
```powershell
# From openbabel source directory:
cmake -B openbabel-build -G "Visual Studio 17 2022" -A x64 `
    -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" `
    -DCMAKE_INSTALL_PREFIX="C:/openbabel-install" `
    -DOPENBABEL_USE_SYSTEM_INCHI=OFF `
    -DENABLE_TESTS=OFF

# Build core library and format plugins (PDB, PDBQT, SDF, etc.)
cmake --build openbabel-build --config Release --target openbabel formats_common formats_misc formats_utility formats_compchem --parallel
cmake --install openbabel-build --config Release
```

### 4. Configure and Build Smina with CMake
From the root of the Smina repository:
```powershell
cmake -B build-msvc -G "Visual Studio 17 2022" -A x64 `
    -DCMAKE_TOOLCHAIN_FILE="C:/vcpkg/scripts/buildsystems/vcpkg.cmake" `
    -DOPENBABEL_DIR="C:/openbabel-install"

cmake --build build-msvc --config Release --parallel
```

Executables (`smina.exe`, `tosmina.exe`, `fromsmina.exe`) will be generated in `build-msvc/Release/`.
The build system automatically copies `openbabel-3.dll`, format plugins (`.obf`), and OpenBabel data tables next to `smina.exe`.
Move the Release folder to your designated location and add the path to the environment variables `PATH`, for the program to work properly.

---

## Runtime Notes & Troubleshooting

### OpenBabel Formats and Data on Windows
Smina uses OpenBabel dynamic format plugins (`.obf`) for reading and writing formats such as PDB, SDF, and MOL2.
- When using **Option 1 (MSYS2 / MinGW-w64)**:
  - Plugins (`.obf`) are automatically copied into `build/windows/release/` during the build.
  - If executing binaries directly in PowerShell / Command Prompt outside the MSYS2 shell, ensure `C:\msys64\ucrt64\bin` is in `$env:PATH` and set `$env:BABEL_LIBDIR = "."`.
- When using **Option 2 (CMake + MSVC)**:
  - OpenBabel format plugins (`.obf`), `openbabel-3.dll`, and data tables are automatically copied into `build-msvc/Release/` next to `smina.exe`.

### Verification & Testing
Test that your compiled binary is working by running:

#### For Option 1 (MSYS2 UCRT64 / MinGW):
```powershell
$env:PATH = "C:\msys64\ucrt64\bin;$env:PATH"
$env:BABEL_LIBDIR = "."
cd build\windows\release

# Check version & help
.\smina.exe --version
.\smina.exe --help

# Test scoring
.\smina.exe --receptor receptor.pdbqt --ligand ligand.pdbqt --score_only

# Test docking (monte carlo search & minimization)
.\smina.exe --receptor receptor.pdbqt --ligand ligand.pdbqt --autobox_ligand ligand.sdf --exhaustiveness 4 --num_modes 3 --out docked.sdf

# Test format converters
.\tosmina.exe ligand.sdf ligand.smina
.\fromsmina.exe ligand.smina
```

#### For Option 2 (Visual Studio 2022 / MSVC):
```powershell
cd build-msvc\Release

# Check version & help
.\smina.exe --version
.\smina.exe --help

# Test scoring
.\smina.exe --receptor receptor.pdbqt --ligand ligand.pdbqt --score_only

# Test docking (monte carlo search & minimization)
.\smina.exe --receptor receptor.pdbqt --ligand ligand.pdbqt --autobox_ligand ligand.pdbqt --exhaustiveness 4 --num_modes 3 --out docked.pdbqt

# Test format converters
.\tosmina.exe ligand.pdbqt ligand.smina
.\fromsmina.exe ligand.smina
```
