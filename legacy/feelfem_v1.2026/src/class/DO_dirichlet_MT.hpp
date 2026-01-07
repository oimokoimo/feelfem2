/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_dirichlet_MT.hpp
 *  Date     : 2002/03/07
 *  Modified : 
 *  
 *  Purpose  : Matrix related Dirichlet generator
 *  
 */

void DoDirichletRoutineHeaderMT(Dirichlet *);   // called in generatortemplate
void DoDirichletArgumentSequence(Dirichlet *);  // subsidary of above
void DoDirichletApplyMatrixMT(Dirichlet *);

void doDirichletAutoVariableDefinitionsMT(Dirichlet *);
