/*
 *   FEEL system   system.h
 *  
 *   FEEL system definition file
 *
 */

#include <stdio.h>

/*[yacc] */
/* extern int yylineno; */

#include "../feel_def/system.h"
extern char *MakeStringCopy();

extern void  Warning();
extern void  SystemError();
extern void  FatalError();

extern char  *pop();               /* direct read from YaccMain.c */
extern char  *PopString();
extern double PopDouble();
extern int    PopInt();

extern void   *FEEL_GetMemory();
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
extern int streq(char *,char *);
extern int strindex(char *,char *);

void ReverseDoubleArray(int n,double d[]);
void FEEL_FreeMemory(void *);

#define F77(x) fprintf(fp,x)
#define COM fprintf(fp,"*\n")
#define PUT fprintf
#define CR  fprintf(fp,"\n")
#define COM2 fprintf(fp,"*----------------------\n")
#define COM3 fprintf(fp,"*----------------------------------------------------------------------\n")



int get_mesh_name_type_by_name( char *);
void store_mesh_name( char * , int );
int extract_inner_edge_list( char *s , char *compos[]);


int get_freedom_by_element_name(char *);

int get_domain_etype_by_name(char *);

int is_feel_test_var(char *);
int is_feel_system_var(char *);

void register_user_func(char *);

void CloseEachOneFile(FILE *);

int streq(char *,char *);
int streq2(char *,char *);

void CloseFile(FILE *);
void MakeFORTsrc(char *);

int how_many_userfuncs();
void print_yylineno();
int what_dimension();
void tolower_buf(char *);


int how_many_int_vars();
int how_many_double_vars();
int how_many_const_vars();


void InitMakeMakefile();
void MakeMakefile();
void DoDeletefile();
void JustifyFORTfile();
void StoreMakefile( char *name , int file_type );
void CloseOneFile();
void make_feel_data_file_1D();
void make_feel_data_file_bamg();  
void make_feel_data_file();
void make_parallel_data(int parallel);
void make_solv_dat();
void make_feel_fort77_modulef();
void make_feel_fort77();


void init_cptime();
void init_data_number();  
void rep_time(char *);
void InitMakeDeletefile();
void get_user_info();
void pre_to_inf_init();
void feel_data_check(); 
void debug_start(); 
void init_scalar_term_convert();
void solve_dat_make_main();
void make_fem_varinfo();
void make_subdomain_info();
void set_solve_max_edatno( int );
void set_boundary_no();
void do_pre_to_inf();
void make_mesh_ctrl_data(); 
void rep_proc(char *);
void mfMakeMakefile();
int  current_edatno();


void comment1(FILE *);
void comment2(FILE *);
void comment_s(FILE *);

void real8(FILE *);

int how_many_open_data_files();
void CopyRight(FILE *);
void TimeStamp(FILE *);
void common_parameters(FILE *);
void CommonBlock(FILE *);

void WriteWinsiz(FILE *,int);

int get_feel_array_size();

void make_inp_node();    /* 節点読み込みプログラム生成 */
void make_inp_edat();    /* 要素データ読み込みプログラム生成 */
void make_inp_nodeset();    /* 節点集合データ読み込みプログラム生成 */

void make_inp_num();     /* 数値データ読み込みプログラム生成 */
void make_inp_ip();

int get_var_kind(char *);

int how_many_points();
int how_many_solves();


int how_many_avs_variables();
void put_nth_avs_feel_name_fp(FILE *fp,int i);
void main_declare_scalar(FILE *fp);

void file_write_open_fort77(FILE *fp);
