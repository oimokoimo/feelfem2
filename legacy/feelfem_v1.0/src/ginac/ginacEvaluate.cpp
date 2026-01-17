/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ginacEvaluate.cpp
 *  Date     : 2001/03/15
 *  Modified : 2002/04/01
 *  
 *  Purpose  : no string here, (STL string is used in ginac)
 *  
 */

#include "feeldef.hpp"
#include "feelfuncs.hpp"  //abortExit

#include <assert.h>
#include <stdio.h>       // for BUFSIZ
#include <strstream.h>
#include <ginac/ginac.h>

using namespace GiNaC;


static symbol a01("a01");
static symbol a02("a02");
static symbol a03("a03");
static symbol a04("a04");
static symbol a05("a05");
static symbol a06("a06");
static symbol a07("a07");
static symbol a08("a08");
static symbol a09("a09");
static symbol a10("a10");
static symbol a11("a11");
static symbol a12("a12");

static symbol x("x");
static symbol y("y");
static symbol z("z");

static ex e;

void setExprGinacEvaluate(char *buf)
{

  ex f(buf,lst(x,y,z,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12 ));
  e = f;

  //  e = ex (buf,lst(x,y,z,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12 ));
  return;
}

void subsExprGinacEvaluate(int no, char *expr )
{
  ex val(expr,lst(x,y,z,a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,a11,a12));

  switch(no) {
  case 0:
    e = e.subs(a01 == val);
    break;

  case 1:
    e = e.subs(a02 == val);
    break;

  case 2:
    e = e.subs(a03 == val);
    break;

  case 3:
    e = e.subs(a04 == val);
    break;

  case 4:
    e = e.subs(a05 == val);
    break;

  case 5:
    e = e.subs(a06 == val);
    break;

  case 6:
    e = e.subs(a07 == val);
    break;

  case 7:
    e = e.subs(a08 == val);
    break;

  case 8:
    e = e.subs(a09 == val);
    break;

  case 9:
    e = e.subs(a10 == val);
    break;

  case 10:
    e = e.subs(a11 == val);
    break;

  case 11:
    e = e.subs(a12 == val);
    break;

  default:
    abortExit("Illegal case number(void subsExprGinacEvaluate(char * subs))");
  }
}


void subsExprGinacEvaluate(int no,double val)
{
  if(no >= MAX_GINAC_VARIABLES) {
    abortExit("Too many variables in subsExprGinacEvaluate");
  }

  switch(no) {
  case 0:
    e = e.subs(a01 == val);
    break;

  case 1:
    e = e.subs(a02 == val);
    break;

  case 2:
    e = e.subs(a03 == val);
    break;

  case 3:
    e = e.subs(a04 == val);
    break;

  case 4:
    e = e.subs(a05 == val);
    break;

  case 5:
    e = e.subs(a06 == val);
    break;

  case 6:
    e = e.subs(a07 == val);
    break;

  case 7:
    e = e.subs(a08 == val);
    break;

  case 8:
    e = e.subs(a09 == val);
    break;

  case 9:
    e = e.subs(a10 == val);
    break;

  case 10:
    e = e.subs(a11 == val);
    break;

  case 11:
    e = e.subs(a12 == val);
    break;

  default:
    abortExit("Illegal case number(void subsExprGinacEvaluate)");
  }

  return;
}

int isExprGinacNumeric(void)
{
  //  return(is_ex_of_type(e,numeric));
  return(is_a<numeric>(e));
}

double getDoubleExprGinac(void)
{
  numeric num;
  double ret;

  //  cerr << "getDoubleExprGinac  e=" << e << endl;

  //  if(!is_ex_of_type(e,numeric)) { from GiNaC 0.9.1 modified
  if(!is_a<numeric>(e)) {
    abortExit("in getDoubleExprGinac not NUMERIC");
  }
  //  num = ex_to_numeric(e);   from GiNaC 0.9.1 modified
  num = ex_to<numeric>(e);

  ret = num.to_double();

  //  cerr << "ret = " << ret << endl;

  return(ret);
}

void setGinacExprToCharBuf(char *buf,int bufsiz)
{
  int stringLength(const char *);
  ostrstream ostr(buf,bufsiz);

  *buf = '\0';
  ostr << e << '\0';

  assert(stringLength(buf) < bufsiz-1);
  
  return;
}
