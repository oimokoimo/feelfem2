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
 */

char *GetOutputRoutineName(int);              // memory allocated here,never...
char *GetOutputCoRoutineName(int);

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
