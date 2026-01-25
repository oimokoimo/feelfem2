/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_dcond_skyline.c
 *      Date:   1993/12/5
 *   
 *   Purpose:   ディリクレ条件ルーチン作成
 *   Functions: 
 *              
 *              この関数はmake_solve_fort77から呼ばれる
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void make_dcond_skyline(solve_no,dcond_no,d_ptr)
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
    F77(",VFG,VD,VFS,VFI,KLD,KH,IPD,neq,inset,nd");

    
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

    F77("      dimension VFG(*),VD(*),VFS(*),VFI(*),KLD(*),KH(*)\n");
    F77("      dimension IPD(*)\n");         
    F77("      dimension inset(2,nd)\n");

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

    /*==============*/
    /* 処理の始まり */
    /*==============*/
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
    
    PUT(fp,"        u = %s\n",
	term_convert(d_ptr->expr->expr_inf,from,to,terms));
	
    F77("        do 110 j=1,neq\n");
    COM;
    F77("          if(ieq         .eq.   j) goto 110\n");
    F77("          if(j           .gt. ieq) goto 105\n");
    F77("          if(ieq-KH(ieq) .gt.   j) goto 110\n");
    COM;
    /*  行列を対称に保つ為には… */
    F77("          lp     = KLD(ieq+1) - ieq + j\n");
    F77("          VFG(j) = VFG(j)     - u   * VFS(lp)\n");
    F77("          VFS(lp)= 0.0d0\n");
    F77("          goto 110\n");
    COM;

    F77(" 105      if(j - KH(j) .gt. ieq) goto 110\n");
    F77("          lp     = KLD(j+1)   - j + ieq\n");
    F77("          VFG(j) = VFG(j)     - u * VFI(lp)\n");
    F77("          VFI(lp)= 0.0d0\n");
    COM;

    F77(" 110    continue\n");
    COM;

    F77("        do 120 j=1,neq\n");
    F77("          if(ieq .eq. j) goto 121\n");
    F77("          if(ieq .gt. j) goto 125\n");
    COM;

    F77("          if(j - KH(j) .gt. ieq) goto 120\n");
    F77("          lp = KLD(j+1)-j+ieq\n");
    F77("          VFS(lp) = 0.0d0\n");
    F77("          goto 120\n");
    COM;

    F77(" 121      VD(ieq)  = 1.0d0\n");
    F77("          VFG(ieq) = u\n");
    F77("          goto 120\n");
    COM;
    
    F77(" 125      if(ieq - KH(ieq) .gt. j) goto 120\n");
    F77("          lp = KLD(ieq+1) - ieq + j\n");
    F77("          VFI(lp) = 0.0d0\n");
    F77(" 120    continue\n");
    F77(" 100  continue\n");
    COM;
    F77("      return\n");
    F77("      end\n");
      
    CloseFile(fp);

    return;
}
