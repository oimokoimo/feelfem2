/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ecal_numerical_nonlinear.c
 *      Date:   1994/03/01
 *   
 *   Purpose:   数値積分法に対応するecal***ルーチンを作成する(非線形版)
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../element/element.h"
#include "../quadrature/quadrature.h"
#include "../var_comp/var_comp.h"

extern int noediv_flag;

void make_ecal_numerical_nonlinear(fp,solve_no,elem_no,quad_no,
				   solve_element_ptr)
     FILE *fp;
     int solve_no;
     int elem_no;
     int quad_no;                     /* これは１から始まる番号を与える */
     SolveElement *solve_element_ptr;
{
    int i,j,k;

    int ndf;       /* 要素内小行列の次元 */
    int do_label;  /* 積分点ループの番号 */
    int *ienp;     /* 局所節点番号配列   */

    int err_flag;

    FILE *fpr;

    Quadrature *quad_ptr;
    Element    *element_ptr;
    FEMvarinfo  *fem_varinfo_ptr;
    FEMvarinfo  *shape_varinfo_ptr;
    FEMvarinfo **fem_varinfo_ptrptr;
    ElementFORT77 *elem77_ptr;
    EWISE_type  *ewise_type_ptr;
    char *quad_name;                  /* 数値積分法の名称 */

    /* 空間変数がある場合の処理フラグ */
    int x_flag,y_flag,z_flag;

    char fname[FNAME_SIZE];
    char buf[EXPR_BUFSIZ];
    char name_buf[38];   /* term convert用 */
    char name_buf2[38];

    /* 数値積分上に現れる補間関数 make_elem_commonsにて設定のもの 
       term convertにて利用                                             */
    int    quad_terms;
    char **quad_term_var_ptr;    /* 先頭にq付きの基底関数名へのポインタ */
    int   *quad_term_type_ptr;   /* 変数の微分に関するフラグ            */

    /* term convert用作業配列 */
    int terms;
    char *from[MAX_TERM_VARS];
    char *to  [MAX_TERM_VARS];

    int   total_freedom;
    int   freedom;   /* 非線形問題用 */
    char *element_name;

    /*=======================================================*/
    
    /* 各パラメータの設定 */
    elem77_ptr = solve_element_ptr -> elem77_dat;

    /*  この関数への引き数quad_noが 1 から始まることに注意する事 */
    quad_name  = *(elem77_ptr->quad_name + (quad_no -1));
    quad_ptr   = get_quadrature_ptr_by_name( quad_name );
					     
    fem_varinfo_ptrptr = elem77_ptr -> fem_var_info_ptrptr;

    quad_terms         = *(elem77_ptr->quad_terms          + (quad_no - 1));
    quad_term_var_ptr  = *(elem77_ptr->quad_term_var_aptr  + (quad_no - 1));
    quad_term_type_ptr = *(elem77_ptr->quad_term_type_aptr + (quad_no - 1));

    /* 空間変数フラグ */
    x_flag             = *(elem77_ptr->x_flag + (quad_no -1 ));
    y_flag             = *(elem77_ptr->y_flag + (quad_no -1 ));
    z_flag             = *(elem77_ptr->z_flag + (quad_no -1 ));

    ndf = elem77_ptr -> elem_freedom;


    do_label = quad_no * 100;  /* 数値積分点繰り返しの為の文番号 */


    /* 形状関数に対するFEMvarinfo構造体の取得 */
    err_flag = YES;
    for(i=0;i<elem77_ptr->fem_vars;i++) {
	fem_varinfo_ptr = *(fem_varinfo_ptrptr + i);
	if(streq(fem_varinfo_ptr-> fem_var_name , SHAPE_FUNCTION_SYMBOL)) {
	    err_flag = NO;
	    break;
	}
    }
    if(err_flag == YES) {
	SystemAbort("Internal Error:make_ecal_numeraical(shape function err)");
    }
    shape_varinfo_ptr = fem_varinfo_ptr;  /* 形状関数へのvarinfoをキープする */
    ienp = fem_varinfo_ptr->ienp;

    comment1(fp);
    PUT(fp,"      do %d itp = 1, NPG%d\n",do_label, quad_no);
    
    /*======================*/
    /* ここから積分点毎処理 */
    /*======================*/
    
    switch(quad_ptr -> dimension) {
      case 1:
	SystemAbort("１次元は未作成 (make_ecal_numerical.c) ");
	break;
	
      case 3:
	SystemAbort("１次元は未作成 (make_ecal_numerical.c) ");

      case 2:
	
	F77("      rj(1,1) = ");
	for(i=0;i<fem_varinfo_ptr->freedom;i++) {
	    if(i != 0) F77(" + ");
	    PUT(fp,"x%d*q%s_%d_x_%d(itp)",*(ienp+i), /* 局所節点番号 */
		fem_varinfo_ptr-> element_name,  /* 要素名(element名) */
		i+1,                              /* 基底関数通し番号  */
		quad_no);                         /* 積分番号          */
	}
	F77("\n");

	F77("      rj(1,2) = ");
	for(i=0;i<fem_varinfo_ptr->freedom;i++) {
	    if(i != 0) F77(" + ");
	    PUT(fp,"y%d*q%s_%d_x_%d(itp)",*(ienp+i), /* 局所節点番号 */
		fem_varinfo_ptr-> element_name,  /* 要素名(element名) */
		i+1,                              /* 基底関数通し番号  */
		quad_no);                         /* 積分番号          */
	}
	F77("\n");

	F77("      rj(2,1) = ");
	for(i=0;i<fem_varinfo_ptr->freedom;i++) {
	    if(i != 0) F77(" + ");
	    PUT(fp,"x%d*q%s_%d_y_%d(itp)",*(ienp+i), /* 局所節点番号 */
		fem_varinfo_ptr-> element_name,   /* 要素名(element名) */
		i+1,                              /* 基底関数通し番号  */
		quad_no);                         /* 積分番号          */
	}
	F77("\n");

	F77("      rj(2,2) = ");
	for(i=0;i<fem_varinfo_ptr->freedom;i++) {
	    if(i != 0) F77(" + ");
	    PUT(fp,"y%d*q%s_%d_y_%d(itp)",*(ienp+i), /* 局所節点番号 */
		fem_varinfo_ptr-> element_name,  /* 要素名(element名) */
		i+1,                              /* 基底関数通し番号  */
		quad_no);                         /* 積分番号          */
	}
	F77("\n");
	COM;

	F77("      det = rj(1,1)*rj(2,2) - rj(1,2)*rj(2,1)\n");
	COM;

	F77("      rij(1,1)= rj(2,2)/det\n");
	F77("      rij(2,2)= rj(1,1)/det\n");
	F77("      rij(1,2)=-rj(1,2)/det\n");
	F77("      rij(2,1)=-rj(2,1)/det\n");
	COM;
	PUT(fp,"      wt  = det * w%d(itp)\n",quad_no);
	break;
	
      default:
	SystemAbort("Inner Error(Illegal dimension in quad_ptr(make_ecal_numerical)");
    }
    
    /*------------------------*/
    /* term convert用配列作成 */
    /*------------------------*/
    /*==============
      変更変数の一覧    特に非線形問題処理に関して注意すること
      ==============
      空間変数 x,y,z  -> GX_NAME77

      スカラー変数
      
      ewise変数
      
      ☆微分以外の基底関数の変更(estXX-YY-ZZ.dat)に登録のもの

      Q1_4   →  qQ1_4_##(itp)      char **quad_term_var_ptr    = *name
                 ^    ^^^^^^^^      int   *quad_term_type_ptr   = *0

      注意：微分値を含むものはLISPプログラムにて変換される
            空間変数 X_IN_QUAD,Y_IN_QUAD,Z_IN_QUAD は、無視する

		 
      ☆element文に出現する変数(保留:eset系ルーチンで、const変数に対する
                                     代入が必要                   dbg: )

      ☆quadrature文に指定されるdouble変数
           (これは、内挿法指定数値積分計算の補助の為に用いられる)
      ☆内挿法指定数値積分
           (これは、各数値積分点での値をまず配列(大きさitpの)に代入する)

      ★非線形問題
        M1 → U_1など
      ======================================================*/
    terms = 0;

    if(x_flag == YES) {
	from[terms] = "x";
	to[terms]   = X_IN_QUAD;
	terms++;
    }
    
    if(y_flag == YES) {
	from[terms] = "y";
	to[terms]   = Y_IN_QUAD;
	terms++;
    }
    
    if(z_flag == YES) {
	from[terms] = "z";
	to[terms]   = Z_IN_QUAD;
	terms++;
    }
    


    /* スカラー変数 */
    for(i=0;i<solve_element_ptr->scalar_knowns;i++) {
	if(terms == MAX_TERM_VARS) {
	    SystemAbort("Too many term converts(make_ecal_numerical)");
	}
	from[terms] = *(solve_element_ptr->scalar_known_name+i);
	sprintf(name_buf,"sc_%s",*(solve_element_ptr->scalar_known_name+i));
	to[terms] = MakeStringCopy(name_buf);
	terms++;
    }

    /* ewise変数 */
    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	if(terms == MAX_TERM_VARS) {
	    SystemAbort("Too many term converts(make_ecal_numerical)");
	}
	from[terms] = *(solve_element_ptr->ewise_known_name+i);
	ewise_type_ptr = get_ewise_type_ptr_by_2name(from[terms],
						     solve_element_ptr->
						     domain_name);
	if( ewise_type_ptr -> quadrature != NULL &&
	    streq(ewise_type_ptr->quadrature,quad_name)) {
	    sprintf(name_buf,"ew_%s(itp)",from[terms]);
	}
	else {
	    sprintf(name_buf,"ew_%s",from[terms]);
	}

	to[terms] = MakeStringCopy(name_buf);
	terms++;
    }

    /* 微分作用素無しの基底関数 */
    for(i=0;i<quad_terms;i++) {
	if(*(quad_term_type_ptr + i ) == 0) {
	    if(streq(*(quad_term_var_ptr+i),X_IN_QUAD)) continue;
	    if(streq(*(quad_term_var_ptr+i),Y_IN_QUAD)) continue;
	    if(streq(*(quad_term_var_ptr+i),Z_IN_QUAD)) continue;

	    if(terms == MAX_TERM_VARS) {
		SystemAbort("Too many term converts(make_ecal_numerical)");
	    }
	    sprintf(name_buf,"%s_%d(itp)",*(quad_term_var_ptr+i),quad_no);
	    from[terms] = *(quad_term_var_ptr +i) + 1;  /* 先頭の'q'をよける */
	    to[terms] =     MakeStringCopy(name_buf);
	    terms++;
	}
    }

    /* 非線形問題 */
    total_freedom = 0;
    for(i=0;i<solve_element_ptr->unknowns;i++) {
	element_name=get_elem_name_by_ND(*(solve_element_ptr->unknown_name+i),
					 solve_element_ptr->domain_name);
	element_ptr = get_element_ptr_by_name(element_name);
	freedom = element_ptr -> basis;

	/* エルミートに対して考慮せず (dbg: ま、これはelemの呼び出しも同じ)*/
	for(j=0;j<freedom;j++) {
	    total_freedom++;
	    sprintf(name_buf,"M%d",total_freedom);
	    from[terms] = MakeStringCopy(name_buf);
	    sprintf(name_buf,"%s_%d",*(solve_element_ptr->unknown_name+i),j+1);
	    to[terms] = MakeStringCopy(name_buf);
	    terms++;
	}
    }
	
    
    /* element文内 double変数で、各積分点毎に評価する変数名のchange */
    

    /*-------------------------------------------------------------------*/

    /* 微分作用素を含む基底関数の計算 */
    COM;

    if(quad_ptr->dimension == 1) {
	SystemAbort("１次元版はまだ作っていません");
    }

    if(quad_ptr->dimension == 3) {
	SystemAbort("３次元版はまだ作っていません");
    }

    /* 2次元の場合 */
    if(quad_ptr->dimension == 2) {
    
	for(i=0;i<quad_terms;i++) {
	    switch(*(quad_term_type_ptr + i)) {
	      case 0:  /* 微分しない */
		break;
		
	      case 1:  /* ｘ微分   */
		PUT(fp,"      %s_%dP = ",*(quad_term_var_ptr+i),quad_no);
		PUT(fp,"rij(1,1)*");
		CutLastCharPRT(fp,*(quad_term_var_ptr+i));
		PUT(fp,"x_%d(itp) +",quad_no);
		PUT(fp,"rij(1,2)*");
		CutLastCharPRT(fp,*(quad_term_var_ptr+i));
		PUT(fp,"y_%d(itp)\n",quad_no);
		break;

	      case 10: /* ｙ微分 */
		PUT(fp,"      %s_%dP = ",*(quad_term_var_ptr+i),quad_no);
		PUT(fp,"rij(2,1)*");
		CutLastCharPRT(fp,*(quad_term_var_ptr+i));
		PUT(fp,"x_%d(itp) +",quad_no);
		PUT(fp,"rij(2,2)*");
		CutLastCharPRT(fp,*(quad_term_var_ptr+i));
		PUT(fp,"y_%d(itp)\n",quad_no);
		break;		
		
	      default:
		SystemAbort("現在対応していない微分作用素が使われました(make_ecal_numerical)");
	    }
	}
    }
		
    /* 空間変数がある時の処理 */
    ienp = shape_varinfo_ptr -> ienp;
    if(x_flag == YES || y_flag  == YES || z_flag == YES) comment1(fp);

    if(x_flag == YES) {
	PUT(fp,"      %s = ",X_IN_QUAD);
	for(i=0;i<shape_varinfo_ptr->freedom;i++) {
	    if(i != 0) F77(" + ");
	    PUT(fp,"x%d*q%s_%d_%d(itp)",*(ienp+i),  /* 局所節点番号 */
		shape_varinfo_ptr->element_name,    /* 要素名(element名) */
		i+1,                                /* 基底関数通し番号  */
		quad_no);                           /* 積分番号          */
	}
	F77("\n");
    }

    if(y_flag == YES) {
	PUT(fp,"      %s = ",Y_IN_QUAD);
	for(i=0;i<shape_varinfo_ptr->freedom;i++) {
	    if(i != 0) F77(" + ");
	    PUT(fp,"y%d*q%s_%d_%d(itp)",*(ienp+i),  /* 局所節点番号 */
		shape_varinfo_ptr->element_name,    /* 要素名(element名) */
		i+1,                                /* 基底関数通し番号  */
		quad_no);                           /* 積分番号          */
	}
	F77("\n");
    }


    if(z_flag == YES) {
	PUT(fp,"      %s = ",Z_IN_QUAD);
	for(i=0;i<shape_varinfo_ptr->freedom;i++) {
	    if(i != 0) F77(" + ");
	    PUT(fp,"z%d*q%s_%d_%d(itp)",*(ienp+i),  /* 局所節点番号 */
		shape_varinfo_ptr->element_name,    /* 要素名(element名) */
		i+1,                                /* 基底関数通し番号  */
		quad_no);                           /* 積分番号          */
	}
	F77("\n");
	
    }


    /*========================*/
    /* 入力データファイルOPEN */
    /*========================*/
    sprintf(fname,ELEM_CAL_DAT_NAME,solve_no,elem_no,quad_no);

    fpr = OpenFileToRead(fname);
    StoreDeletefile( fname );
    

    comment1(fp);
    /*==========================*/
    /* 要素小行列への足し込処理 */
    /*==========================*/
    for(i=0;i<ndf;i++) {
	for(j=0;j<ndf;j++) {
	    if(!fgets(buf,sizeof(buf),fpr)) {
		SystemAbort("ファイル読み込みエラー(make_ecal_numerical)");
	    }
	    if(strlen(buf) >= EXPR_BUFSIZ - 1 - 100) {  /* 100 は安全係数 */
		SystemAbort("数式が複雑すぎる(make_ecal_numerical)");
	    }
	    if(buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = '\0';
	    if(streq(buf,LISP_EXP_ZERO)) {
		continue;                    /* ０は足し込まない */
	    }
	    
            if(strlen(buf) > LIMIT_LINE && noediv_flag != YES) {
              make_ecal_elem_div(term_convert(buf,from,to,terms),fp);
              PUT(fp,"      ea(%d,%d)=ea(%d,%d)+dt*wt\n",i+1,j+1,i+1,j+1);
            } 
            else {
	      PUT(fp,"      ea(%d,%d)=ea(%d,%d)+(",i+1,j+1,i+1,j+1);
	      PUT(fp,"%s)*wt\n",term_convert(buf,from,to,terms));
            }
	    /*
	    PUT(fp,"      ea(%d,%d)=ea(%d,%d)+(",i+1,j+1,i+1,j+1);
	    PUT(fp,"%s)*wt\n",term_convert(buf,from,to,terms));
	    */
	}
    }
    COM;

    /*============================*/
    /* 要素荷重項への足し込み処理 */
    /*============================*/
    for(i=0;i<ndf;i++) {
	if(!fgets(buf,sizeof(buf),fpr)) {
	    SystemAbort("ファイル読み込みエラー(make_ecal_numerical)");
	}
	if(buf[strlen(buf)-1] == '\n') buf[strlen(buf)-1] = '\0';
	if(streq(buf,LISP_EXP_ZERO)) {
	    continue;                    /* ０は足し込まない */
	}
	    
        if(strlen(buf) > LIMIT_LINE && noediv_flag != YES) {
          make_ecal_elem_div(term_convert(buf,from,to,terms),fp);
          PUT(fp,"      eb(%d)=eb(%d)+dt*wt\n",i+1,i+1);
        }
        else {
	  PUT(fp,"      eb(%d)=eb(%d)+(",i+1,i+1);
	  PUT(fp,"%s)*wt\n",term_convert(buf,from,to,terms));
        }
    }
    CloseFile(fpr);


    comment1(fp);
    PUT(fp,"%5d continue\n",do_label);


    return;

}


static CutLastCharPRT(fp , s )   /* 最後の文字だけ出力しない */
     FILE *fp;
     char *s;
{
    while(*(s+1)) {
	PUT(fp,"%c",*s);
	s++;
    }
    return;
}

