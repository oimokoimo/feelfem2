/*
 *  feelfem  (original)  Version  1.0
 *  Copyright (C) NEC Corporation 1999
 *  Programmed by Hidehiro FUJIO
 *  Date:     1999-07-19
 *  Modified: 1999-07-19
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Purpose: main program
 *
 *  Notes:
 *   - Parser and language spec are carried over from feelfem 1.0.
 *   - Back-end and build system are updated for modern C++ toolchains.
 *
 *
 *   main program
 *
 */

#include <iostream>
#include <cstdlib>

#include "../class/Configure.hpp"
#include "../class/feelfem.hpp"     // extern declaration for flags
#include "../class/feeldef.hpp"
#include "../class/feelfuncs.hpp"     

//#include "../class/Configure.hpp"

#include "parse.h"


#include "lex.h"

void debug_execute(void);
void feelfem(void);


void usage()
{
  
  switch(feelfem_language) {
    
  case ENGLISH:
  default:
    std::cerr <<"usage: feelfem [options] [pde-files]\n";
    std::cerr <<"\n";
    std::cerr <<"Options\n";
    std::cerr <<"\n";
//  std::cerr <<"       -debug          : debug mode\n"; 

    std::cerr <<"  " << OPTION_MESHONLY  <<"       : generate mesh data only\n";
    std::cerr <<"  " << OPTION_DEBUG     <<"          : debug mode\n"; 
    std::cerr <<"  " << OPTION_DEBUG_FULL    <<"      : debug mode\n"; 
    std::cerr <<"  " << OPTION_WRTDEBUGCODE<<"   : generate code with debugging code.\n";
    std::cerr <<"  " <<OPTION_DISPDEBUG  <<"      : X-window debug mode\n";
    std::cerr << std::endl;
    break;
  }

  return;
}

int feelfem_setoption( int argc, char **argv, int *src_flag)
{
  int errors;
  errors = 0;

  for(int i=0;i<argc;i++) {
    *(src_flag+i) = 0;
  }

  for(int i=1;i<argc;i++) {

    if(streq(*(argv+i),OPTION_WEB)) {
      feelfem_web = YES;
      continue;
    }

    if(streq(*(argv+i),OPTION_MESHONLY)) {
      feelfem_meshonly = YES;
      continue;
    }

    if(streq(*(argv+i),OPTION_DEBUG)) {
      feelfem_debug = YES;
      feelfem_debug_msglevel = DEBUG_MSG_NORMAL;
      continue;
    }

    if(streq(*(argv+i),OPTION_DEBUG_FULL)) {
      feelfem_debug = YES;
      feelfem_debug_msglevel = DEBUG_MSG_FULL;
      continue;
    }

    if(streq(*(argv+i),OPTION_WRTDEBUGCODE)) {
      wrtDEBUGcodeFlag = YES;
      continue;
    }

    if(streq(*(argv+i),OPTION_DISPDEBUG)) {
      dispDebugFlag = YES;
      continue;
    }

    
    if(**(argv+i) == '-') {
	    std::cerr << "Unknown option " << *(argv+i) << "\n";
      errors = errors + 1;
      continue;
    }

    *(src_flag + i) = 1;
  }


  return(errors);
}


int main( int argc, char **argv)
{

	std::cout << "Finite Element Code Generator feelfem2 v2.0 " << std::endl ;
    //    "NEC Corporation(c) 1999-2002" << endl ;
  

  int *src_flag=new int[argc];

  int error;
  error = feelfem_setoption( argc , argv , src_flag);

  if(error) {
    usage();
    exit(1);
  }


  int source_files;
  source_files   = 0;
  for(int i=0;i<argc;i++) {
    if( *(src_flag+i) == YES) {
      ++source_files;
    }
  }

  if(source_files == 0) {
     initLex();    // initialization of numberOfLines
     feelfem_currentFileName = "stdin";
     storeSourceFileName(feelfem_currentFileName);
     if(yyparse()) {
       exit(1);
     }
  }
  else {

    // read default file
    if(freopen(feelfemconf.GetBasicPDE(),"r",stdin) == 0) {
	    std::cerr << "feelfem : cannot open " << feelfemconf.GetBasicPDE() << "\n";
      exit(1);
    }
    feelfem_currentFileName = feelfemconf.GetBasicPDE();
    storeSourceFileName(feelfem_currentFileName);
    initLex();   
    if(yyparse()) {
      exit(1);
    }


    // open pde files
    int ptr = 0;
    while(source_files) {


      if(*(src_flag+ptr) == YES) {
	source_files--;

	if(freopen(argv[ptr],"r",stdin) == 0) {
		std::cerr << "feelfem : cannot open " << argv[ptr] << "\n";
	  exit(1);
	}
	feelfem_currentFileName = argv[ptr];
	storeSourceFileName(feelfem_currentFileName);
	initLex();   
      
	if(yyparse()) {
	  exit(1);
	}
      }
      ptr++;

    }  // while(source_files) 

  }    // if(source_files == 0)


  if(feelfem_debug) debug_execute();     // In parser directory

//  feelfem();                             // In main directory
                                         // main/feelfem.cpp
  std::cout <<"Currently feelfem() is commented out. " << std::endl;
}
