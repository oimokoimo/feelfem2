/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_cptime.cpp
 *  Date     : 2002/04/19 01:54
 *  Purpose  : Library module generator
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
#include "SL_feelP2.hpp"

static int come_yet_cptime = 0;


void SL_feelP2::SL_cptime(int makeFlag)
{
  const char *sourceName;

  if(come_yet_cptime == 1)  return;
  else                  come_yet_cptime = 1;

  sourceName = "cptime.c";
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSourceRAW("#include <stdio.h>");
  writeSourceRAW("#include <sys/types.h>");
  writeSourceRAW("#include <sys/times.h>");
  writeSourceRAW("#include <time.h>");
  writeSourceRAW("");
  writeSourceRAW("static long  user_time,total_user_time;");
  writeSourceRAW("static long   sys_time,total_sys_time;");
  writeSourceRAW("static long  c_user_time,total_c_user_time;");
  writeSourceRAW("static long   c_sys_time,total_c_sys_time;");
  writeSourceRAW("static struct tms cpu_time;");
  writeSourceRAW("");
  writeSourceRAW("void timeinit_()");
  writeSourceRAW("{");
  writeSourceRAW("    if( -1 == times( &cpu_time )) {");
  writeSourceRAW("	fprintf(stderr,\"Cannot call times routine\\n\");");
  writeSourceRAW("    }");
  writeSourceRAW("");
  writeSourceRAW("    user_time    = cpu_time.tms_utime;");
  writeSourceRAW("    sys_time     = cpu_time.tms_stime;");
  writeSourceRAW("");
  writeSourceRAW("    c_user_time  = cpu_time.tms_cutime;");
  writeSourceRAW("    c_sys_time   = cpu_time.tms_cstime;");
  writeSourceRAW("");
  writeSourceRAW("    total_user_time = 0;");
  writeSourceRAW("    total_sys_time  = 0;");
  writeSourceRAW("");
  writeSourceRAW("    total_c_user_time = 0;");
  writeSourceRAW("    total_c_sys_time  = 0;");
  writeSourceRAW("");
  writeSourceRAW("    return;");
  writeSourceRAW("}");
  writeSourceRAW("");
  writeSourceRAW("double erapstime_()");
  writeSourceRAW("{");
  writeSourceRAW("    long ut,st;");
  writeSourceRAW("    long cut,cst;");
  writeSourceRAW("    double ret_value;");
  writeSourceRAW("");
  writeSourceRAW("    if( -1 == times( &cpu_time )) {");
  writeSourceRAW("	fprintf(stderr,\"Cannot call times routine\\n\");");
  writeSourceRAW("    }");
  writeSourceRAW("");
  writeSourceRAW("    ut = cpu_time.tms_utime - user_time;");
  writeSourceRAW("    st = cpu_time.tms_stime - sys_time ;");
  writeSourceRAW("    total_user_time += ut;");
  writeSourceRAW("    total_sys_time  += st;");
  writeSourceRAW("");
  writeSourceRAW("    cut = cpu_time.tms_cutime - c_user_time;");
  writeSourceRAW("    cst = cpu_time.tms_cstime - c_sys_time ;");
  writeSourceRAW("    total_c_user_time += cut;");
  writeSourceRAW("    total_c_sys_time  += cst;");
  writeSourceRAW("");
  writeSourceRAW("    user_time = cpu_time.tms_utime;");
  writeSourceRAW("    sys_time  = cpu_time.tms_stime;");
  writeSourceRAW("");
  writeSourceRAW("    c_user_time = cpu_time.tms_cutime;");
  writeSourceRAW("    c_sys_time  = cpu_time.tms_cstime;");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("    ret_value = (double)(total_user_time + total_sys_time)/(double)CLK_TCK;");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("    return(ret_value);");
  writeSourceRAW("}");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
