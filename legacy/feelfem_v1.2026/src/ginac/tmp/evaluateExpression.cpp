/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : evaluateExpression.cpp
 *  Date     : 2001/03/12
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */


//#include "Expression.hpp"
#include <ginac/ginac.h>

using namespace GiNaC;

void evaluateBufGinac( char *buf)
{
  symbol a01("a01");
  symbol a02("a02");
  symbol a03("a03");
  symbol a04("a04");
  symbol a05("a05");
  symbol a06("a06");
  symbol a07("a07");
  symbol a08("a08");
  symbol a09("a09");
  symbol a10("a10");
  symbol a11("a11");
  symbol a12("a12");
  symbol a13("a13");
  symbol a14("a14");
  symbol a15("a15");
  symbol a16("a16");
  symbol a17("a17");
  symbol a18("a18");
  symbol a19("a19");
  symbol a20("a20");
  symbol a21("a21");
  symbol a22("a22");
  symbol a23("a23");
  symbol a24("a24");
  symbol a25("a25");
  symbol a26("a26");
  symbol a27("a27");
  symbol a28("a28");
  symbol a29("a29");
  symbol a30("a30");

  symbol x("x");
  symbol y("y");
  symbol z("z");

  //  ex e(buf,lst(x,y,z,
  //	       a01,a02,a03,a04,a05,a06,a07,a08,a09,a10,
  //	       a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,
  //	       a21,a22,a23,a24,a25,a26,a27,a28,a29,a30 ));

  //  ex e(buf,lst(x,y,z));

  ex e(buf,lst(x,y,z, \
	       a01,a02,a03,a04,a05,a06,a07,a08,a09,a10, \
	       a11,a12 ));

  cerr << "BUF  in ginac =" <<buf << "\n";
  cerr << "EVAL in ginac =" <<e << "\n";

}

