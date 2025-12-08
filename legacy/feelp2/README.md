# Legacy feelp2 sample: Modified 8-node Serendipity Element (Kikuchi)

This directory contains a legacy **feelp2** script developed in the early-to-mid 1990s as part of the original *feelfem* project.

This sample demonstrates:

- An **explicit definition of the modified 8-node serendipity quadrilateral element** proposed by Prof. Kikuchi.
- A complete **2D linear elasticity problem** written in a DSL-like FEM description language.
- **Exact solutions (`uex`, `vex`)** embedded in the script for numerical verification.
- Automatic **Fortran code generation** as the original execution target.
- Post-processing including **contour plots and error visualization**.

This script predates modern FEM DSL frameworks such as FEniCS and represents an early independent implementation of:

- Variational (weak-form) based problem description
- Explicit element-level shape function definition
- Symbolic-style expression of PDE operators (`dx`, `dy`)
- Boundary condition handling (`dbc`, `nbc`)
- Quadrature and solver selection inside the DSL

---

## Historical Context

- **1990–1991**: Initial development of FEM code generators using a LISP-based symbolic engine (feel P1).
- **1992–1995**: Development of **feelp2**, introducing:
  - Weak-form based FEM description
  - Trial/test function notation
  - Explicit element definition capability
- **1999–2003**: Full reimplementation in C++ with GiNaC as **feelfem**, adding:
  - Object-oriented pseudo-code representation
  - Parallel solvers
  - GiD mesh interface
  - Unstructured mesh support

This script belongs to the **feelp2 era** and is preserved as a **historical and technical reference** for the design philosophy of *feelfem2*.

---

## Technical Highlights of This Sample

- **Element type**: Modified 8-node serendipity quadrilateral
- **Element mapping**: Explicit geometric correction using temporary coefficients (`t1`–`t8`)
- **Problem type**: 2D linear elasticity
- **Boundary conditions**:
  - Dirichlet (fixed displacement)
  - Neumann (traction boundary)
- **Exact solution embedded**:
  ```text
  uex(x,y), vex(x,y)

