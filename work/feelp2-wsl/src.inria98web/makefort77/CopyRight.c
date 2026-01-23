/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *
 *  コピーライトの出力プログラム
 *
 *  Modified: 1996/01/24  Add Parallel copyright message
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

void ParallelCopyRight(FILE *);

void CopyRight( fp )
     FILE *fp;
{
    fprintf(fp,"c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    fprintf(fp,"c     feel p2 fort77 program\n");
    fprintf(fp,"c     Copyright(C) NEC Corporation 1993\n");
    fprintf(fp,"c ======================================\n");
    
    if(parallel) { ParallelCopyRight(fp); }
    return;
}

void ParallelCopyRight( fp )
     FILE *fp;
{
    fprintf(fp,"* Parallel Version (Cenju-3/MPI)\n");
    fprintf(fp,"c ======================================\n");
}

