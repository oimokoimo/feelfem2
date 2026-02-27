/*
 *  feelfem v1.0 NEC Corporation (C) 1999,2000,2001
 *                   Programmed  by  Hidehiro FUJIO
 *
 *  Filename : SL_binio.cpp
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
#include "SL_LIB_feelP2Achim.hpp"

static int come_yet_binio = 0;


void SL_LIB_feelP2Achim::SL_binio(int makeFlag)
{
  const char *sourceName;

  if(come_yet_binio == 1)  return;
  else                  come_yet_binio = 1;

  sourceName = "binio.c";
  OpenSource(sourceName,makeFlag);

  // ORIGINAL SOURCE STARTS-----------------


  writeSourceRAW("#include <stdio.h>");
  writeSourceRAW("");
  writeSourceRAW("static   FILE *fd;");
  writeSourceRAW("void binopen_(char *filename,int *strlength)");
  writeSourceRAW("{");
  writeSourceRAW("  *(filename+*strlength) = 0;");
  writeSourceRAW("  fprintf(stderr,\"BINARY FILENAME=[\%s]\\n\",filename);");
  writeSourceRAW("");
  writeSourceRAW("  fd = fopen(filename,\"wb\");");
  writeSourceRAW("  if(fd == 0) {");
  writeSourceRAW("    fprintf(stderr,\"Cannot open file \%s to binary write\\n\",filename);");
  writeSourceRAW("    exit(1);");
  writeSourceRAW("  }");
  writeSourceRAW("  return;");
  writeSourceRAW("}");
  writeSourceRAW("");
  writeSourceRAW("void binclose_(void)");
  writeSourceRAW("{");
  writeSourceRAW("  fclose(fd);");
  writeSourceRAW("  return;");
  writeSourceRAW("}");
  writeSourceRAW("");
  writeSourceRAW("void binwritestr_(void *str, int *byte)");
  writeSourceRAW("{");
  writeSourceRAW("  int ret;");
  writeSourceRAW("  ret = fwrite(str,1,*byte,fd);");
  writeSourceRAW("  if(ret == 0) {");
  writeSourceRAW("    fprintf(stderr,\"binwritestr failed.\\n\");");
  writeSourceRAW("    exit(1);");
  writeSourceRAW("  }");
  writeSourceRAW("  return;");
  writeSourceRAW("}");
  writeSourceRAW("");
  writeSourceRAW("void binwriteint_(void *ptr)");
  writeSourceRAW("{");
  writeSourceRAW("  int ret;");
  writeSourceRAW("  ret = fwrite(ptr,4,1,fd);");
  writeSourceRAW("  if(ret == 0) {");
  writeSourceRAW("    fprintf(stderr,\"binwritestr failed.\\n\");");
  writeSourceRAW("    exit(1);");
  writeSourceRAW("  }");
  writeSourceRAW("  return;");
  writeSourceRAW("}");
  writeSourceRAW("");
  writeSourceRAW("void binwriteints_(void *ptr, int *times)");
  writeSourceRAW("{");
  writeSourceRAW("  int ret;");
  writeSourceRAW("  ret = fwrite(ptr,4,*times,fd);");
  writeSourceRAW("  if(ret == 0) {");
  writeSourceRAW("    fprintf(stderr,\"binwriteints failed.\\n\");");
  writeSourceRAW("    exit(1);");
  writeSourceRAW("  }");
  writeSourceRAW("  return;");
  writeSourceRAW("}");
  writeSourceRAW("");
  writeSourceRAW("void binwritedbls_(void *ptr, int *times)");
  writeSourceRAW("{");
  writeSourceRAW("  int ret;");
  writeSourceRAW("  ret = fwrite(ptr,8,*times,fd);");
  writeSourceRAW("  if(ret == 0) {");
  writeSourceRAW("    fprintf(stderr,\"binwriteints failed.\\n\");");
  writeSourceRAW("    exit(1);");
  writeSourceRAW("  }");
  writeSourceRAW("  return;");
  writeSourceRAW("}");

  // ORIGINAL SOURCE END-------------------

  CloseSource();

  return;
}
