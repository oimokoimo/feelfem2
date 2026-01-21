/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   pre_to_inf.c
 *      Date:   1993/07/05
 *   
 *   Purpose:   前置記法の数式をFORTRAN形式に変換する。データに
 *              整数定数を含んではいけない。
 *              
 */

#include <stdio.h>
#include "../feel_def/feel_def.h"
#include "../system/system.h"
extern FILE *popen(const char *command, const char *type);
extern int   pclose(FILE *stream);

extern char *feel_dir;         /* for win32 */

static int expressions = 0;
char    *expr[MAX_EXPRESSIONS];
char   **adrs[MAX_EXPRESSIONS];

void pre_to_inf_init()
{
    expressions = 0;
    return;
}


/* 数式をスタックに積む */

void pre_to_inf_push(exp,save_adr)
     char *exp;
     char **save_adr;
{

    if(mesh_only == YES) return;  /* 15/oct/98 (inria98)*/


    if(expressions == MAX_EXPRESSIONS) {
	SystemAbort("LISPプログラムに引き渡す数式の数が多すぎます。(pre_to_inf_push)\n");
    }


    expr[expressions] = exp;
    adrs[expressions] = save_adr;
    
    expressions++;

    return;
}

/* 実際に変換を行う */
void do_pre_to_inf()
{
    FILE *fp;
    int i;
    char buf[BUFSIZ];


    if(expressions == 0) return; /* なにも数式が無い！？ */

    if(mesh_only   == YES) return;  /* 15/oct/98 (inria98) may not come here */

#ifdef MSDOS
    fp = fopen(DOS_LISP_TMP,"w");
#else
    fp = popen(LISP_COMMAND,"w");
#endif

    if(fp == NULL) {
	SystemAbort("Cannot open lisp pipe.(do_pre_to_inf)\n");
    }

    lisp_exp_print( fp );

    fprintf(fp,"(setq fp (open \"%s\" :direction :output) )\n",LISP_OUT_FILE);

    for(i=0;i<expressions;i++) {
	fprintf(fp,"(exp-print-fp '%s fp)\n",expr[i]);
    }

    fprintf(fp,"(close fp)\n");

#ifdef MSDOS
    fclose(fp);
    { char buf2[BUFSIZ];
      sprintf(buf2,DOS_LISP_COMMAND,feel_dir,feel_dir);
      sprintf(buf,"%s <%s >NUL",buf2,DOS_LISP_TMP);
    }
    system(buf);
    system("DEL $lisp.l");
#else
    pclose(fp);
#endif

    fp =OpenFileToRead(LISP_OUT_FILE);
    StoreDeletefile( LISP_OUT_FILE );     

    for(i=0;i<expressions;i++) {
	char *cp;
	fgets(buf,sizeof(buf),fp);

	cp =  MakeStringCopy(buf);
	*(adrs[i]) = cp ; 
	*(cp+strlen(cp)-1) = '\0';

    }
    fclose(fp);

    sprintf(buf,"rm %s",LISP_OUT_FILE);     /* LISPの出力ファイルを削除 */
/*    system(buf); */

    return;
}
