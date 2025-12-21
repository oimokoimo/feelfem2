/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_check_main.c
 *      Date:   1993/07/10
 *  Modified:   1995/03/02
 *   
 *   
 *   Purpose:   solve文の構造体データをチェックしデータを完成する
 *              メインプログラム
 *              
 *  固有値問題に対応するためのmodify  1995/03/02
 *              
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


void solve_check_main()
{

    /* solve文中に現れる変数に関するcheckとデータ作成 
     *  領域積分項に対してSolveElement構造体に情報を代入(known変数の切り出し) 
     *  SolveElementの各Equationのneumann条件仮変数のまとめてSolveElement
     *  構造体へ代入する
     *
     *  非線形問題の場合に、初期値設定に用いられた変数に関しknown変数切り出し
     */
    solve_chk_var();

    /* solve文中のinitial文に対する処理
     * solve_chk_bd_varにてsolve文へknown変数の追加を行う。
     * 順番に注意が必要
     */
    solve_chk_initial(); 

    /* 未知fem変数、および境界項も含めsolve文中に現れる変数の
       切り出しと、Solve構造体への情報代入  

       sovle_element->domain_nameの確定                       */
    solve_chk_bd_var();


    solve_chk_var_vs_domain();    /* 各solve_elementで指定されているdomain
   		        	     と、fem変数、ewise変数との整合性がとれて
	【境界項については未適用】   いるかどうかの検査,
				     及びSolveElement->etypeに値を代入  
	  		             ewise_type_ptr->etypeにも代入しましょう */

    solve_chk_quad_method();  /* 指定されている数値積分法が定義されて
				 いるかどうか調べる                   
				 solve_element->etypeの値を使う関係上 
				 上のルーチンよりの後によばれるべき   */

    solve_chk_shape_function();   /* 各solve_elementの形状変換関数の指定 
				     dbg: 現在はisoparametricに関する
				          設定はしていない               */
    

    solve_chk_test_function();    /* 試験関数に関する検査を行う */

    solve_chk_only_neumann();     /* ノイマン条件右辺にのみ出現するfem変数の
				     各SolveElementへの登録                 */
    /* FORTRAN生成の為にはsolve_dat_makeルーチン群の
       FORT77構造体シリーズへの代入により完成する               */
    
    /* 境界条件に関するエラー検査 */
    /* 特に境界名称が宣言されているかどうかの検査 */
    solve_chk_boundary();         

    /* 【注意】DirichletData,NeumannData等の検査は
       solve_ptr -> unknown 等を参照する為、順番は一番最後にすること */
    solve_chk_DirichletData();    /* Dirichlet条件に関するエラー検査 */

    solve_chk_NeumannData();
    
    solve_chk_EigenProblem();

    return;
}
