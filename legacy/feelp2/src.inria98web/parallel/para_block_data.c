/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   para_block_data.c
 *      Date:   1995/09/18
 *  Modified:   1996/04/24(Bug FIX)
 *   
 *   Purpose:   並列処理用ブロックデータ作成プログラムを作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

para_block_data()

{
    FILE *fp;

    int i,j,k;

    int solves;
    int solve_no;
    int solve_elements,elemg;
    int max_nodes;
    int dconds,nconds;
    int total_dconds,total_nconds;
    
    Solve          *solve_ptr;
    SolveElement   *solve_element_ptr;
    SolveFORT77    *solve77_ptr;
    ElementFORT77 **elem77_ptrptr,*elem77_ptr;
    ElemDat        *elem_dat_ptr;
    DirichletData **d_ptrptr,*d_ptr;
    NeumannData   **n_ptrptr,*n_ptr;

    
    /* Makefile に登録する */
    StoreMakefile( BLOCK_DATA_FNAME , USER_LIBRARY);    

    /* ファイルオープン */
    fp = OpenFileToWrite( BLOCK_DATA_FNAME );



    /* solve文の数  */
    solves = how_many_solves();
    
    /* 全体のdcond数、ncond数の積算 */
    total_dconds = 0;
    total_nconds = 0;

    for(i=0;i<solves;i++) {
	solve_ptr = get_nth_solve_ptr(i);
	total_dconds = total_dconds + solve_ptr -> d_conditions;
	total_nconds = total_nconds + solve_ptr -> n_conditions;
    }


    for(i=0;i<solves;i++) {

	solve_ptr = get_nth_solve_ptr(i);
	solve77_ptr = solve_ptr->solve77_ptr;
	
	/* SolveElementは一つと仮定している */
	solve_element_ptr = *(solve_ptr->solve_elem_dat+0000);
	elem77_ptrptr     =   solve77_ptr->elem77_ptrptr;
	elem77_ptr        = *(elem77_ptrptr + 00000);
	elem_dat_ptr      =   elem77_ptr ->elem_dat;
	d_ptrptr          =   solve_ptr -> d_dat;
	n_ptrptr          =   solve_ptr -> n_dat;


	/* 基本変数の設定 */	
	solve_no  = solve77_ptr -> solve_no;
	elemg     = solve77_ptr -> elemg;
	max_nodes = solve77_ptr -> max_nodes;
	solve_elements = solve_ptr -> solve_elements;
	dconds =  solve_ptr -> d_conditions;
	nconds =  solve_ptr -> n_conditions;
	  

	PUT(fp,"      subroutine ");
	PUT(fp,BLOCK_DATA_NAME,i+1);
	PUT(fp,"(nbase,feel)\n");

	if(solve_elements != 1) {   /* 一応かいておく */
	    SystemAbort("Illegal parameter para_block_data:01");
	}

	/* 定型部分 */
	
	if(i==0) {                /* CopyRight等は最初だけ */
	    CopyRight(fp);
	    TimeStamp(fp);
	}
	real8(fp);

	common_parameters(fp);
	comment1(fp);
	
	PUT(fp,"      real*4    feel(*)\n");
	PUT(fp,"      integer*4 nbase(2,npe)\n");
	
	comment1(fp);

	/* COMMONブロック */
	CommonBlock(fp);

	F77("      data nedtno/");
	PUT(fp,"%d/\n",elem_dat_ptr -> edatno);


	comment1(fp);

	PUT(fp,"      NO = %d\n",i+1);

	F77("      np_push = np_work\n");

	/* 時間測定ルーチン */
	PUT(fp,"      call time_rep(1,'before read%d_1',io_out,isum)\n",
	    i+1);
	COM;

	F77("      do 1 ipe = 1, npe\n");
	
	F77("*\n");
	F77("*  Adjust Memory alignment\n");
	F77("*\n");
	
	F77("      if(mod(np_work,2) .eq.0) then\n");
	F77("        nbase(1,ipe) = np_work\n");
	F77("      else\n");
	F77("        np_work = np_work+1\n");
	F77("        nbase(1,ipe) = np_work\n");
	F77("      endif\n");
	
	COM;

	PUT(fp,"      ncont1 = %d\n",MAX_PARA_NCONT_1);
	PUT(fp,"      ncont2 = npe*2+%d\n",MAX_PARA_NCONT_2);

	COM;

	PUT(fp,"      call f_alloc(npp_icons,'Header 1',ncont1,0)\n");
	PUT(fp,"      call f_alloc(npp_ipdat,'Header 2',ncont2,0)\n");
	

	/* PE-data read サブルーチンコール */

	PUT(fp,"******\n");
	PUT(fp,"      call read_pdat%d(feel,ipe,nbase,\n",i+1);
	PUT(fp,"     $                feel(npp_icons),feel(npp_ipdat),\n");
	PUT(fp,"     $                npp_ipdat)\n");

	PUT(fp,"      nbase(2,ipe) = np_work-nbase(1,ipe)\n");
	PUT(fp,"******\n");
	
	COM;

	PUT(fp,"    1 continue\n");
	COM;

	/* 時間report */
	PUT(fp,"      call time_rep(1,'after read%d_1',io_out,isum)\n",i+1);
	COM;

	F77("* Write parallel solve data to scratch file\n");
	COM;
	
	/* OPEN文 */
	F77("      io_scrtch = io_fem + NO -1\n");
	COM;
	F77("      open(unit=io_scrtch,status='scratch',\n");
	F77("     $     form='unformatted')\n");
	COM;

	/* 時間report */
	PUT(fp,"      call time_rep(1,'before write%d',io_out,isum)\n",i+1);
	COM;

	/* スクラッチにプログラムを書く */
	F77("      do 2 i=nbase(1,1),np_work\n");
	F77("        write(io_scrtch) feel(i)\n");
	F77("    2 continue\n");
	COM;

	/* 時間report */
	PUT(fp,"      call time_rep(1,'after write%d',io_out,isum)\n",i+1);
	COM;


	PUT(fp,"      n_smaxp(%d) = np_work\n",i+1);
	PUT(fp,"***\n");

	F77("* RESET np_work\n");
	F77("      np_work = np_push\n");
	COM;

	F77("      return\n");
	F77("      end\n");


	/*****************************/
	/* PE-data read サブルーチン */
	/*****************************/
	PUT(fp,"      subroutine read_pdat%d(feel,ipe,nbase,\n",i+1);
	PUT(fp,"     $           icons,ipdat,npp_ipdat)\n");

	comment1(fp);
	real8(fp);
	common_parameters(fp);
	

	/* 基本パラメータ */
	PUT(fp,"      parameter (NEG = %d)\n",elemg);
	if(dconds) {
	    PUT(fp,"      parameter (NDC = %d)\n",dconds);
	}
	if(nconds) {
	    PUT(fp,"      parameter (NNC = %d)\n",nconds);
	}

	/* 関数引数の宣言 */
	PUT(fp,"      real*4    feel(*)\n");
	PUT(fp,"      dimension nbase(2,npe)\n");
	

	COM;
	PUT(fp,"*  icons(*)   control value\n");
	PUT(fp,"*  ipdat(1,*) ADDRESS   ipdat(2,*) size\n");
	PUT(fp,"      dimension icons(ncont1)\n");
	PUT(fp,"      dimension ipdat(2,ncont2)\n");

	/* FEEL solve文関連の宣言 */
	PUT(fp,"      dimension nedtno(NEG)\n");
	PUT(fp,"      dimension nenfre(%d,NEG)\n",max_nodes);
	if(dconds) {
	    PUT(fp,"      dimension nsetno(NDC)\n");
	}
	if(nconds) {
	    PUT(fp,"      dimension nbedtno(NNC)\n");
	}
	PUT(fp,"      character word*10\n");

	COM;
	
	CommonBlock(fp);
	comment1(fp);

	/* FEEL solve文関連のdata文宣言 */
	F77("      data nedtno/");
	for(j=0;j<elemg;j++) {
	    if(j!=0) F77(",");
	    elem77_ptr = *(elem77_ptrptr + j);
	    elem_dat_ptr = elem77_ptr -> elem_dat;
	    PUT(fp,"%d",elem_dat_ptr -> edatno);
	}
	F77("/\n");
	
	/* 情報nenfre */
	F77("      data nenfre/");
	for(j=0;j<elemg;j++) {
	    if(j!=0) F77(",\n     $          ");
	    
	    elem77_ptr = *(elem77_ptrptr + j);
	    for(k=0;k<max_nodes;k++) {
		if(k != 0) F77(",");
		if(k >= elem77_ptr->nodes) {
		    F77("0"); continue;
		}
		PUT(fp,"%d",*(elem77_ptr->node_freedom + k));
	    }
	}
	F77("/\n");

	/* 情報nsetno */
	if(dconds) {
	    F77("      data nsetno/");
	    for(k=0;k<dconds;k++) {
		if(k != 0) F77(",");
		d_ptr = *(d_ptrptr + k);
		PUT(fp,"%d",d_ptr->b_nodeset);
	    }
	    F77("/\n");
	}
	
	/* 情報 nbedtno */
	if(nconds) {
	    F77("      data nbedtno/");
	    for(k=0;k<nconds;k++) {
		if(k != 0) F77(",");
		n_ptr = *(n_ptrptr + i);
		PUT(fp,"%d",n_ptr -> belem_no);
	    }
	    F77("/\n");
	}
	
	/********************/
	/*  プログラム本体  */
	/********************/

	/* 【dat.PE@@@.X ファイルをOPENする 】 */
	PUT(fp,"*[ OPEN dat.PE@@@.X data file @@@ starts 0]\n");
	PUT(fp,"      iunit = io_tmp\n");
	PUT(fp,"      if(nedtno(1).gt.10) then\n");
	PUT(fp,"        stop 'nedtno(read_pdat%d)'\n",i+1);
	PUT(fp,"      endif\n");
	PUT(fp,"      mkar1 = (ipe-1)/100\n");
	PUT(fp,"      mkar2 = (ipe-1-mkar1*100)/10\n");
	PUT(fp,"      mkar3 =  ipe-1-mkar1*100-mkar2*10\n");
	PUT(fp,"      if(ipe.le.10) then\n");
	PUT(fp,"        open(unit=iunit,file='dat.PE'//char(48+mkar3)//\n");
	PUT(fp,"     $       '.'//char(48+nedtno(1)))\n");
	PUT(fp,"      else if(ipe.le.100) then\n");
	PUT(fp,"        open(unit=iunit,file='dat.PE'//char(48+mkar2)//\n");
	PUT(fp,"     $       char(48+mkar3)//'.'//char(48+nedtno(1)))\n");
	PUT(fp,"      else if(ipe.le.1000) then\n");
	PUT(fp,"        open(unit=iunit,file='dat.PE'//char(48+mkar1)//\n");
	PUT(fp,"     $       char(48+mkar2)//char(48+mkar3)//\n");
	PUT(fp,"     $       '.'//char(48+nedtno(1)))\n");
	PUT(fp,"      else\n");
	PUT(fp,"        stop 'ipe over 999'\n");
	PUT(fp,"      endif\n");
	COM;
	F77("***\n");
	COM;

	/* 基本パラメータを読む */
	COM;

	F77("* read space dimension\n");
	F77("      read(iunit,9001) ndim\n");
	F77("      icons(1) = ndim\n");
	F77("***\n");

	F77("* read the number of sub-regions\n");
	F77("      read(iunit,9001) npesum\n");
	F77("      if(npe.ne.npesum) stop 'npesum error'\n");
	F77("      icons(2) = npesum\n");
	F77("***\n");

	F77("* read the sub domain node number\n");
	F77("      read(iunit,9001) npmaxsub\n");
	F77("      icons(3) = npmaxsub\n");
	F77("***\n");

	F77("* read number of element groups\n");
	F77("      read(iunit,9001) nmatrix\n");
	F77("      icons(14) = nmatrix\n");

/*  削除 Apr24 1996 14:47:33 ファイルの手直しによる
	F77("      if(nedtno(1).ne.nmatrix) stop 'nedtno error'\n");
 */

	F77("***\n");

	F77("* read number of subdomain elements and subdomain nodes\n");
	F77("      read(iunit,9011) nelemsub,np\n");
	F77("      icons(4) = nelemsub\n");
	F77("      icons(5) = np\n");
	F77("***\n");

	F77("* read word 'NSET'\n");
	F77("      read(iunit,9021) word\n");
	F77("      if(word.ne.'NSET') stop 'NSET error'\n");
	COM;
	F77("      read(iunit,9001) ndisub\n");
	F77("      if(ndisub.gt.MAX_NODESET) stop 'ndisub error'\n");
	F77("      icons(6) = ndisub\n");
	F77("***\n");

	F77("* read word 'EDAT'\n");
	F77("      read(iunit,9021) word\n");
	F77("      if(word.ne.'EDAT') stop 'EDAT error'\n");
	COM;
	F77("      read(iunit,9001) neusub\n");
	F77("      if(neusub+1.gt.MAX_EDATSET) stop 'neusub'\n");
	F77("      icons(7) = neusub\n");
	F77("***\n");

	F77("* Adjust memory alignment\n");
	F77("      if(mod(np_work,2).eq.0) np_work=np_work+1\n");
	F77("***\n");
	
	F77("* allocate x,y array\n");
	F77("      if(ndim .ne. 2) stop 'Now, 2-dimensional only'\n");
	F77("      npp_xsub = np_work\n");
	F77("      npp_ysub = npp_xsub+npmaxsub*2\n");
	F77("      np_work = npp_ysub+npmaxsub*2\n");
	F77("      ipdat(1,1)=npp_xsub-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,1)=npmaxsub\n");
	F77("      ipdat(1,2)=npp_ysub-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,2)=npmaxsub\n");
	F77("***\n");

	F77("* set icons base number\n");
	F77("      nmade = ndim\n");
	F77("***\n");

	F77("* read node data\n");
	F77("      if(ndim .ne. 2) stop 'Now, 2-dimensional only'\n");
	F77("      call data_nodsub2(iunit,feel(npp_xsub),\n");
	F77("     $                         feel(npp_ysub),npmaxsub)\n");
	F77("***\n");

	F77("* allocate sub-domain arrays\n");
	F77("      call f_alloc(npp_isubelem,'Read isubelem',nelemsub*np,0)\n");
	F77("      ipdat(1,nmade+1)=npp_isubelem-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+1)=nelemsub*np\n");
	F77("*\n");

	F77("      call f_alloc(npp_nelegru,'Read nelegru',nelemsub,0)\n");
	F77("      ipdat(1,nmade+2)=npp_nelegru-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+2)=nelemsub\n");
	F77("*\n");
	
	F77("      call f_alloc(npp_nloglo,'Read nloglo',npmaxsub,0)\n");
	F77("      ipdat(1,nmade+3)=npp_nloglo-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+3)=npmaxsub\n");
	F77("*\n");
	
	F77("      call f_alloc(npp_nsendlist,'Read nsendlist',npesum,0)\n");
	F77("      ipdat(1,nmade+4)=npp_nsendlist-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+4)=npesum\n");
	F77("*\n");
	
	F77("      call f_alloc(npp_nrecvlist,'Read nrecvlist',npesum,0)\n");
	F77("      ipdat(1,nmade+5)=npp_nrecvlist-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+5)=npesum\n");
	F77("*\n");

	/* BLOCK A */
	F77("      if(ndisub.gt.0) then\n");
	F77("        call f_alloc (npp_ndikaz,'Read ndikaz',ndisub,0)\n");
	F77("        ipdat(1,nmade+6)=npp_ndikaz-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+6)=ndisub\n");
	F77("      else if (ndisub.eq.0) then\n");
	F77("        call f_alloc (npp_ndikaz,'Read ndikaz',1,0)\n");
	F77("        ipdat(1,nmade+6)=npp_ndikaz-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+6)=1\n");
	F77("      end if\n");
	F77("*\n");

        /* B */
	F77("      if (ndisub.gt.0) then\n");    
	F77("        call f_alloc (npp_ndinum,'Read ndinum',ndisub,0)\n");
	F77("        ipdat(1,nmade+7)=npp_ndinum-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+7)=ndisub\n");
	F77("      else if (ndisub.eq.0) then\n");
	F77("  	     call f_alloc (npp_ndinum,'Read ndinum',1,0)\n");
	F77("        ipdat(1,nmade+7)=npp_ndinum-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+7)=1\n");
	F77("      end if\n");
	F77("*\n");

	/* C */
	F77("      if (neusub.gt.0) then\n");    
	F77("        call f_alloc (npp_neukaz,'Read neukaz',neusub,0)\n");
	F77("        ipdat(1,nmade+8)=npp_neukaz-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+8)=neusub\n");
	F77("      else if (neusub.eq.0) then\n");
	F77("        call f_alloc (npp_neukaz,'Read neukaz',1,0)\n");
	F77("        ipdat(1,nmade+8)=npp_neukaz-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+8)=1\n");
	F77("      end if\n");
	F77("*\n");
	
	/* D */
	F77("	   if (neusub.gt.0) then\n");
	F77("	     call f_alloc (npp_neunum,'Read neunum',neusub,0)\n");
	F77("        ipdat(1,nmade+9)=npp_neunum-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+9)=neusub\n");
	F77("      else if (neusub.eq.0) then\n");
	F77("        call f_alloc (npp_neunum,'Read neunum',1,0)\n");
	F77("        ipdat(1,nmade+9)=npp_neunum-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+9)=1\n");
	F77("      end if\n");	F77("*\n");

	F77("      call f_alloc(npp_matno,'Read matno',nelemsub,0)\n");
	F77("      ipdat(1,nmade+10)=npp_matno-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+10)=nelemsub\n");
	F77("*\n");

	F77("*---------------------\n");
	F77("* Read sub-domain data\n");
	F77("*---------------------\n");
	F77("      call p_read_pedatA(iunit,npesum,npmaxsub,nelemsub,\n");
	F77("     $                 np,ndisub,neusub,\n");
	F77("     $                 feel(npp_isubelem),feel(npp_nelegru),\n");
	F77("     $                 feel(npp_nloglo),feel(npp_matno),\n");
	F77("     $                 feel(npp_nsendlist),feel(npp_nrecvlist),\n");
	F77("     $                 feel(npp_ndikaz),feel(npp_ndinum),\n");
	F77("     $                 feel(npp_neukaz),feel(npp_neunum),\n");
	F77("     $                 ipe,nmatrix)\n");
	F77("***\n");
	
	F77("* read inner nodes in sub-domain\n");
	F77("      read(iunit,9001) ndaisum\n");
	F77("      call f_alloc(npp_nainod,'Read nainod',ndaisum,0)\n");
	F77("      call p_read_pedatB(iunit,ndaisum,feel(npp_nainod))\n");
	F77("***\n");

	F77("* read interface nodes in sub-domain\n");
	F77("      read(iunit,9001) ndinsum\n");
	F77("      if(ndinsum.ne.0) then\n");
	F77("        call f_alloc(npp_ninnod,'Read ninnod',ndinsum,0)\n");
	F77("        call p_read_pedatB(iunit,ndinsum,feel(npp_ninnod))\n");
	F77("      endif\n");
	F77("***\n");

	F77("*--------------------------------------------------\n");
	F77("* Make equation number array from node number array\n");
	F77("*--------------------------------------------------\n");
	F77("* allocate memory\n");
	PUT(fp,"      call f_alloc(npp_ipdsub,'solve%d(ipdsub)',npmaxsub,0)\n",
	    i+1);
	PUT(fp,"      call f_alloc(npp_IPFsub,'solve%d(ipdsub)',npmaxsub,0)\n",
	    i+1);
	F77("      call zeroi(feel(npp_ipdsub),npmaxsub)\n");
	F77("      call zeroi(feel(npp_IPFsub),npmaxsub)\n");
	F77("      ipdat(1,11+nmade)=npp_ipdsub-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,11+nmade)=npmaxsub\n");
	F77("      ipdat(1,12+nmade)=npp_IPFsub-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,12+nmade)=npmaxsub\n");
	F77("***\n");

	F77("* make equation number from node number\n");
	F77("      if(NEG .ne. 1) stop 'Now, NEG must be 1'\n");
	F77("      do 50 i=1,NEG\n");
	F77("        call ipf_nfree(nelemsub,np,feel(npp_IPFsub),\n");
	F77("     $                   feel(npp_isubelem),nenfre(1,i))\n");
	F77("   50 continue\n");
	F77("*\n");
	F77("      call makeipd(feel(npp_IPFsub),feel(npp_ipdsub),\n");
	F77("     $             npmaxsub,neq_sub)\n");
	F77("      icons(8)=neq_sub\n");
	F77("***\n");

	/* 内点上の方程式番号データ生成 */
	F77("* Calculate number of equations for inner nodes\n");
	F77("      call p_calc_eqno(ndaisum,feel(npp_nainod),naisum,\n");
	F77("     $                feel(npp_IPFsub),npmaxsub)\n");
	F77("      icons(9)= naisum\n");
	F77("***\n");

	F77("* Make equation number array for inner nodes\n");
	F77("      call f_alloc(npp_naieq,'Make naieq',naisum,0)\n");
	F77("      call p_make_eqno(ndaisum,feel(npp_nainod),\n");
	F77("     $                 feel(npp_IPFsub),feel(npp_ipdsub),\n");
	F77("     $                 feel(npp_naieq),naisum,npmaxsub)\n");
	F77("      ipdat(1,13+nmade)=npp_naieq-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,13+nmade)=naisum\n");
	F77("***\n");

	/* インタフェース上の方程式番号データ生成 */
	F77("* Calculate number of equations for interface nodes\n");
	F77("      if(ndinsum .ne. 0) then\n");
	F77("        call p_calc_eqno(ndinsum,feel(npp_ninnod),\n");
	F77("     $                  ninsum,feel(npp_IPFsub),npmaxsub)\n");
	F77("        icons(10) = ninsum\n");
	F77("***\n");

	F77("* Make equation number array for interface node\n");
	F77("        call f_alloc(npp_nineq,'make nineq',ninsum,0)\n");
	F77("        call p_make_eqno(ndinsum,feel(npp_ninnod),\n");
	F77("     $                   feel(npp_IPFsub),feel(npp_ipdsub),\n");
	F77("     $                   feel(npp_nineq),ninsum,npmaxsub)\n");
	F77("        ipdat(1,nmade+14) = npp_nineq-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+14) = ninsum\n");
	F77("      endif\n");
	F77("***\n");


	F77("* Read information for SEND/RECEIVE\n");
	PUT(fp,"      call p_read_srdat%d(npe,iunit,feel(npp_nsendlist),\n",
	    i+1);
	F77("     $     nsendnum,feel,ipe,npesum,feel(npp_nrecvlist),\n");
	F77("     $     nrecvnum,innersum,icons,ipdat,nmade,\n");
	F77("     $     feel(npp_IPFsub),feel(npp_ipdsub),npmaxsub,\n");
	F77("     $     nbase,ndisub,neusub)\n");
	F77("***\n");
	
	/* Dirichlet条件用データを読み込む */
	if(total_dconds) {
	    F77("* Read Dirichlet boundary node data\n");
	    F77("      call f_alloc(npp_npsyo,'Read npsyo',ndisub,0)\n");
	    F77("      call f_alloc(npp_npins,'Read npins',ndisub,0)\n");
	    F77("      ipdat(1,nmade+21)=npp_npsyo-nbase(1,ipe)+nbase(1,1)\n");
	    F77("      ipdat(2,nmade+21)=ndisub\n");
	    F77("      ipdat(1,nmade+22)=npp_npins-nbase(1,ipe)+nbase(1,1)\n");
	    F77("      ipdat(2,nmade+22)=ndisub\n");
	    F77("*\n");
	    PUT(fp,"      call p_read_ddat_%d(iunit,feel(npp_ndikaz),\n",i+1);
	    F77("     $                  feel(npp_ndinum),feel(npp_npsyo),\n");
	    F77("     $                  feel(npp_npins),ndisub,feel,\n");
	    F77("     $                  ipdat,nbase,ncont2,nmade,ipe,\n");
	    F77("     $                  np_work,np_push)\n");
	    F77("***\n");
	}
	
	/* Neumann条件用データを読み込む */
	if(total_nconds) {
	    F77("* Read Neumann boundary EDAT data\n");
	    F77("      call f_alloc(npp_npibsub,'Read npibsub',neusub,0)\n");
	    F77("      ipdat(1,nmade+23)=npp_npibsub-nbase(1,ipe)+nbase(1,1)\n");
	    F77("      ipdat(2,nmade+23)=neusub\n");
	    F77("*\n");
	    PUT(fp,"      if(neusub.ne.0) then\n");
	    PUT(fp,"        call p_read_ndat(iunit,feel(npp_npibsub),\n",i+1);
	    F77("     $       feel(npp_neukaz),feel(npp_neunum),ndisub,neusub,\n");
	    F77("     $       feel,ipdat,nbase,ncont2,nmade,ipe)\n");
	    F77("         endif\n");
	    F77("***\n");
	}


	/* 読み込みを終え、ファイルをクローズする */
	F77("****************\n");
	F77("*     CLOSE FILE\n");
	F77("****************\n");
	F77("      close(unit=iunit)\n");
	F77("***\n");

	/* FORMAT 文 */
	F77(" 9001 format(i8)\n");
	F77(" 9011 format(2i8)\n");
	F77(" 9021 format(a4)\n");
	F77("      return\n");
	F77("      end\n");
    
	/* 送信／受信データ読み込みルーチン p_read_srdat@@(旧read_srp2の作成)*/
	
	PUT(fp,"      subroutine p_read_srdat%d(npe,iunit,nsendlist,\n",i+1);
	PUT(fp,"     $           nsendnum,feel,ipe,npesum,nrecvlist,\n");
	PUT(fp,"     $           nrecvnum,innersum,icons,ipdat,nmade,\n");
	PUT(fp,"     $           IPFsub,ipdsub,npmaxsub,nbase,\n");
	PUT(fp,"     $           ndisub,neusub)\n");
	
	comment1(fp);
	real8(fp);
	comment1(fp);
	
	/* 【配列宣言】 */
	F77("      dimension nbase(2,npe)\n");
	F77("      real*4    feel(*)\n");
	F77("      dimension nsendlist(npesum)\n");
	F77("      dimension nrecvlist(npesum)\n");
	F77("      dimension icons(*),ipdat(2,*)\n");
	F77("      dimension IPFsub(npmaxsub),ipdsub(npmaxsub)\n");
	
	comment1(fp);

	F77("****************\n");
	F77("* Read send data\n");
	F77("****************\n");
	F77("      nsendnum = 0\n");
	COM;
	
	F77("      if(nsendlist(ipe).eq.1) then\n");
	F77("        read(iunit,9001) nsendnum\n");
	F77("      endif\n");
	F77("      icons(11)=nsendnum\n");
	COM;

	F77("      call f_alloc(npp_nsendtable,'Read nsendtable',npesum,0)\n");
	F77("      ipdat(1,nmade+15)=npp_nsendtable-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+15)=npesum\n");
	COM;
	
	F77("      call f_alloc(npp_nsendndkaz,'Read nsendndkaz',npesum,0)\n");
	F77("      call f_alloc(npp_nsendkaz,'Read nsendkaz',npesum,0)\n");
	F77("      ipdat(1,nmade+17)=npp_nsendkaz-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+17)=npesum\n");
	COM;

	F77("      call f_alloc(npp_npseod,'Read npseod',npesum,0)\n");
	F77("***\n");

	F77("* call Read send data subroutine\n");
	F77("      call p_read_sdat(feel(npp_nsendtable),nsendnum,\n");
	F77("     $     feel(npp_nsendndkaz),feel,iunit,feel(npp_npseod),\n");
	F77("     $     npmaxsub,npesum,ipe,nsendlist)\n");
	COM;

	F77("****************\n");
	F77("* Read recv data\n");
	F77("****************\n");
	F77("      nrecvnum = 0\n");
	COM;
	
	F77("      if(nrecvlist(ipe).eq.1) then\n");
	F77("        read(iunit,9001) nrecvnum\n");
	F77("      endif\n");
	COM;
	
	F77("      icons(12)=nrecvnum\n");
	F77("*\n");

	F77("      call f_alloc(npp_nrecvtable,'Read nrecvtable',npesum,0)\n");
	F77("      ipdat(1,nmade+16)=npp_nrecvtable-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+16)=npesum\n");
	COM;

	F77("      call f_alloc(npp_nrecvndkaz,'Read nrecvndkaz',npesum,0)\n");
	F77("      call f_alloc(npp_nrecvkaz,'Read nrecvkaz',npesum,0)\n");
	F77("      ipdat(1,nmade+18)=npp_nrecvkaz-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+18)=npesum\n");
	COM;
	
	F77("      call f_alloc(npp_npreod,'Read npreod',npesum,0)\n");
	F77("***\n");
	
	F77("* call Read recv data subroutine\n");
	PUT(fp,"      call p_read_rdat(feel(npp_nrecvtable),nrecvnum,\n");
	F77("     $     feel(npp_nrecvndkaz),feel,iunit,feel(npp_npreod),\n");
	F77("     $     npmaxsub,npesum,ipe,nrecvlist)\n");
	COM;
	
	F77("****************************\n");
	F77("* Make equation number array\n");
	F77("****************************\n");
	F77("      call f_alloc(npp_npsre,'Read npsre',npesum,0)\n");
	F77("      ipdat(1,nmade+19)=npp_npsre-nbase(1,ipe)+nbase(1,1)\n");
	F77("      ipdat(2,nmade+19)=npesum\n");
	COM;

	F77("      call p_make_sreq(nsendnum,\n");
	F77("     $     feel(npp_nsendndkaz),feel,iunit,feel(npp_npseod),\n");
	F77("     $     IPFsub,ipdsub,npmaxsub,feel(npp_npsre),nmade,\n");
	F77("     $     feel(npp_nsendkaz),nrecvnum,npesum,ipdat,nbase,\n");
	F77("     $     ipe,feel(npp_nrecvndkaz),\n");
	F77("     $     feel(npp_npreod),feel(npp_nrecvkaz),nsendlist,\n");
	F77("     $     nrecvlist,ndisub,neusub,npe)\n");
	COM;


	F77("***************************\n");
	F77("* Make scalar product array\n");
	F77("***************************\n");

	F77("      innersum=0\n");
	COM;
	
	F77("      if(nrecvlist(ipe).eq.1) then\n");
	F77("        read(iunit,9001) innersum\n");
	F77("        call f_alloc(npp_innernd,'Read Innernd',innersum,0)\n");
	F77("        call p_read_prdat(iunit,innersum,feel(npp_innernd))\n");
	F77("      endif\n");
	F77("***\n");
	F77("* Make equation number array for inner product\n");
	F77("      nintotal=1\n");
	F77("      if(nrecvlist(ipe).eq.1) then\n");
	F77("*\n");
	F77("*     PE No. [ipe] has data to receive\n");
	F77("*\n");
	F77("        call p_calc_eqno(innersum,feel(npp_innernd),nintotal,\n");
	F77("     $                   IPFsub,npmaxsub)\n");
	F77("*\n");
	F77("        call f_alloc(npp_ninner,'Read inner',nintotal,0)\n");
	F77("        ipdat(1,nmade+20)=npp_ninner-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+20)=nintotal\n");
	F77("*\n");
	F77("        call p_make_eqno(innersum,feel(npp_innernd),IPFsub,\n");
	F77("     $                   ipdsub,feel(npp_ninner),nintotal,\n");
	F77("     $                   npmaxsub)\n");
	F77("*\n");
	F77("      else\n");
	F77("*\n");
	F77("* npp_ninner must be exist, though no need to use...\n");
	F77("*\n");
	F77("        call f_alloc(npp_ninner,'ninner',1,0)\n");
	F77("        ipdat(1,nmade+20)=npp_ninner-nbase(1,ipe)+nbase(1,1)\n");
	F77("        ipdat(2,nmade+20)=1\n");
	F77("        nintotal=1\n");
	F77("        call zeroi(feel(npp_ninner),1)\n");
	F77("      endif\n");
	F77("*\n");
	F77("      icons(13)=nintotal\n");
	F77("***\n");
	
	F77(" 9001 format(i8)\n");
	F77("      return\n");
	F77("      end\n");


	/**********************************************/
	/* Dirichlet,Neumann 条件存在下のサブルーチン */
	/**********************************************/
	
	/* 次のサブルーチンは、Dirichlet条件がソース中に一つでもある場合のみ
	   作成する。(total_dcondsが指標)。各solve文では、そのsolve文に
	   Dirichlet条件がある場合と無い場合では処理が異なるので注意する事 */
	   
	if(total_dconds) {
	    PUT(fp,"      subroutine p_read_ddat_%d(iunit,ndikaz,ndinum,\n",
		i+1);
	    F77("     $             npp_nsyori,npp_inset,ndisub,feel,\n");
	    F77("     $             ipdat,nbase,ncont2,nmade,ipe,np_work,np_push)\n");
	    comment1(fp);
	    
	    real8(fp);

	    if(dconds) {   /* このsolve文にDirichlet条件がある場合 */
		PUT(fp,"      parameter (NDC = %d)\n",dconds);
		F77(   "      dimension nsetno(NDC)\n");
	    }
	    COM;

	    F77("      real*4 feel(*)\n");
	    F77("      dimension ndikaz(ndisub),ndinum(ndisub)\n");
	    F77("      dimension npp_nsyori(ndisub),npp_inset(ndisub)\n");
	    F77("      dimension ipdat(2,*),nbase(2,*)\n");
	    
	    COM;

	    if(dconds) {
		F77("      data nsetno/");
		for(j=0;j<dconds;j++) {
		    if(j != 0) F77(",");
		    d_ptr = *(d_ptrptr + j);
		    PUT(fp,"%d",d_ptr->b_nodeset);
		}
		F77("/\n");
	    }
	    
	    comment1(fp);
	    
	    F77("      do 10 i=1,ndisub\n");
	    F77("        if (ndikaz(i).gt.0) then\n");
	    F77("          read(iunit,9001) nosub\n");
	    
	    if(dconds) {  
		F77("          do 20 j=1,NDC\n");
		F77("            if(nsetno(j).eq.nosub) then\n");
		F77("              goto 30\n");
		F77("            endif\n");
		F77("   20     continue\n");
	    }
 	    F77("          np_push=np_work\n");
	    COM;
            F77("   30     continue\n");
	    
	    COM;
	    F77("          call f_alloc(npp_nsyori(i),'nsyori(i)',\n");
	    F77("     $                 ndikaz(i),0)\n");
	    F77("          ipdat(1,nmade+23+i)=npp_nsyori(i)- \n");
	    F77("     $            nbase(1,ipe)+nbase(1,1)\n");
	    F77("          ipdat(2,nmade+23+i)=ndikaz(i)\n");
	    COM;
	    F77("          call f_alloc(npp_inset(i),'inset(i)',\n");
	    F77("     $                 ndikaz(i)*ndinum(i),0)\n");
	    F77("          ipdat(1,nmade+23+ndisub+i)=npp_inset(i) -\n");
	    F77("     $                     nbase(1,ipe)+nbase(1,1)\n");
	    F77("          ipdat(2,nmade+23+ndisub+i)=ndikaz(i)*ndinum(i)\n");
	    
	    COM;
	    F77("          call p_read_d_nset(iunit,ndikaz(i),ndinum(i),\n");
	    F77("     $          feel(npp_nsyori(i)),feel(npp_inset(i)))\n");
	    COM;
	    
	    if(dconds) {
		F77("          do 50 j=1,NDC\n");
		F77("            if(nsetno(j).eq.nosub) then\n");
		F77("              goto 60\n");
		F77("            endif\n");
		F77("   50     continue\n");
	    }
	    F77("          np_work=np_push\n");
	    F77("   60     continue\n");
	    F77("        endif\n");
	    COM;
	    F77("   10 continue\n");
	    F77("***\n");
	    
	    F77("      return\n");
	    COM;
	    
	    F77(" 9001 format(i8)\n");
	    F77("***\n");
	    F77("      end\n");
	    

	}   /* if(total_dconds) に対応する括弧。
	       ここは、pdeファイル中にディリクレ条件がある場合のみ書く */
    

    }   /* solve文の数のループ */



    CloseFile(fp);
}

