/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MakeMakefile.cpp
 *  Date     : 2000/11/21
 *  Modified : 2000/11/21
 *  Modified : 2001/02/02 orderedPtrList
 *  
 *  Purpose  : MakeMakefile.cpp (Under Source.hpp)
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

#include "feeldef.hpp"
#include "feelfuncs.hpp"    // fora abortExit
#include "Source.hpp"
#include "MakefileObject.hpp"

#include "Configure.hpp"


//void debug_f77itr(orderedPtrList <MakefileObject *> & debug_list)
//{
//  listIterator <MakefileObject *>itritr(debug_list);
//  fprintf(stderr,"LIST : ");
//  for(itritr.init();!itritr();++itritr) {
//    fprintf(stderr," ");
//    itritr()->putFPObjectName(stderr);
//    fprintf(stderr,"(%d)",itritr()->getMakeFlag());
//  }
//  fprintf(stderr,"\n");
//}

// static variable in class Source declaration
int Source::numberOfSourceFiles = 0;         // initialization 
orderedPtrList <MakefileObject *> Source::f90_basic_list;
orderedPtrList <MakefileObject *> Source::f90_library_list;
orderedPtrList <MakefileObject *> Source::f90_model_list;
orderedPtrList <MakefileObject *> Source::f90_problem_list;
orderedPtrList <MakefileObject *> Source::f90_main_list;

orderedPtrList <MakefileObject *> Source::f77_basic_list;
orderedPtrList <MakefileObject *> Source::f77_library_list;
orderedPtrList <MakefileObject *> Source::f77_model_list;
orderedPtrList <MakefileObject *> Source::f77_problem_list;
orderedPtrList <MakefileObject *> Source::f77_main_list;

orderedPtrList <MakefileObject *> Source::c_basic_list;
orderedPtrList <MakefileObject *> Source::c_library_list;
orderedPtrList <MakefileObject *> Source::c_model_list;
orderedPtrList <MakefileObject *> Source::c_problem_list;
orderedPtrList <MakefileObject *> Source::c_main_list;

orderedPtrList <MakefileObject *> Source::cpp_basic_list;
orderedPtrList <MakefileObject *> Source::cpp_library_list;
orderedPtrList <MakefileObject *> Source::cpp_model_list;
orderedPtrList <MakefileObject *> Source::cpp_problem_list;
orderedPtrList <MakefileObject *> Source::cpp_main_list;


void Source::StoreSourceUniq(const char *name, int makeFlag)
{
  string fname = name;
  if(outerSourceFile.includes(fname)) {
    return;
  }

  outerSourceFile.add(fname);
  StoreSource(name,makeFlag);

  std::cerr << "Source = " << name << "  makeFlag = " << makeFlag << std::endl;

  return;
}

void Source::StoreSource(const char *name, int makeFlag)
{

  numberOfSourceFiles++;


  MakefileObject *newObj = new MakefileObject(name, makeFlag);
  
  int lang_type  = newObj->getLanguageType();
  int make_flag  = newObj->getMakeFlag();
  int list_level;

  if(make_flag       <= UPTO_OBJLEVEL_BASIC  ) {
    list_level = OBJLEVEL_BASIC;
  }
  else if (make_flag <= UPTO_OBJLEVEL_LIBRARY) {
    list_level = OBJLEVEL_LIBRARY;
  }
  else if (make_flag <= UPTO_OBJLEVEL_MODEL  ) {
    list_level = OBJLEVEL_MODEL;
  }
  else if (make_flag <= UPTO_OBJLEVEL_PROBLEM) {
    list_level = OBJLEVEL_PROBLEM;
  }
  else if (make_flag <= UPTO_OBJLEVEL_MAIN   ) {
    list_level = OBJLEVEL_MAIN;
  }
  else {

	  std::cout << "make_flag = "<< make_flag << "  src name=" << name <<"\n";
    abortExit("make_flag is illegal : in Source::StoreSource(char *,int)");
  }


  switch( lang_type ) {

  case LANG_F77:
    switch(list_level) {

    case OBJLEVEL_BASIC:
      f77_basic_list.add( newObj );
      break;

    case OBJLEVEL_LIBRARY:
      f77_library_list.add( newObj );
      break;
    case OBJLEVEL_MODEL:
      f77_model_list.add( newObj );
      break;
    case OBJLEVEL_PROBLEM:
      f77_problem_list.add( newObj );
      break;
    case OBJLEVEL_MAIN:
      f77_main_list.add( newObj );
      break;
    }
    break;

  case LANG_F90:
    switch(list_level) {
    case OBJLEVEL_BASIC:
      f90_basic_list.add( newObj );
      break;
    case OBJLEVEL_LIBRARY:
      f90_library_list.add( newObj );
      break;
    case OBJLEVEL_MODEL:
      f90_model_list.add( newObj );
      break;
    case OBJLEVEL_PROBLEM:
      f90_problem_list.add( newObj );
      break;
    case OBJLEVEL_MAIN:
      f90_main_list.add( newObj );
      break;
    }
    break;


  case LANG_C:
    switch(list_level) {
    case OBJLEVEL_BASIC:
      c_basic_list.add( newObj );
      break;
    case OBJLEVEL_LIBRARY:
      c_library_list.add( newObj );
      break;
    case OBJLEVEL_MODEL:
      c_model_list.add( newObj );
      break;
    case OBJLEVEL_PROBLEM:
      c_problem_list.add( newObj );
      break;
    case OBJLEVEL_MAIN:
      c_main_list.add( newObj );
      break;
    }
    break;


  case LANG_CPLUSPLUS:
    switch(list_level) {
    case OBJLEVEL_BASIC:
      cpp_basic_list.add( newObj );
      break;
    case OBJLEVEL_LIBRARY:
      cpp_library_list.add( newObj );
      break;
    case OBJLEVEL_MODEL:
      cpp_model_list.add( newObj );
      break;
    case OBJLEVEL_PROBLEM:
      cpp_problem_list.add( newObj );
      break;
    case OBJLEVEL_MAIN:
      cpp_main_list.add( newObj );
      break;
    }
    break;

  default:
    fprintf(stderr,"Cannot find language type =%d\n",lang_type);
    abortExit("NOT SUPPORT LANG TYPE Source::StoreSource");
  }


  return;
}


void Source::makeMakefile( int compiler_type )
{

  // Fortran 77
  int f77_basic_src;
  int f77_library_src;
  int f77_model_src;
  int f77_problem_src;
  int f77_main_src;
  int f77_total_src;

  f77_basic_src   = f77_basic_list.getNumberOfElements();
  f77_library_src = f77_library_list.getNumberOfElements();
  f77_model_src   = f77_model_list.getNumberOfElements();
  f77_problem_src = f77_problem_list.getNumberOfElements();
  f77_main_src    = f77_main_list.getNumberOfElements();

  f77_total_src   = f77_basic_src   + f77_library_src + f77_model_src +
                    f77_problem_src + f77_main_src;

  // Fortran 90
  int f90_basic_src;
  int f90_library_src;
  int f90_model_src;
  int f90_problem_src;
  int f90_main_src;
  int f90_total_src;

  f90_basic_src   = f90_basic_list.getNumberOfElements();
  f90_library_src = f90_library_list.getNumberOfElements();
  f90_model_src   = f90_model_list.getNumberOfElements();
  f90_problem_src = f90_problem_list.getNumberOfElements();
  f90_main_src    = f90_main_list.getNumberOfElements();

  f90_total_src   = f90_basic_src   + f90_library_src + f90_model_src +
                    f90_problem_src + f90_main_src;


  // C
  int c_basic_src;
  int c_library_src;
  int c_model_src;
  int c_problem_src;
  int c_main_src;
  int c_total_src;

  c_basic_src   = c_basic_list.getNumberOfElements();
  c_library_src = c_library_list.getNumberOfElements();
  c_model_src   = c_model_list.getNumberOfElements();
  c_problem_src = c_problem_list.getNumberOfElements();
  c_main_src    = c_main_list.getNumberOfElements();

  c_total_src   = c_basic_src   + c_library_src + c_model_src +
                  c_problem_src + c_main_src;

  // C++
  int cpp_basic_src;
  int cpp_library_src;
  int cpp_model_src;
  int cpp_problem_src;
  int cpp_main_src;
  int cpp_total_src;

  cpp_basic_src   = cpp_basic_list.getNumberOfElements();
  cpp_library_src = cpp_library_list.getNumberOfElements();
  cpp_model_src   = cpp_model_list.getNumberOfElements();
  cpp_problem_src = cpp_problem_list.getNumberOfElements();
  cpp_main_src    = cpp_main_list.getNumberOfElements();

  cpp_total_src   = cpp_basic_src   + cpp_library_src + cpp_model_src +
                    cpp_problem_src + cpp_main_src;


  /*
    cout << "f77 = " << f77_total_src << "\n";
    cout << "f90 = " << f90_total_src << "\n";
    cout << "c   = " << c_total_src   << "\n";
    cout << "cpp = " << cpp_total_src << "\n";
  */

  FILE *fp;
  fp = fileOpenToWrite(MAKEFILE_NAME);
  if(fp == NULL) {
    fprintf(stderr,"Cannot Open %s to write\n",MAKEFILE_NAME);
    fprintf(stderr,"Makefile not generated.\n");
    return;
  }

  // Header
  fprintf(fp,"#------------------------------------------------\n");
  fprintf(fp,"#  feelfem makefile\n");
  fprintf(fp,"#  Date : %s\n",getdate());
  fprintf(fp,"#\n");
  fprintf(fp,"#------------------------------------------------\n");


  // COMPILER section
  if(f77_total_src>0) {
    fprintf(fp,"F77      = %s\n",feelfemconf.GetF77());
  }
  if(f90_total_src>0) {
    fprintf(fp,"F90      = %s\n",feelfemconf.GetF90());
  }
  if(cpp_total_src>0) {
    fprintf(fp,"CPP      = %s\n",feelfemconf.GetCPP());
  }
  if(c_total_src  >0) {
    if(cpp_total_src >0) {
      fprintf(fp,"CC       = %s\n",feelfemconf.GetCPP());
    }
    else {
      fprintf(fp,"CC       = %s\n",feelfemconf.GetCC());
    }

  }

  fprintf(fp,"\n");

  // LINKER section
  if(f90_total_src >0 ) {
    fprintf(fp,"LINKER   = $(F90)\n");
  }
  else if(f77_total_src >0) {
    fprintf(fp,"LINKER   = $(F77)\n");
  }
  else if(cpp_total_src >0) {
    fprintf(fp,"LINKER   = $(CPP)\n");
  }
  else {
    fprintf(fp,"LINKER   = $(CC)\n");
  }
  fprintf(fp,"\n");
    

  // FLAGS section
  if(f77_total_src>0) {
    fprintf(fp,"FFLAGS   =\n");
  }
  if(f90_total_src>0) {
    fprintf(fp,"FFLAGS   =\n");
  }
  if(cpp_total_src>0) {
    fprintf(fp,"CFLAGS   =\n");
  }
  if(c_total_src  >0) {
    if(cpp_total_src >0) {
      ;  // do nothing
    }
    else {
      fprintf(fp,"CFLAGS   =\n");
    }
  }
  fprintf(fp,"\n");


  // link, library options 
  fprintf(fp,"LIBDIR =\n");

  fprintf(fp,"LIBS   = ");
  feelfemconf.WriteLIBSinMakefile(fp);
  fprintf(fp,"\n");


  fprintf(fp,"\n");
  fprintf(fp,"\n");

  // SUFFIXES section
  fprintf(fp,".SUFFIXES:");
  if(f77_total_src>0) {
    fprintf(fp," .f");
  }
  if(f90_total_src>0) {
    fprintf(fp," .f90");
  }
  if(cpp_total_src>0) {
    fprintf(fp," .cpp");
  }
  if(c_total_src  >0) {
    fprintf(fp," .c");
  }

  fprintf(fp," .o\n");
  fprintf(fp,"\n");


  // Compilation rules
  if(f77_total_src>0) {
    fprintf(fp,".f.o:\n");
    fprintf(fp,"%c$(F77) $(FFLAGS) $(INCLUDES) -c $<\n",'\t');
    fprintf(fp,"\n");
  }
  if(f90_total_src>0) {
    fprintf(fp,".f90.o:\n");
    fprintf(fp,"%c$(F90) $(FFLAGS) $(INCLUDES) -c $<\n",'\t');
    fprintf(fp,"\n");
  }
  if(cpp_total_src>0) {
    fprintf(fp,".cpp.o:\n");
    fprintf(fp,"%c$(CPP) $(CFLAGS) $(INCLUDES) -c $<\n",'\t');
    fprintf(fp,"\n");
  }
  if(c_total_src  >0) {
    fprintf(fp,".c.o:\n");
    fprintf(fp,"%c$(CC) $(CFLAGS) $(INCLUDES) -c $<\n",'\t');
    fprintf(fp,"\n");
  }
  fprintf(fp,"\n");
  fprintf(fp,"\n");

  // PROGRAM
  fprintf(fp,"PROGRAM  = %s\n",FEELFEM_EXEC_NAME);
  fprintf(fp,"\n");


  // OBJS

  // F77
  if(f77_total_src > 0) {
    fprintf(fp,"F77_BASIC_OBJS  =");
    writeObjList(fp,f77_basic_list);
    fprintf(fp,"\n");

    fprintf(fp,"F77_LIBRARY_OBJS=");
    writeObjList(fp,f77_library_list);
    fprintf(fp,"\n");

    fprintf(fp,"F77_MODEL_OBJS  =");
    writeObjList(fp,f77_model_list);
    fprintf(fp,"\n");

    fprintf(fp,"F77_PROBLEM_OBJS=");
    writeObjList(fp,f77_problem_list);
    fprintf(fp,"\n");

    fprintf(fp,"F77_MAIN_OBJS   =");
    writeObjList(fp,f77_main_list);
    fprintf(fp,"\n");

    fprintf(fp,"F77_MOD_OBJS    = $(F77_BASIC_OBJS) $(F77_LIBRARY_OBJS) \\\n");
    fprintf(fp,"                  $(F77_MODEL_OBJS) $(F77_PROBLEM_OBJS)\n");
    fprintf(fp,"\n");  
    fprintf(fp,"\n");
  }

  // F90
  if(f90_total_src > 0) {
    fprintf(fp,"F90_BASIC_OBJS  =");
    writeObjList(fp,f90_basic_list);
    fprintf(fp,"\n");

    fprintf(fp,"F90_LIBRARY_OBJS=");
    writeObjList(fp,f90_library_list);
    fprintf(fp,"\n");

    fprintf(fp,"F90_MODEL_OBJS  =");
    writeObjList(fp,f90_model_list);
    fprintf(fp,"\n");

    fprintf(fp,"F90_PROBLEM_OBJS=");
    writeObjList(fp,f90_problem_list);
    fprintf(fp,"\n");

    fprintf(fp,"F90_MAIN_OBJS   =");
    writeObjList(fp,f90_main_list);
    fprintf(fp,"\n");

    fprintf(fp,"F90_MOD_OBJS    = $(F90_BASIC_OBJS) $(F90_LIBRARY_OBJS) \\\n");
    fprintf(fp,"                  $(F90_MODEL_OBJS) $(F90_PROBLEM_OBJS)\n");
    fprintf(fp,"\n");  
    fprintf(fp,"\n");
  }


  // C
  if(c_total_src > 0) {
    fprintf(fp,"C_BASIC_OBJS  =");
    writeObjList(fp,c_basic_list);
    fprintf(fp,"\n");

    fprintf(fp,"C_LIBRARY_OBJS=");
    writeObjList(fp,c_library_list);
    fprintf(fp,"\n");

    fprintf(fp,"C_MODEL_OBJS  =");
    writeObjList(fp,c_model_list);
    fprintf(fp,"\n");

    fprintf(fp,"C_PROBLEM_OBJS=");
    writeObjList(fp,c_problem_list);
    fprintf(fp,"\n");

    fprintf(fp,"C_MAIN_OBJS   =");
    writeObjList(fp,c_main_list);
    fprintf(fp,"\n");

    fprintf(fp,"C_MOD_OBJS    = $(C_BASIC_OBJS) $(C_LIBRARY_OBJS) \\\n");
    fprintf(fp,"                $(C_MODEL_OBJS) $(C_PROBLEM_OBJS)\n");
    fprintf(fp,"\n");  
  }

  // CPP
  if(cpp_total_src > 0) {
    fprintf(fp,"CPP_BASIC_OBJS  =");
    writeObjList(fp,cpp_basic_list);
    fprintf(fp,"\n");

    fprintf(fp,"CPP_LIBRARY_OBJS=");
    writeObjList(fp,cpp_library_list);
    fprintf(fp,"\n");

    fprintf(fp,"CPP_MODEL_OBJS  =");
    writeObjList(fp,cpp_model_list);
    fprintf(fp,"\n");

    fprintf(fp,"CPP_PROBLEM_OBJS=");
    writeObjList(fp,cpp_problem_list);
    fprintf(fp,"\n");

    fprintf(fp,"CPP_MAIN_OBJS   =");
    writeObjList(fp,cpp_main_list);
    fprintf(fp,"\n");


    fprintf(fp,"CPP_MOD_OBJS    = $(CPP_BASIC_OBJS) $(CPP_LIBRARY_OBJS) \\\n");
    fprintf(fp,"                  $(CPP_MODEL_OBJS) $(CPP_PROBLEM_OBJS)\n");
    fprintf(fp,"\n");
    fprintf(fp,"\n");

  }


  // MOD_OBJS
  {
    int flag;
    flag = 0;
    fprintf(fp,"MOD_OBJS        = ");
    
    if(f77_total_src > 0) {
      fprintf(fp,"$(F77_MOD_OBJS)");
      flag = 1;
    }

    if(f90_total_src > 0) {
      if(flag == 1) {
	fprintf(fp," \\\n");
	fprintf(fp,"                  ");
      }
      fprintf(fp,"$(F90_MOD_OBJS)");
      flag = 1;
    }

    if(c_total_src > 0) {
      if(flag == 1) {
	fprintf(fp," \\\n");
	fprintf(fp,"                  ");
      }
      fprintf(fp,"$(C_MOD_OBJS)");
      flag = 1;
    }


    if(cpp_total_src > 0) {
      if(flag == 1) {
	fprintf(fp," \\\n");
	fprintf(fp,"                  ");
      }
      fprintf(fp,"$(CPP_MOD_OBJS)");
      flag = 1;
    }
    fprintf(fp,"\n");
    fprintf(fp,"\n");
  }

  // MAIN_OBJS
  {
    int flag;
    flag = 0;
    fprintf(fp,"MAIN_OBJS       = ");
    
    if(f77_total_src > 0) {
      fprintf(fp,"$(F77_MAIN_OBJS)");
      flag = 1;
    }

    if(f90_total_src > 0) {
      if(flag == 1) {
	fprintf(fp," \\\n");
	fprintf(fp,"                  ");
      }
      fprintf(fp,"$(F90_MAIN_OBJS)");
      flag = 1;
    }

    if(c_total_src > 0) {
      if(flag == 1) {
	fprintf(fp," \\\n");
	fprintf(fp,"                  ");
      }
      fprintf(fp,"$(C_MAIN_OBJS)");
      flag = 1;
    }


    if(cpp_total_src > 0) {
      if(flag == 1) {
	fprintf(fp," \\\n");
	fprintf(fp,"                  ");
      }
      fprintf(fp,"$(CPP_MAIN_OBJS)");
      flag = 1;
    }
    fprintf(fp,"\n");
    fprintf(fp,"\n");
  }


  // all
  fprintf(fp,"all  : feelgo\n");
  fprintf(fp,"\n");

  // feelgo
  fprintf(fp,"feelgo : $(MOD_OBJS) $(MAIN_OBJS)\n");
  fprintf(fp,"%c$(LINKER) -o feelgo $(MOD_OBJS) $(MAIN_OBJS) $(LIBDIR) $(LIBS)\n",'\t');

  fprintf(fp,"\n");
  fprintf(fp,"\n");


  // clean
  fprintf(fp,"clean :\n");

  if(f90_total_src > 0) {
    fprintf(fp,"%crm -r *.o feelgo *.d work.pc work.pcl\n",'\t');
  }
  else {
    fprintf(fp,"%crm -r *.o feelgo\n",'\t');
  }


  // End of Makefile
  fclose(fp);


}
  
void Source::writeObjList(FILE *fp,orderedPtrList<MakefileObject *> & objLst)
{
  int line;
  int length;

  length = 18;   // initial value
  line   =  1;

  listIterator <MakefileObject *>itr(objLst);
  for(itr.init(); !itr; ++itr ) {
    int nameLength = itr()->getObjectNameLength();
    
    if(nameLength + length > 60) {
      fprintf(fp," \\\n");
      fprintf(fp,"                 ");   // 17 spaces , because of 1 plus next 
      length = 18;
    }
    fprintf(fp," ");
    itr()->putFPObjectName(fp);

    //    fprintf(fp,"(%d)",itr()->getMakeFlag());  // debug

    length+= nameLength;   // for obj name
    length++;              // for space
  }
  return;
}
