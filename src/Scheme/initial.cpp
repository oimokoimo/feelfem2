/*
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes: Initialization , 
 *
 *
 */


#include "Solve.hpp"
#include "Source.hpp"
#include "SolveScheme.hpp"
#include "ElemScheme.hpp"
#include "EcalScheme.hpp"

// Solve class
int Solve::solves       = 0;

// SolveScheme class
int SolveScheme::solveSchemes = 0;

// ElemScheme class
int ElemScheme::elemSchemes = 0;

int EcalScheme::ecalSchemes = 0;


