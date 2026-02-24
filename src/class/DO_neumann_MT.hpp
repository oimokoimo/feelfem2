/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_neumann_MT.hpp
 *  Date     : 2002/04/11
 *  Modified : 
 *  
 *  Purpose  : Matrix related Neumann generator
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

void DoNeumannRoutineHeaderMT(Neumann *);
void DoNeumannArgumentSequenceMT(Neumann *);
void DoNeumannApplyMatrixMT(Neumann *);
  
void doNeumannVariableDefinitionsMT(void);
