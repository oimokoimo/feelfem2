/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 * 
 */

#include<stdio.h>

comment1(fp)
     FILE *fp;
{
    fprintf(fp,"c --------------------------------------------------------------------\n");
    return;
}

comment2(fp)
     FILE *fp;
{
    fprintf(fp,"c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    return;
}

comment_s(fp)
     FILE *fp;
{
    fprintf(fp,"c -----\n");
    return;
}
