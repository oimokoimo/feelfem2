/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNunit.hpp
 *  Date     : 2001/02/14
 *  Modified : 
 *  
 *  Purpose  : Syntax unit class (mostly for debugging use)
 *  
 */

#ifndef FEM_SYNTAX_UNIT
#define FEM_SYNTAX_UNIT

#include <stream.h>

#include "../../class/feelfuncs.hpp"
#include "../../class/feeldef.hpp"
#include "../../class/list.hpp"
#include "../../class/string.hpp"

class Expression;
class Variable;
class Main;


class SNunit {
protected:
  int   classType;  //    
  char *className;  // debugging information
  int   lineNumber; // line number
  int   fileNumber; // Source file No.

  

public:
  SNunit(char *name,int type) 
    : className( name ), classType( type ) , lineNumber( 0 ) {
    
    fileNumber = currentSourceFileNo();    // in check/SystemErrorFilename.cpp
  }

  //  virtual void print(ostream&) = 0;

  virtual void print(ostream &);

  // for expression
  virtual int  howManyNotDefinedVariable(int flag,void *ptr1,void *ptr2) {
    cerr << "THIS IS VIRTUAL howManyNotDefinedVariable in SNunit\n";
    cerr << "NAME = " << className << endl;
    return(1);
  }

  virtual int  howManyNotDefinedFunction(int flag,void *ptr1,void *ptr2) {
    cerr << "THIS IS VIRTUAL howManyNotDefinedFunction in SNunit\n";
    cerr << "NAME = " << className << endl;
    return(1);
  }

  virtual int  howManyNotAssignedVariable(int flag,void *ptr1,void *ptr2) {
    cerr << "THIS IS VIRTUAL howManyNotAssignedVariable in SNunit\n";
    cerr << "NAME = " << className << endl;
    return(1);
  }


  virtual void exprPrint(char *buf ,int flag,void *ptr1,void *ptr2) {
    cerr << "THIS IS VIRTUAL exprPrint in SNunit\n";
    cerr << "CLASS= " << className << endl;
  }

  virtual int isAlreadyUsedName( list <string> &strLst) {
    cerr << "THIS IS VIRTUAL isAlreadyUsedName(list <string> &strLst)\n";
    cerr << "CLASS= " << className << endl;
    return(1);
  }

  // Parsing error message related function
  virtual void errWrtNameNO(ostream &,int) { 
    cerr << "THIS IS VIRTUAL errWrtName in SNunit\n";
    cerr << "CLASS= " << className << endl;
  }
  virtual void errWrtName(ostream &) { 
    cerr << "THIS IS VIRTUAL errWrtName in SNunit\n";
    cerr << "CLASS= " << className << endl;
  }

  virtual void errWrtData(ostream &) { 
    cerr << "THIS IS VIRTUAL errWrtData in SNunit\n";
    cerr << "CLASS= " << className << endl;
  }

  void wrtLineNumber(ostream &ost) {
    ost << lineNumber;
    return;
  }

  void wrtSourceFilename(ostream &ost) {
    wrtErrSourceFilename( ost, fileNumber);
    return;
  }

  
  void LineNumber(int ln) { lineNumber = ln; }

  void debugwrt(void) { cout << "UNIT : "<<className <<"\n"; }

  int GetType(void) {
    return classType;
  }

  virtual Variable *CreateVariablePtr(void)
  {
    cerr << "This is virtual Variable *CreateVariablePtr(void) in SNunit\n";
    cerr << "CLASS= " << className << endl;
    return(0);
  }

  // check routines
  virtual int Check(void) {
    cerr << "This is virtual Check function in SNunit.\n";
    return(1);
  }

  // generating corresponding class
  virtual int InfoGenerate(void) {
    cerr << "This is virtual InfoGenerate funciton in SNunit.\n";
    return(1);
  }


  virtual void CodeGenerate(void) {
    cerr << "This is virtual CodeGenerate funciton in SNunit.\n";
    return;
  }

  virtual void CodeGenerateMain(void *,Main *) {
    cerr << "This is virtual CodeGenerateMain funciton in SNunit.\n";
    cerr << "Be careful argument is (void *,Main *) !!!\n";

    return;
  }

};

#endif
