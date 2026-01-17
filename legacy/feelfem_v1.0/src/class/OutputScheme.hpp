/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : OutputScheme.hpp
 *  Date     : 2002/04/16 (BCN)
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_OUTPUTSCHEME_CLASS
#define FEM_OUTPUTSCHEME_CLASS

#include "Output.hpp"

class OutputScheme {
  
public:
  OutputScheme();
  ~OutputScheme();

  void GiDOutput ( Output * );           // GiD output

  // file management routines
  virtual void OutputRoutineInitialize(Output *);
  virtual void OutputRoutineTerminate (Output *);
  
  // Basic subroutine procedures
  virtual void OutputRoutineHeader      (Output *);

  virtual void OutputParameters         (Output *);
  virtual void OutputVariableDefinitions(Output *);

  virtual void OutputStatement          (Output *);

  virtual void OutputReturnSequence     (Output *);


  // Gid Related
  virtual void OutputMeshData           (Output *);

};

#endif
