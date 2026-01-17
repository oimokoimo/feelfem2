/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : Fortran77Generator
 *  Date     : 1999/11/11
 *  Modified : 1999/11/12 Not public Source
 *  
 *  Purpose  : Fortran code generator class
 *  
 */

#ifndef FEM_CLASS_FORTRAN77GENERATOR
#define FEM_CLASS_FORTRAN77GENERATOR

#include <stdio.h>

class Fortran77Generator {

public:

  Fortran77Generator();
  ~Fortran77Generator();

  // File pointer setting
  void Fortran77GeneratorSetFP(FILE *);

  void writeSource   ( const char *);
  void writeSourceRAW( const char *);
  void pushSource    ( const char *);
  void pushSourceInt ( const int   );
  void flushSource   ( void        );

  void wrtDEBUGcode  ( const char *);   // write debug information

  // source starters
  void copyright();
  void timestamp();
  void fortImplicit();


  void comment();    // line  ----------
  void com();        // small *
  void COMMENTlong(char *);

  // Memory allocation   f_alloc family
  // 
  void mallocF77     (char *varname, char *comment, char *size, char *type);
  void mallocF77imode(char *varname, char *comment, char *size, char *type);
  void mallocF77check(void);



  // Common Fortran 77 modules
  void F77_MPI_Initialize(void);
  void F77_MPI_Finalize(void);
  void F77_MPI_Abort(void);



private:
  FILE *fp;
  char srcBUF[BUFSIZ];
  char *srcPtr;
  int  pushFlag;        // pointer to srcBUF

};

#endif


