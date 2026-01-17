/*
 *  File YaccMain.c
 *  
 *  Date      1991/12/24
 *  Modified  1992/08/10
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

int web_exec     = 0;
int avs_mesh_ref = 0;

int command_nodeset = 0;

/*-- Yacc/Lex variables --*/
extern int yylineno;

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
    if(argc != 14) {
      SystemAbort("feel parser argument ERROR");
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
	 ;
	/* change_feel_array_size(atoi(argv[5])); */
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



    if(status_no_delete) {
       int i;
       fprintf(stderr,"parser command : ");
       for(i=0;i<argc;i++) {
         fprintf(stderr,"%s ",argv[i]);
       }
       fprintf(stderr,"\n");
    }

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
