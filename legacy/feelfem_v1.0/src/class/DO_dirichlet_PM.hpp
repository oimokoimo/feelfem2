/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_dirichlet.hpp
 *  Date     : 2001/11/29
 *  Modified : 2002/06/26   add loopstart,calcboundaryvalue,loopend
 *  
 *  Purpose  : DoDirichlet family
 *  
 */

void  DoDirichletArgumentVariableDefinitionsPM(Dirichlet *);
void  doDirichletAutoVariableDefinitionsPM(Dirichlet *);
void  DoDirichletInitializer(Dirichlet *);
void  DoDirichletLoopStart(Dirichlet *);
void  DoDirichletCalcBoundaryValue(Dirichlet *);
void  DoDirichletLoopEnd(Dirichlet *);
void  DoDirichletReturnSequencePM(Dirichlet *);

// called in DoDirichletCalcBoundaryValue()
void  doSetDirichletValue(Dirichlet *);


// called from DoDirichletArgumentSequencePM(Dirichlet *); in MatrixModel
void  doIthDirichletCallInSolvePM(Solve *,int );   // call sentence in solve
void  doIthDirichletCallInSolvePM2(Solve *,int );   // call sentence in solve
void  doDirichletArgumentSequencePM(Dirichlet *);  // subroutine sentence dcond

