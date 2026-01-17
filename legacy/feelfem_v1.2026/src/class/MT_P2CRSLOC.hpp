/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2CRSLOC.hpp
 *  Date     : 2000/03/24
 *  Modified : 2000/03/24
 *  
 *  Purpose  : Distributed CRS storage for FEEL P2/CRSLOC program model
 *  
 */

#ifndef FEM_CLASS_MT_P2CRSLOC
#define FEM_CLASS_MT_P2CRSLOC

#include "PM_feelP2DRAMA.hpp"           // FEM Program Model

class MT_P2CRSLOC : public PM_feelP2DRAMA {

public:
  MT_P2CRSLOC();  // Constructor
  ~MT_P2CRSLOC(); // Destructor

  // P2/CRS dependent argument list
  void pushMatrixArgumentsCalled(void);      // valmat,indptr,....
  void pushMatrixArgumentsAllocated(void);   // feel(np_VALMAT),...
  void writeMatrixDeclarations(void);


  // nvmax,nfmax ......

  void DoSolveCallLinearNeumannData  ( Solve *);
  void DoSolveCallLinearDirichletData( Solve *);
  void DoSolveCallEdevRoutine        ( Solve *); //distributed case, obligatoy
  void DoSolveFreeMemoryMT();
 
  // solve related
#include "DO_solve_MT.hpp"


  // Element Assembly   
#include "DO_elem_MT.hpp"

  // Dirichlet Conditions
#include "DO_dirichlet_MT.hpp"

  // Neumann Conditions
  void DoNeumannRoutineHeaderMT(Neumann *);
  void DoNeumannArgumentSequenceMT(Neumann *);
  void DoNeumannApplyMatrixMT(Neumann *);


  // ElemGenerator main
  void GenerateCoSolveElemGenerator( Solve *);
  void GenerateCoSolveEdevRoutine( Solve *);

};

#endif





