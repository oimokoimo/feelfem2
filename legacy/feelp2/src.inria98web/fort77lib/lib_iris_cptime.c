/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1993/10/14
 *   
 *   Purpose:   lib_iris_cptime.c
 *   Functions: cptime
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

lib_iris_cptime()
{
    FILE *fp;
    StoreMakefile("cptime.c",SYSTEM_LIBRARY);
    if(LIMIT_FILE == 1) return;

    fp = OpenFileToWrite("cptime.c");

    F77("void cptime_(ii)\n");
    F77("long *ii;\n");
    F77("{\n");
    F77("long clock();\n");
    F77("*ii = clock() / 1000;\n");
    F77("return;\n");
    F77("}\n");

    CloseFile(fp);
    return;
}


    
