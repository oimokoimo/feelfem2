/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   elem_fort77_main_CG.c
 *      Date:   1994/04/19
 *   
 *   Purpose:   要素プログラムの作成(CG解法対応版)
 *              
 *   Functions: subroutine elemXX_YY の作成, 
 *
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"


void elem_fort77_main_MPPSCG( no , solve_element_ptr )
     int no;                         /* solve文内のlocal番号 */
     SolveElement *solve_element_ptr;   /* SolveElement 構造体  */
{
    int i,j;

    ElementFORT77 *elem77_ptr;
    int            solve_no;
    int            equations;
    int            solve_element_unknowns;
    int            freedom;
    int            nodes;                /* 要素内節点数 */
    int            tmp;
    int            dimension;
    Equation      *eq_ptr;
    FEMvarinfo   **fem_varinfo_ptrptr;
    FEMvarinfo    *fem_varinfo_ptr;
    ElemDat       *elem_dat_ptr;
    EWISE_type    *ewise_type_ptr;
    char          *var_name;
    char          *domain_name;
    char         **chaptrptr;
    
    char fname[BUFSIZ];

    FILE *fp;

    /* 要素プログラム生成データ */
    elem77_ptr = solve_element_ptr -> elem77_dat;
    solve_no   = solve_element_ptr -> solve_no;
    solve_element_unknowns = solve_element_ptr -> unknowns;
    elem_dat_ptr = elem77_ptr->elem_dat;

    dimension = what_dimension();
    domain_name = solve_element_ptr -> domain_name;

    nodes = elem_dat_ptr -> nodes;

    /*********/
/*    SystemWarning("elem77_main_MPPSCGはまだ製作途中です"); */
    
    /*********/

    /* 
      種別：解析的積分処理を行うもの
            数値積分を行うもの
	      複数の積分が必要なもの
     */	     

    /* ファイルOpen */
    sprintf(fname,ELEM_MAIN_FNAME,solve_no,no);

    StoreMakefile( fname ,USER_LIBRARY);
    fp = OpenFileToWrite( fname );

    equations = solve_element_ptr -> equations;   /* 連立の数 */
    


    /* 【LINE-STEP-1】引き数の設定 */
    F77("      subroutine ");
    PUT(fp,ELEM_MAIN_NAME,solve_no,no);
    
    switch(dimension) {
      case 1: 
	SystemAbort("ERROR");
	break;
      case 2:
	F77("(x,y,ielem,nelem,np,A,JA,NNN,MJ,B,IPD,matno,nloglo,npmaxsub,JDP,nelegru");
	break;
      case 3:
	SystemAbort("ERROR");
	break;
    }

    /* 非線形問題の場合、unknown_femも持って来ないといけない */
    if(solve_element_ptr -> nonlinear_flag == YES) {
	/* dbg: nonlinear_flag はまだ設定していない */
	for(i=0;i<solve_element_unknowns;i++) {
	    F77(",");
	    PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr ->unknown_name+i));
	}
    }
	
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	    F77(",");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->fem_known_name+i));
    }

    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	    F77(",");
	PUT(fp,EWISE_VAR_NAME77,*(solve_element_ptr->ewise_known_name+i));
    }

    for(i=0;i<solve_element_ptr->scalar_knowns;i++) {
	    F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(solve_element_ptr->scalar_known_name+i));
    }    
    
    F77(")\n");

    /* LINE-STEP-2 【定形宣言】 */
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);
    
    /* LINE-STEP-3 【パラメータ宣言】 */
    /* [1]要素自由度 */
    PUT(fp,"      parameter (NDF = %d)\n",elem77_ptr->elem_freedom);
    
    /* [2]数値積分法に関する設定 */
    for(i=0;i<elem77_ptr->quad_methods;i++) {
	if(!streq(*(elem77_ptr->quad_name+i) , ANALYTIC_QUAD)) {
	    PUT(fp,"* No.%d Numerical integration method[%s]\n",i+1,
		*(elem77_ptr->quad_name + i));
	}
    }

    for(i=0;i<elem77_ptr->quad_methods;i++) {
	if(!streq(*(elem77_ptr->quad_name+i) , ANALYTIC_QUAD)) {
	    PUT(fp,"      parameter (NPG%d = %5d)\n",i+1,
		get_quad_nodes_by_name(*(elem77_ptr->quad_name + i)));
	}
    }

    COM;

    /* LINE-STEP-4 【dimension宣言】*/
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
    
    F77("      dimension ielem(np,nelem)\n");
    F77("      dimension A(NNN,MJ),JA(NNN,MJ),B(NNN)\n");
    F77("      dimension IPD(*)\n");
    F77("      dimension nelegru(*),nloglo(*),matno(*)\n");

    /* 非線形問題の場合、unknown_femも持って来ないといけない */
    if(solve_element_ptr -> nonlinear_flag == YES) {
	/* dbg: nonlinear_flag はまだ設定していない */
	for(i=0;i<solve_element_unknowns;i++) {
	    F77("      dimension ");
	    PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr ->unknown_name+i));
	    F77("(*)\n");
	}
    }
	
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	F77("      dimension ");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->fem_known_name+i));
	F77("(*)\n");
    }

    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	F77("      dimension ");
	PUT(fp,EWISE_VAR_NAME77,*(solve_element_ptr->ewise_known_name+i));
	tmp = get_ewise_nodes(*(solve_element_ptr->ewise_known_name+i),
			      solve_element_ptr -> domain_name );
	if(tmp == 1) {
	    F77("(*)\n");
	}
	else {
	    PUT(fp,"(%d,*)\n",tmp);
	}
    }

    for(i=0;i<solve_element_ptr->scalar_knowns;i++) {
	F77("      real*8 ");
	PUT(fp,SCALAR_VAR_NAME77,*(solve_element_ptr->scalar_known_name+i));
	F77("\n");
    }    
    
    COM;    
    /* LINE-STEP-5 【elemルーチン内で用いる補助配列】*/
    F77("      dimension  ienp(NDF)\n"); /* 小行列←→局所節点番号 */
    F77("      dimension  iedp(NDF)\n"); /* 自由度のdenstination   */
    F77("      dimension  ikp(NDF)\n");  /* 方程式番号を計算する補助配列 */
    
    /* LINE-STEP-6 【elemルーチン内で用いる補助COMMON文】*/
    PUT(fp,"      common /em%d_%d/ ea(NDF,NDF),eb(NDF)\n",solve_no,no);


    /* LINE-STEP-  【数値積分法に関するCOMMON文】 */
/*
    for(i=0;i<elem77_ptr->quad_methods;i++) {
	if(*(elem77_ptr->quad_terms+i) == 0) continue;

	COM;
	
	PUT(fp,"      common /em%d_%d_%d/",solve_no,no,i+1);
	chaptrptr = *(elem77_ptr->quad_term_var_aptr+i);
	for(j=0;j<*(elem77_ptr->quad_terms+i);j++) {
	    if(j != 0) F77(",");
	    PUT(fp,"%s_%d(NPG%d)",*(chaptrptr+j),i+1,i+1);
	}

	chaptrptr = *(elem77_ptr->quad_const_var_aptr + i);
	for(j=0;j<*(elem77_ptr->quad_consts+i);j++) {
	    PUT(fp,",qc%d_%s",i+1,*(chaptrptr+j));
	}
	F77("\n");
    }
    
    COM;
    */

    /* LINE-STEP-  【節点情報に関する配列ienp,iedpデータ文】 */
    /* 注意: 要素小行列の未知変数は、未知変数順に付ける dbg: */
 
    /* 配列 ienpデータ文 */


    F77("      data ienp/ ");
    fem_varinfo_ptrptr = elem77_ptr -> fem_var_info_ptrptr;
    for(i=0;i<solve_element_unknowns;i++) {

	if(i != 0){  /* 桁合わせ */
	    F77("     $            ");
	}
        
	var_name = *(solve_element_ptr->unknown_name + i);
	tmp  = NO;    /* 目的のFEMvarinfo構造体が見つかったかどうかのフラグ */

	/* FEMvarinfo構造体走査 */

	for(j=0;j<elem77_ptr->fem_vars;j++) {
	    fem_varinfo_ptr = *(fem_varinfo_ptrptr + j);

	    if(streq(var_name , fem_varinfo_ptr -> fem_var_name) ) {
		tmp = YES;
		break;
	    }
	}

	if(tmp == NO) {
	    SystemAbort("該当するFEMvarinfo構造体が不明[ienp](elem_fort77_main)");
	}
	
	freedom = fem_varinfo_ptr -> freedom;
	for(j=0;j<freedom;j++) {
	    if(j == 0) {
		PUT(fp,"%d",*(fem_varinfo_ptr->ienp+j));
	    }
	    else {
		PUT(fp,",%d",*(fem_varinfo_ptr->ienp+j));
	    }
	}
	if(i != solve_element_unknowns -1 ) F77(",\n");
    }
    F77("/\n");


    /* 配列iedpデータ文 */

    F77("      data iedp/ ");
    fem_varinfo_ptrptr = elem77_ptr -> fem_var_info_ptrptr;
    for(i=0;i<solve_element_unknowns;i++) {

	if(i != 0){  /* 桁合わせ */
	    F77("     $            ");
	}
        
	var_name = *(solve_element_ptr->unknown_name + i);
	tmp  = NO;    /* 目的のFEMvarinfo構造体が見つかったかどうかのフラグ */

	/* FEMvarinfo構造体走査 */
	for(j=0;j<elem77_ptr->fem_vars;j++) {

	    fem_varinfo_ptr = *(fem_varinfo_ptrptr + j);


	    if(streq(var_name , fem_varinfo_ptr -> fem_var_name) ) {
		tmp = YES;
		break;
	    }
	}

	if(tmp == NO) {
	    SystemAbort("該当するFEMvarinfo構造体が不明[iedp](elem_fort77_main)");
	}
	
	freedom = fem_varinfo_ptr -> freedom;
	for(j=0;j<freedom;j++) {
	    if(j == 0) {
		PUT(fp,"%d",*(fem_varinfo_ptr->iedp+j));
	    }
	    else {
		PUT(fp,",%d",*(fem_varinfo_ptr->iedp+j));
	    }
	}
	if(i != solve_element_unknowns -1 ) F77(",\n");
    }
    F77("/\n");
	
    comment1(fp);
	


    /* 数値積分初期化が一回のみで良い場合 */
    if(solve_element_ptr->quad_type == NO) {

	/* LINE-STEP-  【数値積分初期化ルーチンの呼び出し】 */
	tmp = 0;
	for(i=0;i<elem77_ptr->quad_methods;i++) {
	    if(*(elem77_ptr->quad_terms+i) == 0) continue;  /* dbg: これを数値
							       積分のフラグと
							       使用可能か？ */
	    tmp++;
	    F77("      call ");
	    PUT(fp,ELEM_SET_NAME,solve_no,no,i+1);
	    F77("\n");
	}
    }

    if(tmp != 0) {
	comment1(fp);
    }
    

    /* LINE-STEP-  【要素ループ】 */
    F77("      do 100 i=1,nelem\n");


    /* LINE-STEP-  【ecalルーチン呼び出し】 */
    F77("        call ");
    PUT(fp,ELEM_CAL_NAME,solve_no,no);
    F77("(");

    for(i=0;i<nodes;i++) {

	if(i != 0) F77(",");

	switch(dimension) {
	  case 1:
	    PUT(fp,"x(ielem(%d,i))",i+1);
	    break;
	    
	  case 2:
	    PUT(fp,"x(ielem(%d,i))",i+1);
	    F77(",");
	    PUT(fp,"y(ielem(%d,i))",i+1);
	    break;

	  case 3:
	    PUT(fp,"x(ielem(%d,i))",i+1);
	    F77(",");
	    PUT(fp,"y(ielem(%d,i))",i+1);
	    F77(",");
	    PUT(fp,"z(ielem(%d,i))",i+1);
	    break;

	  default:
	    SystemAbort("internal error(dimension err@elem_fort77_main)");
	}
    }

    /* fem変数展開に関する注意
       現在エルミート要素には対応していない！！！
       この件については、make_ecal.cの記述が選考しているのでそちらを
       参照の事   */
    
    /* 非線形の場合は、未知fem変数の内容も送る */
    if(solve_element_ptr->nonlinear_flag == YES) {
	for(i=0;i<solve_element_ptr -> unknowns;i++) {
	    var_name = *(solve_element_ptr->unknown_name+i);
	    
	    /* fem変数の自由度を得る */
	    freedom=get_fem_var_freedom_by_ND( var_name,
					      solve_element_ptr->domain_name);
	    fem_varinfo_ptr = get_femvarinfo(var_name,
					     elem77_ptr->fem_var_info_ptrptr,
					     elem77_ptr->fem_vars);
	    for(j=0;j<freedom;j++) {
		F77(",");
		PUT(fp,FEM_VAR_NAME77,var_name);
		PUT(fp,"(ielem(%d,i))",*(fem_varinfo_ptr->ienp + j));
	    }
	}
    }

    /* 既知fem変数の引き数への展開 */
    for(i=0;i<solve_element_ptr->fem_knowns;i++) {
	var_name = *(solve_element_ptr->fem_known_name + i);
	freedom = get_fem_var_freedom_by_ND(var_name,domain_name);
	fem_varinfo_ptr = get_femvarinfo(var_name,
					 elem77_ptr->fem_var_info_ptrptr,
					 elem77_ptr->fem_vars);
	for(j=0;j<freedom;j++) {
	    F77(",");
	    PUT(fp,FEM_VAR_NAME77,var_name);
	    PUT(fp,"(nloglo(ielem(%d,i)))",*(fem_varinfo_ptr->ienp + j));
	}
    }
    
    /* ewise変数の引き数への展開 */
    for(i=0;i<solve_element_ptr->ewise_knowns;i++) {
	var_name = *(solve_element_ptr->ewise_known_name + i);
	
	/* 数値積分法の積分点と同一の自由度を有する場合は配列として
	   わたす。それ以外のewise変数は、一要素一自由度のみのはず！ */
	F77(",");
	PUT(fp,EWISE_VAR_NAME77,var_name);

	ewise_type_ptr = get_ewise_type_ptr_by_2name(var_name , domain_name);
	
	/* ewise変数が数値積分指定の場合は、数値積分法と一致している
	   はず。これは、他のところでエラーチェックしている */
	if(ewise_type_ptr->quadrature != NULL) {
	    /* 数値積分の積分点毎に自由度、ewise変数は２次元配列 */
	    F77("(1,i)");    
	}
	else {
	    F77("(nelegru(i))");
	}
    }

    /* スカラー変数の引き数への展開 */
    for(i=0;i<solve_element_ptr->scalar_knowns;i++) {
	F77(",");
	PUT(fp,SCALAR_VAR_NAME77,*(solve_element_ptr->scalar_known_name + i));
    }

    F77(")\n");


    /* LINE-STEP-  【全体行列への足し込み】 */
    F77("      do 200 j=1,NDF\n");
    F77("        ikp(j) = IPD(ielem(ienp(j),i)) + iedp(j)\n");
    F77(" 200  continue\n");
    COM;

    F77("      do 300 j=1,NDF\n");
    F77("        jp = ikp(j)\n");
    COM;
    F77("        do 400 k=1,NDF\n");
    F77("          kp= ikp(k)\n");
    COM;
    F77("          if(kp .EQ. jp) then\n");
    F77("            A (kp,JDP) = A(kp,JDP) + ea(k,j)\n");
    F77("            B (kp)     = B(kp)     + eb(k)\n");
    F77("            JA(kp,JDP) = kp\n");
    F77("            GOTO 400\n");
    COM;
    F77("          else if(kp.gt.jp) then\n");
    F77("            DO 410 ii = 1,JDP-1\n");
    F77("              if( JA(kp,ii) .eq. 0) then\n");
    F77("                JA(kp,ii) = jp\n");
    F77("                A (kp,ii) = A(kp,ii) + ea(k,j)\n");
    F77("                GOTO 400\n");
    F77("              endif\n");
    F77("              if( JA(kp,ii) .eq. jp) then\n");
    F77("                A (kp,ii) = A(kp,ii) + ea(k,j)\n");
    F77("                GOTO 400\n");
    F77("              endif\n");
    F77("  410       continue\n");
    F77("            write(*,*) 'A(*,*) LEFT ERROR'\n");
    F77("            write(*,*) 'KP=',kp\n"); 
    F77("            write(*,*) (JA(kp,iii),iii=1,JDP-1)\n");
    F77("            stop 'AT ELEM'\n");
    F77("          else\n");

    F77("            DO 420 ii=JDP+1,MJ\n");
    F77("              if( JA(kp,ii) .eq. 0) then\n");
    F77("                JA(kp,ii) = jp\n");
    F77("                A (kp,ii) = A(kp,ii) + ea(k,j)\n");
    F77("                GOTO 400\n");
    F77("              endif\n");
    F77("              if( JA(kp,ii) .eq. jp) then\n");
    F77("                A (kp,ii) = A(kp,ii) + ea(k,j)\n");
    F77("                goto 400\n");
    F77("              endif\n");
    F77("  420       continue\n");          
    F77("            write(*,*) 'A(*,*) RIGHT ERROR'\n");
    F77("            write(*,*) 'KP=',kp\n"); 
    F77("            write(*,*) (JA(kp,iii),iii=JDP+1,MJ)\n");
    F77("            stop 'AT ELEM'\n");
    F77("          endif\n");

    F77("  400   continue\n");
    F77("  300 continue\n");        
    
    COM;
    /* LINE-STEP-  【ループ文の対】 */
    F77(" 100  continue\n");
    COM;

    F77("      do 500 j = 1, MJ\n");
    F77("        do 600 i = 1,NNN\n");
    F77("          if(JA(i,j) .EQ. 0) then\n");
    F77("            JA(i,j) = i\n");
    F77("             A(i,j) = 0.0d0\n");
    F77("          endif\n");
    F77(" 600    continue\n");
    F77(" 500  continue\n");
    COM;
    
    F77("      return\n");
    F77("      end\n");

    CloseFile(fp);

    return;
}
