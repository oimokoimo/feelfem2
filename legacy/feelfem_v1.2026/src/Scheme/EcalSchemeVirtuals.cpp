/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : EcalSchemeVirtuals.cpp
 *  Date     : 2002/02/20
 *  Modified : 
 *  
 *  Purpose  : 
 *  
 */
#include <iostream.h>
#include "EcalScheme.hpp"

void EcalScheme::EcalRoutineInitialize  (Solve *,SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalRoutineTerminate   (SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalRoutineHeader      (SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalParameters         (SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalVariableDefinitions(SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalInitializer        (SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalElementMatInitialize(SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalQuadLoopStart     (int, SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalCalcJacobian      (int, SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalSetValAtGaussP    (int, SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalCalcElementMatRHS (int, SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalQuadLoopEnd       (int, SolveElement *){ cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalReturnSequence     (SolveElement *){ cerr << "EcalScheme virtual \n"; }
