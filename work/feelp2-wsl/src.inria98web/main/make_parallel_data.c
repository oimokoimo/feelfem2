/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_parallel_data.c
 *      Date:   1994/12/07
 *   
 *   Purpose:   make parallel_data.c
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#define  PROG_NAME_DECOMP  "feel.decomp"
#define  PROG_NAME_PDATA   "feel.pdata"

void make_parallel_data( parallel )
     int parallel;
{
    char com[BUFSIZ];

    fprintf(stderr,"Making parallel data  ...");

    /*  DECOMP */
    sprintf(com,"%s %d",PROG_NAME_DECOMP,parallel);
    system(com);

    /*  PDATA  */
    sprintf(com,"%s %d",PROG_NAME_PDATA,parallel);
    system(com);


    fprintf(stderr,"done\n");
    return;
}
