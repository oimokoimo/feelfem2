/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_solve_lisp.c
 *      Date:   1993/10/25
 *   
 *   Purpose:   LISPプログラム作成のメインルーチン
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"

extern char *feel_dir;

void make_solve_lisp()
{
    FILE *lisp_program;

    int i,j;
    int solves;
    int solve_elements;

    Solve         *solve_ptr;
    SolveElement **solve_element_ptrptr;
    SolveElement  *solve_element_ptr;
    SolveFORT77   *solve_f77_ptr;
    ElementFORT77 *elem_f77_ptr;

    int nconds;
    NeumannData **n_ptrptr,*n_ptr;

    /* LISPプログラムオープン */
    
    if(status_lisp_debug) {
	lisp_debug_fp = OpenFileToWrite(LISP_EXEC_FILE); 
    }

#ifdef MSDOS
    lisp_program = fopen(DOS_LISP_TMP,"w");
#else
    lisp_program = popen(LISP_COMMAND,"w");   
#endif

    /*======================*/
    /* ファイルから読み込む */
    /*======================*/
    /*  read_LISP_procedure(lisp_program); */

    /*==============*/
    /* 直接書き込む */ 
    /*==============*/
    lisp_package( lisp_program ) ;


    solves = how_many_solves();
    
    /*========================*/
    /* 連立一次方程式系の処理 */
    /*========================*/
    for(i=0;i<solves;i++) {
	solve_ptr            = get_nth_solve_ptr(i);
	solve_elements       = solve_ptr -> solve_elements;
	solve_element_ptrptr = solve_ptr -> solve_elem_dat;

	LISP_SEND(lisp_program,";==================================================\n");
	LISP_SEND_d(lisp_program,"; solve文 No.%d\n",i+1);
	LISP_SEND(lisp_program,";==================================================\n");


	for(j=0;j<solve_elements;j++) {
	    LISP_SEND(lisp_program,";---------------------\n");
	    LISP_SEND_dd(lisp_program,"; SolveElement %d-%d\n",i+1,j+1);
	    LISP_SEND(lisp_program,";---------------------\n");

	    solve_element_ptr = *(solve_element_ptrptr + j);
	    make_elem_lisp( lisp_program , solve_ptr, solve_element_ptr );

	}
    }
    /*========================*/
    /* ノイマン条件設定の為   */
    /*========================*/
    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr(i);
	solve_element_ptrptr = solve_ptr -> solve_elem_dat;	

	n_ptrptr = solve_ptr -> n_dat;
	nconds   = solve_ptr -> n_conditions;
	
	for(j=0;j<nconds;j++) {
	    LISP_SEND(lisp_program,";--------------------\n");
	    LISP_SEND_dd(lisp_program,"; Neumann cond %d-%d\n",i+1,j+1);
	    LISP_SEND(lisp_program,";--------------------\n");
	    
	    /* ここで境界に対応するsolve_elementを捜し出す */
	    if(solve_ptr->solve_elements != 1) {
		SystemAbort("複数domainはncond設定に対応せず@make_solve_lisp");
	    }

	    solve_element_ptr = *(solve_element_ptrptr + 0 );
	    /*                                          ^^^ */

	    n_ptr = *(n_ptrptr + j);


	    make_ncond_lisp(lisp_program,solve_ptr,solve_element_ptr,
			    n_ptr , i+1,j+1 );
	}
    }


    /* LISP プログラム実行 */

    if(status_lisp_debug) {
	CloseFile(lisp_debug_fp);
	fprintf(stderr,"LISP プログラムを出力しました(debug)\n");
    }

#ifdef MSDOS
    fclose(lisp_program);
    { char buf[BUFSIZ],buf2[BUFSIZ];
      sprintf(buf2,DOS_LISP_COMMAND,feel_dir,feel_dir);
      sprintf(buf,"%s <%s >NUL",buf2,DOS_LISP_TMP);
      system(buf);
      system("DEL $lisp.l");
    }

#else

    pclose(lisp_program);

#endif


    return;
}

