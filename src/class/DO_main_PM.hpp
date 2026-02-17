/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_main.hpp
 *  Date     : 2001/11/29
 *  Modified : 
 *  
 *  Purpose  : DoMainRoutine family
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

// Main common components
void DoMainRoutineHeaderPM(Main *);
void DoMainRoutineArgumentSequencePM(Main *);
void DoMainRoutineParameters(Main *);
void DoMainRoutineVariableDefinitions(Main *);
void DoMainRoutineInitializer(Main *);
void DoMainRoutineReportInitializer(Main *);
void DoMainRoutineDataInput(Main *);
void DoMainRoutineSchemeStart(Main *);
void DoMainRoutineInitialValue(Main *);
void DoMainRoutineSchemeFinish(Main *);
void DoMainRoutineTerminationSequence(Main *);

void doMainVariableInitialValue( Variable *); // scalar var with initial value


// main coroutine control
void GenerateMainCoRoutine(Main *);

