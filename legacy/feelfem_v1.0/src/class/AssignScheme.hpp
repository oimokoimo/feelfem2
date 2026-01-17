/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : AssignScheme.hpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_ASSIGNSCHEME_CLASS
#define FEM_ASSIGNSCHEME_CLASS

#include "Assign.hpp"

class AssignScheme {
  
public:
  AssignScheme();
  ~AssignScheme();

  void NormalAssignment ( Assign * );           // scalar with no geometry

  void NormalAssignmentEwiseQuad( Assign * );   // ewise quad with no geometry
  void NormalAssignmentEwiseQuadCoroutine(Assign *);

  void NormalAssignmentIntegral( Assign * );   // Integration of region
  void NormalAssignmentIntegralCoroutine(Assign *);

  

  // file management routines
  virtual void AssignRoutineInitialize(Assign *);
  virtual void AssignRoutineTerminate (Assign *);
  
  // Basic subroutine procedures
  virtual void AssignRoutineHeader      (Assign *);

  virtual void AssignParameters         (Assign *);
  virtual void AssignVariableDefinitions(Assign *);

  virtual void AssignGetGeometryData    (Assign *);
  
  virtual void AssignStatement          (Assign *);

  virtual void AssignReturnSequence     (Assign *);


  // Coroutines
  virtual void AssignCoRoutineInitialize (Assign *);
  virtual void AssignCoRoutineReturnSequence   (Assign *);
  virtual void AssignCoRoutineTerminate        (Assign *);

  // EwiseQuad subroutines
  //  //  virtual void AssignRoutineHeaderEwQuad (Assign *);
  virtual void AssignParametersEwQuad    (Assign *);
  virtual void AssignVariableDefinitionsEwQuad (Assign *);
  virtual void AssignInitializeEwQuad    (Assign *); 
  virtual void AssignLoopStartEwQuad     (Assign *);         // ewise quad
  virtual void AssignAssignmentEwQuad    (Assign *);
  virtual void AssignLoopEndEwQuad       (Assign *);

  // EwiseQuad Coroutines
  virtual void AssignCoRoutineHeaderEwQuad      (Assign *);  
  virtual void AssignCoRoutineParametersEwQuad  (Assign *);
  virtual void AssignCoRoutineVariableDefinitionsEwQuad (Assign *);
  virtual void AssignCoRoutineQuadratureSettingsEwQuad  (Assign *);
  virtual void AssignCoRoutineStatementEwQuad           (Assign *); 

  // Integral routines
  virtual void AssignInitializeIntegral  (Assign *);
  virtual void AssignAssignmentIntegral  (Assign *);
  virtual void AssignLoopEndIntegral     (Assign *);

  // Integral Coroutines
  virtual void AssignCoRoutineHeaderIntegral      (Assign *);  
  virtual void AssignCoRoutineVariableDefinitionsIntegral (Assign *);
  virtual void AssignCoRoutineStatementIntegral(Assign *);

};

#endif
