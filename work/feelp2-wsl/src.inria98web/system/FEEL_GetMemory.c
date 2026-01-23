/*
 * FEEL system Prototype Version 2
 * 
 * File     FEEL_GetMemory.c
 * Made     1992/08/20
 * Modified 
 * Version  0.0
 *
 * Modified by chappy 
 *
 * Purpose: Get Memory from heap area
 *
 */


#include <stdio.h>
#include <stdlib.h>   /* malloc, calloc */
#include "../feel_def/feel_msg.h"
#include "system.h"

void *FEEL_GetMemory(size_t size)
{
    void *cp;

    if (size == 0) return NULL;

    cp = calloc(1, size);   /* 0初期化込み */

    if (cp == NULL) {
        SystemAbort("No more heap memory");
    }

    return cp;
}

double *FEEL_GetMemory_double(size_t n)
{
    double *dble;

    if (n == 0) return NULL;

    dble = (double *)calloc(n, sizeof(double));

    if (dble == NULL) {
        SystemAbort("No more heap memory(double)");
    }

    return dble;
}
