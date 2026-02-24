/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_F90.hpp
 *  Date     : 2003/01/26
 *  Modified : 
 *  
 *  Purpose  :
 *  
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *
 */

  void pushInteger4sc(void);     // integer                                 ::
  void pushInteger4pm(void);     // integer,parameter                       ::
  void pushInteger4Ptr1(void);   // integer,dimension(:),pointer            ::
  void pushInteger4Ptr2(void);   // integer,dimension(:,:),pointer          ::
  void pushInteger4In(void);     // integer,intent(in)                      ::
  void pushTypeDefCC(const char *);    // STRING            ....                  ::
  void pushLogical(void);        // locical                                 ::

  void writeInteger4sc(const char *);    // integer                        
  void writeInteger4pm(const char *);    // integer,parameter              
  void writeInteger4Ptr1(const char *);  // integer,dimension(:),pointer   
  void writeInteger4Ptr2(const char *);  // integer,dimension(:,:),pointer 
  void writeInteger4In(const char *);    // integer,intent(in)             
  void writeLogical(const char *);

  void pushReal8sc(void);        // real(kind=REAL8)                        ::
  void pushReal8pm(void);        // real(kind=REAL8)                        ::
  void pushReal8Ptr1(void);      // real(kind=REAL8),dimension(:),pointer   ::
  void pushReal8Ptr2(void);      // real(kind=REAL8),dimension(:,:),pointer ::
  void pushReal8Array1(void);    // real(kind=REAL8),dimension(:)           ::

  void writeReal8sc(const char *);   // real(kind=REAL8)                   
  void writeReal8pm(const char *);   // real(kind=REAL8)                   
  void writeReal8Ptr1(const char *); // real(kind=REAL8),dimension(:),pointer
  void writeReal8Ptr2(const char *); // real(kind=REAL8),dimension(:,:),pointer

  // for F90 use statements
  void F90useAlways(void);
  void F90useFEMDataType(void);

  void F90useMainPM(void);      // for main routine
  void F90useSolvePM(Solve *);  // for solve routine
  void F90useElemPM(SolveElement *);
  void F90useDirichletPM(void); // for dirichlet routine
  void F90useNeumannPM(void);   // for neumann routine

