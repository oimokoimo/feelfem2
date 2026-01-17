/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ncondgen.c
 *  Date     : 2000/01/13
 *  Modified : 2000/01/14
 *  
 *  Purpose  : Output neumann data
 *  
 */


#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void ncondgen(solve_no,ncond_no,solve_ptr,n_ptr)
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

    FILE *GetFEELFEMFP();



    if(solve_ptr->solve_elements != 1) {
	SystemAbort("make_ncond_skyline内での多重domain未対応");
    }
    solve_element_ptr = *(solve_ptr->solve_elem_dat + 0);
    etype = solve_element_ptr->etype;



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


    fp = GetFEELFEMFP();
    
    fprintf(fp,"%8d%8d  ***ncond(ncondgen)\n",solve_no,ncond_no);
    

    /* for NPG */
    fprintf(fp,"%8d  (NPG)\n",n_ptr ->gauss_points);
    fprintf(fp,"%8d  (NDF)\n",freedom);


    sprintf(fname,EST_DAT_FILE,solve_no,ncond_no*100,1);
    fp_read = fopen( fname ,"r");
    if(fp_read==NULL) {
      fprintf(stderr,"Cannot open %s(ncondgen)\n",fname);
      exit(1);
    }

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
    fclose( fp_read );

    sprintf(fname,ELEM_CAL_DAT_NAME,solve_no,ncond_no*100,1);
    fp_read = fopen(fname,"r");
    if(fp_read==NULL) {
      fprintf(stderr,"Cannot open %s(ncondgen)\n",fname);
      exit(1);
    }
    
    expr_ba_flag = NO;

    expr_ba = (char **)FEEL_GetMemory(sizeof(char *) * freedom * freedom);
    expr_bb = (char **)FEEL_GetMemory(sizeof(char *) * freedom );

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

    for(i=0;i<freedom;i++) {
	if(!fgets(buf,sizeof(buf),fp_read)) {
	    SystemAbort("ファイル読み込みエラー in bb reading...");
	}
	if(buf[strlen(buf)-1] == '\n') {
	    buf[strlen(buf)-1] = '\0';
	}
	*(expr_bb + i) = MakeStringCopy(buf);
    }

    fclose(fp_read);

    fprintf(fp,"***START OF QUADRATURE array\n");
    for(i=0;i<terms;i++) {

	if(streq(*(var_ptr+i),"qx")) continue;
	if(streq(*(var_ptr+i),"qy")) continue;
	
	fprintf(fp,"%s\n",*(var_ptr+i));
    }
    fprintf(fp,"***END OF QUADRATURE array\n");
    

    flag = NO;
    fprintf(fp,"****START OF IENP\n");
    for(i=0;i<solve_element_ptr->unknowns;i++) {
	eb_ptr = *(n_ptr -> unknown_basis + i);
	for(j=0;j<eb_ptr->basis;j++) {
	    fprintf(fp,"%d\n",*(eb_ptr->ienp+j));
	}
    }
    fprintf(fp,"****END OF IENP\n");

    fprintf(fp,"*****START OF IEDP\n");
    for(i=0;i<solve_element_ptr->unknowns;i++) {
	eb_ptr = *(n_ptr -> unknown_basis + i);
	for(j=0;j<eb_ptr->basis;j++) {
	    PUT(fp,"%d\n",*(eb_ptr->iedp+j));
	}
    }
    fprintf(fp,"*****END OF IEDP\n");


    /* 980728  Modified for feelweb */
    /*    ncond_element_parameter( fp , solve_element_ptr);*/  /* caution! */



    gauss_p = gauss_point( n_ptr->gauss_points ); /* n点ガウス積分積分点座標 */
    gauss_w = gauss_weight(n_ptr->gauss_points ); /* n点ガウス積分積分点重み */

    
    fprintf(fp,"%8d   (gauss_points)\n",n_ptr->gauss_points);
    for(i=0;i<n_ptr->gauss_points;i++) {
	switch(etype) {
	  case TRI:     /* r は 0 ≦ r ≦ 1 */
	    PUT(fp,"%19.15f     (gx(%d))\n",(*(gauss_p+i)+1.0) / 2.0,i+1);
	    PUT(fp,"%19.15f     ( w(%d))\n",(*(gauss_w+i)    ) / 2.0,i+1);
	    break;
	    
	  case RECT:    /* r は -1 ≦ r ≦ 1 */
	    PUT(fp,"%19.15f     (gx(%d))\n",*(gauss_p+i),i+1 );
	    PUT(fp,"%19.15f     ( w(%d))\n",*(gauss_w+i),i+1 );
	    break;

	  default:
	    SystemAbort("現在対応は三角形、四辺形のみ(@make_ncond_skyline)");
	}
    }

    switch(etype) {
      case TRI:
	fprintf(fp,"0.0D0        (S VALUE TRIANGLE)\n");
	break;

      case RECT:
	fprintf(fp,"-1.0D0       (S VALUE RECTANBLE)\n");
	break;
	
      default:
	break;
    }
    
    fprintf(fp,"**** START OF TERMS\n");
    for(i=0;i<terms;i++) {
	if(streq(*(var_ptr+i),"qx")) continue;
	if(streq(*(var_ptr+i),"qy")) continue;
	fprintf(fp,"%s(i)  %s\n",*(var_ptr+i),*(expr_ptr+i));
    }
    fprintf(fp,"**** END OF TERMS\n");


    fprintf(fp,"%8d  (boundary_points for LOOP 200)\n",n_ptr->boundary_points);
    fprintf(fp,"%8d  (n_ptr->fem_vars)\n",n_ptr->fem_vars);

    if(n_ptr->fem_vars) { fprintf(fp,"***START OF FEM VARS FORMULA\n"); }
    for(i=0;i<n_ptr->fem_vars;i++) {
	eb_ptr = *(n_ptr->fem_known_basis + i);

	for(j=0;j<eb_ptr->basis;j++) {
	    PUT(fp,"       %s_%d = ",*(n_ptr->fem_var_name + i),j+1);
	    PUT(fp,FEM_VAR_NAME77,*(n_ptr->fem_var_name + i));
	    PUT(fp,"(ielem(%d,i))\n",*(eb_ptr->ienp+j));
	}
    }
    if(n_ptr->fem_vars) { fprintf(fp,"***END OF FEM VARS FORMULA\n"); }


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



    eb_ptr = n_ptr->shape_basis;
    fprintf(fp,"*** dx formula\n");
    for(i=0;i<eb_ptr->basis;i++) {
	if(i != 0) {
	  fprintf(fp,"+");
	}
	fprintf(fp," x%d*q%s_%d_x(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
	    *(eb_ptr->basis_no+i)+1);
    }
    F77("\n");


    fprintf(fp,"*** dy formula\n");
    for(i=0;i<eb_ptr->basis;i++) {
	if(i != 0) {
	  fprintf(fp,"+");
	}
	fprintf(fp," y%d*q%s_%d_x(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
	    *(eb_ptr->basis_no+i)+1);
    }
    F77("\n");




    fprintf(fp,"%8d    (xflag for qx assignment existence flag)\n",
	    xflag);
    if(xflag == YES) {
      fprintf(fp,"*** qx formula\n");

	for(i=0;i<eb_ptr->basis;i++) {
	    if(i != 0) {
		fprintf(fp,"+");
	    }
	    fprintf(fp,"x%d*q%s_%d(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
		*(eb_ptr->basis_no+i)+1);
	}
	F77("\n");
    }


    fprintf(fp,"%8d    (yflag for qy assignment existence flag)\n",
	    yflag);
    if(yflag == YES) {
      fprintf(fp,"*** qy formula\n");
	for(i=0;i<eb_ptr->basis;i++) {
	    if(i != 0) {
	      fprintf(fp,"+");
	    }
	    fprintf(fp,"y%d*q%s_%d(itp)",*(eb_ptr->ienp+i),eb_ptr->element_name,
		*(eb_ptr->basis_no+i)+1);
	}
	F77("\n");
    }



    fprintf(fp,"%8d     (expr_ba_flag, again)\n",expr_ba_flag);
    if(expr_ba_flag) {
	for(i=0;i<freedom;i++) {
	    for(j=0;j<freedom;j++) {

	      /*if(streq(*(expr_ba + i*freedom + j),LISP_EXP_ZERO)) continue;
	       */
	      fprintf(fp,"%d %d (ba for i,j ba(%d,%d))\n",i+1,j+1,i+1,j+1);
		PUT(fp,"%s\n",term_convert(*(expr_ba+i*freedom+j),
					       term_from,
					       term_to,
					       term_converts));
	    }
	}
	/* end of ba */
	fprintf(fp,"***** END OF BA FORMULA\n");
    }


    fprintf(fp,"%8d    (freedom again for bb) \n",freedom);
    for(i=0;i<freedom;i++) {
      /*	if(streq(*(expr_bb+i),LISP_EXP_ZERO)) continue; */
	
      fprintf(fp,"%8d  (bb(%d))\n",i+1,i+1);
      fprintf(fp,"%s\n",term_convert(*(expr_bb+i),
				       term_from,
				       term_to,
				       term_converts));
    }
    fprintf(fp,"owari for Neumanndata (solve%d/ncond%d)\n",solve_no,ncond_no);

    return;
}
