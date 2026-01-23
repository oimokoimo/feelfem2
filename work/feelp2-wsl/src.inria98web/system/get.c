/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get.c
 *      Date:   1993/11/12
 *   
 *   Purpose:   ファイルからの入出力  一行単位の入出力 
 *              
 *   Functions: geti_file( fp )  行に数字が書いてあるダケの仮定で数値を返す
 *              fgets_file(...)  fgetsと同じ、エラー処理を行う,呼元関数名も渡す
 */
#include <stdio.h>
#include <stdlib.h>
#include "../feel_def/feel_msg.h"

int geti_file( fp )
     FILE *fp;
{
    int num;
    char buf[BUFSIZ];

    if(!fgets(buf,sizeof(buf),fp)) {
	SystemAbort("Read File failed.(geti_file)");
    }
    return(atoi(buf));
}

void fgets_file( buf ,size , fp , from)
     char *buf;
     int   size;
     FILE *fp;
     char *from;
{
    if(!fgets(buf,size,fp)) {
	char tmpbuf[BUFSIZ];
	sprintf(tmpbuf,"関数%sにてファイルの読み取りに失敗",from);
	SystemAbort(tmpbuf);
    }
    return;
}



