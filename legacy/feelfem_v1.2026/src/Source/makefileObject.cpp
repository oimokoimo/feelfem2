/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : makefileObject.cpp
 *  Date     : 2000/11/21
 *  Modified : 2000/11/21
 *  
 *  Purpose  : makefileObject class
 *  
 */
#include <stdio.h>

#include "feelfuncs.hpp"
#include "string.hpp"
#include "MakefileObject.hpp"

int operator <( const MakefileObject &obj1,  const MakefileObject &obj2)
{

  if( obj1.makeFlag != obj2.makeFlag) {
    return (obj1.makeFlag < obj2.makeFlag);    
  }
  return( obj1.sourceName < obj2.sourceName ); 
}

int operator ==(const MakefileObject &obj1, const MakefileObject &obj2)
{

  // TEMPORARY CODING       streq is not good
  //  fprintf(stderr,"OPERATOR== %s(%d) %s(%d)\n",obj1.sourceName,obj1.makeFlag,
  //	  obj2.sourceName,obj2.makeFlag);
  
  if( obj1.makeFlag == obj2.makeFlag && streq(obj1.sourceName,obj2.sourceName)) {
    return ( obj1.makeFlag == obj2.makeFlag);
  }
  return( 1 == 0);
}


MakefileObject::MakefileObject()
{
  cerr << "Default MakefileObject constructor was called...(It may be error)\n";
  return;  // do nothing now
}

MakefileObject::MakefileObject(const char *name, int flag)
{
  sourceName = name;
  makeFlag   = flag;

  language   = getLanguageType( name );   // Judge the language type

  objectName = name;

  convertObj( objectName ,language);

  //  cout << "src=[" << sourceName << "]" <<", obj=[" << objectName <<"]\n";
  
  return;  
}

MakefileObject::~MakefileObject()
{
  return;  // do nothing now
}

int MakefileObject::getLanguageType(const char *name) //this private function(char*)
{
  int length;

  length = stringLength( name );

  // is F77?   .f 
  if(strindex(name,".f")   == length - 1) {
    return (LANG_F77);
  }

  // is F90    .f90
  if(strindex(name,".f90") == length - 3) {
    return( LANG_F90);
  }

  // is C      .c
  if(strindex(name,".c") == length -   1) {
    return( LANG_C );
  }

  // is C++    .cpp
  if(strindex(name,".cpp") == length - 3) {
    return( LANG_CPLUSPLUS );
  }

  fprintf(stderr,"UNKNOWN language type source %s\n",name);
  abortExit("in makefileObject.cpp");

}

int MakefileObject::getLanguageType(void)  // this public function(void)
{
  return(language);
}

int MakefileObject::getMakeFlag(void)  // this public function(void)
{
  return(makeFlag);
}


void MakefileObject::convertObj( string &str , int language)
{
  int length;
  length = stringLength( str );

  switch ( language ){
  case LANG_F77:
  case LANG_C:
    str[length-1] = 'o';
    return;

  case LANG_F90:
  case LANG_CPLUSPLUS:
    str[length-3] = 'o';
    str[length-2] = '\0';
    return;
  }

}

int MakefileObject::getObjectNameLength(void)
{
  return(stringLength( objectName ) );
}


void MakefileObject::putFPObjectName(FILE *fp)
{
  fprintf(fp,"%s",(char *)objectName);

  return;
}


char *MakefileObject::getObjectName(void)
{
  return(objectName);
}

  
ostream & operator << (ostream &cout, MakefileObject &mobj )
{
  string str  = mobj.getObjectName();

  cout << "(dbg:MakefileObject=[" << str << 
    "(" << mobj.getMakeFlag() << ")]";

  return cout;
}
