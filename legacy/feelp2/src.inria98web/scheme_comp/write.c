/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   write.c
 *      Date:   1993/06/28
 *   
 *   Purpose:   write文の処理
 *   Functions: 
 *              
 *              
 */

#include "../system/system.h"
#include "scheme_comp.h"


static int write_args = 0;

static int write_exprs = 0;
static Expression *write_expr[MAX_RW_ARGS];

static int   write_strings = 0;
static char *write_string[MAX_RW_ARGS];

static int   kind[MAX_RW_ARGS];
static int    file_io_no[MAX_SCHEMES];
static Write *fwrite_ptr_buf[MAX_SCHEMES];
static int   file_writes=0;


Write_parse_init()
{
    write_args = 0;
    write_exprs = 0;
    write_strings = 0;

    return;
}

File_Write_parse_init()
{
    write_args = 0;
    write_exprs = 0;
    write_strings = 0;

    return;
}


Write_st()
{
    int i;
    Write *write_struct;
    
    int *kind_save;
    Expression  *expr;
    char       **string;

    write_struct = (Write *)FEEL_GetMemory(sizeof(Write));

    kind_save = (int *)FEEL_GetMemory(sizeof(int) * write_args);
    if(write_exprs != 0) {
	expr      = (Expression *)FEEL_GetMemory(sizeof(Expression) * write_exprs);
    }
    
    if(write_strings != 0) {
	string    = (char **)FEEL_GetMemory(sizeof(char *) * write_strings);
    }

    for(i=0;i<write_args;i++) {
	*(kind_save + i ) = kind[i];
    }

    for(i=0;i<write_exprs;i++) {
	(expr+i)->expr = write_expr[i]->expr;
	(expr+i)->identifiers = write_expr[i]->identifiers;
	(expr+i)->identifier  = write_expr[i]->identifier;
	(expr+i)->functions = write_expr[i]->functions;
	(expr+i)->function = write_expr[i]->function;
    }

    for(i=0;i<write_strings;i++) {
	*(string+i) = write_string[i];
    }

    write_struct -> args     = write_args;
    write_struct -> yylineno = yylineno_info();
    write_struct -> string = string;
    write_struct -> kind   = kind_save;
    write_struct -> expr   = expr;
    
    store_scheme( WRITE , write_struct );

    return;
}


File_Write_st()
{
    int i;
    Write *write_struct;
    Write *write_ptr;
    
    int *kind_save;
    int find_flag;
    Expression  *expr;
    char       **string;

    write_struct = (Write *)FEEL_GetMemory(sizeof(Write));

    kind_save = (int *)FEEL_GetMemory(sizeof(int) * write_args);
    if(write_exprs != 0) {
	expr      = (Expression *)FEEL_GetMemory(sizeof(Expression) * write_exprs);
    }
    
    if(write_strings != 0) {
	string    = (char **)FEEL_GetMemory(sizeof(char *) * write_strings);
    }

    for(i=0;i<write_args;i++) {
	*(kind_save + i ) = kind[i];
    }

    for(i=0;i<write_exprs;i++) {
	(expr+i)->expr = write_expr[i]->expr;
	(expr+i)->identifiers = write_expr[i]->identifiers;
	(expr+i)->identifier  = write_expr[i]->identifier;
	(expr+i)->functions = write_expr[i]->functions;
	(expr+i)->function = write_expr[i]->function;
    }

    for(i=0;i<write_strings;i++) {
	*(string+i) = write_string[i];
    }

    write_struct -> filename = PopString();
    
    /* 同一のファイルへの出力が既に宣言してあるかどうか？ */
    find_flag = NO;
    for(i=0;i<file_writes;i++) {
	write_ptr = fwrite_ptr_buf[i];
	if(streq(write_ptr->filename,write_struct->filename))  {
	    find_flag = YES;
	    write_struct->file_io_no = write_ptr->file_io_no;
	    break;
	}
    }
    /* 同一のファイル宣言がなければ、ファイル番号を割り付ける */
    if(find_flag == NO) {
	write_struct -> file_io_no = get_data_file_number();
	file_io_no[file_writes]     = write_struct -> file_io_no;
	fwrite_ptr_buf[file_writes] = write_struct;
	file_writes++;
    }

    write_struct -> args     = write_args;
    write_struct -> yylineno = yylineno_info();
    write_struct -> string = string;
    write_struct -> kind   = kind_save;
    write_struct -> expr   = expr;
    
    store_scheme( FILE_WRITE , write_struct );

    return;
}

write_st_expression()
{
    
    if(write_args == MAX_RW_ARGS) {
	get_expr_structure();    /* ダミーread */
	SystemError_yy("Too many arguments in a write sentence.",yylineno_info());
	return;
    }
    
    write_expr[write_exprs] = get_expr_structure();

    kind[write_args] = EXPR;

    write_exprs++;
    write_args++;

    return;
}

write_st_string()
{
    if(write_args == MAX_RW_ARGS) {
	pop();
	SystemError_yy("Too many arguments in a write sentence.",yylineno_info());
	return;
    }
    
    write_string[write_strings] = PopString();
    
    kind[write_args] = STRING;
    
    write_strings++;
    write_args++;


    return;    
}

void file_write_open_fort77(fp)
     FILE *fp;
{
    int i;
    Write *write_ptr;

    for(i=0;i<file_writes;i++) {
	write_ptr = fwrite_ptr_buf[i];
	PUT(fp,"      open(unit=(io_tmp+%d),file=%s)\n",file_io_no[i],
	    write_ptr->filename);
    }
    COM;
}

    

