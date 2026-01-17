/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : AssignGeneratorTemplate.hpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_ASSIGNGENERATORTMPLATE
#define FEM_CLASS_ASSIGNGENERATORTMPLATE

#include "AssignScheme.hpp"
#include "Assign.hpp"

template <class PgMODEL> class AssignGeneratorTemplate
  : public PgMODEL, public AssignScheme {

public:
  AssignGeneratorTemplate()  {;}  // do nothing in template generator class
  ~AssignGeneratorTemplate() {;}

  void AssignRoutineInitialize   (Assign *);
  void AssignRoutineTerminate    (Assign *);

  void AssignRoutineHeader       (Assign *);
  void AssignParameters          (Assign *);

  void AssignVariableDefinitions (Assign *);

  void AssignGetGeometryData     (Assign *);
  void AssignStatement           (Assign *);

  void AssignReturnSequence      (Assign *);


  // Coroutines
  void AssignCoRoutineInitialize (Assign *);
  void AssignCoRoutineReturnSequence   (Assign *);
  void AssignCoRoutineTerminate        (Assign *);

  // EwiseQuad subroutines
  //  void AssignRoutineHeaderEwQuad (Assign *);
  void AssignParametersEwQuad    (Assign *);
  void AssignVariableDefinitionsEwQuad (Assign *);
  void AssignInitializeEwQuad    (Assign *);
  void AssignLoopStartEwQuad     (Assign *);         // ewise quad
  void AssignAssignmentEwQuad    (Assign *);
  void AssignLoopEndEwQuad       (Assign *);

  // EwiseQuad Coroutines
  void AssignCoRoutineHeaderEwQuad      (Assign *);  
  void AssignCoRoutineParametersEwQuad  (Assign *);
  void AssignCoRoutineVariableDefinitionsEwQuad (Assign *);
  void AssignCoRoutineQuadratureSettingsEwQuad  (Assign *);
  void AssignCoRoutineStatementEwQuad           (Assign *); 

  // Integral
  void AssignInitializeIntegral(Assign *);
  void AssignAssignmentIntegral(Assign *);
  void AssignLoopEndIntegral   (Assign *);

  // Integral Coroutines
  void AssignCoRoutineHeaderIntegral              (Assign *);  
  void AssignCoRoutineVariableDefinitionsIntegral (Assign *);
  void AssignCoRoutineStatementIntegral           (Assign *); 


private:
  int   assignNo;
  char *routineName;
  char *sourceName;

};

/////////////////////////////////////////////
template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignRoutineInitialize(Assign *asPtr)
{
  assignNo    = asPtr->GetAssignNo();
  routineName = GetAssignRoutineName( assignNo );
  sourceName  = GetSourceName( routineName );
  OpenSource(sourceName,LINKLEVEL_ASSIGN);
  
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignRoutineTerminate(Assign *asPtr)
{
  CloseSource();
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignRoutineHeader (Assign *asPtr)
{
  DoAssignRoutineHeader( asPtr );
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignParameters (Assign *asPtr)
{
  DoAssignParameters( asPtr );
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignVariableDefinitions (Assign *asPtr)
{
  DoAssignVariableDefinitions( asPtr );
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignGetGeometryData (Assign *asPtr)
{
  DoAssignGetGeometryData( asPtr );
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignStatement (Assign *asPtr)
{
  DoAssignStatement( asPtr );
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignReturnSequence (Assign *asPtr)
{
  DoAssignReturnSequence( asPtr );
  return;
}

// Coroutines
template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineInitialize (Assign *asPtr)
{
  assignNo    = asPtr->GetAssignNo();
  routineName = GetAssignCoRoutineName( assignNo );
  sourceName  = GetSourceName( routineName );
  OpenSource(sourceName,LINKLEVEL_COASSIGN);

  return;
}


template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineReturnSequence   (Assign *asPtr)
{
  DoAssignCoRoutineReturnSequence   (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineTerminate        (Assign *asPtr)
{
  CloseSource();
  return;
}

// EwiseQuad subroutines
//template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
//AssignRoutineHeaderEwQuad (Assign *asPtr) 
//{
//  DoAssignRoutineHeaderEwQuad (asPtr);
//  return;
//}


template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignParametersEwQuad    (Assign *asPtr)
{
  DoAssignParametersEwQuad    (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignVariableDefinitionsEwQuad (Assign *asPtr)
{
  DoAssignVariableDefinitionsEwQuad (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignInitializeEwQuad     (Assign *asPtr)
{
  DoAssignInitializeEwQuad     (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignLoopStartEwQuad     (Assign *asPtr)
{
  DoAssignLoopStartEwQuad     (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignAssignmentEwQuad    (Assign *asPtr) 
{
  DoAssignAssignmentEwQuad    (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignLoopEndEwQuad       (Assign *asPtr)
{
  DoAssignLoopEndEwQuad       (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignLoopEndIntegral   (Assign *asPtr)
{
  DoAssignLoopEndIntegral   (asPtr);
  return;
}


  // EwiseQuad Coroutines
template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineHeaderEwQuad      (Assign *asPtr)
{
  DoAssignCoRoutineHeaderEwQuad(asPtr); 
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineParametersEwQuad  (Assign *asPtr)
{
  DoAssignCoRoutineParametersEwQuad  (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineVariableDefinitionsEwQuad (Assign *asPtr)
{
  DoAssignCoRoutineVariableDefinitionsEwQuad (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineQuadratureSettingsEwQuad  (Assign *asPtr)
{
  DoAssignCoRoutineQuadratureSettingsEwQuad  (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineStatementEwQuad           (Assign *asPtr)
{
  DoAssignCoRoutineStatementEwQuad(asPtr);
  return;
}

// integral routines
template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignInitializeIntegral     (Assign *asPtr)
{
  DoAssignInitializeIntegral (asPtr);
  return;
}

// integral routines
template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignAssignmentIntegral     (Assign *asPtr)
{
  DoAssignAssignmentIntegral (asPtr);
  return;
}

// integral coroutines
template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineHeaderIntegral      (Assign *asPtr)
{
  DoAssignCoRoutineHeaderIntegral(asPtr); 
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineVariableDefinitionsIntegral (Assign *asPtr)
{
  DoAssignCoRoutineVariableDefinitionsIntegral (asPtr);
  return;
}

template <class PgMODEL> void AssignGeneratorTemplate <PgMODEL>::
AssignCoRoutineStatementIntegral           (Assign *asPtr)
{
  DoAssignCoRoutineStatementIntegral(asPtr);
  return;
}

#endif
