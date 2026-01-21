/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   check.c
 *      Date:   1993/06/03 (Modified)
 *   
 *  Modified:   1998/09/03 AVS extension
 *   
 *   Purpose:   check.c
 *   Functions: feel文の依存関係の検査、未完の構造体完成(ewise,fem等)
 *              
 *              checkとは、データの妥当性を検討しつつ、
 *              データを完成させるルーチン群である。
 */
#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


void feel_data_check()         /* checkする各項目について対応する関数名を列挙する */
{
    /* メッシュブロックに関するcheck */

    region_subdomain_check();    /* subdomainに関するチェック*/


    region_domain_check();       /* 各region名にダブリがないか？
				    各regionを構成する点が存在するか？ 
				    各domainは同じetypeを持つregionにより
				    構成されているか？                   

				    ★各domainに対応するregionに対して
				      region番号を設定する
				    */



    if( how_many_errors() ) {
	if(english_mesg) {
	    SystemAbort("There are fatal error in mesh definitions.");
	}
	else {
	    SystemAbort("領域定義に基本的な誤りがある");
	}
    }    

    point_check_order();         /* ○点の種別の登録
				      →外部境界点、内部境界点、孤立点
				    ○点のmeshno(メッシュ生成時番号)付加
				      →連番号付加
				      */

    refine_check();              /* refine check, This must after point order*/
    /* var_check */

    /*
     * fem変数、ewise変数のデータ作成とエラー検査
     * FEM_type,EWISE_type  → FEM_var,EWISE_varへの情報の移し替え
     *
     * check/var_fem_ewise_datmake.c
     */
    fem_var_element_check();  /* fem文で指定されているelementの有無の確認と
				 shape番号の決定                            */

    ewise_var_check();        /* ewise変数の検査 
			       *  ewise_type->pointの設定
			       *  quadratureは座標点代入
			       */
    var_fem_ewise_datmake();

    /* 変数名,変数種別の登録と多重定義の有無の検査 */
    /*                  ^^^^   これは、let文検査の際に使用する */
    var_register(); 

    /*
     * 変数名が予約語でないこと
     * FORTRANの予約語、関数名でないこと
     *
     */
    var_reserved_check(); 


    /*
     *   定数変数のpre_to_infの準備
     */
    var_const_pretoinf();

    
    /*
     * fem変数の検査
     * ○拘束条件の変数が存在し、型があっていること
     */ 
    

    /* element check */
    element_check();

    /* quadrature check */
    quad_check();                    /* dbg: CAUTION: 現在はpre_to_infのみ
					93/11/15                           */

    /*=============*/
    /*scheme check */
    /*=============*/

    /* goto文、label文に関して定義されているか検査し、
       行番号を割り振る。
     */
    scheme_gotolabel_check();

    /* if文に関して検査 */
    scheme_if_check();


    /* read文、write文に対して変数が定義されているか検査し、
       pre_to_inf_push()を行う                                */
    scheme_rw_check();
    scheme_plot_check();



    /* contour文に対して、指定されている変数がFEM変数で単一domain定義か
       調べる */
    scheme_contour_check();


    /* displacement文に対して、指定されている変数がFEM変数で単一domain定義か
       調べる */
    scheme_displacement_check();

    /* perspect文に対して、指定されている変数がFEM変数で単一domain定義か
       調べる */
    scheme_perspect_check();

    /* showvec文に対して、調べる */
    scheme_showvec_check();
    
    /* let文検査は最後の最後 */

    /*
     * 各scheme文における引き数の変数の型の妥当性
     */

    /*
     * solve文に対して
     */

    solve_check_main();


    /*
     * 代入文に関する検査  これは、varに関するデータを作成してから
     *                     実行する必要があるため、check系の最後に処理を実行
     */
    /* let文等に関して
     * 変数名が宣言されていること
     * 式の代入関係の評価が可能であること
     * pre_to_inf_pushを必要なものに対して行う(dx,dy,dz等は注意が必要)
     *
     */      
    scheme_let_check();  

    /* NORMの計算式の検査、これはlet文に付随するものだが… */
    scheme_norm_check();

    /* ADAPTMESH */
    scheme_adaptmesh_check();

    /* AVS check */
    avs_check();

    return;
}
