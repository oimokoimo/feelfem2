/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MainScheme.hpp
 *  Date     : 2000/04/07
 *  Modified : 2000/04/07
 *  
 *  Purpose  : Main routine generator
 *  
 */

#ifndef FEM_CLASS_MAINSCHEME
#define FEM_CLASS_MAINSCHEME

class Main;

class MainScheme {
public:
  MainScheme();
  ~MainScheme();

  // Scheme Libraries
  void NormalMainProgram( Main *);


  // File management routines    
  virtual void MainRoutineInitialize(Main *);
  virtual void MainRoutineTerminate(Main *);

  virtual void MainRoutineHeader(Main *);
  virtual void MainRoutineParameters(Main *);
  virtual void MainRoutineVariableDefinitions(Main *);

  // Initializers 
  virtual void MainRoutineInitializer(Main *);
  virtual void MainRoutineReportInitializer(Main *);

  virtual void MainRoutineDataInput  (Main *);
  virtual void MainRoutineSchemeStart(Main *);

  virtual void MainRoutineInitialValue(Main *);

  virtual void MainGenerateScheme (Main *);


  virtual void MainRoutineSchemeFinish(Main *);
  virtual void MainRoutineTerminationSequence(Main *);

private:

  
};
    
#endif

