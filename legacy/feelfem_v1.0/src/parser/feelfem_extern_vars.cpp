/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999,2000
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feelfem_extern_vars.cpp
 *  Date     : 2001/01/15
 *  Modified : 2001/03/08
 *  Modified : 2001/12/18 add dispDebugFlag  (for X11 debug)
 *  
 *  Purpose  : define and allocate extern variables
 *  
 */
#include "../class/feeldef.hpp"
#include "../class/list.hpp"

// gloval options
int feelfem_meshonly       = NO;
int feelfem_web            = NO;
int feelfem_debug          = NO;
int feelfem_debug_msglevel = DEBUG_MSG_NORMAL;

int wrtDEBUGcodeFlag       = NO;
int dispDebugFlag          = NO;


int feelfem_platform = Linux;
int feelfem_language = ENGLISH;
char *feelfem_currentFileName;


// To store parsing information
list <void *>      parseGeomLst;
list <void *>      parseMeshLst;
list <void *>      parseSchemeLst;
list <void *>      parseVarLst;
list <void *>      parseElementLst;
list <void *>      parseQuadratureLst;
