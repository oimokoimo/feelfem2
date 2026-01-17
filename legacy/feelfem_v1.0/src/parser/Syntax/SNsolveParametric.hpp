/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : SNsolveParametric.hpp
 *  Date     : 2002/02/19
 *  Modified : 
 *  
 *  Purpose  : solveParametric class for parser  (reference aumc)
 *  
 */

#ifndef FEM_SYNTAX_SOLVEPARAMETRIC
#define FEM_SYNTAX_SOLVEPARAMETRIC

#include "SNunit.hpp"
#include "../../class/string.hpp"

class SNsolveParametric : public SNunit {
public:
  SNsolveParametric( char *nm ) :
    SNunit("solveParametric",SN_SOLVEPARAMETRIC) 
  { parametricName = nm; }

  void print(ostream & ost) { ost << "solveParametric="
                                  <<  parametricName
				  << "\n";            }

  const string getName(void) {
    return( parametricName );
  }

  // for error message
  void errWrtName(ostream &ost ) {
    ost << parametricName;
    return;
  }


private:
  string parametricName;

};


#endif
