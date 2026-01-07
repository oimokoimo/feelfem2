/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MainNormalMainProgram.cpp
 *  Date     : 2000/04/07
 *  Modified : 2000/04/07
 *  
 *  Purpose  : Generate main routine for normal main routine
 *  
 */

#include "MainScheme.hpp"

void MainScheme::NormalMainProgram( Main *mainPtr )
{
  MainRoutineInitialize( mainPtr );

  MainRoutineHeader( mainPtr );
  MainRoutineParameters( mainPtr );
  MainRoutineVariableDefinitions( mainPtr );

  // Initializers 
  MainRoutineInitializer( mainPtr );
  MainRoutineReportInitializer( mainPtr );

  MainRoutineDataInput( mainPtr );

  MainRoutineSchemeStart( mainPtr );   // allocate ewise vars, etc.
  
  MainRoutineInitialValue( mainPtr );  // scalar initial values

  MainGenerateScheme( mainPtr );

  MainRoutineSchemeFinish( mainPtr );
  MainRoutineTerminationSequence( mainPtr );

  // Termination of generating
  MainRoutineTerminate( mainPtr );

  return;
}
