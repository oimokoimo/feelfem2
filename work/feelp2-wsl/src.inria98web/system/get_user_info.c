/*
 * FEEL system Prototype Version 2
 * 
 * File     get_user_info.c
 * Made     1992/09/25
 * Modified 1998/09/17  (Windows32 extension)
 * Modified 1999/03/31  (complete getenv, but stopping...)
 * Version  0.0
 *
 * Purpose: get user information
 *
 */

#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "system.h"

#ifdef MSDOS
#include <time.h>
#endif

extern char *feel_date;
extern char *feel_user;
extern char *feel_dir;
extern char *AVSExpress_dir;
extern char *current_dir;
extern char *MakeStringCopy();

void get_user_info()
{
  char buf[BUFSIZ];
  
#ifdef MSDOS
    time_t ltime;
    time(&ltime);

    feel_date = MakeStringCopy( ctime(&ltime));
    *(feel_date+strlen(feel_date)-1) = '\0';

    feel_user = getenv("USERNAME");
    if(feel_user == NULL) feel_user = MakeStringCopy("win32");

    feel_dir  = getenv("FEELDIR");
    if(feel_dir == NULL) feel_dir = DEFAULT_DOS_FEEL_DIR;

    AVSExpress_dir = getenv("XP_ROOT");
    if(AVSExpress_dir == NULL) AVSExpress_dir = DEFAULT_DOS_EXPRESS_DIR;

    if(_getcwd(buf,BUFSIZ) == NULL) {
      current_dir == DEFAULT_CURRENT_DIR;
    }
    else {
      current_dir = MakeStringCopy(buf);
    }

#else
    char *get_com_from_pipe();
    char *get_user_name();

    feel_date = get_com_from_pipe("date");
    /*    feel_dir  = getenv("FEELDIR");       */      /* This is for LISP */
    *(feel_date+strlen(feel_date)-1) = '\0';

    if(web_mode) {
	feel_user = "FEEL WEB";
    }
    else {
	feel_user = get_user_name();
    }


    if(web_mode) {
      current_dir == DEFAULT_CURRENT_DIR;
      if(MACHINE==Windows) {
	AVSExpress_dir = DEFAULT_DOS_EXPRESS_DIR;
      }
      else {
	AVSExpress_dir = DEFAULT_UNIX_EXPRESS_DIR;
      }
    }
    else {

      AVSExpress_dir = getenv("XP_ROOT");
      if(AVSExpress_dir == NULL) AVSExpress_dir = DEFAULT_UNIX_EXPRESS_DIR;

      if(getcwd(buf,BUFSIZ) == NULL) {
	current_dir == DEFAULT_CURRENT_DIR;
      }
      else {
	current_dir = MakeStringCopy(buf);
      }
    }  /* end of web mode judge for AVS setting */


    return;

#endif
    
}

#ifdef MSDOS

/* MS-DOS does not support full pipe functionality */

#else

char *get_com_from_pipe(command)
     char *command;
{
    FILE *pfp;
    char buf[BUFSIZ];

    pfp = popen(command,"r");
    if(pfp == NULL) {
	SystemAbort("cannot open pipe(get_com_from_pipe).");
    }
    
    fgets(buf,sizeof buf,pfp);
    pclose(pfp);
    
    return(MakeStringCopy(buf));
}

#endif


#ifdef MSDOS
 
  /* MSDOS user name define in former routine */

#else

char *get_user_name()
{
    int uid,i;
    char buf[BUFSIZ];
    char name[38];
    char uid_buf[10];
    char *cp,*np;
    FILE *fp;
    char *MakeStringCopy();

    uid = getuid();

    fp = fopen("/etc/passwd","r");

    if(fp == NULL) {
	SystemAbort("cannot read /etc/passwd(get_user_info).");
    }
    
    np = name;
    *np = '\0';

    while(fgets(buf,sizeof buf,fp)) {
	cp = buf;
	i  = 0;

	while(i < 2) {
	    if(*cp == ':') i++;
	    cp++;
	}

	np = uid_buf;
	while(*cp != ':') {
	    *np = *cp;
	    np++;
	    cp++;
	}
	*np = '\0';
	
	if(atoi(uid_buf) != uid) continue;

	cp++;
	while(*cp != ':') cp++;

	cp++;
	np = name;

	while(*cp != ':') {
	    *np = *cp;
	    cp++;
	    np++;
	}
	*np = '\0';

	break;
    }

    fclose(fp);
	    
    return(MakeStringCopy(name));
}
#endif






