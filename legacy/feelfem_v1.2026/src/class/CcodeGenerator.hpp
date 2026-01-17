/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : CcodeGenerator.hpp
 *  Date     : 1999/11/11
 *  Modified : 2002/03/12
 *  
 *  Purpose  : Code generation depend on C language
 *  
 */

#ifndef FEM_CLASS_CCODEGENERATOR
#define FEM_CLASS_CCODEGENERATOR

#include <stdio.h>
#include <assert.h>

#define C_TEXT_LENGTH   78
#define C_TEXT_FROM     60
#define C_MAX_TEXT_LEN 120


class CcodeGenerator {

public:
  CcodeGenerator();
  ~CcodeGenerator();

  void CcodeGeneratorSetFP(FILE *);

  void copyright();
  void timestamp();
  void comment();
  void com();
  void COMMENTlong(char *);

  void Csrc(char *);
  void writeSource(const char *);
  void writeSourceRAW(const char *);
  void pushSource(const char *);
  void pushSourceInt(const int );
  void pushSourceDbl(const double);
  void pushSourceChar(char );
  void flushSource(const char *);
  void flushSource(void);

  void CcodeGenerator::wrtDEBUGcode(const char *);





private:

  int  FindNextPOS(char *);

  FILE *fp;
  char srcBUF[BUFSIZ];
  char *srcPtr;
  int pushFlag;
};

#endif
