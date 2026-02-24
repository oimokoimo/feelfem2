/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Fortran90Generator.hpp
 *  Date     : 2000/10/16
 *  Modified : 2000/
 *  
 *  Purpose  : Fortran 90 code generator class
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
 *
 */

#ifndef FEM_CLASS_FORTRAN90GENERATOR
#define FEM_CLASS_FORTRAN90GENERATOR


#define F90_TEXT_LENGTH   78
#define F90_TEXT_FROM     60
#define F90_MAX_TEXT_LEN 120

class Fortran90Generator {

public:

  Fortran90Generator();
  ~Fortran90Generator();

  // File pointer setting
  void Fortran90GeneratorSetFP(FILE *);

  void writeSource   ( const char *);
  void writeSourceRAW( const char *);
  void pushSource    ( const char *);
  void pushSourceInt ( const int   );
  void pushSourceDbl ( const double);
  void pushSourceHAT ( const char *);   // change ^ -> **
  void pushSourceChar( char );
  void flushSource   ( const char *);
  void flushSource   ( void        );

  void wrtDEBUGcode  ( const char *);  // write debug information
  
  // source starters
  void copyright();
  void timestamp();
  void fortImplicit();

  void comment();    // line  ----------
  void com();        // small *
  void COMMENTlong(const char *);

  // Memory allocation   allocate insentric function
  void mallocF90(const char *);
  void mallocF90check(void);


  // Common Fortran90 modules
  void F90_MPI_Initialize(void);
  void F90_MPI_Finalize(void);
  void F90_MPI_Abort(void);

protected:
  int  spaceDim;


private:

  int  FindNextPOS(char *);   // next delimitor

  FILE *fp;
  char srcBUF[BUFSIZ];
  char *srcPtr;
  int  pushFlag;        // pointer to srcBUF

};

#endif
