# feel p2 + bamg (INRIA 1997–1998) revival  



This repository contains a revived working environment for **feel p2** and the **bamg (Bidimensional Anisotropic Mesh Generator)** originally developed and used during my stay at **INRIA (1997–1998)**.

After more than 25 years, the original code base has been brought back to life and is now executable on a modern Linux system, thanks to containerization.

## What is revived

- **bamg v0.62** (F. Hecht, INRIA)
- **feel p2** finite element framework
- Anisotropic adaptive mesh generation
- Newton-based nonlinear solver workflow (DNORM convergence confirmed)

All binaries are built inside a Podman container, but the resulting executables also run correctly on the host system.

## How it was revived

This revival was completed in **Ito (伊東)** during a personal **keirin (track cycling) training camp**.

In the mornings and evenings:
- cycling training,
- onsen,
- quiet concentration.

Between races and recovery:
- resurrecting 1990s C/Fortran code,
- resolving pre-ISO C compatibility issues,
- rebuilding bamg with a minimal, historically faithful toolchain.

In the late 1990s, recompiling `feel.parse` on an **EWS4800/220 (R3000, 120 MHz, 32 MB)** took long enough for a coffee break.  
Today, on a **Dell XPS 8950**, the same build finishes almost instantly.

Time passed — the code waited.

## Build environment

- OS: Ubuntu 18.04 (container)
- Compiler: gcc / g++ 4.8
- Container runtime: Podman
- Legacy compatibility headers:
  - `iostream.h`
  - `fstream.h`
  - `iomanip.h`
  - `new.h`

The container acts as a **time capsule** preserving the original assumptions of the code.

## Status

- ✅ `bamg` executable runs
- ✅ adaptive mesh generation works
- ✅ feel p2 + bamg coupling works

## Historical note

This code was written during my stay at INRIA in 1997–1998.
It survived silently for decades.
In Ito, during a keirin camp, it finally returned to life.

Some things are not obsolete.
They were just waiting.

— Hidehiro Fujio
