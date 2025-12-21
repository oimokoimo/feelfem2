#include <stdio.h>

#include "FEM_FORT77.h"

#define ONE_LINE  72

static char src[100];
static char buf[100];
static int  len = 0;

setF77( fp , word )
     FILE *fp;
     char *word;
{
    if(len+strlen(word)+1 >= ONE_LINE) {
	PUT(fp,"%s\n",src);
	len = 6;
	sprintf(src,"     &");
	sprintf(src+len,"%s",word);
	len = len + strlen(word);
    }
    else {
	sprintf(src+len,"%s",word);
	len = len + strlen(word);
    }
    return;
}

setF77sd(fp,string,num)
     FILE *fp;
     char *string;
     int   num;
{
    sprintf(buf,"%s%d",string,num);
    setF77(fp,buf);
    return;
}

setF77d(fp,num)
     FILE *fp;
     int   num;
{
    sprintf(buf,"%d",num);
    setF77(fp,buf);
    return;
}
    
setF77string(fp,s)
     FILE *fp;
     char *s;
{
    char buf2[3];
    while(*s) {
	sprintf(buf2,"%c%c",*s,'\0');
	setF77(fp,buf2);
	s++;
    }
    return;
}


putF77( fp )
     FILE *fp;
{
    PUT(fp,"%s\n",src);
    len = 0;
    src[0] = '\0';
    return;
}
