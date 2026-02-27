/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_getdate.cpp
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

static int come_yet_getdate = 0;


void SL_feelP2::SL_getdate(int makeFlag)
{
  const char *sourceName;

  if(come_yet_getdate == 1)  return;
  else                  come_yet_getdate = 1;

  sourceName = "getdate.c";
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSourceRAW("/*");
  writeSourceRAW(" *  getdat.c function for UNIX system to get current date by 'date' command");
  writeSourceRAW(" *");
  writeSourceRAW(" *  Date          1997/10/09 16:30");
  writeSourceRAW(" *  Programmed by Hidehiro FUJIO");
  writeSourceRAW(" *");
  writeSourceRAW(" *  It returns character*16 pointer, and this is allocated local memory");
  writeSourceRAW(" *  in this file.");
  writeSourceRAW(" *");
  writeSourceRAW(" */");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("#include <stdio.h>");
  writeSourceRAW("#include <stdlib.h>");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("/* Format");
  writeSourceRAW("   1234567890123456X");
  writeSourceRAW("   1965/09/11 17:45   */");
  writeSourceRAW("");
  writeSourceRAW("void getdate_(datebuf)        /* Returns 16byte string */");
  writeSourceRAW("char *datebuf;");
  writeSourceRAW("{");
  writeSourceRAW("  FILE *pfp;");
  writeSourceRAW("  char  buf[BUFSIZ];");
  writeSourceRAW("");
  writeSourceRAW("  char  whatday[11];");
  writeSourceRAW("  char  month[11];");
  writeSourceRAW("  int   imonth;");
  writeSourceRAW("  int   day;");
  writeSourceRAW("  char  time[11];");
  writeSourceRAW("  char  timezone[11];");
  writeSourceRAW("  int   year;");
  writeSourceRAW("");
  writeSourceRAW("  int   ret;");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("  /* use date command to get date */");
  writeSourceRAW("  pfp = (FILE *)popen(\"date\",\"r\");");
  writeSourceRAW("  fgets(buf,sizeof(buf),pfp);");
  writeSourceRAW("  ret = pclose(pfp);");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("  if(pfp == NULL || ret != 0) {");
  writeSourceRAW("    sprintf(datebuf,\"----/--/-- --:--\");");
  writeSourceRAW("    return;");
  writeSourceRAW("  }");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("  /* Read buffer */");
  writeSourceRAW("  sscanf(buf,\"\%s \%s \%d \%s \%s \%d\",whatday,month,&day,time,timezone,&year);");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("  /*  Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec */");
  writeSourceRAW("  switch(month[0]) {");
  writeSourceRAW("  case 'J':");
  writeSourceRAW("    if(month[1] == 'a') {");
  writeSourceRAW("      imonth = 1;");
  writeSourceRAW("    }");
  writeSourceRAW("    else if(month[2] == 'n') {");
  writeSourceRAW("      imonth = 6;");
  writeSourceRAW("    }");
  writeSourceRAW("    else {");
  writeSourceRAW("      imonth = 7;");
  writeSourceRAW("    }");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  case 'F':");
  writeSourceRAW("    imonth = 2;");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  case 'M':");
  writeSourceRAW("    if(month[2] == 'r') {");
  writeSourceRAW("      imonth = 3;");
  writeSourceRAW("    }");
  writeSourceRAW("    else {");
  writeSourceRAW("      imonth = 5;");
  writeSourceRAW("    }");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  case 'A':");
  writeSourceRAW("    if(month[1] == 'p') {");
  writeSourceRAW("      imonth = 4;");
  writeSourceRAW("    }");
  writeSourceRAW("    else {");
  writeSourceRAW("      imonth = 8;");
  writeSourceRAW("    }");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  case 'S':");
  writeSourceRAW("    imonth = 9;");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  case 'O':");
  writeSourceRAW("    imonth = 10;");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  case 'N':");
  writeSourceRAW("    imonth = 11;");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  case 'D':");
  writeSourceRAW("    imonth = 12;");
  writeSourceRAW("    break;");
  writeSourceRAW("");
  writeSourceRAW("  }");
  writeSourceRAW("");
  writeSourceRAW("  /* time */");
  writeSourceRAW("  time[5] = '\\0';");
  writeSourceRAW("");
  writeSourceRAW("  /*   Again, the format is");
  writeSourceRAW("       1234567890123456X");
  writeSourceRAW("       1965/09/11 17:45     */");
  writeSourceRAW("");
  writeSourceRAW("  sprintf(datebuf,\"\%4d/\%2d/\%2d \%s\",year,imonth,day,time);");
  writeSourceRAW("");
  writeSourceRAW("");
  writeSourceRAW("  /* add 0 if space in month and day */");
  writeSourceRAW("  if(*(datebuf+5) == ' ') *(datebuf+5) = '0';");
  writeSourceRAW("  if(*(datebuf+8) == ' ') *(datebuf+8) = '0';");
  writeSourceRAW("");
  writeSourceRAW("  /* return */");
  writeSourceRAW("  return;");
  writeSourceRAW("}");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
