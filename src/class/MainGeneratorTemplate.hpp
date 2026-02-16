/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MainGeneratorTemplate.hpp
 *  Date     : 2000/04/10
 *  Modified : 2000/04/10
 *  Modified : 2001/01/31  ADD LINKLEVEL_MAIN
 *  
 *  Purpose  : Generate Main routine
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

#ifndef FEM_CLASS_MAINGENERATORTEMPLATE
#define FEM_CLASS_MAINGENERATORTEMPLATE

#include "feeldef.hpp"
#include "MainScheme.hpp"
#include "feelfuncs.hpp"
#include "list.hpp"
#include "parseExternals.hpp"
#include "../parser/Syntax/SNunit.hpp"

template <class ProgramMODEL> class MainGeneratorTemplate
  : public ProgramMODEL, public MainScheme {

public:
   MainGeneratorTemplate() {;}
  ~MainGeneratorTemplate() {;}

  void MainRoutineInitialize  (Main *);

  void MainRoutineHeader(Main *);
  void MainRoutineParameters(Main *);
  void MainRoutineVariableDefinitions(Main *);

  // Initializers 
  void MainRoutineInitializer(Main *);
  void MainRoutineReportInitializer(Main *);

  void MainRoutineDataInput(Main *);
  void MainRoutineSchemeStart(Main *);
  void MainRoutineInitialValue(Main *);

  void MainGenerateScheme( Main *);

  void MainRoutineSchemeFinish(Main *);
 
  void MainRoutineTerminationSequence(Main *);
   
  void MainRoutineTerminate(Main *);

  //  virtual void GenerateMainCoRoutine(Main *);
  using ProgramMODEL::GetMainSourceName;
  using ProgramMODEL::OpenSource;
  using ProgramMODEL::CloseSource;
  using ProgramMODEL::GenerateMainCoRoutine;

  using ProgramMODEL::DoMainRoutineHeaderPM;
  using ProgramMODEL::DoMainRoutineParameters;
  using ProgramMODEL::DoMainRoutineVariableDefinitions;
  using ProgramMODEL::DoMainRoutineInitializer;
  using ProgramMODEL::DoMainRoutineReportInitializer;
  using ProgramMODEL::DoMainRoutineDataInput;
  using ProgramMODEL::DoMainRoutineSchemeStart;
  using ProgramMODEL::DoMainRoutineInitialValue;
  using ProgramMODEL::DoMainRoutineTerminationSequence;
  using ProgramMODEL::DoMainRoutineSchemeFinish;


private:
  int   solveNo;
  int   elemNo;
  char *routineName;
  char *sourceName;
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineInitialize (Main *mainPtr )
{
  sourceName  = GetMainSourceName();
  OpenSource(sourceName,LINKLEVEL_MAIN);
  
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineTerminate (Main *mainPtr)
{
  CloseSource();

  // coroutines
  GenerateMainCoRoutine( mainPtr );
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineHeader (Main *mainPtr)
{
  DoMainRoutineHeaderPM(mainPtr);        // PM model

  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineParameters(Main *mainPtr)
{
  DoMainRoutineParameters(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineVariableDefinitions(Main *mainPtr)
{
  DoMainRoutineVariableDefinitions(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineInitializer(Main *mainPtr)
{
  DoMainRoutineInitializer(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineReportInitializer(Main *mainPtr)
{
  DoMainRoutineReportInitializer(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineDataInput(Main *mainPtr)
{
  DoMainRoutineDataInput(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineSchemeStart(Main *mainPtr)
{
  DoMainRoutineSchemeStart(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineInitialValue(Main *mainPtr)
{
  DoMainRoutineInitialValue(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineTerminationSequence(Main *mainPtr)
{
  DoMainRoutineTerminationSequence(mainPtr);
  return;
}

template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainRoutineSchemeFinish(Main *mainPtr)
{
  DoMainRoutineSchemeFinish(mainPtr);
  return;
}



//
template <class ProgramMODEL> void MainGeneratorTemplate<ProgramMODEL>::
MainGenerateScheme(Main *mainPtr)
{
  listIterator <void *>itrScheme(parseSchemeLst);
  for(itrScheme.init(); !itrScheme; ++itrScheme) {
    SNunit *snPtr = (SNunit *)itrScheme();
    void   *vPtr  = this;
    snPtr->CodeGenerateMain(vPtr,mainPtr);
  }

  return;
}

//template <class ProgramMODEL>void MainGeneratorTemplate<ProgramMODEL>::
//GenerateMainCoRoutine(Main *mainPtr)
//{
//  cerr << "OOIMOKOIMO\n";
//
//  dbgGeneratorReport("void MainGeneratorTemplate::GenerateMainCoRoutine()",
//  	             "virtual function in MainGeneratorTemplate.hpp called");
//  return;
//}


#endif
