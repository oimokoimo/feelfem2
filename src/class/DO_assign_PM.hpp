/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DO_assign_PM.hpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  : Assignment related code generation function
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


char *GetAssignRoutineName(int);              // memory allocated here,never...
char *GetAssignCoRoutineName(int);

// in main routine
void DoMainScheme_assign(Main *, Assign *);

// service routines
void pushAssignRoutineName      ( Assign *);
void pushAssignCoRoutineName    ( Assign *);

// in assign routine
void DoAssignRoutineHeader      ( Assign *);
void DoAssignParameters         ( Assign *);
void DoAssignVariableDefinitions( Assign *);
void DoAssignGetGeometryData    ( Assign *);
void DoAssignStatement          ( Assign *);
void DoAssignReturnSequence     ( Assign *);

// General CoRoutine
void DoAssignCoRoutineReturnSequence   ( Assign *);


// Ewise-Quad let main
//void DoAssignRoutineHeaderEwQuad ( Assign *);
void DoAssignParametersEwQuad    ( Assign *);
void DoAssignVariableDefinitionsEwQuad ( Assign *);
void DoAssignInitializeEwQuad     ( Assign *);
void DoAssignLoopStartEwQuad     ( Assign *);
void DoAssignAssignmentEwQuad    ( Assign *);
void DoAssignLoopEndEwQuad       ( Assign *);

// Ewise-Quad colet
void DoAssignCoRoutineHeaderEwQuad( Assign *); 
void DoAssignCoRoutineParametersEwQuad  ( Assign *);
void DoAssignCoRoutineVariableDefinitionsEwQuad ( Assign *);
void DoAssignCoRoutineQuadratureSettingsEwQuad  ( Assign *);
void DoAssignCoRoutineStatementEwQuad( Assign *);

// Integral
void DoAssignInitializeIntegral(Assign *);
void DoAssignAssignmentIntegral(Assign *);
void DoAssignLoopEndIntegral   (Assign *);

// Integral colet
void DoAssignCoRoutineHeaderIntegral( Assign *); 
void DoAssignCoRoutineVariableDefinitionsIntegral( Assign *);
void DoAssignCoRoutineStatementIntegral(Assign *);
void doAssignIntegral(Assign *);

// DoAssignStatement family
void doAssignScalar(Assign *asPtr);
void doAssignFEMnode(Assign *asPtr);
void doAssignEWISEmaterial(Assign *asPtr);

void doAssignEwquadCalcInterpolation(Element *,int);
void doAssignEwquadJacobian(Assign *);
void doAssignEwquadRQconv(Assign *);
void doAssignEwiseQuad(Assign *);
void doAssignEwquadEvalAtGaussP(Assign *);

void pushEwquadJacobiSub(int,int *,const char *,const char *,const char *);
void pushEwquadDiffSub_1st(Element *,int,int,int);
