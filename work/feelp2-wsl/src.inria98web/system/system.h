/*
 *   FEEL system   system.h
 *  
 *   FEEL system definition file
 *
 */

#include <stdio.h>

/*[yacc] */
/* extern int yylineno; */


extern char *MakeStringCopy();

extern void  Warning();
extern void  SystemError();
extern void  FatalError();

extern char  *pop();               /* direct read from YaccMain.c */
extern char  *PopString();
extern double PopDouble();
extern int    PopInt();

extern char   *FEEL_GetMemory();
extern double *FEEL_GetMemory_double();

extern char   *term_convert();     /* 数式中の変数名を変換テーブルに従って
				      変換する */
extern char   *term_convert_scalar(); /* スカラー変数専用のterm_convert
					 これは、write,read文用に       */

extern FILE *OpenFileToWrite();
extern FILE *OpenFileToRead();

extern FILE *OpenPipeToRead();

extern char *get_nth_uniq_item();

/*[YaccExpression.c]*/

extern char *get_expression_string();
extern char **get_exp_identifiers();
extern char **get_exp_functions();


#define F77(x) fprintf(fp,x)
#define COM fprintf(fp,"*\n")
#define PUT fprintf
#define CR  fprintf(fp,"\n")
#define COM2 fprintf(fp,"*----------------------\n")
#define COM3 fprintf(fp,"*----------------------------------------------------------------------\n")


