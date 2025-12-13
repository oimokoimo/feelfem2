#include <iostream.h>

#include "TermConvert.hpp"
#include "string.hpp"
#include "list.hpp"


void main()
{

  TermConvert tc;

  //  cerr << "add oimo,koimo\n";
  tc.storeConvertPair( "oimo" , "too" );

  //  cerr << "add koimo,koimo\n";
  tc.storeConvertPair( "koimo" , "(_m1*p1_(x,y)*_m2*p2_(x,y)" );



  char *org,*conv;
  org   ="10.34d0*oimo * (koimo- 10.34d-4)";
  conv  = tc.convertExpressionString( org);

  cerr << "original "<<org << endl;
  cerr << "output   "<<conv<< endl;
  //  cerr << "end\n";

  /*  list <string> lst;
  

  
   lst.add( "str oimo" );
   lst.add( "str koimo" );

    cerr << "lst destructor invoking...\n";
  */


}
