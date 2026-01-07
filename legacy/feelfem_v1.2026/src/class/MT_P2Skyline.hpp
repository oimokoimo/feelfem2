/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MT_P2Skyline.hpp
 *  Date     : 1999/11/02
 *  Modified : 1999/11/18
 *  
 *  Purpose  : Matrix Allocations for feel P2 skyline type
 *  
 */

#ifndef FEM_CLASS_MT_P2SKYLINE
#define FEM_CLASS_PM_P2SKYLINE

#include "PM_feelP2.hpp"           // FEM Program Model

class MT_P2Skyline : public PM_feelP2 {

public:
  MT_P2Skyline();  // Constructor
  ~MT_P2Skyline(); // Destructor


                                        // nvmax,nfmax ......
  void DoSolveCallLinearNeumannData  ( Solve *);
  void DoSolveCallLinearDirichletData( Solve *);
  void DoSolveCallEdevRoutine        ( Solve *); //distributed case, obligatoy

  void DoSolveFreeMemoryMT();

  //
#include "DO_solve_MT.hpp"

  // ElemGenerator main
  void GenerateCoSolveElemGenerator( Solve *);

  
};

#endif





