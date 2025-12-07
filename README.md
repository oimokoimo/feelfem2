# feelfem2 — A Beautiful FEM DSL for Education and Research

feelfem2 is a next-generation FEM (Finite Element Method) DSL and code generation framework,
designed to produce **beautiful, readable, and mathematically faithful Fortran codes** directly
from weak-form problem descriptions.

This project is a spiritual and technical successor to the original *feelfem* system
(1990s–2000s), reimagined with modern design principles, educational focus, and full openness.

feelfem2 started quietly at a hot-spring inn in Yugawara, early in the morning,
after a bottle of sake and a long conversation with an AI.
That origin is not accidental: this project is about **time, memory, mathematics, and beauty**.

---

## Philosophy

feelfem2 is built on the following principles:

- **Weak form first** — Users write mathematical weak formulations directly.
- **Separation of concerns** — Problem definition, discretization, assembly, solvers, and post-processing are cleanly separated.
- **Beautiful generated code** — The output Fortran code is intended to be *educationally exemplary*.
- **Trial ≠ Test is allowed** — True Petrov-Galerkin experiments are supported.
- **Numerical truth is visible** — H1 norm, energy norms, and stabilization effects must be directly observable.
- **Education-oriented, but not toy** — Simple enough for undergraduates, deep enough for researchers.

feelfem2 is **not**:
- A GUI-centered black box
- A fluid-only finite-volume solver
- A performance-at-all-costs industrial product

It is a **living mathematical instrument**.

---

## Core DSL Concepts (Draft)

```text
fem   u[P2], v[P2], p[P1];
fem  tu[P2], tv[P2], tp[P1];
ewise sigma[P2];

solve[u,v,p ; tu,tv,tp] {
  nonlinear;
  quadrature gauss3x3;

  weq: integral( dot(grad(u), grad(tu)) );
  weq: integral( p * div(tu) );
  weq: integral( div(u) * tp );

  nbc: g = 10, on top;
  dbc: u = 0, on left, right, bottom;
}
