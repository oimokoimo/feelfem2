/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MainSchemeVirtuals.cpp
 *  Date     : 2000/04/07
 *  Modified : 2000/04/07
 *  
 *  Purpose  : Generate main routine for normal main routine
 *  
 */
#include <iostream.h>
#include "MainScheme.hpp"

void MainScheme::MainRoutineInitialize( Main *mainPtr )
 { cout << "This is virtual funcs mainroutineinitialize\n"; }

void MainScheme::MainRoutineHeader( Main *mainPtr )
 { cout << "This is virtual funcs(Mainroutineheader)\n"; }

void MainScheme::MainRoutineParameters( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutineparameters)\n"; }

void MainScheme::MainRoutineVariableDefinitions( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutinevariabledefinitions)\n"; }

void MainScheme::MainRoutineInitializer( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutineinitializer)\n"; }

void MainScheme::MainRoutineReportInitializer( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutinereportinitializer)\n"; }

void MainScheme::MainRoutineDataInput( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutinedatainput)\n"; }

void MainScheme::MainRoutineSchemeStart( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutineschemestart)\n"; }

void MainScheme::MainRoutineInitialValue( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutineinitialvalue)\n"; }

void MainScheme::MainGenerateScheme( Main *mainPtr )
 { cout << "This is virtual funcs(maingeneratescheme)\n"; }

void MainScheme::MainRoutineSchemeFinish( Main *mainPtr )
 { cout << "This is virtual funcs(mainroutineschemefinish)\n"; }

void MainScheme::MainRoutineTerminationSequence( Main *mainPtr )
 { cout << "This is virtual funcs(MainRoutineTerminateionSequence)\n"; }

void MainScheme::MainRoutineTerminate( Main *mainPtr )
 { cout << "This is virtual funcs(MainRoutineTerminate)\n"; }

