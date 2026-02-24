/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem.hpp
 *  Date     : 2000/11/09
 *  Modified : 2001/05/28
 *  
 *  Purpose  : External variables
 *  
 */

#ifndef FEELFEM_FEELFEMHPP
#define FEELFEM_FEELFEMHPP


#define NOTE(MESG)  if(feelfem_debug) std::cerr << MESG << std::endl

void doNothingNow( const char *);


// Global control variables
extern int feelfem_web;
extern int feelfem_meshonly;
extern int feelfem_debug;
extern int feelfem_debug_msglevel;
extern int feelfem_mesh_generator;
extern int wrtDEBUGcodeFlag;
extern int dispDebugFlag;

extern int feelfem_language;
extern const char *feelfem_currentFileName;

#endif
