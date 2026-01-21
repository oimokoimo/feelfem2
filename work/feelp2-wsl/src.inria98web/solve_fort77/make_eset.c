/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_eset.c
 *      Date:   1993/11/14
 *   
 *   Purpose:   esetXX_YYルーチンを作成する
 *   Functions: 
 *              
 *              数値積分に関する配列を設定する
 *              
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"
#include "../quadrature/quadrature.h"

void make_eset( solve_no, elem_no, solve_element_ptr  )
     int solve_no;
     int elem_no;
     SolveElement *solve_element_ptr;
{
    FILE *fp;
    
    int quad_no;             /* 積分法の数のループ用変数 */
    int i,j,k;
    int dimension;           /* 節点空間次元   */
    int freedom;             /* 各FEM変数の自由度を入れる為の一時変数 */
    char *var_name;          /* 変数名を入れる為の一時変数 */
    int quad_methods;        /* 積分法の数 */
    
    
    /* 各情報ポインタの宣言 */
    ElementFORT77 *elem77_ptr;
    ElemDat       *elem_dat_ptr;
    Quadrature    *quad_ptr;
    QuadWeight    *qw_ptr;
    Expression    **expr_ptrptr,*expr_ptr;
    
    Element **element_ptrptr,*element_ptr;
    Expression  *element_let_expr;
    char        *let_var_name;
    int element_types;

    int nodes;
    int consts;
    int doubles;
    int quad_lets;
    int interpolates;
    int *type_ptr;
    int flag;
    
    int terms;
    char *from[MAX_TERM_VARS];
    char *to[MAX_TERM_VARS];
    char name_buf[38];
    char fmt_buf[38];
    
    char fname[80];   /* ファイル名作成用 */ 
    
    char *chaptr,**chaptrptr;     /* COMMON文宣言用、配列代入文作成用 */
    char *chaptr2,**chaptrptr2;   /* 配列代入文作成用 */
    
    
    /* 各種構造体ポインタ設定 */
    elem77_ptr   = solve_element_ptr -> elem77_dat;
    elem_dat_ptr = elem77_ptr -> elem_dat;
    
    /* 基本変数代入 */
    quad_methods = elem77_ptr -> quad_methods;
    
    
    for(quad_no = 0;quad_no < quad_methods;quad_no++) {  /*積分法毎に
							   サブルーチン作成 */
	/* 解析的積分の場合スキップ */
	if(*(elem77_ptr->quad_type+quad_no) == ANALYTICAL) continue;
	
	
	/* Quadrature構造体の代入 */
	quad_ptr = get_quadrature_ptr_by_name(*(elem77_ptr->quad_name + quad_no));

	
	dimension = quad_ptr->dimension;   /* what_dimension()は使わない */
	
	
	/* Quadrature構造体内の変数をlocalに代入 */
	consts        = quad_ptr-> consts;
	doubles       = quad_ptr-> doubles;
	interpolates  = quad_ptr-> interpolates;
	quad_lets     = quad_ptr-> quad_lets;

	
	/* ファイルOPEN */
	sprintf(fname,ELEM_SET_FNAME,solve_no,elem_no,quad_no+1);


	StoreMakefile( fname ,USER_LIBRARY);
	fp = OpenFileToWrite( fname ); 
/*	fp = stderr;  */
	

	
	/*======================*/
	/* subroutine宣言       */
	/*======================*/
	F77("      subroutine ");
	PUT(fp,ELEM_SET_NAME,solve_no,elem_no,quad_no+1);


	/* quad_typeが指定される場合は、節点座標も持って行く */
	if(solve_element_ptr->quad_type != NO) {
	    int ii;

	    F77("(");
	    for(ii=0;ii<elem_dat_ptr->nodes;ii++) {
		if(ii != 0) F77(",");

		switch(dimension) {           /* 節点順 */
		  case 1:
		    PUT(fp,"x%d",ii+1);
		    break;
		    
		  case 2:
		    PUT(fp,"x%d,y%d",ii+1,ii+1);
		    break;
		    
		  case 3:
		    PUT(fp,"x%d,y%d,z%d",ii+1,ii+1,ii+1);
		    break;
		    
		  default:
		    SystemAbort("空間次元に異常があります(make_eset)");
		}
	    }
	    F77(")");
	}

	F77("\n");
	
	
	/*======================*/
	/* 定形宣言             */
	/*======================*/
	CopyRight(fp);
	TimeStamp(fp);
	real8(fp);
	
	/*========================*/
	/* 数値積分点数parameter文*/
	/* parameter NPGXX= YYY   */
	/*========================*/    
	PUT(fp,"      parameter (NPG%d = %d)\n",quad_no+1,
	    *(elem77_ptr -> quad_points+quad_no));
	
	
	/*======================*/
	/* 変数型宣言           */
	/*======================*/
	
	
	/* 数値積分法に関するCOMMON文 */
	PUT(fp,"      common /em%d_%d_%d/",solve_no,elem_no,quad_no+1);
	
	/* 積分点、重みに関する配列   */
	switch(dimension) {
	  case 1:
	    PUT(fp,GX_NAME77,quad_no+1);
	    PUT(fp,"(NPG%d),",quad_no+1);
	    break;
	    
	  case 2:
	    PUT(fp,GX_NAME77,quad_no+1);
	    PUT(fp,"(NPG%d),",quad_no+1);
	    PUT(fp,GY_NAME77,quad_no+1);
	    PUT(fp,"(NPG%d),",quad_no+1);
	    break;
	    
	  case 3:
	    PUT(fp,GX_NAME77,quad_no+1);
	    PUT(fp,"(NPG%d),",quad_no+1);
	    PUT(fp,GY_NAME77,quad_no+1);
	    PUT(fp,"(NPG%d),",quad_no+1);
	    PUT(fp,GZ_NAME77,quad_no+1);
	    PUT(fp,"(NPG%d),",quad_no+1);
	    break;
	    
	}
	PUT(fp,"w%d(NPG%d)\n",quad_no+1,quad_no+1);
	
	
	/* 積分用配列変数のcommonブロック */
	chaptrptr = *(elem77_ptr->quad_term_var_aptr + quad_no);
	for(j=0;j<*(elem77_ptr->quad_terms+quad_no);j++) {
	    if(j == 0)  {
		F77("     $       ");
	    }
	    /* 空間変数無視 */
	    if(streq(*(chaptrptr+j),"qx")) continue;
	    if(streq(*(chaptrptr+j),"qy")) continue;
	    if(streq(*(chaptrptr+j),"qz")) continue;

	    PUT(fp,",%s_%d(NPG%d)",*(chaptrptr+j),quad_no+1,quad_no+1);
	}
	
	/* 積分用const変数のcommonブロック */
	chaptrptr = *(elem77_ptr->quad_const_var_aptr + quad_no);
	for(j=0;j<*(elem77_ptr->quad_consts+quad_no);j++) {
	    F77(",");
	    PUT(fp,QUAD_CONST_NAME77,quad_no+1,*(chaptrptr+j));
	}
	F77("\n");    /* COMMON文の終わり */


	comment1(fp);
	
	/*========================*/
	/* term convert用配列作成 */
	/*========================*/
	terms = 0;
	/* 定数変数名 */
	for(i=0;i<consts;i++) {
	    if(i == MAX_TERM_VARS) {
		SystemAbort("Too many const vars for term_convert(make_eset)");
	    }
	    from[terms] = *(quad_ptr->const_var + i);
	    sprintf(name_buf,QUAD_CONST_NAME77,quad_no + 1 , 
		    *(quad_ptr->const_var + i));
	    to[terms]  = MakeStringCopy(name_buf);
	    terms++;
	}
	
	/* estルーチンでは、double変数は出て来ないはず。
	   よってdouble変数をterm_convertに登録しない   */

	/* 上のはうそで、要素内に要素の座標を関数とする基底関数
	   定義がある場合はこのルーチンで処理する               */
	
	
	/*======================*/
	/* 定数変数の宣言代入   */
	/*======================*/
	expr_ptrptr = quad_ptr -> const_val;
	for(i=0;i<consts;i++) {
	    expr_ptr = *(expr_ptrptr + i);
	    F77("      ");
	    PUT(fp,QUAD_CONST_NAME77,quad_no+1,*(quad_ptr->const_var+i));
	    F77(" = ");
	    PUT(fp,"%s\n",term_convert(expr_ptr->expr_inf,from,to,terms));
	}


	/*==============================*/
	/* 定数変数に関する代入文の展開 */
	/*==============================*/
	type_ptr    = quad_ptr -> let_var_type;
	expr_ptrptr = quad_ptr -> let_val;
	chaptrptr   = quad_ptr -> let_var;
	flag        = NO;
	for(i=0;i<quad_lets;i++) {
	    if(*(type_ptr + i) != CONST) continue;
	    expr_ptr = *(expr_ptrptr + i);

	    if(flag == NO) {    /* 代入文と宣言文の間にコメント一発 */
		COM;
		flag = YES;
	    }
	    F77("      ");
	    PUT(fp,QUAD_CONST_NAME77,quad_no+1,*(chaptrptr+i));
	    F77(" = ");
	    PUT(fp,"%s\n",term_convert(expr_ptr->expr_inf,from,to,terms));
	}
	comment1(fp);

	/*===============================*/
	/* element定義におけるdouble変数 */
	/* の計算式                      */
	/*===============================*/
	if(solve_element_ptr->quad_type != NO) {
	    element_ptrptr = solve_element_ptr -> elem_ptrptr;
	    element_types  = solve_element_ptr -> element_types;

	    for(i=0;i<element_types;i++) {
		element_ptr = *(element_ptrptr+i);
		if(element_ptr->element_lets == 0) continue;

		for(j=0;j<element_ptr->element_lets;j++) {
		    element_let_expr = *(element_ptr->let_expr + j);
		    let_var_name     = *(element_ptr->let_var_name +j);
		    
		    F77("      ");
		    PUT(fp,"%s = %s\n",let_var_name,
			element_let_expr->expr_inf);
		}
	    }
	}
	/*===============================*/
	/* 積分点座標、重み配列の初期化  */
	/*===============================*/
	nodes = quad_ptr->nodes;   /* nodesは重複使用しています */
	for(i=0;i<nodes;i++) {
	    qw_ptr = *(quad_ptr->quad_weight_ptrptr + i);
	    
	    switch(quad_ptr->dimension) {
		
	      case 1:
		F77("      ");
		PUT(fp,GX_NAME77,quad_no+1);
		PUT(fp,"(%d) = ",i+1);
		PUT(fp,"%s\n",term_convert(qw_ptr->r->expr_inf,from,to,terms));
		break;
		
	      case 2:
		F77("      ");
		PUT(fp,GX_NAME77,quad_no+1);
		PUT(fp,"(%d) = ",i+1);
		PUT(fp,"%s\n",term_convert(qw_ptr->r->expr_inf,from,to,terms));
		
		F77("      ");
		PUT(fp,GY_NAME77,quad_no+1);
		PUT(fp,"(%d) = ",i+1);
		PUT(fp,"%s\n",term_convert(qw_ptr->s->expr_inf,from,to,terms));
		break;
		
	      case 3:
		F77("      ");
		PUT(fp,GX_NAME77,quad_no+1);
		PUT(fp,"(%d) = ",i+1);
		PUT(fp,"%s\n",term_convert(qw_ptr->r->expr_inf,from,to,terms));
		
		F77("      ");
		PUT(fp,GY_NAME77,quad_no+1);
		PUT(fp,"(%d) = ",i+1);
		PUT(fp,"%s\n",term_convert(qw_ptr->s->expr_inf,from,to,terms));
		
		F77("      ");
		PUT(fp,GZ_NAME77,quad_no+1);
		PUT(fp,"(%d) = ",i+1);
		PUT(fp,"%s\n",term_convert(qw_ptr->t->expr_inf,from,to,terms));
		break;
		
	      default:
		SystemAbort("dimension(make_eset)");
	    }
	    F77("      ");
	    PUT(fp,WEIGHT_NAME77,quad_no+1);
	    PUT(fp,"(%d) = ",i+1);
	    PUT(fp,"%s\n",term_convert(qw_ptr->weight->expr_inf,from,to,terms));
	}

	/*========================*/
	/* 形状関数積分点値の代入 */
	/*========================*/

	/*===================================*/
	/* term convert用情報追加            */
	/* 空間変数r,s,tをGX_NAME77等に変更  */
	/*===================================*/
	terms = 0;
	/* 定数変数名 */
	
	if(MAX_TERM_VARS < terms + 4) {
	    SystemAbort("No space for term_convert(make_eset[2])");
	}
	/* x 座標 */
	from[terms] = LOCAL_X_VAR;
	sprintf(fmt_buf ,"%s(itp)",GX_NAME77);
	sprintf(name_buf,fmt_buf,quad_no+1);
	to[terms] =   MakeStringCopy(name_buf);
	terms++;

	/* y 座標 */
	from[terms] = LOCAL_Y_VAR;
	sprintf(fmt_buf ,"%s(itp)",GY_NAME77);
	sprintf(name_buf,fmt_buf,quad_no+1);
	to[terms] =   MakeStringCopy(name_buf);
	terms++;

	/* z 座標 */
	from[terms] = LOCAL_Z_VAR;
	sprintf(fmt_buf ,"%s(itp)",GZ_NAME77);
	sprintf(name_buf,fmt_buf,quad_no+1);
	to[terms] =   MakeStringCopy(name_buf);
	terms++;

	comment1(fp);

	PUT(fp,"      do 100 itp=1,NPG%d\n",quad_no+1);
	COM;
	
	chaptrptr = *(elem77_ptr->quad_term_var_aptr + quad_no);
	chaptrptr2= *(elem77_ptr->quad_term_expr_aptr + quad_no);
	for(j=0;j<*(elem77_ptr->quad_terms+quad_no);j++) {

	    /* 空間変数無視 */
	    if(streq(*(chaptrptr+j),X_IN_QUAD)) continue;
	    if(streq(*(chaptrptr+j),Y_IN_QUAD)) continue;
	    if(streq(*(chaptrptr+j),Z_IN_QUAD)) continue;

            PUT(fp,"        %s_%d(itp) = ",*(chaptrptr+j),quad_no+1,quad_no+1);
            PUT(fp,"%s\n",
		term_convert(*(chaptrptr2+j),from,to,terms));
        }
	COM;
	
	F77("  100 continue\n");

	/* 終了処理 */	
	COM;

	F77("      return\n");
	F77("      end\n");

	CloseFile(fp);   /* 一つのesetファイル作成終了 */

    }   /* quad_methodsのループ */

    return;
}


