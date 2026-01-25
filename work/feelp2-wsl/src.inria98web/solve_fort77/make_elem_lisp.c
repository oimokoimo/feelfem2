/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_elem_lisp.c
 *      Date:   1993/10/25
 *   
 *   Purpose:   要素小行列プログラム作成LISPコード生成
 *              
 *              この関数内で、SolveElementに共通なLISPシンボルをsetqする
 *              
 *              *test-funcs*
 *              *coff-vect*
 *              *eval-vars*
 *              *eval-vars* の各シンボルへのsetq
 *              *shape-funcs*
 *              
 *              
 *   
 *              
 *              
 *              
 *              
 *  注意 ａ : 実際のLISPプログラムの実行は、各積分法単位に実行される
 *            ここで割り付けたLISP変数は共通に使う
 *
 *  注意 ｂ : この関数内でElementFORT77構造体の積分法に関する集計を実行
 *            している
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"
#include "../solve_comp/solve_comp.h"
#include "../quadrature/quadrature.h"

#include "solve_fort77_funcs.h"

void make_elem_lisp( fp , solve_ptr , solve_element_ptr)

     FILE         *fp;
     Solve        *solve_ptr;
     SolveElement *solve_element_ptr;
{
    int i,j;

    int solve_no;   /* solve文番号 */
    int elem_no;    /* elem文番号       これらはFORTRAN作成時に利用 */
    
    int unknowns;
    int equations;
    int terms;

    int type;  /* DIFFEQ,WEAKEQ,FUNCTIONAL */

    int quad_methods;  
    int *quad_type;      /* ElementFORT77構造体用 */
    int *quad_points;    /* ElementFORT77構造体用 */
    char **quad_name;    /* ElementFORT77構造体用 */
    int specify_flag;    /* 試験関数指定のカウンター */

    int freedom;
    int tmp,tmp2;
    char *tmpcha;

    char *fem_unknown_element[MAX_EQUATIONS];/* 未知変数の基底名をいれる */
    int fem_unknown_freedom[MAX_EQUATIONS];  /* 未知変数の自由度を入れる */
    char *fem_test_function[MAX_EQUATIONS];  /* 試験関数を入れる         */
    int test_function_freedom[MAX_EQUATIONS];  /* 試験関数の自由度    */

    ElementFORT77 *elem_77_ptr;
    Quadrature    *quad_ptr;     /* 数値積分点数代入用 */
   
    Equation **eq_ptrptr;
    Equation  *eq_ptr;
    char     **eq_method_ptr;
    char      *eq_method;

    char      *coff_vec;    /* (m1 m2 m3 m4 ....) のリスト */
    char      *test_func;   /* (q1_1 q1_2 ..... ) のリスト */

    char       listp_st[LISP_BUFSIZ];  /* この関数内で書く為のリスト */

    char      *cp;    /* temporary use */

    solve_no   = solve_element_ptr -> solve_no;
    elem_no    = solve_element_ptr -> element_no;

    type      = solve_element_ptr -> type;        /* 方程式のタイプ */
    unknowns  = solve_element_ptr -> unknowns;    /* 注意:solve文のものを利用*/
    equations = solve_element_ptr -> equations;
    eq_ptrptr = solve_element_ptr -> eq_data;

    elem_77_ptr = solve_element_ptr ->elem77_dat; /* ElemFORT77->quad_method
						     設定の為  */
    /*==============================*/
    /* 未知変数の基底関数名を入れる */
    /*   → fem_unknown_element[]   */
    /*==============================*/
    /* 現在は、solve文で陽に指定したものを使っているが、
       将来、複数の領域上の多重問題に対応する時には、solve文の
       未知変数を参考に、各SolveElement内の式から未知変数を抜き出さないと
       いけない   */

    if(unknowns != equations) {
	SystemAbort("MULTI dom拡張はまだされていません。(make_elem_lisp)");
    }

    /*==============================*/
    /* 未知変数の自由度を入れる     */
    /*   → fem_unknown_freedom[]   */
    /* および全自由度の計算         */
    /*==============================*/    
    freedom = 0;
    for(i=0;i<unknowns;i++) {    /* MULTI domain時にはequationによる検索 */
	fem_unknown_element[i] = 
	  get_elem_name_by_ND( *(solve_element_ptr -> unknown_name + i),
			      solve_element_ptr -> domain_name       );
	/* 注意 get_elem_name_by_NDも作り代えが必要(Multi-domain時) 
	   今は、domain name によるチェックを実行していない。
	   今後、fem_type構造体に doamin_ptrに関する情報をいれれば対応する？*/
	fem_unknown_freedom[i] 
	  = get_freedom_by_element_name(fem_unknown_element[i]);

/*	DBGWRT("element = %s  freedom = %d\n",	fem_unknown_element[i],
	       fem_unknown_freedom[i]  );
*/
	freedom = freedom  + fem_unknown_freedom[i] ;
    }

    /*===============================================================*/
    /* 試験関数リスト *test-funcs* 作成                              */
    /* (試験関数はsolve_chk_test_functionで確定されているものとする) */
    /*===============================================================*/
    /* 試験関数リストは汎関数停留値問題では存在せず */
    if(solve_element_ptr -> type != FUNCTIONAL ) {
    for(i=0;i<equations;i++) {  /* equations と unknownsは等しいと仮定される
				   MULTI-domain拡張時には、注意が必要  
				   これは、solve_chk_test_function でも
				   問題にされている                       */
	eq_ptr = *(eq_ptrptr+i);
	if(eq_ptr -> test_function == NULL) {
	    SystemAbort("試験関数が設定されていません(make_elem_lisp)");
	}
	fem_test_function[i] = eq_ptr->test_function;
	test_function_freedom[i] = 
	  get_freedom_by_element_name(eq_ptr->test_function);
    }
    make_test_funcs_vect(fp,fem_test_function,test_function_freedom,equations);
    }
    /*==================================*/
    /* 係数リスト     *coff-vect*  作成 */
    /*==================================*/
    make_coff_vect( fp,  freedom );

    /*==================================*/
    /* 展開関数リスト *eval-vars*  作成 */
    /* 先ずは未知fem変数                */
    /*==================================*/
    tmp = 1;
    for(i=0;i<unknowns;i++) { /* fem_unknown_element[],
				 fem_unknown_freedom[]を利用する
				 これらの配列はunknown_nameと順が同じ */

	make_unknown_eval_var(fp,*(solve_element_ptr -> unknown_name + i),tmp,
			      fem_unknown_element[i],
			      fem_unknown_freedom[i]);
	/* dbg: エルミート要素についても同様に扱う。
	   連立一次方程式後の分解の際に処理を行う    */
	
	tmp = tmp + fem_unknown_freedom[i];
    }
    /*==================================*/
    /* 既知fem変数に対する展開          */
    /*==================================*/
    /* この既知fem変数に関する展開では、エルミート要素などへの
       対応が問題となるので、要注意。                            

       数値積分法で内挿法が指定される物は、
       *quad_eval* に登録し、evalをキャンセルする。
       この登録は各数値積分法毎の作成時に登録する。   */

    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	make_known_eval_var( fp, *(solve_element_ptr->fem_known_name + i),
			     solve_element_ptr->domain_name );
    }
    /*==================================*/
    /* *eval-var* の作成                */
    /*==================================*/
    LISP_SEND(fp,"(setq *eval-vars* '(");
    for(i=0;i<unknowns;i++) {
	LISP_SEND_s(fp," %s",*(solve_element_ptr->unknown_name+i));
    }
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	LISP_SEND_s(fp," %s",*(solve_element_ptr->fem_known_name + i));
    }
    LISP_SEND(fp,") )\n");

    /*=================================*/
    /* *fem-funcs* の作成              */
    /*   未知関数、既知関数、試験関数  */
    /*   に用いられている要素一覧      */
    /*=================================*/
    LISP_SEND(fp,"(setq *fem-funcs* \n  '(");

    /* fem未知関数から */
    for(i=0;i<unknowns;i++) {
	if(i!= 0) {
	    LISP_SEND(fp,"    ");
	}
	for(j=0;j<fem_unknown_freedom[i];j++) {
	    LISP_SEND_sd(fp,"%s_%d ",fem_unknown_element[i],j+1);
	}
	LISP_SEND(fp,"\n");
    }

    /* 試験関数(汎関数停留値問題の場合はなし) */
    if(solve_element_ptr -> type != FUNCTIONAL ) {
	for(i=0;i<equations;i++) {
	    LISP_SEND(fp,"    ");
	    for(j=0;j<test_function_freedom[i];j++) {
		LISP_SEND_sd(fp,"%s_%d ",fem_test_function[i],j+1);
	    }
	    LISP_SEND(fp,"\n");
	}
    }

    /* 形状変換関数を入れる */
    tmp = get_freedom_by_element_name(solve_element_ptr -> shape_func);
    LISP_SEND(fp,"    ");
    for(i=0;i<tmp;i++) {
	LISP_SEND_sd(fp,"%s_%d ",solve_element_ptr->shape_func,i+1);
    }    

    /* 既知関数を入れる(*fem-func*に) */
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	tmpcha = get_elem_name_by_ND(*(solve_element_ptr-> fem_known_name+i),
				     solve_element_ptr  -> domain_name );
	tmp    = get_freedom_by_element_name(tmpcha);

	LISP_SEND(fp,"    ");
	for(j=0;j<tmp;j++) {
	    LISP_SEND_sd(fp,"%s_%d ",tmpcha,j+1);
	}
	LISP_SEND(fp,"\n");
    }

    LISP_SEND(fp,"     ) )\n");

    /*=================================*/
    /* 各*fem-funcs* へのboundの生成   */
    /*   未知関数、既知関数、試験関数  */
    /*   に用いられている要素一覧      */
    /*=================================*/
    /* fem未知関数から */
    for(i=0;i<unknowns;i++) {
	make_fem_funcs_bound(fp,fem_unknown_element[i]);
    }

    /* 試験関数(汎関数停留値問題の場合はなし) */
    if(solve_element_ptr -> type != FUNCTIONAL ) {
	for(i=0;i<equations;i++) {
	    make_fem_funcs_bound(fp,fem_test_function[i]);
	}
    }

    /* 既知関数へのbound */
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	tmpcha = get_elem_name_by_ND(*(solve_element_ptr-> fem_known_name+i),
				     solve_element_ptr  -> domain_name );
	make_fem_funcs_bound(fp,tmpcha);
    }

    /*==================================*/
    /* 形状変換関数の割り付け           */
    /*   *shape-funcs* の定義           */
    /*==================================*/
    tmp = get_freedom_by_element_name(solve_element_ptr -> shape_func);
    LISP_SEND(fp,"(setq *shape-funcs* '(");
    for(i=0;i<tmp;i++) {
	LISP_SEND_sd(fp,"%s_%d ",solve_element_ptr->shape_func,i+1);
    }
    LISP_SEND(fp,")  )\n");

    /* 形状関数へのbound  */
    make_fem_funcs_bound(fp, solve_element_ptr -> shape_func);

    /*==================================*/
    /* 積分法の種類を抜き出すプログラム */
    /*==================================*/
    /* 関数uniq_list を利用 */
    uniq_list_init();

    for(i=0;i<equations;i++) {
	eq_ptr         = *(eq_ptrptr + i);
	terms          = eq_ptr -> equation_terms;
	eq_method_ptr  = eq_ptr -> eq_method;
	for(j=0;j<terms;j++) {
	    eq_method = *(eq_method_ptr + j);
	    put_uniq_name(  eq_method );
	}
    }

    /* 積分法の種類 */
    quad_methods = how_many_uniq_items();

    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
    /* ElementFORT77構造体に反映 
       １)数値積分法の数
       ２)数値積分法かそうでないか
       ３)要素自由度の数                 
       ４)数値積分法の名前          */
    /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

    elem_77_ptr -> quad_methods = quad_methods;
    quad_type = (int *)FEEL_GetMemory(sizeof(int) * quad_methods);
    quad_points = (int *)FEEL_GetMemory(sizeof(int) * quad_methods);
    quad_name = (char **)FEEL_GetMemory(sizeof(char *) *quad_methods);
    for(i=0;i<quad_methods;i++) {
	*(quad_name+i) = MakeStringCopy(get_nth_uniq_item(i));
    }
    elem_77_ptr -> quad_name = quad_name;
    elem_77_ptr -> quad_type = quad_type;
    elem_77_ptr -> quad_points = quad_points; /* 数値積分法の点数 */
    elem_77_ptr -> elem_freedom = freedom;    /* 要素内自由度 */

    /*================================*/
    /* 各積分法毎にマトリックスを作成 */
    /* solve_element内で積分法にてLOOP*/
    /* 各積分法がLISPの基本単位       */
    /*================================*/
    for(i=0;i<quad_methods;i++) {

	LISP_SEND(fp,";----------------------\n");
	LISP_SEND_ddd(fp,"; 積分法  %d-%d-%d\n",solve_no,elem_no,i+1);
	LISP_SEND(fp,";----------------------\n");

	/* ElementFORT77構造体に反映 */	
	if(streq(get_nth_uniq_item(i),ANALYTIC_QUAD)) {
	    *(quad_type+i) = ANALYTICAL;
	    *(quad_points+i) = 0;      /* 解析的積分法の場合は０にしておく */
	}
	else {
	    *(quad_type+i) = NUMERICAL; 
	    /* 数値積分の場合は積分点数もElementFORT77で持っておく */
	    quad_ptr = get_quadrature_ptr_by_name(*(quad_name+i));
	    *(quad_points+i) = quad_ptr -> nodes;
	}
	
	/* 次のルーチンで、骨格部を作成する */

	switch(type) {
	  case FUNCTIONAL:
	  case DIFFEQ:
	    SystemAbort("まだ作ってません(make_elem_lisp)");
	    
	  case WEAKEQ:
	    make_weak_eq_WEQ(solve_no , elem_no , i+1,get_nth_uniq_item(i),solve_element_ptr,fp); 
	    break;
	}


    }

    return;
}


