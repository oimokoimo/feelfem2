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
#include <iostream>
#include "EcalScheme.hpp"

void EcalScheme::EcalRoutineInitialize  (Solve *,SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalRoutineTerminate   (SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalRoutineHeader      (SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalParameters         (SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalVariableDefinitions(SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalInitializer        (SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalElementMatInitialize(SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalQuadLoopStart     (int, SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalCalcJacobian      (int, SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalSetValAtGaussP    (int, SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalCalcElementMatRHS (int, SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalQuadLoopEnd       (int, SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
void EcalScheme::EcalReturnSequence     (SolveElement *){ std::cerr << "EcalScheme virtual \n"; }
