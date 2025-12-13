/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : OutputGeneratorTemplate.hpp
 *  Date     : 2002/07/17
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_OUTPUTGENERATORTEMPLATE
#define FEM_CLASS_OUTPUTGENERATORTEMPLATE

#include "OutputScheme.hpp"
#include "Output.hpp"

template <class PgMODEL> class OutputGeneratorTemplate
  : public PgMODEL, public OutputScheme {

public:
   OutputGeneratorTemplate() {;}
  ~OutputGeneratorTemplate() {;}

  void OutputRoutineInitialize   (Output *);
  void OutputRoutineTerminate    (Output *);

  void OutputRoutineHeader       (Output *);
  void OutputRoutineParameters   (Output *);

  void OutputVariableDefinitions (Output *);
  void OutputParameters          (Output *);

  void OutputGetGeometryData     (Output *);
  void OutputStatement           (Output *);

  void OutputReturnSequence      (Output *);

  // Gid
  void OutputMeshData            (Output *);

private:
  int   outputNo;
  char *routineName;
  char *sourceName;
};


template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputRoutineInitialize(Output *outputPtr)
{
  outputNo    = outputPtr->GetOutputNo();
  routineName = GetOutputRoutineName( outputNo );
  sourceName  = GetSourceName( routineName );
  OpenSource(sourceName,LINKLEVEL_OUTPUT);
  
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputRoutineTerminate(Output *outputPtr)
{
  CloseSource();
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputRoutineHeader (Output *outputPtr)
{
  DoOutputRoutineHeader( outputPtr );
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputParameters (Output *outputPtr)
{
  DoOutputParameters( outputPtr );
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputVariableDefinitions (Output *outputPtr)
{
  DoOutputVariableDefinitions( outputPtr );
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputGetGeometryData (Output *outputPtr)
{
  DoOutputGetGeometryData( outputPtr );
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputStatement (Output *outputPtr)
{
  DoOutputStatement( outputPtr );
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputReturnSequence (Output *outputPtr)
{
  DoOutputReturnSequence( outputPtr );
  return;
}

template <class PgMODEL> void OutputGeneratorTemplate <PgMODEL>::
OutputMeshData (Output *outputPtr)
{
  DoOutputMeshData( outputPtr );
  return;
}

#endif
