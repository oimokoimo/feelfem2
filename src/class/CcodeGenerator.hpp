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

#ifndef FEM_CLASS_CCODEGENERATOR
#define FEM_CLASS_CCODEGENERATOR

#include <iostream>
#include <cassert>

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
  void COMMENTlong(const char *);

  void Csrc(const char *);
  void writeSource(const char *);
  void writeSourceRAW(const char *);
  void pushSource(const char *);
  void pushSourceInt(const int );
  void pushSourceDbl(const double);
  void pushSourceChar(char );
  void flushSource(const char *);
  void flushSource(void);

  void wrtDEBUGcode(const char *);





private:

  int  FindNextPOS(char *);

  FILE *fp;
  char srcBUF[BUFSIZ];
  char *srcPtr;
  int pushFlag;
};

#endif
