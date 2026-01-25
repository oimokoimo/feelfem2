/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_solve_ctrl77_MPPSCG.c
 *      Date:   1994/04/18
 *  Modified:   1996/02/07(Wed)
 *   
 *   Purpose:   solveブロックのコントロールfortranプログラムの生成(CG系解法)
 *   Functions: 並列処理系用
 *              
 *              各solve文の作成ルーチン、入力は、solve文構造体
 *              SolveFORT77 構造体が入力となる
 *              
 *              
 */

#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../system/system.h"
#include "../feel_def/basic_struct.h"
#include "../solve_comp/solve_comp.h"

#include "../parallel/parallel.h"
#include "solve_fort77_funcs.h"

make_solve_ctrl77_MPPSCG( solve_ptr, solve77_ptr ,CG_type)
     Solve       *solve_ptr;
     SolveFORT77 *solve77_ptr;
     int CG_type;
{
    int i,j;
    int flag;
    
    int solve_no;
    
    int elemg;   /* 要素グループの個数、SolveElementの数 */
    int solve_elements;  /* 上と重複しているが… */
    SolveElement *solve_element_ptr;
    
    int max_nodes;
    int dconds,nconds;
    
    FILE *fp;
    
    ElementFORT77 **elem77_ptrptr,*elem77_ptr;   
    ElemDat        *elem_dat_ptr;
    DirichletData **d_ptrptr,*d_ptr; 
    NeumannData   **n_ptrptr,*n_ptr;
   
    char fname[30];
    
    /* 基本変数コピー */
    solve_no      = solve77_ptr -> solve_no;
    elemg         = solve77_ptr -> elemg;
    solve_elements= solve_ptr   -> solve_elements;
    elem77_ptrptr = solve77_ptr -> elem77_ptrptr;
    max_nodes     = solve77_ptr -> max_nodes;


    dconds   = solve_ptr -> d_conditions;
    d_ptrptr = solve_ptr -> d_dat;

    nconds   = solve_ptr -> n_conditions;
    n_ptrptr = solve_ptr -> n_dat;
    
    /* solve文 本体のプログラム作成 */
    
    if(solve_no < 10 ) {
	sprintf(fname,"solve0%d.f",solve_no);
    }
    else {
	sprintf(fname,"solve%d.f",solve_no);
    }
    
    StoreMakefile( fname ,USER_LIBRARY);
    fp = OpenFileToWrite( fname );
    
    
    /* LINE-STEP-01【subroutine文の作成】 */
    if(solve_no < 10 ) {
	PUT(fp,"      subroutine ");
	PUT(fp,SOLVE_NAME77_A,solve77_ptr->solve_no);
        PUT(fp,"(");
    }
    else {
        PUT(fp,"      subroutine ");
	PUT(fp,SOLVE_NAME77_B,solve77_ptr->solve_no);
        PUT(fp,"(");
    }
    
    /*--------------*/
    /* 引き数の設定 */
    /*--------------*/
    
    /* 変数feelの受け渡し */
    /* ワーク領域は、インデックスが1から始まる用にメインから呼ぶ。
       call solve??(feel(np_work),てな具合)             */
    
    
    F77("feel,imode,nbase");
    
    switch(what_dimension()) {
      case 1:
	F77(",x");
	break;
	
      case 2:
	F77(",x,y");
	break;
	
      case 3:
	F77(",x,y,z");
	break;
    }
    
    
    /* fem 変数 */
    for(i=0;i<solve77_ptr->fem_vars;i++) {
	PUT(fp,",");
	PUT(fp,FEM_VAR_NAME77,*(solve77_ptr->fem_var_name + i));
    }
    
    /* ewise 変数 */
    for(i=0;i<solve77_ptr->ewise_vars;i++) {
	PUT(fp,",");
	PUT(fp,EWISE_VAR_NAME77,*(solve77_ptr->ewise_var_name + i));
    }
    
    /* scalar 変数 */
    for(i=0;i<solve77_ptr->scalar_vars;i++) {
	PUT(fp,",");
	PUT(fp,SCALAR_VAR_NAME77,*(solve77_ptr->scalar_var_name + i));
    }
    
    F77(",noerr)\n");
    
    
    /* LINE-STEP-2 【定形部分】 */
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);

    PUT(fp,"      include %s\n",MPI_HEADER_FILE);

    common_parameters(fp);
    comment1(fp);
    
    /* LINE-STEP-3 【要素グループ数のパラメータ(SolveElementの個数)】*/
    /*             【Dirichlet条件設定の境界数】                     */
    /*             【Neumann条件設定の境界数】                       */
    PUT(fp,"      parameter (NEG = %d)\n",elemg);
    if(dconds) {
	PUT(fp,"      parameter (NDC = %d)\n",dconds);
    }
    if(nconds) {
	PUT(fp,"      parameter (NNC = %d)\n",nconds);
    }
    /* 並列版ソルバーの相対残差値 */
    F77("      parameter (eps = 1.0d-12)\n");
    comment1(fp);

    
    /*------------*/
    /* 仮変数宣言 */
    /*------------*/
    
    /* ワーク変数feelの定義 */
    PUT(fp,"      real*4 feel(*)\n");
    
    switch(what_dimension()) {
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

    /* ＣＧ法に関するパラメータ用配列宣言 */
    /* parapara  RPM(*)を削除(96/02/07)   */
    COM;
    F77("      dimension IPM(10)\n");
    
    /* feel変数の為の配列宣言 */
    comment1(fp);
    
    flag = NO; /* dimension文の最初の,出力抑制の為 */
    if(solve77_ptr->fem_vars+solve77_ptr->ewise_vars != 0) {
	PUT(fp,"      dimension ");
    }
    
    /* fem 変数 */
    for(i=0;i<solve77_ptr->fem_vars;i++) {
	if(flag == YES) F77(",");
	flag = YES;
	PUT(fp,FEM_VAR_NAME77,*(solve77_ptr->fem_var_name + i));
	PUT(fp,"(*)");
    }
    
    /* ewise 変数 */
    for(i=0;i<solve77_ptr->ewise_vars;i++) {
	if(flag == YES) F77(",");
	flag = YES;
	PUT(fp,EWISE_VAR_NAME77,*(solve77_ptr->ewise_var_name + i));
	PUT(fp,"(*)");
    }
    F77("\n");
    
    /* scalar変数に対する宣言 */
    for(i=0;i<solve77_ptr->scalar_vars;i++) {
	int type;
	type = get_var_kind(*(solve77_ptr->scalar_var_name + i));
	
	switch(type) {
	  case CONST:
	  case DOUBLE:
	    PUT(fp,"      real*8 ");
	    break;
	    
	  case INT:
	    PUT(fp,"      integer*4 ");
	    break;
	    
	  default:
	    SystemAbort("Scalar variable type ERROR (make_solve_ctrl77)");
	}
	PUT(fp,SCALAR_VAR_NAME77,*(solve77_ptr->scalar_var_name + i));
	F77("\n");

    }
    comment1(fp);

    /*=============================================================*/
    /* 【要素グループが複数の場合】 */
    /*              np_ielem(NEG)           要素節点データのポインタ */
    /*              np_matno(NEG)           要素データのポインタ     */
    /*                                                             */
    /* 要素情報配列 nedtno(NEG)             要素節点集合データ番号 */
    /*              nonode(NEG)             節点無し自由度         */
    /*              nenfre(max_nodes,NEG)   各要素内節点自由度配列 */
    /*                                                             */
    /* 【Dirichlet条件用節点集合データ番号用】                     */
    /*              np_inset(NDC)                                  */
    /*              nsetno(NDC)             数値データ集合番号     */
    /*                                                             */
    /* 【Neumann条件用節点集合データ番号用】                       */
    /*              np_bielem(NNC)          Neumann条件辺要素データ*/
    /*              np_bmatno(NNC)          Neumann条件辺要素番号  */
    /*              nbedtno(NNC)            境界要素EDAT番号       */
    /*                                                             */
    /*=============================================================*/
    COM;
    F77("      integer   p_size,p_status(mpi_status_size)\n");
    F77("      dimension nbase(2,npe)\n");
    COM;

    /* 削除(Apr 24:1996:14:47版
       F77("      dimension np_ielem(NEG),np_matno(NEG)\n"); */

    F77("      dimension nedtno(NEG)\n");
    F77("      dimension nonode(NEG)\n");

    if(dconds) {
	/* 削除(Apr 24:1996:14:47版	
	   F77("      dimension np_inset(NDC)\n"); */
	F77("      dimension nsetno(NDC)\n");
    }
    
    if(nconds) {
	/* 削除(Apr 24:1996:14:47版
	   F77("      dimension np_bielem(NNC)\n"); */

	/* 削除(Apr 24:1996:14:47版
	F77("      dimension np_bmatno(NNC)\n"); */
	
	F77("      dimension nbedtno(NNC)\n");
    }

    PUT(fp,"      dimension nenfre(%d,NEG)\n",max_nodes);

    /* Commonブロック */
    CommonBlock(fp);
    comment1(fp);

    /*====================*/
    /* 問題定義data文     */
    /*====================*/

    /*------------------------------------------*/
    /* 要素節点集合番号の情報配列nedtnoのdata文 */
    /*------------------------------------------*/
    
    F77("      data nedtno/");
    for(i=0;i<elemg;i++) {
	if(i != 0) F77(",");
	elem77_ptr = *(elem77_ptrptr + i);
	elem_dat_ptr = elem77_ptr -> elem_dat;

	/* subdomain expansion */
	if(elem77_ptr -> subdomain_flag == YES) {
	    PUT(fp,"%d",elem77_ptr->sub_edat_no);
	}
	else {
	    PUT(fp,"%d",elem_dat_ptr -> edatno);
	}

    }
    F77("/\n");

    /*----------------------------------------*/
    /* 節点なし自由度の情報配列nonodeのdata文 */
    /*----------------------------------------*/
    F77("      data nonode/");
    for(i=0;i<elemg;i++) {
	if(i != 0) F77(",");
	elem77_ptr = *(elem77_ptrptr + i);
	PUT(fp,"%d",elem77_ptr -> nodeless_freedom);
    }
    F77("/\n");

    /*------------------------------*/
    /* 要素内自由度を定めるデータ文 */
    /*------------------------------*/
    F77("      data nenfre/");
    for(i=0;i<elemg;i++) {                 
	if(i != 0 ) F77(",\n     $             ");
	
	elem77_ptr = *(elem77_ptrptr + i);
	for(j=0;j<max_nodes;j++) {
	    if(j != 0) F77(",");
	    if(j >= elem77_ptr->nodes) {
		F77("0"); continue;
	    }
	    PUT(fp,"%d",*(elem77_ptr->node_freedom + j));
	}
    }
    F77("/\n");

    /*-------------------------------------------*/
    /* Dirichlet境界条件節点集合番号data文       */
    /*-------------------------------------------*/
    if(dconds != 0) {
	F77("      data nsetno/");
	for(i=0;i<dconds;i++) {
	    if(i!=0) F77(",");
	    d_ptr = *(d_ptrptr + i);
	    PUT(fp,"%d",d_ptr->b_nodeset);
	}
	F77("/\n");
    }
    /*-----------------------------------------*/
    /* Neumann境界条件境界要素番号data文       */
    /*-----------------------------------------*/
    if(nconds != 0) {
	F77("      data nbedtno/");
	for(i=0;i<nconds;i++) {
	    if(i!=0) F77(",");
	    n_ptr = *(n_ptrptr + i);
	    PUT(fp,"%d",n_ptr->belem_no);
	}
	F77("/\n");
    }
	
    comment2(fp);

    /*=======================*/
    /* solve制御ルーチン本体 */
    /*=======================*/

    /* 節点累積自由度配列、連立一次係数格納情報配列の作成 */
    /* COMMON /feel_sol/n_sstat(*)フラグによって変化させる */

    /* FORTRAN 変数 NO は solve_noを持つ */
    /*■□■ レポート ■□■*/
    /* 並列版では削除 */


    PUT(fp,"      NO = %d\n",solve_no);
    PUT(fp,"      np_push = np_work\n");
    PUT(fp,"***\n");



    /*☆☆☆ 並列データ読み込み ☆☆☆*/
    PUT(fp,"* Read parallel control data\n");
    COM;
    
    PUT(fp,"      ncont1 = 20\n");
    PUT(fp,"      ncont2 = npe*2 + 80\n");
    COM;
    
    PUT(fp,"      iunit = io_fem + NO -1\n");
    COM;

    PUT(fp,"      if(p_rank.eq.0) then\n");
    PUT(fp,"        rewind(iunit)\n");
    COM;

    /* 並列版 時間出力 */
    PUT(fp,"        call time_rep(1,'before read%d_2',io_out,isum)\n",solve_no);
    PUT(fp,"        do 1 i=nbase(1,1),n_smaxp(NO)\n");
    PUT(fp,"          read(iunit) feel(i)\n");
    PUT(fp," 1      continue\n");
    /* 並列版 時間出力 */
    PUT(fp,"        call time_rep(1,'after read%d_2',io_out,isum)\n",solve_no);
    COM;

    PUT(fp,"      endif\n");
    F77("*-----------------\n");
    F77("      call mpi_bcast(isum,1,mpi_integer,0,\n");
    F77("     $               mpi_comm_world,ierror)\n");

    /* CJ時間計測初期化 */
    F77("      call time_repcj(0,p_rank,npe,'INITIALIZE',io_out,isum)\n");

    
    F77("*-----------------\n");
    F77("* Broadcast nbase \n");
    F77("*-----------------\n");
    
    F77("      call mpi_bcast(nbase(1,1),npe*2,mpi_integer,0,\n");
    F77("     $               mpi_comm_world,ierr)\n");
    F77("      call mpi_bcast(ncont1,1,mpi_integer,0,\n");
    F77("     $               mpi_comm_world,ierr)\n");
    F77("      call mpi_bcast(ncont2,1,mpi_integer,0,\n");
    F77("     $               mpi_comm_world,ierr)\n");
    COM;
    F77("* Broadcast data from PE0 to all other PEs\n");
    F77("      call mpi_bcast(n_smaxp(NO),1,mpi_integer,0,\n");
    F77("     $               mpi_comm_world,ierr)\n");
    COM;

    F77("* 128000 means bloadcast data size per one message passing\n");
    F77("      nbt = (n_smaxp(NO)-nbase(1,1)+1)/(128000/4)\n");
    F77("      do 11 i=1,nbt\n");
    F77("        iptr = 32000*(i-1)+nbase(1,1)\n");
    F77("        call mpi_bcast(feel(iptr),32000,mpi_real,0,\n");
    F77("     $                 mpi_comm_world,ierr)\n");
    F77("  11  continue\n");
    F77("      if(32000*nbt+nbase(1,1) .lt. n_smaxp(1)) then\n");
    F77("        call mpi_bcast(feel(32000*nbt+nbase(1,1)),\n");
    F77("     $       n_smaxp(NO)-32000*nbt-nbase(1,1)+1,mpi_real,0,\n");
    F77("     $       mpi_comm_world,ierr)\n");
    F77("      endif\n");
    F77("***\n");
    
    F77("* Memory move\n");
    F77("      call p_memory_move(feel(nbase(1,p_rank+1)),\n");
    F77("     $                   feel(nbase(1,1)),nbase(2,p_rank+1))\n");
    F77("*\n");
    
    F77("* Adjust np_work pointer\n");
    F77("      np_work = nbase(1,1)+nbase(2,p_rank+1)\n");
    F77("*\n");
    
    
    F77("* Set parallel parameters\n");
    F77("      call p_solve_pmset( npe,feel,feel(nbase(1,1)),\n");
    F77("     $      feel(nbase(1,1)+ncont1),ncont1,ncont2,ndim,\n");
    F77("     $      npesum,npmaxsub,nelemsub,np,ndisub,neusub,neq_sub,\n");
    F77("     $      naisum,ninsum,nsendnum,nrecvnum,nintotal,nmatrix,\n");
    F77("     $      npp_xsub,npp_ysub,npp_isubelem,\n");
    F77("     $      npp_nelegru,npp_nloglo,\n");
    F77("     $      npp_nsendlist,npp_nrecvlist,\n");
    F77("     $      npp_ndikaz,npp_ndinum,npp_neukaz,\n");
    F77("     $      npp_neunum,npp_matno,\n");
    F77("     $      npp_ipdsub,npp_IPFsub,npp_naieq,npp_nineq,\n");
    F77("     $      npp_nsendtable,npp_nrecvtable,npp_nsendkaz,\n");
    F77("     $      npp_nrecvkaz,npp_npsre,npp_ninner,npp_npsyo,\n");
    F77("     $      npp_npins,npp_npibsub)\n");
    COM;

    F77("* Allocate Matrix array\n");
    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(npp_B,'solve%d (B)',neq_sub,1,imode)\n",solve_no);

    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(npp_U,'solve%d (U)',neq_sub,1,imode)\n",solve_no);

    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(npp_KK_MJ,'solve%d(KK_MJ)',npmaxsub,0,imode)\n",
	solve_no);

    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(npp_KK_MJR,'solve%d(KK_MJR)',npmaxsub,0,imode)\n",
	solve_no);

    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(npp_KK_MJL,'solve%d(KK_MJL)',npmaxsub,0,imode)\n",
	solve_no);
    PUT(fp,"      if(imode .NE. 0) return\n");
    F77("*\n");

    /* 96'5/16追加分 */
    F77("      call zerod(feel(npp_B),neq_sub)\n");
    F77("      call zerod(feel(npp_U),neq_sub)\n");
    
    
    F77("      call p_set_MJ(MJ,feel(npp_isubelem),nelemsub,np,\n");
    F77("     $       nenfre(1,1),feel(npp_KK_MJ),npmaxsub,\n");
    F77("     $       feel(npp_KK_MJR),feel(npp_KK_MJL))\n");
    COM;

    F77("      JDP=MJ/2+1\n");
    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(npp_A, 'solve%d (A)',neq_sub*MJ,1,imode)\n",solve_no);
    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(npp_JA,'solve%d(JA)',neq_sub*MJ,0,imode)\n",solve_no);
    PUT(fp,"      if(imode .NE. 0) return\n");
    COM;
    
    F77("      call zerod(feel(npp_A),neq_sub*MJ)\n");
    F77("      call zeroi(feel(npp_JA),neq_sub*MJ)\n");
    comment1(fp);




    /* 行列データ作成用のデータはすべてmk_pdatで作成したので
       ここではデータ作成は必要無し                          */



    /* 非対称行列用の剛性行列の作成 */
    /*======================*/
    /* elemルーチン呼び出し */
    /*======================*/    
    for(i=0;i<elemg;i++) {

	solve_element_ptr = *(solve_ptr->solve_elem_dat + i);

	/* ielem等のデータ読み込み */
	comment1(fp);
	PUT(fp,"*  Element No.%d\n",i+1);
	PUT(fp,"*--------------------------\n");


	F77(   "      call ");
        PUT(fp,ELEM_MAIN_NAME,solve_no,i+1);
	switch(what_dimension()) {
	  case 1:
	    F77("(feel(npp_xsub),");
	    break;
	    
	  case 2:
	    F77("(feel(npp_xsub),feel(npp_ysub),");
	    break;
	    
	  case 3:
	    F77("(feel(npp_xsub),feel(npp_ysub),feel(npp_zsub),");
	    break;
	}
	PUT(fp,"feel(npp_isubelem),nelemsub,np,");

	/* 行列用配列 */
	F77("feel(npp_A),feel(npp_JA),neq_sub,MJ,feel(npp_B),");

	/* 累積節点自由度 */
	F77("feel(npp_ipdsub),feel(npp_matno),");   

	/* 局所←→全体節点番号対応配列 */
	F77("feel(npp_nloglo),npmaxsub,JDP,feel(npp_nelegru)");

	/* fem未知変数(非線形問題の時のみ)dbg:現在未対応 */
	if(solve_element_ptr -> nonlinear_flag == YES) {
	    SystemAbort("Nonlinear detected in linear program generation");
	}

	/* 既知fem変数 */
	for(j=0;j<solve_element_ptr->fem_knowns;j++) {
	    F77(",");
	    PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->fem_known_name+j));
	}

	/* 既知ewise変数 */
	for(j=0;j<solve_element_ptr->ewise_knowns;j++) {
	    F77(",");
	    PUT(fp,EWISE_VAR_NAME77,*(solve_element_ptr->ewise_known_name+j));
	}

	/* スカラー変数 */
	for(j=0;j<solve_element_ptr->scalar_knowns;j++) {
	    F77(",");
	    PUT(fp,SCALAR_VAR_NAME77,*(solve_element_ptr->
				       scalar_known_name+j));
	}

	F77(")\n");


	COM;          /*■□■ レポート ■□■*/
	/* レポートは並列版では削除 */
    }

    /* ノイマン境界条件処理ルーチン */

    if(nconds == 0) {
	F77("*------------------------------\n");
	F77("* NO Neumann coundary condition\n");
	F77("*------------------------------\n");
    }
    else {
	F77("*------------------------------\n");
	F77("* Neumann CONDITION\n");
	F77("*------------------------------\n");
    }
    for(i=0;i<nconds;i++) {    
	PUT(fp,"      call ");
	PUT(fp,NCOND_NAME,solve_no,i+1);
	PUT(fp,"(feel(npp_xsub),feel(npp_ysub),\n");
	F77(   "     $       feel(npp_A),feel(npp_JA),\n");
	F77(   "     $       feel(npp_B),feel(npp_ipdsub),\n");
	F77(   "     $       feel(npp_npibsub),feel(npp_matno),\n");
	F77(   "     $       feel(npp_neukaz),feel(npp_neunum),\n");
	F77(   "     $       nbedtno,feel,npmaxsub,nelemsub,neq_sub,MJ,JDP,\n");
	F77(   "     $       neusub,NNC");

	for(j=0;j<n_ptr -> fem_vars;j++) {
	    F77(",");
	    PUT(fp,FEM_VAR_NAME77,*(n_ptr->fem_var_name + j));
	}
	for(j=0;j<n_ptr->scalar_vars;j++) {
	    F77(",");
	    PUT(fp,SCALAR_VAR_NAME77,*(n_ptr->scalar_var_name + j));
	}
	F77(")\n");

    }

    COM;          /*■□■ レポート ■□■*/
    /* 並列版では削除 */
    
    /*================================*/
    /* ディリクレ境界条件処理ルーチン */
    /*================================*/
    if(dconds == 0) {
	F77("*------------------------------\n");
	F77("* NO Dirichlet coundary condition\n");
	F77("*------------------------------\n");
    }
    else{
	F77("*------------------------------\n");
	F77("* Dirichlet CONDITION\n");
	F77("*------------------------------\n");
    }

    for(i=0;i<dconds;i++) {
	if(i != 0 ) F77("*---\n");
	d_ptr = *(d_ptrptr + i);

	F77("      call ");
	PUT(fp,DCOND_NAME,solve_no,i+1);

	/* x,y座標 */
	F77("(feel(npp_xsub),feel(npp_ysub)");
	F77(",feel(npp_A),feel(npp_JA),feel(npp_B)");
	F77(",feel(npp_ipdsub),feel(npp_npsyo)");
	F77(",feel(npp_npins),feel(npp_ndikaz),feel(npp_ndinum)");
	F77(",nsetno,feel,npmaxsub,neq_sub,MJ,JDP,ndisub,NDC");

	/* 既知変数の書き込み */
	for(j=0;j<d_ptr -> fem_vars;j++) {
	    F77(",");
	    PUT(fp,FEM_VAR_NAME77,*(d_ptr->fem_var_name + j));
	}
	for(j=0;j<d_ptr->scalar_vars;j++) {
	    F77(",");
	    PUT(fp,SCALAR_VAR_NAME77,*(d_ptr->scalar_var_name + j));
	}
	F77(")\n");
    }
    COM;          /*■□■ レポート ■□■*/
    /* 並列版では削除 */

    F77("*----------------------------------\n");
    F77("*   Send/Receive Buffer allocation \n");  
    F77("*----------------------------------\n");
    F77("      call p_make_srbuff(p_rank,nsendnum,nrecvnum,npesum,\n");
    F77("     $      feel(npp_nsendkaz),feel(npp_nrecvkaz),\n");
    F77("     $      feel(npp_nsendlist),feel(npp_nrecvlist),\n");
    F77("     $      nsesum,nresum)\n");
    COM;
    
    F77("      if((nsesum .EQ. 0) .AND. (nresum .EQ. 0)) then\n");
    PUT(fp,"        call f_alloc(npp_srb,'solve%d(srb)',1,1,0)\n",solve_no);
    F77("        nsesum = 1\n");
    F77("        nresum = 0\n");
    F77("      else if((nsesum+nresum) .NE. 0) then\n");
    PUT(fp,"        call f_alloc(npp_srb,'solve%d(srb)',nsesum+nresum,1,0)\n",solve_no);
    F77("      else\n");
    F77("        stop 'nsesum,nresum error'\n");
    F77("      endif\n");
    COM;

    F77("      call p_solve_plset(p_rank,feel,neq_sub,feel(npp_B),\n");
    F77("     $      feel(npp_srb),feel(npp_npsre),nsendnum,\n");
    F77("     $      nrecvnum,npesum,nsesum,nresum,\n");
    F77("     $      feel(npp_nsendkaz),feel(npp_nrecvkaz),\n");
    F77("     $      feel(npp_nsendlist),feel(npp_nrecvlist),\n");
    F77("     $      feel(npp_nsendtable),feel(npp_nrecvtable))\n");
    
    /*========================*/
    /* 連立一次方程式呼びだし */
    /*========================*/


    F77("*-------------------\n");
    F77("*  MPPSCG ROUTINE   \n");
    F77("*-------------------\n");
    F77(   "      IPM(1) = 0\n");
    COM;
    
    PUT(fp,"      call f_alloc(npp_W,'solve%d(W)',neq_sub*8,1,0)\n",solve_no);

    F77("*------------------------------------\n");
    F77("* Specify maximum iteration number IT\n");
    F77("*------------------------------------\n");

    F77(   "      IT = neq_sub\n");
    F77(   "      call mpi_allreduce(IT,IT,1,mpi_integer,\n");
    F77(   "     $                    mpi_sum,mpi_comm_world,ierror)\n");
    F77(   "      IT = IT / npe\n");
    F77(   "      if(IT   .LT. 0 ) stop 'Itereation counter error'\n");
    F77(   "*\n");

    PUT(fp,"      call time_repcj(1,p_rank,npe,'before solver%d',io_out,isum)\n",solve_no);


    F77("*-------------------\n");
    F77("* CALL MPPSCG SOLVER\n");
    F77("*-------------------\n");
    

    F77("      call p_unsym_mscg(");

    F77(      "     p_rank,feel,feel(npp_A),MJ,neq_sub,\n");
    F77("     $     feel(npp_JA),JDP,feel(npp_B),\n");
    F77("     $     feel(npp_U),naisum,feel(npp_naieq),nintotal,\n");
    F77("     $     feel(npp_ninner),npesum,nsendnum,nrecvnum,\n");
    F77("     $     nsesum,nresum,feel(npp_nsendlist),\n");
    F77("     $     feel(npp_nrecvlist),feel(npp_nsendkaz),\n");
    F77("     $     feel(npp_nrecvkaz),feel(npp_nsendtable),\n");
    F77("     $     feel(npp_nrecvtable),feel(npp_npsre),\n");
    F77("     $     feel(npp_srb),eps,IPM,IT,feel(npp_W),\n");
    F77("     $     rnorm,KTI,noerr)\n");

    F77("*\n");
    /* 並列ソルバーの例外処理 */
    F77("           if(noerr .EQ. 1) return\n");
    
    /*■□■ レポート ■□■*/
    F77("*--------------------------------------------------------\n");
    PUT(fp,"      call time_repcj(1,p_rank,npe,'after solver%d',io_out,isum)\n",solve_no);



    /* 96/5/16 挿入分 */
    F77("      if (p_rank .EQ. 0) then\n");
    F77("        call rep_CG(KTI,rnorm,io_out)\n");
    F77("      endif\n");


    comment1(fp);

    /* 解のfem変数への反映 */
    /* 今は、element wiseに実行 (これは大変非効率的 dbg: 対象)*/

    for(i=0;i<solve_elements;i++) {
	solve_element_ptr = *(solve_ptr -> solve_elem_dat + i);


	/*============================*/
	/* edevルーチン呼び出し文作成 */
	/*============================*/
	COM;
	PUT(fp,"        call edev%d_%d",solve_no,i+1);
	PUT(fp,"(feel(npp_U),feel(npp_ipdsub),feel(npp_isubelem),feel(npp_nloglo),nelemsub,np,npmaxsub");
	for(j=0;j<solve_element_ptr->unknowns;j++) {
	    F77(",");
	    PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
	}
	F77(")\n");
	COM;
	
    }
    /*■□■ レポート ■□■*/
    /* 並列版では削除 */


    F77("*---------------------------------------\n");
    F77("* Allocate work variables for Collection\n");
    F77("*---------------------------------------\n");

    /* 並列版での終了処理前課程 */
    PUT(fp,"      call f_alloc(npp_sb,'collect_(sb)',npmaxsub*%d,1,0)\n",
	solve_element_ptr->unknowns);

    F77("      call f_alloc(npp_ndsub,'collect_(ndsub)',npe,0,0)\n");
    PUT(fp,"      call f_alloc(npp_rb,'collect_(rb)',npmax*%d,1,0)\n",
	solve_element_ptr->unknowns);
    F77("      call f_alloc(npp_nrb,'collect_(nrb)',npmax,0,0)\n");


    /* FEM変数の値ををＰＥ０に集める */
    F77("*------------------------------\n");
    F77("* Collect the solution into PE0\n");
    F77("*------------------------------\n");
    PUT(fp,"      call collec_sol%d(p_rank",solve_no);
    for(j=0;j<solve_element_ptr->unknowns;j++) {
	F77(",");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
    }
    F77(",feel(npp_nloglo),npmaxsub,feel(npp_sb),feel(npp_ndsub),");
    F77("feel(npp_rb),feel(npp_nrb),npmax,npe)\n");

    
    /*================*/
    /* BROADCAST 処理 */
    /*================*/
    comment1(fp);
    F77("* Broadcast solution from PE0 to each PE\n");
    COM;
    for(j=0;j<solve_element_ptr->unknowns;j++) {
	F77("      call mpi_bcast(");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
	F77(",npmax,mpi_double_precision,\n");
	F77("     $     0,mpi_comm_world,ierror)\n");
    }
    
    /* 終了処理 */
    comment1(fp);
    F77("      np_work = np_push\n");   /* 領域開放 */
    COM;
    F77("      return\n");
    F77("      end\n");

    CloseFile(fp);
    /*===========================*/
    /* solve制御ルーチン作成終了 */
    /*===========================*/


    /* CAUTION!!!!! */
    /* 例外的ですが、ここから、collec_solルーチンを呼ばしてもらいます */
    make_collec_sol(solve_no,solve_element_ptr);

    return;
}
