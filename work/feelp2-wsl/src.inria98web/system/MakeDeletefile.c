/*
 *   FEEL system  MakeMakefile.c
 *  
 *   MakeDeletefile   一時ファイルを登録、消すルーチン
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../system/system.h"

#ifdef MSDOS
#include <io.h>
#endif

extern int parallel;

static char *delete_file_name[MAX_FILES];
static int   files = 0;
static FILE *Makefile_fp;

void InitMakeDeletefile()
{
    files = 0;

    return;
}

void StoreDeletefile( name )
     char *name;
{
    int i;


    if(parallel != 0) {
      if(streq(name,"MESH.PLN")) return;
    }


    if(files == MAX_FILES) {
	SystemWarning("Too many Temporary file(StoreDeletefile)");
	return;
    }
    for(i=0;i<files;i++) {
	if(streq(delete_file_name[i],name)) {
	    SystemWarning_s("Duplicated delete filename %s",name);
	    return;
	}
    }

    delete_file_name[files] = MakeStringCopy( name );
    files ++;

    return;
}

void DoDeletefile()
{
    int i;
    char com[BUFSIZ];

    for(i=0;i<files;i++ ) {
#ifdef MSDOS
	remove(delete_file_name[i]);
#else
	sprintf(com,"rm %s",delete_file_name[i]);
	system(com);
#endif

    }
    return;
}



