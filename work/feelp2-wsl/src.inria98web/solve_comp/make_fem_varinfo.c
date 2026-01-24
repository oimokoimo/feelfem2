/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_fem_varinfo.c
 *      Date:   1993/10/29
 *  Modified:   1994/06/28,1994/08/01
 *   
 *   Purpose:   ElementFORT77内の構造体FEMvarinfoを作成
 *              
 *              要素毎に数値積分点での基底関数値再計算必要か？フラグの計算
 *              solve_element_ptr->quad_type  の設定(３箇所)
 *              
 *              1994/08/01  境界積分項のみに現れるfem変数も登録する
 *                これは、solve_element_ptr->known_fem_nameに登録することに
 *                よって行おう。(たいへん遺憾ですが…)
 *              
 * Functions:   local_element_no2D() 局所節点番号を得る関数    １から
 *              local_element_po2D() 節点内自由度順を得る関数  ０から
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "solve_comp.h"
#include "../var_comp/var_comp.h"
#include "../element/element.h"

int local_element_no1D(Frac r,ElemDat *elem_dat_ptr);
int local_element_no2D(Frac r,Frac s,ElemDat *elem_dat_ptr);
int local_element_po2D(int local_no,char *var_name,int ntype,ElemDat *elem_dat_ptr);
int local_element_po1D(int local_no,char *var_name,int ntype,ElemDat *elem_dat_ptr);
int frac_neq(Frac a ,Frac b);

void make_fem_varinfo()
{
    int i,j,k,l;

    int solves;
    int solve_elements;

    Solve *solve_ptr;
    SolveElement *solve_element_ptr;
    ElemDat *elem_dat_ptr;
    ElementFORT77 *elem_fort77_ptr;
    FEMvarinfo   **fem_varinfo_ptrptr;
    FEMvarinfo    *fem_varinfo_ptr;
    Element       *element_ptr;
    char          *var_name;
    char          *element_name;


    Frac r,s,t;

    int fem_vars,fem_vars_ptr;
    int basis;
    int unknowns;
    int knowns;
    int neumann_onlys;  /* ノイマンデータのみに現れるfem既知変数 */

    int ntype;        /* for節点値意味 */

    /* 菊地スペシャル用 */
    int find_flag;         /* 要素構造体格納用 */
    int quad_type;         /* 要素計算時に再計算が必要か？フラグ */
    int element_types;     /* 要素種数(SolveElement内の構造体)   */
    Element *elem_ptr_save[MAX_ELEMENT]; /* 要素構造体の配列     */
    Element **elem_ptrptr;
    
    int local_no;     /* 局所節点番号       (for ienp)*/
    int local_po;     /* 節点での自由度準位 (for iedp)*/

    solves = how_many_solves();

    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr( i ) ;

	solve_elements = solve_ptr -> solve_elements;

	for(j=0;j<solve_elements;j++) {
	    
	    solve_element_ptr = *(solve_ptr -> solve_elem_dat + j);
	    elem_fort77_ptr   = solve_element_ptr -> elem77_dat;

	    quad_type     = 0;     /* 各SolveElement単位に確定する */
	    element_types = 0;     /* 各SolveElement単位に確定する */

	    unknowns = solve_element_ptr -> unknowns;
	    knowns   = solve_element_ptr -> fem_knowns;
	    neumann_onlys = solve_element_ptr -> ndata_fem_knowns;

	    /* FEMvarinfo へのサイズ確定とElementFORT77への反映 */
	    /* 最後の + 1 は 形状変換関数の分                   */
	    fem_vars = unknowns + knowns + neumann_onlys + 1;
/*
	    STRESS;
	    DBGWRT("XXXXXXXXXXXXXXXXXXXXXXfem_vars = %d\n",fem_vars);
	    NORMAL;
*/
	    elem_fort77_ptr ->fem_vars = fem_vars;

	    fem_vars_ptr = 0;

	    /* まず領域確保 */
	    fem_varinfo_ptrptr = (FEMvarinfo **)
	      FEEL_GetMemory(sizeof(FEMvarinfo *) * fem_vars);
	    elem_fort77_ptr -> fem_var_info_ptrptr = fem_varinfo_ptrptr;
	    elem_dat_ptr = elem_fort77_ptr -> elem_dat;

	    /* ここから始まる大レース */

	    /* まず、fem unknown var から */
	    for(k=0;k<unknowns;k++) {
		var_name = *(solve_element_ptr->unknown_name + k);
		element_name = 
		  get_elem_name_by_ND(var_name ,
				      solve_element_ptr->domain_name);
		element_ptr = get_element_ptr_by_name( element_name );

		/* elem_ptrptr格納用 その１／３*/
		find_flag = NO;
		for(l=0;l<element_types;l++) {
		    if(elem_ptr_save[i] == element_ptr) {
			find_flag = YES;
			break;
		    }
		}
		if(find_flag == NO) {
		    elem_ptr_save[element_types] = element_ptr;
		    element_types++;
		}

		

		/* 要素毎再計算が必要かどうか？ unknown変数について */
		quad_type += element_ptr -> quad_type;
		
		/* 領域確保と、ElementFORT77構造体下への反映 */
		fem_varinfo_ptr = 
		  (FEMvarinfo *)FEEL_GetMemory(sizeof (FEMvarinfo));
		*(fem_varinfo_ptrptr+fem_vars_ptr) = fem_varinfo_ptr;
		fem_vars_ptr ++;
		basis = element_ptr -> basis;

		/* 名称の名前等をあらたに割り付けてはいない CAUTION: */
		fem_varinfo_ptr -> fem_var_name = var_name;
		fem_varinfo_ptr -> element_name = element_name;
		fem_varinfo_ptr -> freedom = basis;

		/* 領域割り当て */
		fem_varinfo_ptr -> ienp = 
		  (int *)FEEL_GetMemory(sizeof(int) * basis);
		fem_varinfo_ptr -> iedp = 
		  (int *)FEEL_GetMemory(sizeof(int) * basis);

		for(l=0;l<basis;l++) {
		    r = *(element_ptr -> r_frac + l);
		    s = *(element_ptr -> s_frac + l);
		    t = *(element_ptr -> t_frac + l);
		    ntype = *(element_ptr -> ntype + l);  /* 節点値意味 */

		    switch( solve_element_ptr -> etype ) {
		      case TRI:
		      case RECT:
			/* 要素内局所節点番号 */
			local_no = local_element_no2D(r,s,elem_dat_ptr);
			/* 節点内自由度位置   */
			local_po = local_element_po2D(local_no,var_name,ntype,
						      elem_dat_ptr);
			*(fem_varinfo_ptr -> ienp + l ) = local_no;
			*(fem_varinfo_ptr -> iedp + l ) = local_po;
			
			break;

                      case LINE:

			/* 要素内局所節点番号 */
			local_no = local_element_no1D(r,elem_dat_ptr);
			/* 節点内自由度位置   */
			local_po = local_element_po1D(local_no,var_name,ntype,
						      elem_dat_ptr);
			*(fem_varinfo_ptr -> ienp + l ) = local_no;
			*(fem_varinfo_ptr -> iedp + l ) = local_po;
			
			break;


		      case CUBE:
		      case TETRA:
			
			SystemAbort("まだ、CUBE,TETRA,LINEには未対応(femvarinfo)");
			break;

		      default:
			SystemAbort("不正なetypeが検出されました(make_fem_varinfo)");
		    }
		}
	    } /* unknowns の終り */


	    /* 既知fem変数について登録 */
	    for(k=0;k<knowns;k++) {
		var_name = *(solve_element_ptr->fem_known_name + k);
		element_name = 
		  get_elem_name_by_ND(var_name ,
				      solve_element_ptr->domain_name);
		element_ptr = get_element_ptr_by_name( element_name );

		/* elem_ptrptr格納用その２／３ */
		find_flag = NO;
		for(l=0;l<element_types;l++) {
		    if(elem_ptr_save[i] == element_ptr) {
			find_flag = YES;
			break;
		    }
		}
		if(find_flag == NO) {
		    elem_ptr_save[element_types] = element_ptr;
		    element_types++;
		}



		/* 要素毎再計算が必要かどうか？ known変数について */
		quad_type += element_ptr -> quad_type;
		
		/* 領域確保と、ElementFORT77構造体下への反映 */
		fem_varinfo_ptr = 
		  (FEMvarinfo *)FEEL_GetMemory(sizeof (FEMvarinfo));
		*(fem_varinfo_ptrptr+fem_vars_ptr) = fem_varinfo_ptr;
		fem_vars_ptr++;
		basis = element_ptr -> basis;

		/* 名称の名前等をあらたに割り付けてはいない CAUTION: */
		fem_varinfo_ptr -> fem_var_name = var_name;
		fem_varinfo_ptr -> element_name = element_name;
		fem_varinfo_ptr -> freedom = basis;

		/* 領域割り当て */
		fem_varinfo_ptr -> ienp = 
		  (int *)FEEL_GetMemory(sizeof(int) * basis);
		fem_varinfo_ptr -> iedp = 
		  (int *)FEEL_GetMemory(sizeof(int) * basis);

		for(l=0;l<basis;l++) {
		    r = *(element_ptr -> r_frac + l);
		    s = *(element_ptr -> s_frac + l);
		    t = *(element_ptr -> t_frac + l);
		    ntype = *(element_ptr -> ntype + l);  /* 節点値意味 */

		    switch( solve_element_ptr -> etype ) {
		      case TRI:
		      case RECT:
			/* 要素内局所節点番号 */
			local_no = local_element_no2D(r,s,elem_dat_ptr);
			*(fem_varinfo_ptr -> ienp + l ) = local_no;
			/* 節点内自由度位置は既知変数のため不要 */
			*(fem_varinfo_ptr -> iedp + l ) = 999;
			break;

		      case LINE:
			/* 要素内局所節点番号 */
			local_no = local_element_no1D(r,elem_dat_ptr);
			*(fem_varinfo_ptr -> ienp + l ) = local_no;
			/* 節点内自由度位置は既知変数のため不要 */
			*(fem_varinfo_ptr -> iedp + l ) = 999;
			break;

		      case CUBE:
		      case TETRA:
			
			SystemAbort("まだ、CUBE,TETRA,LINEには未対応(femvarinfo)");
			break;

		      default:
			SystemAbort("不正なetypeが検出されました(make_fem_varinfo)");
		    }
		}
	    } /* knowns の終わり */










	    /* 対症療法  ノイマン条件内だけに現れる既知fem変数の追加登録
	     * ここで、問題となるのは複数SolveElement拡張時における選択
	     * を現在していないことであるが、現在、SolveElementは一個なので
	     * よしとしましょう。Solve->knownsから持って来ないのは、
	     * Dirichlet条件のみに現れる既知FEM変数を除外する為です。
	     * 1994/08/01
	     */

	    /* ノイマンデータのみのfem既知変数について登録 */
	    for(k=0;k<neumann_onlys;k++) {
		var_name = *(solve_element_ptr->ndata_fem_name + k);
		element_name = 
		  get_elem_name_by_ND(var_name ,
				      solve_element_ptr->domain_name);
		element_ptr = get_element_ptr_by_name( element_name );

		/* elem_ptrptr格納用その２／３ */
		find_flag = NO;
		for(l=0;l<element_types;l++) {
		    if(elem_ptr_save[i] == element_ptr) {
			find_flag = YES;
			break;
		    }
		}
		if(find_flag == NO) {
		    elem_ptr_save[element_types] = element_ptr;
		    element_types++;
		}



		/* 要素毎再計算が必要かどうか？ known変数について */
		quad_type += element_ptr -> quad_type;
		
		/* 領域確保と、ElementFORT77構造体下への反映 */
		fem_varinfo_ptr = 
		  (FEMvarinfo *)FEEL_GetMemory(sizeof (FEMvarinfo));
		*(fem_varinfo_ptrptr+fem_vars_ptr) = fem_varinfo_ptr;
		fem_vars_ptr++;
		basis = element_ptr -> basis;

		/* 名称の名前等をあらたに割り付けてはいない CAUTION: */
		fem_varinfo_ptr -> fem_var_name = var_name;
		fem_varinfo_ptr -> element_name = element_name;
		fem_varinfo_ptr -> freedom = basis;

		/* 領域割り当て */
		fem_varinfo_ptr -> ienp = 
		  (int *)FEEL_GetMemory(sizeof(int) * basis);
		fem_varinfo_ptr -> iedp = 
		  (int *)FEEL_GetMemory(sizeof(int) * basis);

		for(l=0;l<basis;l++) {
		    r = *(element_ptr -> r_frac + l);
		    s = *(element_ptr -> s_frac + l);
		    t = *(element_ptr -> t_frac + l);
		    ntype = *(element_ptr -> ntype + l);  /* 節点値意味 */

		    switch( solve_element_ptr -> etype ) {
		      case TRI:
		      case RECT:
			/* 要素内局所節点番号 */
			local_no = local_element_no2D(r,s,elem_dat_ptr);
			*(fem_varinfo_ptr -> ienp + l ) = local_no;
			/* 節点内自由度位置は既知変数のため不要 */
			*(fem_varinfo_ptr -> iedp + l ) = 999;
			break;

		      case LINE:
			/* 要素内局所節点番号 */
			local_no = local_element_no1D(r,elem_dat_ptr);
			*(fem_varinfo_ptr -> ienp + l ) = local_no;
			/* 節点内自由度位置は既知変数のため不要 */
			*(fem_varinfo_ptr -> iedp + l ) = 999;
			break;
			

		      case CUBE:
		      case TETRA:
			
			SystemAbort("まだ、CUBE,TETRA,LINEには未対応(femvarinfo)");
			break;

		      default:
			SystemAbort("不正なetypeが検出されました(make_fem_varinfo)");
		    }
		}
	    } /* neumann_onlys の終わり */


	    /*================*/
	    /* 形状関数の登録 */
	    /*================*/
	    var_name = SHAPE_FUNCTION_SYMBOL;  
	    element_name = solve_element_ptr -> shape_func;
	    element_ptr = get_element_ptr_by_name( element_name );

	    /* elem_ptrptr格納用 (形状関数用 その３／３)*/
	    find_flag = NO;
	    for(l=0;l<element_types;l++) {
		if(elem_ptr_save[i] == element_ptr) {
		    find_flag = YES;
		    break;
		}
	    }
	    if(find_flag == NO) {
		elem_ptr_save[element_types] = element_ptr;
		element_types++;
	    }

	    /* 要素毎再計算が必要かどうか？ 形状変換関数について */
	    quad_type += element_ptr->quad_type;
		
	    /* 領域確保と、ElementFORT77構造体下への反映 */
	    fem_varinfo_ptr = 
	      (FEMvarinfo *)FEEL_GetMemory(sizeof (FEMvarinfo));
	    *(fem_varinfo_ptrptr+fem_vars_ptr) = fem_varinfo_ptr;
	    fem_vars_ptr++;
	    basis = element_ptr -> basis;

	    /* var_nameは領域をあらたに割り付ける。それ以外は    */
	    /* 名称の名前等をあらたに割り付けてはいない CAUTION: */
	    fem_varinfo_ptr -> fem_var_name = MakeStringCopy(var_name);
	    fem_varinfo_ptr -> element_name = element_name;
	    fem_varinfo_ptr -> freedom = basis;

	    /* 領域割り当て */
	    fem_varinfo_ptr -> ienp = 
	      (int *)FEEL_GetMemory(sizeof(int) * basis);
	    fem_varinfo_ptr -> iedp = 
	      (int *)FEEL_GetMemory(sizeof(int) * basis);

	    for(l=0;l<basis;l++) {
		r = *(element_ptr -> r_frac + l);
		s = *(element_ptr -> s_frac + l);
		t = *(element_ptr -> t_frac + l);
		ntype = *(element_ptr -> ntype + l);  /* 節点値意味 */
		
		switch( solve_element_ptr -> etype ) {
		  case TRI:
		  case RECT:
		    /* 要素内局所節点番号 */
		    local_no = local_element_no2D(r,s,elem_dat_ptr);
		    *(fem_varinfo_ptr -> ienp + l ) = local_no;
		    /* 節点内自由度位置は形状変換関数のため不要 */
		    *(fem_varinfo_ptr -> iedp + l ) = 999;
		    break;

		  case LINE:
		    /* 要素内局所節点番号 */
		    local_no = local_element_no1D(r,elem_dat_ptr);
		    *(fem_varinfo_ptr -> ienp + l ) = local_no;
		    /* 節点内自由度位置は形状変換関数のため不要 */
		    *(fem_varinfo_ptr -> iedp + l ) = 999;
		    break;

		  case CUBE:
		  case TETRA:
			
		    SystemAbort("まだ、CUBE,TETRA,LINEには未対応(femvarinfo)");
		    break;
		    
		  default:
		    SystemAbort("不正なetypeが検出されました(make_fem_varinfo)");
		}
	    }
	    /* 形状変換関数登録分の終わり */

	    /* 菊地スペシャル関連情報の割り当て */
	    solve_element_ptr->quad_type = quad_type;
	    solve_element_ptr->element_types = element_types;
	    elem_ptrptr = (Element **)FEEL_GetMemory(sizeof(Element *) *
						     element_types       );
	    for(l=0;l<element_types;l++) {
		*(elem_ptrptr + l) = elem_ptr_save[l];
	    }
	    solve_element_ptr->elem_ptrptr = elem_ptrptr;

	} /* solve_elements の終わり */

    }  /* solvesの終わり */
    return;
}

/* 関数 local_element_no2D   ２次元局所節点番号を返す
   機能 elem_dat_ptrに表されている要素内節点のうち、指定の節点が
        何番目かを返す。返す値は1から始まる

   この関数群は、ecalルーチン等での変数引渡の際に必要となる番号確定の為
 */

int local_element_no2D(r,s,elem_dat_ptr)
     Frac     r,s;
     ElemDat *elem_dat_ptr;
{
    int i;
    int nodes;
    Node **node_ptrptr;
    Node  *node_ptr;
    Frac  rr,ss;

    nodes       = elem_dat_ptr -> nodes;
    node_ptrptr = elem_dat_ptr -> node_ptrptr;


    for(i=0;i<nodes;i++) {
	node_ptr = *(node_ptrptr + i);
	rr = node_ptr -> r;
	ss = node_ptr -> s;

	if(frac_neq(rr,r) || frac_neq(ss,s)) continue;

	return(i+1);  /* １から始まる番号 */
    }


    SystemAbort("与えられた節点座標が存在しません(local_element_no2D)");

}


/* 関数 local_element_po2D  節点内自由度順を返す
   機能 elem_dat_ptrのlocal_no番目節点のうち、指定の自由度が
        何番目かを返す。返す値は0から始まる

   この関数群は、ecalルーチン等での変数引渡の際に必要となる番号確定の為
 */
int local_element_po2D(local_no,var_name,ntype,elem_dat_ptr)
     int   local_no;          /* 1 から始まる */
     char *var_name;
     int   ntype;
     ElemDat *elem_dat_ptr;
{
    int i;
    int freedom;
    Node *node_ptr;

    node_ptr = *(elem_dat_ptr -> node_ptrptr + local_no - 1);
    freedom  = node_ptr -> freedom;   

    if(freedom == 0) {
	SystemAbort("freedomが０になった(local_element_po2D");
	/* 未知変数に関して、freedomが０になることは無い(93/11/01) */
    }

    for(i=0;i<freedom;i++) {
	if(streq(var_name,*(node_ptr->var_name_ptr + i))
	   && *(node_ptr->node_type + i) == ntype) {
	    return(i);
	}
    }

    SystemAbort("指定自由度がElemDat構造体に登録されていない(local_element_po2D(make_fem_varinfo)");
    return -1;

}



/* 関数 local_element_no1D   １次元局所節点番号を返す
   機能 elem_dat_ptrに表されている要素内節点のうち、指定の節点が
        何番目かを返す。返す値は1から始まる

   この関数群は、ecalルーチン等での変数引渡の際に必要となる番号確定の為
 */

int local_element_no1D(r,elem_dat_ptr)
     Frac     r;
     ElemDat *elem_dat_ptr;
{
    int i;
    int nodes;
    Node **node_ptrptr;
    Node  *node_ptr;
    Frac  rr;

    nodes       = elem_dat_ptr -> nodes;
    node_ptrptr = elem_dat_ptr -> node_ptrptr;


    for(i=0;i<nodes;i++) {
	node_ptr = *(node_ptrptr + i);
	rr = node_ptr -> r;

	if(frac_neq(rr,r)) continue;

	return(i+1);  /* １から始まる番号 */
    }

    SystemAbort("与えられた節点座標が存在しません(local_element_no1D)");

}


/* 関数 local_element_po1D  節点内自由度順を返す
   機能 elem_dat_ptrのlocal_no番目節点のうち、指定の自由度が
        何番目かを返す。返す値は0から始まる

   この関数群は、ecalルーチン等での変数引渡の際に必要となる番号確定の為
 */
int local_element_po1D(local_no,var_name,ntype,elem_dat_ptr)
     int   local_no;          /* 1 から始まる */
     char *var_name;
     int   ntype;
     ElemDat *elem_dat_ptr;
{
    int i;
    int freedom;
    Node *node_ptr;

    node_ptr = *(elem_dat_ptr -> node_ptrptr + local_no - 1);
    freedom  = node_ptr -> freedom;   

    if(freedom == 0) {
	SystemAbort("freedomが０になった(local_element_po2D");
	/* 未知変数に関して、freedomが０になることは無い(93/11/01) */
    }

    for(i=0;i<freedom;i++) {
	if(streq(var_name,*(node_ptr->var_name_ptr + i))
	   && *(node_ptr->node_type + i) == ntype) {
	    return(i);
	}
    }

    SystemAbort("指定自由度がElemDat構造体に登録されていない(local_element_po2D(make_fem_varinfo)");

}
