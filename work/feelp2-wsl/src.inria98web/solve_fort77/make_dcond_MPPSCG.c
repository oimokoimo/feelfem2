/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_dcond_MPPSCG.c
 *      Date:   1996/04/03
 *              1996/04/22
 *   
 *   Purpose:   ディリクレ条件ルーチン作成(並列処理版)
 *   Functions: 
 *              
 *              この関数はmake_solve_fort77から呼ばれる
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void make_dcond_MPPSCG(solve_no,dcond_no,d_ptr)
     int            solve_no;   /* solve文番号       */
     int            dcond_no;   /* dirichlet条件番号 */
     DirichletData *d_ptr;
{
    int i;
    int dimension;

    int terms;
    char *from[MAX_TERM_VARS];
    char *to[MAX_TERM_VARS];

    FILE *fp;
    char fname[FNAME_SIZE];
    char name_buf[38];
    char name_buf2[38];

    
    sprintf(fname,DCOND_FNAME,solve_no,dcond_no);

    StoreMakefile(fname,USER_LIBRARY);
    fp = OpenFileToWrite(fname);
    
    /*---
      subroutine文の作成
      ---*/
    F77("      subroutine ");
    PUT(fp,DCOND_NAME,solve_no,dcond_no);
    
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
	SystemAbort("what dimension ERROR(make_dcond_skyline)");
    }

    /*
     * 引き数  
     *         KH(*),KLD(*)
     *         IPD(*)       累積節点自由度
     *         
     *         inset(2,nd)  節点集合データ(自由度距離付)
     *         nd           節点数
     */
    F77(",A,JA,B,ipdsub,npp_nsyori,npp_inset,ndikaz,ndinum,nsetno,");
    F77("feel,npmaxsub,neq_sub,MJ,JDP,ndisub,NDC");


    
    for(i=0;i<d_ptr->fem_vars;i++) {
	F77(",");
	PUT(fp,FEM_VAR_NAME77,*(d_ptr->fem_var_name + i));
    }

    for(i=0;i<d_ptr->scalar_vars;i++) {
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(d_ptr->scalar_var_name + i));
    }
    
    F77(")\n");

    /*============*/
    /*  定形宣言  */
    /*============*/
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);

    comment1(fp);
    /*=======================*/
    /* 引き数のdimension宣言 */
    /*=======================*/

    F77("      real*4 feel(*)\n");
    COM;

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


    F77("      dimension A(neq_sub,MJ),JA(neq_sub,MJ),B(neq_sub)\n");
    F77("      dimension ipdsub(*)\n");         
    F77("      dimension npp_nsyori(ndisub),npp_inset(ndisub)\n");
    F77("      dimension ndikaz(ndisub),ndinum(ndisub)\n");
    F77("      dimension nsetno(*)\n");

    for(i=0;i<d_ptr->fem_vars;i++) {
	if(i==0) COM;
	F77("      dimension ");
	PUT(fp,FEM_VAR_NAME77,*(d_ptr->fem_var_name + i));
	F77("(*)\n");
    }

    for(i=0;i<d_ptr->scalar_vars;i++) {
	if(i==0) COM;
	F77("      real*8 ");
	PUT(fp,SCALAR_VAR_NAME77,*(d_ptr->scalar_var_name + i));
	F77("\n");
    }
    COM;

    comment1(fp);

    /* 境界条件数の判定とCOルーチンの呼び出し */
    PUT(fp,"      N_dcond_no = %d\n",dcond_no);
    PUT(fp,"      N_nsetno   = nsetno(N_dcond_no)\n");
    COM;

    PUT(fp,"      if(ndikaz(N_nsetno) .le. 0) return\n");

    /* COルーチンの呼び出し */
    COM;
    F77("      call ");
    PUT(fp,DCOND_CO_NAME,solve_no,dcond_no);
    F77("(x,y,A,JA,MJ,B,ipdsub,neq_sub,feel(npp_inset(N_nsetno)),");
    F77("ndikaz(N_nsetno),feel(npp_nsyori(N_nsetno)),JDP");

    for(i=0;i<d_ptr->fem_vars;i++) {
	F77(",");
	PUT(fp,FEM_VAR_NAME77,*(d_ptr->fem_var_name + i));
    }

    for(i=0;i<d_ptr->scalar_vars;i++) {
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(d_ptr->scalar_var_name + i));
    }
    F77(")\n");

    comment1(fp);
    PUT(fp,"      return\n");
    PUT(fp,"      end\n");
    CloseFile(fp);

    /*==============================================================*/
    /*==============================================================*/
    /*==============================================================*/

    /* COルーチンの書き出し */
    sprintf(fname,DCOND_CO_FNAME,solve_no,dcond_no);

    StoreMakefile(fname,USER_LIBRARY);
    fp = OpenFileToWrite(fname);    

    F77("      subroutine ");
    PUT(fp,DCOND_CO_NAME,solve_no,dcond_no);

    F77("(x,y,A,JA,MJ,B,IPD,neq,inset,nd,nsyori,JDP)\n");
    COM;
    real8(fp);
    COM;

    /* 配列宣言 */
    F77("      dimension x(*),y(*)\n");
    F77("      dimension A(neq,MJ),JA(neq,MJ),B(neq)\n");
    F77("      dimension nsyori(nd)\n");
    F77("      dimension IPD(*)\n");
    F77("      dimension inset(2,nd)\n");

    /*==========================*/
    /* 処理の始まり(並列処理版) */
    /*==========================*/
    F77("      do 100 i=1,nd\n");
    COM;
    
    /*   基本変数  ip    節点番号  
     *             ieq   方程式番号
     */

    F77("        ip  = inset(1,i)\n");
    F77("        ieq = IPD(ip) + inset(2,i)\n");

    /*=======================*/
    /* Dirichlet条件式の生成 */
    /*=======================*/

    /*------------------------*/
    /* term convert用配列作成 */
    /*------------------------*/
    /*==============
      変更変数の一覧
      ==============
      fem変数     u  -> fem_u(ip)
      scalar変数  p  -> sc_p
      空間変数    x  -> x(ip)
      ==========================================*/
    terms = 0;

    switch(dimension) {
      case 3:
	from[terms] = "z";
	to[terms]   = "z(ip)";
	terms++;

      case 2:
	from[terms] = "y";
	to[terms]   = "y(ip)";
	terms++;

      case 1:
	from[terms] = "x";
	to[terms]   = "x(ip)";
	terms++;
	break;

      default:
	break;
    }

    for(i=0;i<d_ptr->fem_vars;i++) {
	sprintf(name_buf2,FEM_VAR_NAME77,*(d_ptr->fem_var_name + i));
	sprintf(name_buf,"%s(ip)",name_buf2);

	from[terms] = *(d_ptr->fem_var_name + i);
	to[terms]   = MakeStringCopy(name_buf);

	terms++;
    }

    for(i=0;i<d_ptr->scalar_vars;i++) {
	sprintf(name_buf,SCALAR_VAR_NAME77,*(d_ptr->scalar_var_name + i));

	from[terms] = *(d_ptr->scalar_var_name + i);
	to[terms]   = MakeStringCopy(name_buf);
	terms++;
    }


    

    /* ディリクレ条件への代入処理 */
    
    F77("        if(nsyori(i).eq.1) then\n");
    COM;
    
    PUT(fp,"          u = %s\n",
	term_convert(d_ptr->expr->expr_inf,from,to,terms));
	

    F77("        do 200 j=1,MJ\n");
    F77("          A(ieq,j) = 0.0D0\n");
    F77(" 200    continue\n");
    COM;

    F77("        A(ieq,JDP) =1.0d0\n");
    F77("        B(ieq)     =  u  \n");
    COM;
    COM;

    F77("      else if(nsyori(i).eq. -1) then\n");
    COM;
    F77("        do 210 ii=1,MJ\n");
    F77("          A(ieq,ii)= 0.0d0\n");
    F77(" 210    continue\n");
    F77("        B(ieq) = 0.0d0\n");
    F77("      else\n");
    F77("        stop 'error nsyori(i)'\n");
    F77("      endif\n");
    comment1(fp);

    F77(" 100  continue\n");
    COM;
    F77("      return\n");
    F77("      end\n");
      
    CloseFile(fp);

    return;
}

