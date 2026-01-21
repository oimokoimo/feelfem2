/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *  implicit real*8 (a-h,o-z) §Œ¿Î∏¿
 */
#include <stdio.h>

real8( fp )
     FILE *fp;
{
    fprintf(fp,"      implicit real*8 (a-h,o-z)\n");
}

