/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ncond_skyline.c
 *      Date:   1994/01/29
 *  Modified:   1994/08/01  ガウス数値積分次数の設定
 *                          BUG-FIX予定(FEM変数空間変数)
 *   
 *   Purpose:   ノイマン条件ルーチン作成
 *   Functions: 
 *              
 *              この関数はmake_solve_fort77から呼ばれる
 *
 *
 *              現在数値積分設定はこの関数内で行っている
 *
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void make_ncond_skyline(solve_no,ncond_no,solve_ptr,n_ptr)
     int            solve_no;   /* solve文番号       */
     int            ncond_no;   /* dirichlet条件番号 */
     Solve       *solve_ptr;
     NeumannData *n_ptr;
{
    int i,j;
    int flag;
    int dimension;
    
    int gauss_points;

    char buf[BUFSIZ];     /* 読み込み用 */

    int terms;            /* 数値積分が必要なterm */
    int dummy;
    char term[80];        /* termの名称 */
    char term2[BUFSIZ];   /* 評価式     */
    int xflag,yflag;      /* x座標、y座標が使われているかどうか */

    char **var_ptr;       /* 評価変数名格納場所 */
    char **expr_ptr;      /* 評価式格納場所     */
    int   *type_ptr;      /* 評価式のタイプ     */

    FILE *fp,*fp_read;
    char fname[FNAME_SIZE];

    int           etype;
    SolveElement *solve_element_ptr;
    EdgeBasis    *eb_ptr;


    double *gauss_w,*gauss_p;            /* ガウス積分点座標／重み */

    int freedom;

    /* term-convert関数用 */
    int term_converts;
    char *term_from[MAX_VARIABLES];
    char *term_to[MAX_VARIABLES];
    char name_buf[38];
    char name_buf2[38];

    /* elem-ecalデータ格納用 */
    char **expr_ba;
    char **expr_bb;
    
    int expr_ba_flag;   /* Matrixへの寄与があるかどうかを見分けるフラグ */

    /*====================================*/
    /* 対応するSolveElement構造体を求める */
    /*====================================*/

    /* 本来は、境界名称からsolve_element_ptr(domain)を求める */
    if(solve_ptr->solve_elements != 1) {
	SystemAbort("make_ncond_skyline内での多重domain未対応");
    }
    solve_element_ptr = *(solve_ptr->solve_elem_dat + 0);
    etype = solve_element_ptr->etype;


    /*=======================================
      境界でのFEM変数に対する局所要素節点番号
      方程式番号への＋α分を計算して
      EdgeBasis構造体を完成させる
      =======================================*/

    /* まずは、未知変数部分から、ついでに自由度を計算する */
    freedom = 0;
    for(i=0;i<solve_element_ptr->unknowns;i++) {
	MakeEdgeBasis_IEDPIENP(*(solve_element_ptr->unknown_name+i) ,
			       *(n_ptr->unknown_basis+i),
			       solve_element_ptr);

	eb_ptr = *(n_ptr -> unknown_basis + i);

	freedom = freedom + eb_ptr -> basis;   /* 自由度の計算 */
    }

    for(i=0;i<n_ptr->fem_vars;i++) {
	MakeEdgeBasis_IEDPIENP(*(n_ptr->fem_var_name + i),
			       *(n_ptr->fem_known_basis+i),
			       solve_element_ptr);
    }

    MakeEdgeBasis_IEDPIENP(SHAPE_FUNCTION_SYMBOL,
			   n_ptr->shape_basis,
			   solve_element_ptr);


    sprintf(fname,NCOND_FNAME,solve_no,ncond_no);

    StoreMakefile(fname,USER_LIBRARY);
    fp = OpenFileToWrite(fname);
    
    /*---
      subroutine文の作成
      ---*/
    F77("      subroutine ");
    PUT(fp,NCOND_NAME,solve_no,ncond_no);
    
    dimension = what_dimension();
    switch(dimension) {
      case 1:
	F77("(x");
	break;
	
      case 2:
	F77("(x,y");
	break;
	
      case 3:
	F77("(x,y,z");
	break;
	
      default:
	SystemAbort("what dimension ERROR(make_ncond_skyline)");
    }

    /*
     * 引き数  
     *         KH(*),KLD(*)
     *         IPD(*)       累積節点自由度
     *         
     */
    F77(",VFG,VKGD,VKGS,VKGI,KLD,KH,IPD,neq,ielem,matno,neelem,nenode");

    
    for(i=0;i<n_ptr->fem_vars;i++) {
	F77(",");
	PUT(fp,FEM_VAR_NAME77,*(n_ptr->fem_var_name + i));
    }

    for(i=0;i<n_ptr->scalar_vars;i++) {
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(n_ptr->scalar_var_name + i));
    }
    
    F77(")\n");

    /*============*/
    /*  定形宣言  */
    /*============*/
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);

    
    /*=========================*/
    /* 数値積分点のPARAMETER文 */
    /*  NPG = XX               */
    /* 境界要素自由度PARAMETER */
    /*  NDF = YY               */
    /*=========================*/
    PUT(fp,"      parameter (NPG = %d)\n",n_ptr ->gauss_points);
    PUT(fp,"      parameter (NDF = %d)\n",freedom);
    COM;

    /*=======================*/
    /* 引き数のdimension宣言 */
    /*=======================*/
    switch(dimension) {
      case 1:
	F77("      dimension x(*)\n");
	break;
      case 2:
	F77("      dimension x(*),y(*)\n");
	break;
      case 3:
	F77("      dimension x(*),y(*),z(*)\n");	
	break;
    }

    F77("      dimension VFG(*),VKGD(*),VKGS(*),VKGI(*),KLD(*),KH(*)\n");
    F77("      dimension IPD(*)\n");         
    F77("      dimension ielem(nenode,neelem)\n");
    F77("      dimension matno(*)\n");

    for(i=0;i<n_ptr->fem_vars;i++) {
	if(i==0) COM;
	F77("      dimension ");
	PUT(fp,FEM_VAR_NAME77,*(n_ptr->fem_var_name + i));
	F77("(*)\n");
    }

    for(i=0;i<n_ptr->scalar_vars;i++) {
	if(i==0) COM;
	F77("      real*8 ");
	PUT(fp,SCALAR_VAR_NAME77,*(n_ptr->scalar_var_name + i));
	F77("\n");
    }
    COM;

    /*================================*/
    /* 記録用のファイル読み込み その１*/
    /*   ESTファイル(関数一覧)        */
    /*================================*/
    sprintf(fname,EST_DAT_FILE,solve_no,ncond_no*100,1);
    fp_read = OpenFileToRead( fname );
    StoreDeletefile( fname );

    terms = geti_file(fp_read);
    var_ptr  = (char **)FEEL_GetMemory(sizeof(char *) * terms);
    expr_ptr = (char **)FEEL_GetMemory(sizeof(char *) * terms);
    type_ptr = (int   *)FEEL_GetMemory(sizeof(int   ) * terms);
    
    xflag    = NO;
    yflag    = NO;
    
    for(i=0;i<terms;i++) {
	fgets_file(buf,sizeof(buf),fp_read,"make_ncond_skyline");
	sscanf(buf,"%s %d %s",term,&dummy,term2);

	*(var_ptr +i) = MakeStringCopy( term  );
	*(expr_ptr+i) = MakeStringCopy( term2 );
	*(type_ptr+i) = dummy;

	if(streq("qx",term)) xflag = YES;
	if(streq("qy",term)) yflag = YES;
    }
    CloseFile( fp_read );

    /*================================*/
    /* 記録用のファイル読み込み その２*/
    /*   ESTファイル(関数一覧)        */
    /*================================*/
    sprintf(fname,ELEM_CAL_DAT_NAME,solve_no,ncond_no*100,1);
    fp_read = OpenFileToRead( fname );
    StoreDeletefile( fname );
    
    expr_ba_flag = NO;

    expr_ba = (char **)FEEL_GetMemory(sizeof(char *) * freedom * freedom);
    expr_bb = (char **)FEEL_GetMemory(sizeof(char *) * freedom );

    /* ba配列への読み込み */
    for(i=0;i<freedom;i++) {
	for(j=0;j<freedom;j++) {
	    if(!fgets(buf,sizeof(buf),fp_read)) {
		SystemAbort("ファイル読み込みエラー in ba reading...");
	    }
	    if(buf[strlen(buf)-1] == '\n') {
		buf[strlen(buf)-1] = '\0';
	    }
	    if(!streq(buf,LISP_EXP_ZERO)) {
		expr_ba_flag = YES;
	    }
	    *(expr_ba + i * freedom + j) = MakeStringCopy(buf);
	}
    }

    /* bbの読み込み */
    for(i=0;i<freedom;i++) {
	if(!fgets(buf,sizeof(buf),fp_read)) {
	    SystemAbort("ファイル読み込みエラー in bb reading...");
	}
	if(buf[strlen(buf)-1] == '\n') {
	    buf[strlen(buf)-1] = '\0';
	}
	*(expr_bb + i) = MakeStringCopy(buf);
    }

    CloseFile(fp_read);

    /*======================*/
    /* 数値積分用の配列宣言 */
    /*======================*/
    F77("      dimension gx(NPG),w(NPG)\n");
    for(i=0;i<terms;i++) {

	/* 空間変数無視 */
	if(streq(*(var_ptr+i),"qx")) continue;
	if(streq(*(var_ptr+i),"qy")) continue;
	
	PUT(fp,"      dimension %s(NPG)\n",*(var_ptr+i));
    }
    COM;
    
    /*===============================*/
    /*  境界要素行列ba,bbの配列宣言  */
    /*===============================*/
    F77("      dimension ba(NDF,NDF)\n");
    F77("      dimension bb(NDF)\n");
    F77("      dimension ikp(NDF)\n");
    COM;

    /*================================*/
    /* 自由度対応配列 iedp,ienpの宣言 */
    /*================================*/
    F77("      dimension ienp(NDF)\n");
    F77("      dimension iedp(NDF)\n");
    COM;
    /*==================================*/
    /* 自由度対応配列 iedp,ienpのdata文 */
    /*==================================*/

    flag = NO;
    F77("      data ienp/ ");
    for(i=0;i<solve_element_ptr->unknowns;i++) {
	eb_ptr = *(n_ptr -> unknown_basis + i);
	for(j=0;j<eb_ptr->basis;j++) {
	    if(flag == YES) F77(",");   /* 最初の一回だけは書かない */
	    flag = YES;
	    PUT(fp,"%d",*(eb_ptr->ienp+j));
	}
    }
    F77("/\n");

    flag = NO;
    F77("      data iedp/ ");
    for(i=0;i<solve_element_ptr->unknowns;i++) {
	eb_ptr = *(n_ptr -> unknown_basis + i);
	for(j=0;j<eb_ptr->basis;j++) {
	    if(flag == YES) F77(",");   /* 最初の一回だけは書かない */
	    flag = YES;
	    PUT(fp,"%d",*(eb_ptr->iedp+j));
	}
    }
    F77("/\n");


    comment1(fp);

    /*==============*/
    /* 処理の始まり */
    /*==============*/
    
    /* 数値積分点の代入 */
    gauss_p = gauss_point( n_ptr->gauss_points ); /* n点ガウス積分積分点座標 */
    gauss_w = gauss_weight(n_ptr->gauss_points ); /* n点ガウス積分積分点重み */

      
    for(i=0;i<n_ptr->gauss_points;i++) {
	switch(etype) {
	  case TRI:     /* r は 0 ≦ r ≦ 1 */
	    PUT(fp,"      gx(%d) = %19.15f\n",i+1,(*(gauss_p+i)+1.0) / 2.0);
	    PUT(fp,"       w(%d) = %19.15f\n",i+1,*(gauss_w+i) / 2.0);
	    break;
	    
	  case RECT:    /* r は -1 ≦ r ≦ 1 */
	    PUT(fp,"      gx(%d) = %19.15f\n",i+1,*(gauss_p+i) );
	    PUT(fp,"       w(%d) = %19.15f\n",i+1,*(gauss_w+i) );
	    break;

	  default:
	    SystemAbort("現在対応は三角形、四辺形のみ(@make_ncond_skyline)");
	}
    }
    COM;

    /*================================*/
    /* 数値積分評価点での評価式の計算 */
    /*================================*/
    switch(etype) {
      case TRI:
	F77("      S = 0.0D0\n");
	break;

      case RECT:
	F77("      S = -1.0D0\n");
	break;
	
      default:
	break;
    }
    COM;
    
    F77("      do 100 i=1,NPG\n");
    F77("        R = gx(i)\n");

    for(i=0;i<terms;i++) {
	/* 空間変数無視 */
	if(streq(*(var_ptr+i),"qx")) continue;
	if(streq(*(var_ptr+i),"qy")) continue;
	
	PUT(fp,"       %s(i) = %s\n",*(var_ptr+i),*(expr_ptr+i));
    }
    F77(" 100  continue\n"); 
    COM;

    /*====================*/
    /* 境界積分項計算本体 */
    /*====================*/
    F77("      do 200 i=1,neelem\n");
    COM;
    
    /* 節点座標値の展開 */
    for(i=0;i<n_ptr->boundary_points;i++) {
	PUT(fp,"       x%d = x(ielem(%d,i))\n",i+1,i+1);
	PUT(fp,"       y%d = y(ielem(%d,i))\n",i+1,i+1);
    }
    COM;

    /* 既知fem変数の値の展開 */
    for(i=0;i<n_ptr->fem_vars;i++) {
	eb_ptr = *(n_ptr->fem_known_basis + i);

	for(j=0;j<eb_ptr->basis;j++) {
	    PUT(fp,"       %s_%d = ",*(n_ptr->fem_var_name + i),j+1);
	    PUT(fp,FEM_VAR_NAME77,*(n_ptr->fem_var_name + i));
	    PUT(fp,"(ielem(%d,i))\n",*(eb_ptr->ienp+j));
	}
	COM;
    }

    /*===================*/
    /* eb,ea配列の初期化 */
    /*===================*/
    if(expr_ba_flag) {
	F77("       do 210 j=1,NDF\n");
	F77("       do 220 k=1,NDF\n");
	F77("        ba(j,k) = 0.0d0\n");
	F77(" 220   continue\n");
	F77(" 210   continue\n");
    }
    F77("       do 230 j=1,NDF\n");
    F77("        bb(j)=0.0d0\n");
    F77(" 230   continue\n");
    COM;

    /*==========================*/
    /* term convert用配列の作成 */
    /*    
     *  Q1_4   →  qQ1_4(itp)   
     *
     *                          */
    /*==========================*/
    term_converts = 0;

    if(xflag == YES) {
	term_from[term_converts] = "x";
	term_to[term_converts]   = X_IN_QUAD;
	term_converts++;
    }

    if(yflag == YES) {
	term_from[term_converts] = "y";
	term_to[term_converts]   = Y_IN_QUAD;
	term_converts++;
    }

    /* スカラー変数 */
    for(i=0;i<n_ptr->scalar_vars;i++) {
	if(term_converts == MAX_VARIABLES) {
	    SystemAbort("too many term converts in ncond_skyline");
	}
	term_from[term_converts] = *(n_ptr->scalar_var_name + i);
	sprintf(name_buf,SCALAR_VAR_NAME77,*(n_ptr->scalar_var_name + i));
	term_to[term_converts] = MakeStringCopy( name_buf );
	term_converts++;
    }

    /* 微分作用素なしの基底関数だけを書く、微分作用素がある奴は
     * エラーにしよう      
     */
    for(i=0;i<terms;i++) {
	if(*(type_ptr + i) == 0) {
	    if(streq(*(var_ptr + i),X_IN_QUAD)) continue;
	    if(streq(*(var_ptr + i),Y_IN_QUAD)) continue;
	    if(streq(*(var_ptr + i),Z_IN_QUAD)) continue;

	    if(term_converts == MAX_VARIABLES) {
		SystemAbort("too many term converts in ncond_skyline");
	    }
	    
	    sprintf(name_buf,"%s(itp)",*(var_ptr + i));
	    term_from[term_converts] = *(var_ptr + i) + 1;/* 先頭のqをよける */
	    term_to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;
	}
    }

/*
    for(i=0;i<terms;i++) {
	switch(*(type_ptr + i)) {
	  case 0:
	    break;

	  default:
	    SystemWarning_yy("現在ノイマン条件内に微分作用素は使用不可",n_ptr->yylineno);
	}
    }
   */

    /*========================*/
    /* 各積分点毎の足し込本体 */
    /*========================*/
    F77("       do 300 itp = 1, NPG\n");
    COM;

    /* sqrt( (dx/dt)^2 + (dy/dt)^2)の計算 */
    /* 形状変換関数 */
    eb_ptr = n_ptr->shape_basis;
    F77("      dx = ");
    for(i=0;i<eb_ptr->basis;i++) {
	if(i != 0) {
	    F77("+");
	}
	PUT(fp," x%d*q%s_%d_x(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
	    *(eb_ptr->basis_no+i)+1);
    }
    F77("\n");

    /* 空間変数がある場合 */
    if(xflag == YES) {
	F77("      qx = ");
	for(i=0;i<eb_ptr->basis;i++) {
	    if(i != 0) {
		F77("+");
	    }
	    PUT(fp,"x%d*q%s_%d(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
		*(eb_ptr->basis_no+i)+1);
	}
	F77("\n");
    }

    /* 空間変数 y がある場合 */
    if(yflag == YES) {
	F77("      qy = ");
	for(i=0;i<eb_ptr->basis;i++) {
	    if(i != 0) {
		F77("+");
	    }
	    PUT(fp,"y%d*q%s_%d(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
		*(eb_ptr->basis_no+i)+1);
	}
	F77("\n");
    }


    F77("      dy = ");
    for(i=0;i<eb_ptr->basis;i++) {
	if(i != 0) {
	    F77("+");
	}
	PUT(fp," y%d*q%s_%d_x(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
	    *(eb_ptr->basis_no+i)+1);
    }
    F77("\n");

    F77("      ds = sqrt(dx*dx+dy*dy)*w(itp)\n");
    

    /*====================*/
    /* 境界要素への足し込 */
    /*====================*/
    if(expr_ba_flag) {
	for(i=0;i<freedom;i++) {
	    for(j=0;j<freedom;j++) {

		if(streq(*(expr_ba + i*freedom + j),LISP_EXP_ZERO)) continue;

		PUT(fp,"        ba(%d,%d)=ba(%d,%d)+(",i+1,j+1,i+1,j+1);
		PUT(fp,"%s)*ds\n",term_convert(*(expr_ba+i*freedom+j),
					       term_from,
					       term_to,
					       term_converts));
	    }
	}
	COM;
    }
    /*====================*/
    /* 境界荷重への足し込 */
    /*====================*/
    for(i=0;i<freedom;i++) {
	if(streq(*(expr_bb+i),LISP_EXP_ZERO)) continue;
	
	PUT(fp,"       bb(%d)=bb(%d)+(",i+1,i+1);
	PUT(fp,"%s)*ds\n",term_convert(*(expr_bb+i),
				       term_from,
				       term_to,
				       term_converts));
    }
    COM;

    F77(" 300  continue\n");

    /*==========================*/
    /* 全体行列、荷重への足し込 */
    /*==========================*/
    F77("       do 400 j=1,NDF\n");
    F77("        ikp(j) = IPD(ielem(ienp(j),i)) + iedp(j)\n");
    F77(" 400   continue\n");
    COM;

    if(expr_ba_flag) {

	/* 境界要素小行列がある場合 */
	F77("       do 600 j=1,NDF\n");
	F77("         jp = ikp(j)\n");
	COM;
	F77("         do 700 k=1,NDF\n");
	F77("            kp = ikp(k)\n");
	COM;
	F77("         if(kp .EQ. jp) goto 705\n");
	F77("         if(kp .GT. jp) goto 710\n");
	COM;
	F77("         lp = KLD(jp+1)-jp+kp\n");
	F77("         VKGI(lp) = VKGI(lp) + ba(j,k)\n");
	F77("         goto 700\n");
	COM;
	F77(" 705     VKGD(jp) = VKGD(jp) + ba(j,j)\n");
	F77("         VFG(jp)  = VFG(jp)  + bb(j)\n");
	F77("         goto 700\n");
	COM;
	F77(" 710     lp = KLD(kp+1)-kp+jp\n");
	F77("         VKGS(lp) = VKGS(lp) + ba(j,k)\n");
	COM;
	F77(" 700   continue\n");
	COM;
	F77(" 600  continue\n");
	COM;
    }
    else {
	/* 境界要素小行列がない場合 */
	F77("       do 600 j=1,NDF\n");
	F77("         VFG(ikp(j)) = VFG(ikp(j)) + bb(j)\n");
	F77(" 600   continue\n");
	COM;
    }

    F77(" 200  continue\n");
    COM;



    F77("      return\n");
    F77("      end\n");
      

    CloseFile(fp);

    return;
}
