/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   MakeFORTsrc.c
 *      Date:   1993/11/17
 *   
 *  Modified:   1998/09/21 (win32 version)
 *   
 *   Purpose:   FORTRANの文法にしたがって、長いファイルを短くする
 *   Functions: 
 *              
 *              
 */

#include <stdlib.h>
#include <string.h>
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/system.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#define DBLBUFSIZ 20000

void MakeFORTsrc( fname )
     char *fname;
{
    FILE *fp_read;
    FILE *fp_write;
    
    char buf[DBLBUFSIZ];
    char com[DBLBUFSIZ];
    char *cp;

    int  column;

    fp_read  = OpenFileToRead( fname );
    fp_write = OpenFileToWrite( TMP_FORTFILE );
    
    while(fgets(buf,sizeof(buf),fp_read)) {
	if(strlen(buf) >= DBLBUFSIZ -1 ) {
	    fclose(fp_read);
	    fclose(fp_write);
	    sprintf(com,"rm -r %s",TMP_FORTFILE);
	    system(com);
	    SystemError_s("Too long line(%s)",fname);
	    SystemAbort(" ");
	}

	if(buf[0] == 'C' || buf[0] == 'c' || buf[0] == '*' ||
	   strlen(buf) < 73                                     ) {
	    fprintf(fp_write,"%s",buf);
	    continue;
	}
	
	column = 0;
	cp = buf;

	while(*cp) {
	    if(column <= 71) {
		fprintf(fp_write,"%c",*cp);
		cp++;
		column++;
	    }
	    else {
		fprintf(fp_write,"\n");
		fprintf(fp_write,"     $%c",*cp);
		column = 8;
		cp++;
	    }
	}
	/* bufの最後はキャリッジリターン */
    }

    fclose(fp_read);
    fclose(fp_write);

#ifdef MSDOS

    sprintf(com,"copy %s %s >NUL",TMP_FORTFILE,fname);
    system(com);
    sprintf(com,"del %s",TMP_FORTFILE);
    system(com);

#else 

    sprintf(com,"mv %s %s",TMP_FORTFILE,fname);
    system(com);

#endif

    return;
}
