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
#ifndef FEM_SYNTAX_UNIT
#define FEM_SYNTAX_UNIT

#include <iostream>

#include "../../class/feelfuncs.hpp"
#include "../../class/feeldef.hpp"
#include "../../class/list.hpp"
#include "../../class/string.hpp"

class Expression;
class Variable;
class Main;

class SNunit {
protected:
  int         classType;   //
  const char* className;   // debugging information
  int         lineNumber;  // line number
  int         fileNumber;  // Source file No.

public:
  SNunit(const char* name, int type)
    : classType(type), className(name), lineNumber(0)
  {
    fileNumber = currentSourceFileNo(); // in check/SystemErrorFilename.cpp
  }

  virtual ~SNunit() ;

  virtual void print(std::ostream&) const;

  // for expression
  virtual int howManyNotDefinedVariable(int, void*, void*) {
    std::cerr << "THIS IS VIRTUAL howManyNotDefinedVariable in SNunit\n";
    std::cerr << "NAME = " << className << std::endl;
    return 1;
  }

  virtual int howManyNotDefinedFunction(int, void*, void*) {
    std::cerr << "THIS IS VIRTUAL howManyNotDefinedFunction in SNunit\n";
    std::cerr << "NAME = " << className << std::endl;
    return 1;
  }

  virtual int howManyNotAssignedVariable(int, void*, void*) {
    std::cerr << "THIS IS VIRTUAL howManyNotAssignedVariable in SNunit\n";
    std::cerr << "NAME = " << className << std::endl;
    return 1;
  }

  virtual void exprPrint(char*, int, void*, void*) {
    std::cerr << "THIS IS VIRTUAL exprPrint in SNunit\n";
    std::cerr << "CLASS= " << className << std::endl;
  }

  virtual int isAlreadyUsedName(list<string>&) {
    std::cerr << "THIS IS VIRTUAL isAlreadyUsedName(list <string> &strLst)\n";
    std::cerr << "CLASS= " << className << std::endl;
    return 1;
  }

  // Parsing error message related function
  virtual void errWrtNameNO(std::ostream&, int) {
    std::cerr << "THIS IS VIRTUAL errWrtName in SNunit\n";
    std::cerr << "CLASS= " << className << std::endl;
  }
  virtual void errWrtName(std::ostream&) {
    std::cerr << "THIS IS VIRTUAL errWrtName in SNunit\n";
    std::cerr << "CLASS= " << className << std::endl;
  }

  virtual void errWrtData(std::ostream&) {
    std::cerr << "THIS IS VIRTUAL errWrtData in SNunit\n";
    std::cerr << "CLASS= " << className << std::endl;
  }

  void wrtLineNumber(std::ostream& ost) { ost << lineNumber; }

  void wrtSourceFilename(std::ostream& ost) {
    wrtErrSourceFilename(ost, fileNumber);
  }

  void LineNumber(int ln) { lineNumber = ln; }

  void debugwrt() { std::cout << "UNIT : " << className << "\n"; }

  int GetType() const { return classType; }

  virtual Variable* CreateVariablePtr() {
    std::cerr << "This is virtual Variable *CreateVariablePtr(void) in SNunit\n";
    std::cerr << "CLASS= " << className << std::endl;
    return nullptr;
  }

  // check routines
  virtual int Check() {
    std::cerr << "This is virtual Check function in SNunit.\n";
    return 1;
  }

  // generating corresponding class
  virtual int InfoGenerate() {
    std::cerr << "This is virtual InfoGenerate funciton in SNunit.\n";
    return 1;
  }

  virtual void CodeGenerate() {
    std::cerr << "This is virtual CodeGenerate funciton in SNunit.\n";
  }

  virtual void CodeGenerateMain(void*, Main*) {
    std::cerr << "This is virtual CodeGenerateMain funciton in SNunit.\n";
    std::cerr << "Be careful argument is (void *,Main *) !!!\n";
  }
};

#endif

