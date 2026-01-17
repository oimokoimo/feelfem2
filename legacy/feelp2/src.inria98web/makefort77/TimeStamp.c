/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 * 
 */

#include <stdio.h>
#include "Extern.h"

TimeStamp( fp )
     FILE *fp;
{
    fprintf(fp,"c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    fprintf(fp,"c Date: %s\n",feel_date);
    fprintf(fp,"c User: %s\n",feel_user);
    fprintf(fp,"c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

    return;
}

