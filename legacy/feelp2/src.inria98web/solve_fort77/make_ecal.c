/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ecal.c
 *      Date:   1993/11/08
 *   
 *   Purpose:   ecalXX_YYルーチンを作成する
 *   Functions: 
 *              
 *              数値積分、解析積分版ともこのプログラムで扱う
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

void make_ecal( solve_no, elem_no, solve_element_ptr  )
     int solve_no;
     int elem_no;
     SolveElement *solve_element_ptr;
{
    FILE *fp;                /* 書き込み用ポインタ */
    FILE *fpr;               /* 読み込み用ポインタ */

    int i,j,k;
    int dimension;           /* 節点空間次元   */
    int nodes;               /* 要素内全節点数 */
    int freedom;             /* 各FEM変数の自由度を入れる為の一時変数 */
    char *var_name;          /* 変数名を入れる為の一時変数 */
    char *domain_name;       /* domain name の為の一時変数 */
    int quad_methods;        /* 積分法の数 */
    int num_quad_flag;       /* 数値積分法があるかないかのフラグ */

    /* 各情報ポインタの宣言 */
    ElementFORT77 *elem77_ptr;
    ElemDat       *elem_dat_ptr;
    EWISE_type *ewise_type_ptr;
    Quadrature    *quad_ptr;

    char fname[80];   /* ファイル名作成用 */ 

    char *chaptr,**chaptrptr;


    /* 各種構造体ポインタ設定 */
    elem77_ptr   = solve_element_ptr -> elem77_dat;
    elem_dat_ptr = elem77_ptr -> elem_dat;

    /* 基本変数代入 */
    dimension = what_dimension();
    nodes = elem_dat_ptr -> nodes;
    domain_name = solve_element_ptr -> domain_name;
    quad_methods = elem77_ptr -> quad_methods;
    
    num_quad_flag = NO;


    /* ファイルOPEN */
    sprintf(fname,ELEM_CAL_FNAME,solve_no,elem_no);

    StoreMakefile( fname ,USER_LIBRARY);
    fp = OpenFileToWrite( fname );

    
    F77("      subroutine ");
    PUT(fp,ELEM_CAL_NAME,solve_no,elem_no);
    F77("(");

    for(i=0;i<nodes;i++) {
	if(i!= 0) F77(",");
	
	switch(dimension) {           /* 節点順 */
	  case 1:
	    PUT(fp,"x%d",i+1);
	    break;

	  case 2:
	    PUT(fp,"x%d,y%d",i+1,i+1);
	    break;
	    
	  case 3:
	    PUT(fp,"x%d,y%d,z%d",i+1,i+1,i+1);
	    break;

	  default:
	    SystemAbort("空間次元に異常があります(make_ecal)");
	}
    }

    /* fem変数に対する展開 
       注意 1  各変数の番号は要素局所番号と常に等しいとは限らない
       注意 2  エルミート要素の微分値に対応する自由度や節点無しの自由度
               は、elemルーチン上では各fem変数(ewise変数)の配列要素として
	       呼び出すが、ここでは連番号で受けることに注意が必要。これは
	       LISPプログラム作成時の負担を軽減し、混乱を防ぐ為の仕様である
	       よって、elemルーチンに比べ、ここの引き数は格段に単純な呼び出
	       され形式になる
   */
    
    /* 変数に関する注意1   fem、ewise変数名がFORTRANの暗黙の型宣言に従わない
                           時は明示的に型宣言を行う

                   注意2   数値積分法とewise変数の位置指定が一致した場合は
                           配列で受ける
     */

    /* 非線形問題の場合は、未知fem変数に対しても展開処理 */
    if(solve_element_ptr->nonlinear_flag == YES) {

	for(i=0;i<solve_element_ptr->unknowns;i++) {
	
	    var_name = *(solve_element_ptr-> unknown_name+i);

	    /* fem変数の自由度を得る */
	    freedom = get_fem_var_freedom_by_ND(var_name, domain_name);
	    
	    for(j=0;j<freedom;j++) {
		PUT(fp,",%s_%d",var_name,j+1);
	    }
	}
    }

    /* 既知fem変数の展開 */
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	var_name = *(solve_element_ptr -> fem_known_name + i);

	/* fem変数の自由度を得る */
	freedom = get_fem_var_freedom_by_ND(var_name, domain_name);
	
	for(j=0;j<freedom;j++) {
	    PUT(fp,",%s_%d",var_name,j+1);
	}
    }

    /* ewise変数の展開  ここでは、配列か否かを気にしなくてよい */
    /* ewise変数は,変数識別子を付ける */
    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	F77(",");
	PUT(fp,EWISE_VAR_NAME77,*(solve_element_ptr -> ewise_known_name + i));
    }
    
    /* scalar変数の展開  ここでは、配列か否かを気にしなくてよい */
    /* scalar変数は,変数識別子を付ける */
    for(i=0;i<solve_element_ptr->scalar_knowns;i++) {
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(solve_element_ptr -> scalar_known_name + i));
    }

    F77(")\n");

    /*======================*/
    /* subroutine文の終わり */
    /*======================*/


    /*======================*/
    /* 定形宣言             */
    /*======================*/
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);
    COM;

    /*======================*/
    /* 要素自由度parameter文*/
    /*======================*/
    PUT(fp,"      parameter (NDF = %d)\n",elem77_ptr->elem_freedom);

    /*========================*/
    /* 数値積分点数parameter文*/
    /* parameter NPGXX= YYY   */
    /*========================*/    
    for(i=0;i<elem77_ptr->quad_methods;i++) {
	/* 解析的積分か？ */
	if(*(elem77_ptr->quad_type+i) == ANALYTICAL) continue;

	num_quad_flag = YES;

	PUT(fp,"      parameter (NPG%d = %d)\n",i+1,
	    *(elem77_ptr->quad_points+i));
    }

    /*======================*/
    /* 変数型宣言           */
    /*======================*/
    COM;    
    /* 非線形問題の場合は、未知fem変数に対しても展開処理 */
    if(solve_element_ptr->nonlinear_flag == YES) {
	for(i=0;i<solve_element_ptr->unknowns;i++) {
	    var_name = *(solve_element_ptr-> unknown_name+i);

	    /* fem変数の自由度を得る */
	    freedom = get_fem_var_freedom_by_ND(var_name, domain_name);

	    PUT(fp,"      real*8 %s_1",var_name);

	    for(j=1;j<freedom;j++) {
		PUT(fp,",%s_%d",var_name,j+1);
	    }
	    F77("\n");
	}
    }

    /* 既知fem変数の型宣言 */
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	var_name = *(solve_element_ptr -> fem_known_name + i);

	/* fem変数の自由度を得る */
	freedom = get_fem_var_freedom_by_ND(var_name, domain_name);
	
	PUT(fp,"      real*8 %s_1",var_name);

	for(j=1;j<freedom;j++) {
	    PUT(fp,",%s_%d",var_name,j+1);
	}
	F77("\n");
    }


    /* ewise変数の型宣言 ewise変数が唯一の数値積分法と型宣言が一致する場合
       配列として宣言する */

    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	ewise_type_ptr = 
	  get_ewise_type_ptr_by_2name(*(solve_element_ptr->ewise_known_name+i),
				      domain_name );
	if(ewise_type_ptr -> quadrature == NULL) continue;

	if(quad_methods != 1) {
	    SystemAbort("quadrature指定のewise変数が複数求積法solve中に存在");
	}
	if(!streq(ewise_type_ptr -> quadrature ,
		  *(elem77_ptr->quad_name ))) {
	    SystemAbort("quadrature指定のewise変数とsolve文の求積法が不一致");
	}
	F77("      dimension ");
	PUT(fp,EWISE_VAR_NAME77,*(solve_element_ptr -> ewise_known_name + i));
	F77("(*)\n");
    }
    
    /* 数値積分法指定時は、ヤコビアン用変数宣言 */
    if(num_quad_flag == YES) {
	COM;
	F77("      dimension rj(3,3)\n");         /* ２次元も3x3で宣言 */
	F77("      dimension rij(3,3)\n");
    }

    /* 要素内小行列に関するCOMMONブロック宣言 */
    COM;
    PUT(fp,"      common /em%d_%d/ ea(NDF,NDF),eb(NDF)\n",solve_no,elem_no);

    /* 数値積分法に関するCOMMON文 */
    for(i=0;i<elem77_ptr->quad_methods;i++) {
	/* 数値積分以外か？ */
	if(*(elem77_ptr->quad_terms+i) == 0) continue;

	quad_ptr = get_quadrature_ptr_by_name(*(elem77_ptr->quad_name + i));

	COM;

	PUT(fp,"      common /em%d_%d_%d/",solve_no,elem_no,i+1);

	switch(quad_ptr->dimension) {
	  case 1:
	    PUT(fp,GX_NAME77,i+1);
	    PUT(fp,"(NPG%d),",i+1);
	    break;
	    
	  case 2:
	    PUT(fp,GX_NAME77,i+1);
	    PUT(fp,"(NPG%d),",i+1);
	    PUT(fp,GY_NAME77,i+1);
	    PUT(fp,"(NPG%d),",i+1);
	    break;
	    
	  case 3:
	    PUT(fp,GX_NAME77,i+1);
	    PUT(fp,"(NPG%d),",i+1);
	    PUT(fp,GY_NAME77,i+1);
	    PUT(fp,"(NPG%d),",i+1);
	    PUT(fp,GZ_NAME77,i+1);
	    PUT(fp,"(NPG%d),",i+1);
	    break;
	    
	}
	PUT(fp,"w%d(NPG%d)\n",i+1,i+1);
	F77("     $       ");

	/* 積分用配列変数のcommonブロック */
	chaptrptr = *(elem77_ptr->quad_term_var_aptr + i);
	for(j=0;j<*(elem77_ptr->quad_terms+i);j++) {


	    /* 空間変数無視 */
	    if(streq(*(chaptrptr+j),"qx")) continue;
	    if(streq(*(chaptrptr+j),"qy")) continue;
	    if(streq(*(chaptrptr+j),"qz")) continue;

	    F77(",");
	    PUT(fp,"%s_%d(NPG%d)",*(chaptrptr+j),i+1,i+1);
	}

	/* 積分用const変数のcommonブロック */
	chaptrptr = *(elem77_ptr->quad_const_var_aptr + i);
	for(j=0;j<*(elem77_ptr->quad_consts+i);j++) {
	    PUT(fp,",qc%d_%s",i+1,*(chaptrptr+j));
	}
	F77("\n");
    }
    comment1(fp);

    /* 菊地スペシャル  要素毎に基底関数が変化する場合 */
    if(solve_element_ptr->quad_type != NO) {
	int ii,jj;
	for(ii=0;ii<elem77_ptr->quad_methods;ii++) {
	    if(*(elem77_ptr->quad_terms+ii) == 0) continue;
	    
	    F77("      call ");
	    PUT(fp,ELEM_SET_NAME,solve_no,elem_no,ii+1);
	    F77("(");
	    for(jj=0;jj<elem_dat_ptr->nodes;jj++) {
		if(jj != 0) F77(",");

		switch(dimension) {           /* 節点順 */
		  case 1:
		    PUT(fp,"x%d",jj+1);
		    break;
		    
		  case 2:
		    PUT(fp,"x%d,y%d",jj+1,jj+1);
		    break;
		    
		  case 3:
		    PUT(fp,"x%d,y%d,z%d",jj+1,jj+1,jj+1);
		    break;
		    
		  default:
		    SystemAbort("空間次元に異常があります(make_eset)");
		}
	    }
	    F77(")\n");
	}
    }

    /* EA,EB配列初期化ルーチン作成 */
    F77("      do 10 i=1,NDF\n");
    F77("        do 11 j=1,NDF\n");
    F77("          ea(i,j) = 0.0d0\n");
    F77(" 11     continue\n");
    F77("        eb(i) = 0.0d0\n");
    F77(" 10   continue\n");


    /* 各数値積分法毎にecal内部ルーチン作成 */
    for(i=0;i<quad_methods;i++) {
	comment1(fp);

	if(*(elem77_ptr->quad_type+i) == ANALYTICAL) {

	    /* 解析的積分法 */
	    make_ecal_analytic(fp,solve_no,elem_no,i+1,solve_element_ptr);

	}
	else {
	    
	    /* 数値積分法 */
	    if(solve_element_ptr->nonlinear_flag == NO) {
		make_ecal_numerical(fp,solve_no,elem_no,i+1,solve_element_ptr);
	    }
	    else {
		make_ecal_numerical_nonlinear(fp,solve_no,elem_no,i+1,solve_element_ptr);
	    }
	}
    }

    COM;
    F77("      return\n");
    F77("      end\n");
    CloseFile(fp);

    return;
}

				    

