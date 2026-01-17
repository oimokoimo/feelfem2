/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : xplot_extern.cpp
 *  Date     : 2001/04/10
 *  Modified : 
 *  
 *  Purpose  : 
 *  
 */
#include "xplot.hpp"
#include "psplot.hpp"

int xplotScreens  = 0;
xplot  *activeXplotPtr  = 0;
psplot *activePsplotPtr = 0;
