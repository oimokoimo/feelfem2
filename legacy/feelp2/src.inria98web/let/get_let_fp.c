/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_let_fp.c
 *      Date:   1994/02/08
 *   
 *   Purpose:   let文のFORTRANプログラム read/writeルーチン
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

static int   come_yet = NO;
static FILE *let_fp;

extern int one_file;

FILE *get_let_fp()
{
    if(come_yet == YES) {
	return(let_fp);
    }

    come_yet = YES;

    let_fp = OpenFileToWrite(ONE_LET_FNAME);
    StoreMakefile(ONE_LET_FNAME,USER_LIBRARY);

    return(let_fp);
}

void close_let_fp()
{
    if(come_yet == YES && one_file != YES) {
	CloseFile( let_fp );
    }

    return;
}

