/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_output_PM.hpp
 *  Date     : 2002/07/17
 *  Modified : 
 *  
 *  Purpose  : Output related code generation function
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

const char *GetOutputRoutineName(int);              // memory allocated here,never...
const char *GetOutputCoRoutineName(int);

// in main routine
void DoMainScheme_output(Main *, Output *);

// service routines
void pushOutputRoutineName      ( Output *);
void pushOutputCoRoutineName    ( Output *);

// in output routine
void DoOutputRoutineHeader      ( Output *);
void DoOutputParameters         ( Output *);
void DoOutputVariableDefinitions( Output *);
void DoOutputGetGeometryData    ( Output *);
void DoOutputStatement          ( Output *);
void DoOutputReturnSequence     ( Output *);


// for Gid
void DoOutputMeshData           ( Output *);
