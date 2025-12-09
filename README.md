# feelfem2

**feelfem2** is a modern re-design and re-implementation of the original **feelfem / FEEL** system,  
a finite element method (FEM) description language and code generation framework developed in the 1990s–2000s.

This project aims to:
- inherit the *conceptual beauty* of FEEL,
- modernize the DSL, parser, and backend architecture,
- and provide an **educational, free, and beautiful FEM code generation environment**.

---

## 1. Background

The original **FEEL / feelfem** system was developed to:

- describe FEM problems at a **weak-form / variational level**,
- generate **vectorized and parallel FEM programs automatically**,
- integrate with **GiD** for pre/post-processing,
- and serve as a **problem-solving environment (PSE) mid-layer**.

### Major Publications

- H. Fujio, *The feelfem System - A Repository System for the Finite Element Method*, IPDPS 2003  
- H. Fujio, F. Kikuchi, *Implementation of covariant and contravariant families of finite elements*, 1998  
- H. Fujio, *FEEL – Numerical Simulation Language for FEM*, 1993–1994  
- H. Fujio et al., *Development of FEM Code Generator for Vector/Parallel Computation*, NEC Technical Report 2002

By **2003**, the overall architecture of FEEL and feelfem was already conceptually complete.

---

## 2. Why feelfem2?

Despite the conceptual maturity, the original implementation suffered from:

- C / C++98 limitations
- lex / yacc based parsing
- strongly pointer-based data structures
- limited portability to modern environments

Meanwhile, modern FEM frameworks such as **FEniCS** appeared —  
but the original goal of **DSL-level mathematical transparency and educational beauty** was never fully achieved elsewhere.

**feelfem2** revives this original vision with modern technology:

- modern parsing frameworks
- clean IR (intermediate representation)
- multiple backends (Fortran, C++, GPU, etc.)
- educational-grade sample codes with **copyright-free beautiful Fortran**

---

## 3. Design Philosophy

- FEM should be described **as mathematics**, not as tangled source code.
- Weak forms, trial/test functions, and boundary conditions should be **first-class language objects**.
- Generated codes must be:
  - readable
  - modifiable
  - verifiable
- FEM education should not be blocked by:
  - weak-form formal barriers
  - broken sample codes full of typos
  - unreadable legacy Fortran

**feelfem2 is designed as a liberation tool for FEM education.**

---

## 4. Legacy Implementation

The historical FEEL / feelfem implementation is preserved under:

