/*
 *   FEEL system   SystemMessage.c
 *  
 *   System Message write routine
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"

static int warnings = 0;
static int errors   = 0;

/* #define STRESS  if(!web_mode)fprintf(stderr,"%c[5m",27)
   #define NORMAL  if(!web_mode)fprintf(stderr,"%c[0m",27) */

void SystemStderr( s )             /* 標準エラー出力に送るだけ */
     char *s;
{
    fprintf(stderr,"%s",s);
    return;
}

void SystemWarning( s )
     char *s;
{
    if(s == NULL) {          /* メッセージがNULLの場合カウントだけ */
	warnings ++;
	return;
    }

    STRESS;
    fprintf(stderr,"FEEL warning  ");
    fprintf(stderr,"%s\n",s);
    NORMAL;
    warnings ++;
    return;
}

void SystemWarning_yy( s  ,lineno)
     char *s;
     int lineno;
{
    if(s == NULL) {          /* メッセージがNULLの場合カウントだけ */
	warnings ++;
	return;
    }

    STRESS;
    fprintf(stderr,"FEEL warning (line %d)  ",lineno);
    fprintf(stderr,"%s\n",s);
    NORMAL;
    warnings ++;
    return;
}

void SystemWarning_d( s , d)
     char *s;
     int d;
{
    STRESS;
    fprintf(stderr,"FEEL warning  ");
    fprintf(stderr,s,d);
    fprintf(stderr,"\n");
    NORMAL;
    warnings ++;
    return;
}    

void SystemWarning_s( s , s2)
     char *s,*s2;
{
    STRESS;
    fprintf(stderr,"FEEL warning  ");
    fprintf(stderr,s,s2);
    fprintf(stderr,"\n");
    NORMAL;
    warnings ++;
    return;
}    

void SystemWarning_ss( s , s2 ,s3)
     char *s,*s2,*s3;
{
    STRESS;
    fprintf(stderr,"FEEL warning  ");
    fprintf(stderr,s,s2,s3);
    fprintf(stderr,"\n");
    NORMAL;
    warnings ++;
    return;
}    


void SystemParseWarning( s )      /* feel言語の構文解析中のワーニング処理 */
     char *s;
{

    STRESS;
    fprintf(stderr,"FEEL warning  ");
    print_yylineno(); 
    fprintf(stderr,"%s\n",s);
    NORMAL;
    warnings ++;
    return;
}


void SystemError( s )
     char *s;
{
    STRESS;
    fprintf(stderr,"FEEL error : ");
    fprintf(stderr,"%s\n",s);
    NORMAL;
    errors++;
    return;
}

void SystemError_yy( s ,lineno)
     char *s;
     int lineno;
{
    STRESS;
    fprintf(stderr,"FEEL error (line %d)  ",lineno);
    fprintf(stderr,"%s\n",s);
    NORMAL;
    errors++;
    return;
}

void SystemError_yy_s( s , arg1 ,lineno)
     char *s,*arg1;
     int lineno;
{
    STRESS;
    fprintf(stderr,"FEEL error (line %d)  ",lineno);
    fprintf(stderr,s,arg1);
    fprintf(stderr,"\n");
    NORMAL;
    errors++;
    return;
}

void SystemError_yy_ss( s , arg1 , arg2 ,lineno)
     char *s,*arg1;
     int lineno;
{
    STRESS;
    fprintf(stderr,"FEEL error (line %d)  ",lineno);
    fprintf(stderr,s,arg1,arg2);
    fprintf(stderr,"\n");
    NORMAL;
    errors++;
    return;
}

void SystemError_s( s , s2)
     char *s,*s2;
{
    STRESS;
    fprintf(stderr,"FEEL error : ");
    fprintf(stderr,s,s2);
    fprintf(stderr,"\n");
    NORMAL;
    errors++;
    return;
}    

void SystemError_sn( s , s2 , n)
     char *s,*s2;
     int   n;
{
    STRESS;
    fprintf(stderr,"FEEL error : ");
    fprintf(stderr,s,s2,n);
    fprintf(stderr,"\n");
    NORMAL;
    errors++;
    return;
}    

void SystemError_ss( s , s2 , s3)
     char *s,*s2,*s3;
{
    STRESS;
    fprintf(stderr,"FEEL error : ");
    fprintf(stderr,s,s2,s3);
    fprintf(stderr,"\n");
    NORMAL;
    errors++;
    return;
}    



void FatalError( s )
     char *s;
{
    STRESS;
    fprintf(stderr,"FEEL Fatal Error %s\n",s);
    fprintf(stderr,"ABORT\n");
    NORMAL;
    exit(1);
}

void SystemAbort( s )
     char *s;
{
    fprintf(stderr,"FEEL Fatal Error: %s\n",s);
    fprintf(stderr,"ABORT\n");
    exit(1);
}

void SystemAbort_s( s ,s2 )
     char *s,*s2;
{
    fprintf(stderr,"FEEL Fatal Error: ");
    fprintf(stderr,s,s2);
    fprintf(stderr," ABORT\n");
    exit(1);
}


int how_many_errors()
{
    return(errors);
}

int how_many_warnings()
{
    return(warnings);
}



void prt_errors_message()
{
    STRESS;
    fprintf(stderr,"%d FEEL Error(s)\n",errors);
    NORMAL;
    return;
}



void prt_warnings_message()
{
    STRESS;
    fprintf(stderr,"%d FEEL Warning(s)\n",warnings);
    NORMAL;
    return;
}









