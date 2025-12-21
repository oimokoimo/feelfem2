/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_fort77_main.c
 *      Date:   1993/07/10
 *  Modified:   1993/10/20
 *   
 *   Testing:   1999/11/26
 *   
 *   Purpose:   solveブロックのコントロールfortranプログラムの生成
 *   Functions: 
 *              
 *              各solve文の作成ルーチン、入力は、solve文構造体
 *              
 *              
 *              SolveFORT77 構造体が入力となる
 *              
 *              
 */

#include <stdio.h>

#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "../feel_def/basic_struct.h"
#include "../solve_comp/solve_comp.h"

make_solve_ctrl77_skyline( solve_ptr, solve77_ptr )
     Solve       *solve_ptr;
     SolveFORT77 *solve77_ptr;
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



    /* TESTING FOR FEELFEM */
/*    solveStructWriter( solve_ptr, solve77_ptr); */
    
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
       call solve??(feel(np_work),てな具合)  OLD F_ALLOC */
    
    
    F77("feel,imode");
    
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
    
    F77(")\n");
    
    
    /* LINE-STEP-2 【定形部分】 */
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);
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
    F77("      dimension np_ielem(NEG),np_matno(NEG)\n");
    F77("      dimension nedtno(NEG)\n");
    F77("      dimension nonode(NEG)\n");
    
    if(dconds) {
	F77("      dimension np_inset(NDC)\n");
	F77("      dimension nsetno(NDC)\n");
    }
    
    if(nconds) {
	F77("      dimension np_bielem(NNC)\n");
	F77("      dimension np_bmatno(NNC)\n");
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
    PUT(fp,"      call report('SOLVE %2d START')\n",solve_no);


    PUT(fp,"      NO = %d\n",solve_no);
    /*    PUT(fp,"      np_push = np_work\n"); OLD F_ALLOC */
    PUT(fp,"      call f_alloc_push\n");
    COM;

    
    /* 累積節点自由度、係数格納情報配列、LU分解MATRIX等の読み込み */
    F77(   "      if( n_sstat(NO) .ne. 0 ) then\n");
    
    /* 上記プログラム作成サブルーチンを呼ぶ */
/*    make_read_solve_data77(fp,solve_fort77);
 */
    F77(   "      stop 'Not Implemented now(make_read_solve_data77)'\n");

    F77(   "c     goto 1\n");  /* 初期作成処理のスキップ */
    F77(   "      endif\n");
    COM;
    
    /* 累積節点自由度計算開始 */
    /* 累積節点自由度配列IPD */
    F77(   "* ---\n");
    F77(   "* IPD (node-wise equation number)\n");
    F77(   "* ------------------\n");
    PUT(fp,"      call f_alloc(np_IPD,'solve_%d(IPD)',npmax,0,0)\n",solve_no);

    /* 節点自由度配列IPF */
    F77(   "* ---\n");
    F77(   "* IPF (node-wise freedom)\n");
    F77(   "* ------------------\n");
    PUT(fp,"      call f_alloc(np_IPF,'solve_%d(IPF)',npmax,0,0)\n",solve_no);
    F77(   "      call zeroi(feel(np_IPD),npmax)\n");
    F77(   "      call zeroi(feel(np_IPF),npmax)\n");
    comment1(fp);

    /*===================*/
    /* 要素積分の為の    */
    /* ielem用領域の取得 */
    /*===================*/
    F77(   "* ---\n");
    F77(   "* IELEM,MATNO (element-node array,materinal no array)\n");
    F77(   "* ------------------\n");    
    F77(   "      do 10 i=1,NEG\n");
    F77(   "        neelem = n_edat(nedtno(i),1)\n");
    F77(   "        nenode = n_edat(nedtno(i),2)\n");
    PUT(fp,"        call f_alloc(np_ielem(i),'solve_%d(ielem:1)',neelem * nenode,0,0)\n",solve_no);
    PUT(fp,"        call f_alloc(np_matno(i),'solve_%d(matno:1)',neelem ,0,0)\n",solve_no);
    /* ielemの取得 */
    F77(   "        iunit = nedtno(i) + io_edat - 1\n");
    F77(   "        call get_ielem(iunit,feel(np_ielem(i)),feel(np_matno(i)),neelem,nenode)\n");
    F77(   "   10 continue\n");
    
    comment1(fp);

    /*====================*/
    /*ノイマン条件の為の  */
    /* bielem用領域の取得 */
    /*====================*/
    if(nconds) {
	F77(   "* ---\n");
	F77(   "      do 15 i=1,NNC\n");
	F77(   "        neelem = n_edat(nbedtno(i),1)\n");
	F77(   "        nenode = n_edat(nbedtno(i),2)\n");
	PUT(fp,"        call f_alloc(np_bielem(i),'solve_%d(bielem)',neelem * nenode,0,0)\n",solve_no);
	PUT(fp,"        call f_alloc(np_bmatno(i),'solve_%d(bmatno)',neelem ,0,0)\n",solve_no);
	/* ielemの取得 */
	F77(   "        iunit = nbedtno(i) + io_edat - 1\n");
	F77(   "        call get_ielem(iunit,feel(np_bielem(i)),feel(np_bmatno(i)),neelem,nenode)\n");
	F77(   "   15 continue\n");

	comment1(fp);

    }

    /*========================*/
    /*  要素の組み立ての開始  */
    /*========================*/
    F77(   "      do 100 i=1,NEG\n");
    /* ipf(*)に各節点自由度を代入 */
    COM;


    F77(   "        call ipf_nfree(n_edat(nedtno(i),1),n_edat(nedtno(i),2),feel(np_IPF),feel(np_ielem(i)),nenfre(1,i))\n");
    COM;
    F77(   "  100 continue\n");
    comment1(fp);
    
    /* 節点無し自由度がある場合の処理 */
    F77(   "      do 200 i=1,NEG\n");
    F77(   "        if(nonode(i) .eq. 0) goto 200\n");

    /* ipd(*)に節点なし自由度を代入       */
    /* 要素の最後の節点に自由度を付加する */
    /* でも、これは少し、延期かなぁ〜?    */
    COM;
    F77(   "        call ipd_nonode(n_edat(nedtno(i),1),n_edat(nedtno(i),2),nonode(i),feel(np_ipd),feel(np_ielem(i)))\n");
    COM;
    F77(   "  200 continue\n");
    comment1(fp);
    
    /* 累積自由度の計算 */
    COM;
    F77("      call makeipd(feel(np_ipf),feel(np_ipd),npmax,neq)\n");  /* → makeipd.f */
    COM;

    /* スカイラインマトリックス用配列メモリ取得 */
    PUT(fp,"      call f_alloc(np_KLD,'solve_%d(KLD)',neq+1,0,0)\n",solve_no);

    /* スカイライン列の高さ用配列、補助配列のメモリ取得 */
    PUT(fp,"      call f_alloc(np_KH, 'solve_%d(KH)', neq,  0,0)\n",solve_no);
    PUT(fp,"      call f_alloc(np_KHa,'solve_%d(KHa)',npmax,0,0)\n",solve_no);
    
    /* スカイライン列高計算プログラム */
    /* その１ 初期設定  (節点毎)配列KHaを、0に初期化 */
    F77("      call zeroi(feel(np_KHa),npmax)\n");

    /* CAUTION:節点無し自由度がある場合の処理はお預け */
    /* 配列 KHa の作成 */
    
    F77("      do 300 i=1,NEG\n");

    /* 要素内最小節点番号を記録 関数【cal_ht_a】呼びだし */
    COM;
    F77(   "        call cal_ht_a(feel(np_ielem(i)),n_edat(nedtno(i),1),n_edat(nedtno(i),2),feel(np_KHa),npmax)\n");
    COM;

    /* 配列KHa の作成終了 */
    F77(   "  300   continue\n");
    comment1(fp);
    F77(   "*    Make array KH\n");

    /* 配列KHの作成 関数【cal_ht】呼びだし*/
    F77(   "      call cal_ht(feel(np_KHa),feel(np_KH),feel(np_IPF),\n");
    F77(   "     $            feel(np_IPD),npmax,neq)\n");
    COM;

    /* 配列KLDの作成 関数【make_KLD】呼びだし */
    /* ncofは、上(下)三角部分の配列の大きさ   */
    F77(   "*   Make KLD\n");
    F77(   "      call make_KLD(feel(np_KH),feel(np_KLD),neq,ncof)\n");


    /* 配列、KHa領域の開放 */
/*    F77(   "*      KH,KHa領域開放\n");
 *    PUT(fp,"      call f_free('solve_%d(KHa)',npmax,0)\n",solve_no);
 *    COM; */

    /* 連立一次方程式の係数の為の領域取得 */
    /*     switch(solve77_ptr->linear_method) {
	   としたい所ですが…
	   現在はスカイライン法のみ！！！！！     */

    /* 配列VFG(右辺ロードベクトル) 領域取得 */
    F77(   "* VFG(Solution)\n");
    PUT(fp,"      call f_alloc(np_VFG,'solve_%d(VFG)',neq,1,0)\n",solve_no);
    COM;

    /* 配列VKGS(上三角) VKGI(下三角) VKGD(対角項) の領域取得 */
    F77(   "* VKGS(Upper) VKGI(Lower) VKGD(Diagonal)\n");

    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(np_VKGS,'solve_%d(VKGS)',ncof,1,imode)\n",solve_no);

    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(np_VKGI,'solve_%d(VKGI)',ncof,1,imode)\n",solve_no);

    PUT(fp,"      imode = -1\n");
    PUT(fp,"      call f_alloc(np_VKGD,'solve_%d(VKGD)',neq, 1,imode)\n",solve_no);
    PUT(fp,"      if(imode .ne. 0) return\n");

    COM;

    /*■□■ レポート ■□■*/
    F77(   "      call rep_msize(neq,ncof)\n");
    COM;

    /*====================================*/
    /*  ディリクレ境界条件を科す節点集合  */
    /*  データの領域確保と初期化          */
    /*====================================*/
    if(dconds != 0) {
	F77("      do 400 i=1,NDC\n");
	F77("        nodes = n_nset(nsetno(i),1)\n");
	F77("        np    = n_nset(nsetno(i),2)\n");
	F77(   "       imode = -1\n");
	PUT(fp,"       call f_alloc(np_inset(i),'solve_%d(INSET)',nodes*np,0,imode)\n",solve_no);
	F77(   "       if(imode .ne. 0) return\n");
	F77("        iunit = nsetno(i) + io_node - 1\n");
	F77("        call get_inset(iunit,feel(np_inset(i)),nodes,np)\n");
	F77("  400 continue\n");
	COM;
    }

    /*====================================*/
    /* dbg:   非線形・線形問題の分岐点    */
    /* 現在は線形問題のみを扱う           */
    /* 将来関数として分割し呼び出す       */
    /*====================================*/

    /* 係数行列、荷重ベクトル作成ルーチン */
    comment1(fp);
    /* まず０クリア */
    F77(   "      call zerod(feel(np_VKGS),ncof)\n");
    F77(   "      call zerod(feel(np_VKGD),neq )\n");
    F77(   "      call zerod(feel(np_VKGI),ncof)\n");
    F77(   "      call zerod(feel(np_VFG) ,neq )\n");
    COM;

    /* サブdomain拡張の為の項を追加 */
    ctrl77_subdomain(fp,elemg,solve_ptr,elem77_ptrptr);


    /*■□■ レポート ■□■*/
    PUT(fp,"      call report('SOLVE %d PREPARATION END')\n",solve_no);
    COM;

    /*======================*/
    /* elemルーチン呼び出し */
    /*======================*/    
    for(i=0;i<elemg;i++) {

	solve_element_ptr = *(solve_ptr->solve_elem_dat + i);
	elem77_ptr        = *(elem77_ptrptr+i);

	/* ielem等のデータ読み込み */
	comment1(fp);
	PUT(fp,"*  Element No.%d\n",i+1);
	PUT(fp,"*--------------------------\n");



	F77(   "      call ");
        PUT(fp,ELEM_MAIN_NAME,solve_no,i+1);
	switch(what_dimension()) {
	  case 1:
	    F77("(x,");
	    break;
	    
	  case 2:
	    F77("(x,y,");
	    break;
	    
	  case 3:
	    F77("(x,y,z,");
	    break;
	}
	PUT(fp,"feel(np_ielem(%d)),feel(np_matno(%d)),n_edat(nedtno(%d),1),n_edat(nedtno(%d),2),",i+1,i+1,i+1,i+1);

	/* 行列用配列 */
	F77("feel(np_VKGS),feel(np_VKGD),");
        F77("feel(np_VKGI),feel(np_VFG),feel(np_KLD)");

	/* 累積節点自由度 */
	F77(",feel(np_IPD)");

	/* fem未知変数(非線形問題の時のみ)dbg:現在未対応 */
	if(solve_element_ptr -> nonlinear_flag == YES) {
	    for(j=0;j<solve_element_ptr->unknowns;j++) {
		F77(",");
		PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name+j));
	    }
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

	/* subdomain拡張 */
	if(elem77_ptr->subdomain_flag != NO) {
	    PUT(fp,",feel(np_subewise%d)",i+1);
	}

	F77(")\n");


	COM;          /*■□■ レポート ■□■*/
	PUT(fp,"      call report('MAKE ELEM%d-%d END')\n",solve_no,i+1);
	


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
	if(i != 0) COM;
	n_ptr = *(n_ptrptr + i);
	PUT(fp,"      neelem = n_edat(nbedtno(%d),1)\n",i+1);
	PUT(fp,"      nenode = n_edat(nbedtno(%d),2)\n",i+1);
	COM;

	F77("      call ");
	PUT(fp,NCOND_NAME,solve_no,i+1);
	F77("(");
	XYZ_in_subroutine(fp);
	F77(",feel(np_VFG),feel(np_VKGD),feel(np_VKGS),feel(np_VKGI)");
	F77(",feel(np_KLD),feel(np_KH),feel(np_IPD),neq,");
	PUT(fp,"feel(np_bielem(%d)),feel(np_bmatno(%d)),neelem,nenode",
	    i+1,i+1);
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
    if(nconds) {
	F77(   "      call report('SET NEUMANN BOUNDARY CONDITION')\n");
    }
    
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
	if(i != 0 ) COM;
	d_ptr = *(d_ptrptr + i);

	F77("      call ");
	PUT(fp,DCOND_NAME,solve_no,i+1);
	switch(what_dimension()) {
	  case 1:
	    F77("(x");
	    break;

	  case 2:
	    F77("(x,y");
	    break;

	  case 3:
	    F77("(x,y,z");
	    break;

	}
	F77(",feel(np_VFG),feel(np_VKGD),feel(np_VKGS),feel(np_VKGI)");
	F77(",feel(np_KLD),feel(np_KH),feel(np_IPD),neq,");
	PUT(fp,"feel(np_inset(%d)),n_nset(nsetno(%d),1)",i+1,i+1);

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
    if(dconds) {
	F77(   "      call report('SET DIRICHLET BOUNDARY CONDITION')\n");
    }

    /*========================*/
    /* 連立一次方程式呼びだし */
    /*========================*/
    F77(   "*=========================\n");
    F77(   "* CALL SKYLINE SOLVER \n");
    F77(   "*=========================\n");
    F77(   "      IFAC = 1\n");
    F77(   "      ISOL = 1\n");
    if(solve_ptr->symmetry_flag == YES) {
	PUT(fp,"      NSYM = 0\n");
    }
    else {
	PUT(fp,"      NSYM = 1\n");
    }

    F77(   "      call SOL(feel(np_VKGS),feel(np_VKGD),feel(np_VKGI),\n");
    F77(   "     $         feel(np_VFG),feel(np_KLD),neq,io_stderr,\n");
    F77(   "     $         IFAC,ISOL,NSYM,ENERG)\n");

    /*■□■ レポート ■□■*/
    COM;
    PUT(fp,"      call report('SOLVER for SOLVE %d END')\n",solve_no);


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
	PUT(fp,"(feel(np_VFG),feel(np_IPD),feel(np_ielem(%d)),n_edat(nedtno(%d),1),n_edat(nedtno(%d),2)",i+1,i+1,i+1);
	for(j=0;j<solve_element_ptr->unknowns;j++) {
	    F77(",");
	    PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
	}
	F77(")\n");
	COM;
	
    }

    /*■□■ レポート ■□■*/
    PUT(fp,"      call report('EDEV for SOLVE %d END')\n",solve_no);
    COM;
    


    /*====================================*/
    /*  ディリクレ境界条件を科す節点集合  */
    /*  データの領域開放                  */
    /*====================================*/
/*    if(dconds != 0) {
 *	F77("      do 500 i=1,NDC\n");
 *	F77("        nodes = n_nset(nsetno(i),1)\n");
 *	F77("        np    = n_nset(nsetno(i),2)\n");
 *	F77("        np_inset(i)=np_work\n");  OLD F_ALLOC  (THIS IS COMMENT)
 *      PUT(fp,"        call f_free('solve_%d(INSET)',nodes*np,0)\n",solve_no);
 *	F77("  500 continue\n");
 *   }
 *   COM;   
 */

    /* 行列係数用配列のメモリ開放(VKGS,VKGD,VKGI) */
/*
 *    PUT(fp,"      call f_free('solve_%d(VKGS)',ncof,0)\n",solve_no);
 *    PUT(fp,"      call f_free('solve_%d(VKGD)',neq,0)\n",solve_no);
 *    PUT(fp,"      call f_free('solve_%d(VKGI)',ncof,0)\n",solve_no);
 *    COM;
 */
    /* 配列KHのメモリ開放 */
/*  PUT(fp,"      call f_free('solve_%d(KH)',neq,0)\n",solve_no);
 *  COM;
 */

    /* ielem,matno配列領域開放 */
/*    F77(   "      do 900 i=NEG,1,-1\n");
 *    F77(   "       neelem = n_edat(nedtno(i),1)\n");
 *    F77(   "       nenode = n_edat(nedtno(i),2)\n");
 *    PUT(fp,"       call f_free('sol%d(matno)',neelem ,0)\n",solve_no);
 *    PUT(fp,"       call f_free('sol%d(ielem)',neelem*nenode,0)\n",solve_no);
 *    F77(   "  900 continue\n");
 */

    /* 終了処理 */
    comment1(fp);
    /*    F77("      np_work = np_push\n");   OLD F_ALLOC */
    F77("      call f_alloc_pop\n");
    COM;
    F77("      return\n");
    F77("      end\n");

    CloseFile(fp);
    /*===========================*/
    /* solve制御ルーチン作成終了 */
    /*===========================*/

    return;
}
