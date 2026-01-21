/*
 *  File YaccMain.c
 *  
 *  Date      1991/12/24
 *  Modified  1992/08/10
 *  Modified  1998/09/03   add avs_mode
 *  Modified  1998/11/02   Modulef/Modulef Module mode
 *
 *  Version   0.0
 *
 *  PURPOSE:  This is the source file of supplimental fuctions
 *            for LEX/YACC program.
 *
 *  FUNCTIONS:
 *
 *           init      Initialize extern variables
 *           yyerror   temporary error display routine
 *           push      This program pushes the identifiers to stack
 *           
 */


#include <stdio.h>

#include <stdlib.h>  /* modernize 2026/01/21 */
#include <string.h>  /* modernize 2026/01/21 */


/*-- Extern variables used in yacc program --*/
int parameters  = 0;   /* to count pushed strings */
int settings    = 0;  
int expressions = 0;   /* to count pushed strings */
int inner_parameters = 0; /* to count inner points */
int condition_type  = 0;
char *if_left_ptr;    /* expression ><= expression の為 */

int parallel    = 0;   /* for parallel */
int parallel_npe= 0;   /* for parallel */

int mesh_only   = 0;
int feel_dim    = 2;   /* default dimension is 2 */
int one_file    = 1;   /* 1 means YES            */
int recursive_mesh_div = 0;  /* recursive mesh division */
int noediv_flag = 0;   /* ecalルーチン内でソースを分割しない */
int subdomain_flag = 0;/* subdomain文を使ったかどうか        */
int skyline_flag = 0;/* skyline methodを使ったかどうか        */

int english_mesg = 0;
int web_mode     = 0;
int bamg_mode    = 0;  /* INRIA BANG mesh generation */

int web_check    = 0;  /* web semantics check */
int web_exec     = 0;  /* web execution (winsiz = 100, nodes = 100, no goto) */

int avs_mode     = 0;  /* AVS mode  (98/09/03) */
int avs_mesh_ref = 0;  /* for tri, rect , set in region statement */

int avs_64bit       ;  /* AVS 64bit for sg6 memory allocation in feelavsout */


int modulef_mode   = 0;  /* Modulef Mode        */
int mf_module_mode = 0;  /* Modulef Module mode */

int command_nodeset = 0;    /* Super defined node number =0 use pde file */

char *pde_src_name  = "Wow???";  /* pde source file name */


/*-- Yacc/Lex variables --*/
int yylineno;     /* 99/12/14  here extern deleted !!! oimokoimo */

/*-- DEFINES --*/

#define  MAX_STACK  100         /* stack for strings */

static int level = 0;
static char *terms[MAX_STACK];


int debug_mode =  0;     /* CAUTION   0 means NO */
int status_lisp_debug =  0;
int status_no_delete  =  0;


int MACHINE;                   /* 計算機フラグ */
int LIMIT_FILE;                /* ライブラリファイルを作らない */

FILE *lisp_debug_fp;
/*-- Yacc/Lex Main routine --*/
main(argc,argv)
int argc;
char *argv[];
{ 
    if(argc != 21) {
      SystemAbort("feel parser argument ERROR(feel and feel.parse mismatch)");
    }

    /* 第一引き数 */
    status_lisp_debug = atoi(argv[1]);

    /* 第２引き数 */
    status_no_delete  = atoi(argv[2]);

    /* 第三引き数 */
    MACHINE           = atoi(argv[3]);

    /* 第４引き数 */
    LIMIT_FILE        = atoi(argv[4]);
    
    /* 第５引き数 (配列FEELの大きさ) */
    if(atoi(argv[5]) > 0) {
	change_feel_array_size(atoi(argv[5]));
    }

    /* 第６引き数(メッシュのみの生成(feel_dat)) */
    if(atoi(argv[6]) == 1) {
	mesh_only = 1;
    }

    /* dai 7 hikisuu( parallel option ) */
    /* 0 means scalar processor */
    parallel = atoi(argv[7]);
    {
	int para;
	para = parallel;
	parallel_npe  = 1;
	while(para)  {
	    parallel_npe = parallel_npe * 2;
	    para--;
	}
    }

    /* dai 8 hikisuu( one source file option ) */
    one_file = atoi(argv[8]);

    /* 第９引き数(メッシュ再分割数) */
    recursive_mesh_div = atoi(argv[9]);


    /* 第１０引数(ecalルーチンソース非分割フラグ */
    noediv_flag = atoi(argv[10]);

    /* dai 11 hikisuu( English Error Message )   */
    english_mesg = atoi(argv[11]);

    /* 第１２引数(Web生成モード) */
    web_mode     = atoi(argv[12]);

    /* No. 13 Bamg option for mesh generation by bamg */
    bamg_mode    = atoi(argv[13]);

    /* No. 14 web check mode */
    web_check    = atoi(argv[14]);

    /* No. 15 web execute mode  */
    web_exec     = atoi(argv[15]);

    /* No. 16 modulef mode */
    modulef_mode = atoi(argv[16]);
    
    /* No. 17 modulef module mode */
    mf_module_mode = atoi(argv[17]);

    if(mf_module_mode == 1) { modulef_mode = 1; } 


    /* No. 18 nodeset (super defined node number) */
    command_nodeset = atoi(argv[18]);


    /* No. 19 PDE file name (Assumed only one 99/03/15) */
    pde_src_name = argv[19];

    if(status_no_delete) {
       int i;
       fprintf(stderr,"parser command : ");
       for(i=0;i<argc;i++) {
         fprintf(stderr,"%s ",argv[i]);
       }
       fprintf(stderr,"\n");
    }

    /* No. 20 avs_64bit mode set */
    avs_64bit = atoi(argv[20]);

    init();
    yyparse();

}

/*-- Initialize Routine --*/
init() {
    level = 0;
    cell_init();   /* list structure initialize for expression LIST */
}


/*-- Error routine --*/
yyerror(s)
char *s;
{
    fprintf(stderr,"Line [%d] ",yylineno);
    fputs(s,stderr);putc('\n',stderr);

   /*  system_error(" "); */
}

print_yylineno()
{
    fprintf(stderr,"Line %d:",yylineno);
    return;
}

int yylineno_info()       /* ソースの現在位置を返す関数 */
{
    return(yylineno);
}





push(s)
char *s;
{
    int len;
    
    len = strlen(s);
    terms[level] = (char *)malloc(len + 1);
    strcpy(terms[level],s);
    level++;
}

char *pop()
{
    static char buf[BUFSIZ];
    
    if(level == 0) {
	FatalError("YACC POP ERROR");
    }
    
    level--;
    strcpy(buf,terms[level]);
    free(terms[level]);
    return(buf);
}


/*-- special processing for inner parameters --*/
pop_push_inner_points(inner_parameters) 
     int inner_parameters;
{
    int i,len;
    char *cp,*poped;
    static char buf[BUFSIZ];

    cp = buf;
    sprintf(cp,"[");
    cp++;


    if(inner_parameters <= 0) {
	FatalError("inner_parameter error(YACC)");
    }
	
    for(i=0;i<inner_parameters;i++) {
	poped = pop();
	len   = strlen(poped);
	sprintf(cp,poped);
	cp+= len;
	if(i != inner_parameters-1) {
	    sprintf(cp,",");
	    cp++;   
	}
    }
    sprintf(cp,"]%c",'\0');
    push(buf);

    return;
}
