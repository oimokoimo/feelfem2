/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_solve_fort77.c
 *      Date:   1993/08/27
 *   
 *   Purpose:   solve文に対応するサブルーチン群を作成する
 *              メインプログラム
 *   Functions: 
 *              
 *              LISPプログラム用のファイル作成
 *
 *              solve文、要素関連subroutineに対するデータ作成
 *                COMMONブロックなどの定義
 *              
 *              solve文制御メインプログラム 作成
 *              各要素プログラム            作成
 *              
 *              
 *   Modified: 1996/02/21  並列処理の付加           
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"


void make_solve_fort77()
{
    int i,j;
    int solves;
    int dconds,nconds;
    int no;

    Solve           *solve_ptr;
    SolveElement    *solve_elem_ptr;
    SolveFORT77     *solve77_ptr;
    
    DirichletData   *dcond_ptr,**dcond_ptrptr;
    NeumannData     *ncond_ptr,**ncond_ptrptr;

    solves = how_many_solves();

    if(solves == 0) {
	SystemWarning("solve文が指定されていません");
	return;    
    }

    /*==========================*/
    /* LISPプログラム作成、実行 */
    /*==========================*/
    FDBGWRT(stderr,"LISP procedures start ...");

    rep_proc("make_solve_lisp");
    make_solve_lisp();

    FDBGWRT(stderr,"done\n");

    /* make_solve_lisp() 内で確定するデータ要素
       
       ElementFORT77->quad_methods   積分法の数  を設定

     */

    /*==========================*/
    /* subroutine作成データ生成 */
    /*==========================*/

    rep_proc("make_solve77_data");
    make_solve77_data(); 

                                      /* 1: 数値積分用COMMONブロック作成
				       */
    /*==========================*/
    /* 実際のsubroutine群作成   */
    /*==========================*/
    for(i=0;i<solves;i++) {
        rep_proc_no("make solve routine",i+1);

	solve_ptr = get_nth_solve_ptr(i);

	solve77_ptr = solve_ptr->solve77_ptr;
	

        /* feelfem */
        solveStructWriter( solve_ptr, solve77_ptr);

	/* 次の関数は各solve文を制御するFORTRANコードを生成する
	   (前回作ったやつは、そこから要素プログラムを生成していた) */

	/* 連立一次方程式解法別に呼び出し */
	switch(solve_ptr -> linear_method) {
	  case SKYLINE:
	    if(solve_ptr -> nonlinear_flag == NO) {
		/*  線形問題  */
		make_solve_ctrl77_skyline( solve_ptr , solve77_ptr );
	    }
	    else {
		/* 非線形問題 */
		make_solve_ctrl77_sk_nonlinear(solve_ptr , solve77_ptr );
	    }
	    break;

	  case MPPSCG:
	    if(solve_ptr-> nonlinear_flag == NO) {
		/*  線形問題  */
		make_solve_ctrl77_MPPSCG( solve_ptr , solve77_ptr ,solve_ptr->
				     linear_method);
	    }
	    else {
		/* 非線形問題 */
/*		make_solve_ctrl77_MPPSCG_nonlinear(solve_ptr , solve77_ptr ,
					       solve_ptr->linear_method);
*/
		fprintf(stderr,"MPPSCG 非線形はまだだよ(ctrl77_non)");
	    }
	    break;
		

	  case PCGS:
	  case PBCG:
	    if(solve_ptr -> nonlinear_flag == NO) {
		/*  線形問題  */
		make_solve_ctrl77_CG( solve_ptr , solve77_ptr ,solve_ptr->
				     linear_method);
	    }
	    else {
		/* 非線形問題 */
		make_solve_ctrl77_CG_nonlinear(solve_ptr , solve77_ptr ,
					       solve_ptr->linear_method);
	    }
	    break;

	  default:
	    SystemWarning("SKYLINE以外は未対応(make_solve_ctrl77 call");
	    break;
	}

	/*============================*/
	/* 境界条件処理プログラム作成 */
	/*============================*/
	dconds       = solve_ptr -> d_conditions;
	dcond_ptrptr = solve_ptr -> d_dat;
	
	nconds       = solve_ptr -> n_conditions;
	ncond_ptrptr = solve_ptr -> n_dat;

	for(j=0;j<dconds;j++) {
	  rep_proc_no("make solve dcond No.",j+1);
	    dcond_ptr = *(dcond_ptrptr + j);
	    dcondgen(i+1,j+1,dcond_ptr);
	    switch( solve_ptr -> linear_method) {

	      case SKYLINE:
		
		if(solve_ptr->nonlinear_flag == NO) {
		    /* 線形問題   */
		    make_dcond_skyline(i+1,j+1,dcond_ptr);
		}
		else {
		    /* 非線形問題 */
		    make_dcond_skyline_nonlinear(i+1,j+1,dcond_ptr);
		}
		break;

	      case MPPSCG:
		if(solve_ptr->nonlinear_flag == NO) {
		    /* 線形問題   */
		    make_dcond_MPPSCG(i+1,j+1,dcond_ptr);
		}
		else {
		    /* 非線形問題 */
		    /* make_dcond_MPPSCG_nonlinear(i+1,j+1,dcond_ptr); */
		    fprintf(stderr,"MPPSCG 非線形はまだだよ(dcond_non)");
		}
		break;

	      case PCGS:
	      case PBCG:
		
		if(solve_ptr->nonlinear_flag == NO) {
		    /* 線形問題   */
		    make_dcond_CG(i+1,j+1,dcond_ptr,solve_ptr->linear_method);
		}
		else {
		    /* 非線形問題 */
		    make_dcond_CG_nonlinear(i+1,j+1,dcond_ptr,
						 solve_ptr->linear_method);
		}
		break;


	      default:
		SystemWarning("指定の数値解法は対応していません(make_dcond)");
		break;
	    }
	}

	for(j=0;j<nconds;j++) {

	  rep_proc_no("make solve ncond No.",j+1);

	    ncond_ptr = *(ncond_ptrptr + j);
 	    ncondgen(i+1,j+1,solve_ptr,ncond_ptr);
	    switch( solve_ptr -> linear_method) {

	      case SKYLINE:
		make_ncond_skyline(i+1,j+1,solve_ptr,ncond_ptr);
		break;

	      case MPPSCG:
		make_ncond_MPPSCG(i+1,j+1,solve_ptr,ncond_ptr);
		break;

	      case PCGS:
	      case PBCG:
		make_ncond_CG(i+1,j+1,solve_ptr,ncond_ptr,
			      solve_ptr->linear_method);
		break;

	      default:
		SystemWarning("指定の線形解法は対応していません(make_ncond)");
		break;
	    }
	}
	
	/*=====================*/
	/* 各要素ルーチン作成  */
	/*=====================*/

	for(j=0;j<solve_ptr->solve_elements;j++) {
	    
	    /* SolveElement構造体を得る */
	    solve_elem_ptr = *(solve_ptr->solve_elem_dat + j);

	    no = solve_elem_ptr -> element_no;

	    /* 各要素内小行列計算プログラムの呼び出し */
	    switch( solve_ptr -> linear_method) {
	      case SKYLINE:

	        elemgen(no,solve_elem_ptr);

		if(solve_ptr->nonlinear_flag == NO) {
		    /* 線形問題の場合 */
		    elem_fort77_main_skyline( no , solve_elem_ptr );
		}
		else {
		    /* 非線形問題の要素行列作成ルーチンcall */
		    elem_fort77_main_sk_nonlinear( no , solve_elem_ptr );
		}
		break;

	      case MPPSCG:
		if(solve_ptr->nonlinear_flag == NO) {
		    /* 線形問題   */
		    elem_fort77_main_MPPSCG(no, solve_elem_ptr);
		}
		else {
		/* 非線形問題 */
	        /* elem_fort77_main_MPPSCG_nonlinear(no, solve_elem_ptr); */
		    fprintf(stderr,"MPPSCG 非線形はまだだよ(elem_fort77_MPP)");
		}
		break;


	      case PCGS:
	      case PBCG:
		if(solve_ptr->nonlinear_flag == NO) {
		    /* 線形問題の場合 */
		    elem_fort77_main_CG( no , solve_elem_ptr );
		}
		else {
		    /* 非線形問題の要素行列作成ルーチンcall */
		    elem_fort77_main_CG_nonlinear( no , solve_elem_ptr );
		}
		break;

		
	      default:
		SystemWarning("指定の数値解法には対応していません");
		break;
	    }

	    /* esetルーチンの作成(解析的積分法のみの場合は作成しない) */
	    make_eset( solve_elem_ptr -> solve_no , no ,solve_elem_ptr );

	    /* ecalルーチンの作成(解析的積分法のみの場合は作成しない) */
	    /* 非線形分岐は、make_ecal関数内で行う                    */
	    make_ecal( solve_elem_ptr -> solve_no , no ,solve_elem_ptr );

	    /* edevルーチンの作成(連立では無い時には考えましょう      */
	    if(solve_ptr->nonlinear_flag == NO) {
		/* 線形問題時 */
		make_edev( solve_elem_ptr -> solve_no , no ,solve_elem_ptr );

	    }
	    else {
		/* 非線形問題時の逐次近似値更新処理 */
		make_nedev( solve_elem_ptr -> solve_no , no ,
			    solve_ptr, solve_elem_ptr         );
	    }
	}
    }
    rep_proc("End of make_solve_fort77");
    return;
}
