/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_basic.hpp"
 *  Date     : 2003/01/25
 *  Modified : 
 *  
 *  Purpose  : Basic code generator for ProgramModel
 *  
 */

void pushCoordinateSource(void);           // push x,y,z

void NameVariableInCalled    (Variable *, string &);
void pushVariableInCalled    (Variable * );                  // one variable
void pushVariableListInCalled(orderedPtrList<Variable *>); // orderedPtrList
void pushVariableListInCalled(list  <Variable *> );         // list version
void pushVariableListInCalledOnlyFEM(list  <Variable *> );  // Only FEM var
void pushVariableListInSolve (orderedPtrList<Variable *>);

void pushVariableNameInMain  (Variable *);
void pushVariableListInMain  (orderedPtrList<Variable *>);

// ecal related push (2002-02-20)
void pushEcalArgumentLstInElem( SolveElement *,orderedPtrList <Variable *> );
void pushEcalArgumentLstInEcal( SolveElement *,orderedPtrList <Variable *> );
void EcalVarDeclarationInEcal( SolveElement *,orderedPtrList <Variable *> );

// variable allocation
void MainVariableAllocation( Variable *);


// Individual push
void pushFEMVariableInCalled        (Variable *);
void pushFEMVariableInSolve         (Variable *);

