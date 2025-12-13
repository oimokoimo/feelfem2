/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_ff90LUMPING.hpp
 *  Date     : 2002/10/07 (copy from MT_ff90SKYLINE.hpp)
 *  Modified : 
 *  
 *  Purpose  : Fortran90 skyline matrix model
 *  
 */

#ifndef FEM_CLASS_MT_FF90LUMPING
#define FEM_CLASS_MT_FF90LUMPING

#include "PM_feelfem90.hpp"                // FEM Program Model

class MT_ff90LUMPING : public PM_feelfem90 {

public:
  MT_ff90LUMPING();  // Constructor
  ~MT_ff90LUMPING(); // Destructor

  void F90useSolveMT(void);

  // P2/CRS dependent argument list
  void pushMatrixArgumentsCalled(void);      // in feelfem90, same as below
  void pushMatrixArgumentsAllocated(void);   // in feelfem90, same as over
  void writeMatrixDeclarations(void);

  // nvmax,nfmax ......

  void DoSolveCallLinearNeumannData  ( Solve *);
  void DoSolveCallLinearDirichletData( Solve *);
  void DoSolveCallEdevRoutine        ( Solve *); // distributed case, obligatoy
  void DoSolveMakeUpdateInformationMT( void   ); // make update information 
                                                 // after dcond
  void DoSolveFreeMemoryMT(); 


  // Solve part
#include "DO_solve_MT.hpp"


  // Element Assembly   
#include "DO_elem_MT.hpp"

  // Dirichlet generator
#include "DO_dirichlet_MT.hpp"


  // Neumann Conditions
#include "DO_neumann_MT.hpp"


  // ElemGenerator main
  void GenerateCoSolveElemGenerator( Solve *);
  void GenerateCoSolveEdevRoutine( Solve *);

};

#endif
