/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   element_check.c
 *      Date:   1993/11/19
 *   
 *   Purpose:   element構造体に対するデータチェックとpre_to_inf
 *   Functions: 呼び出し関数
 *                element_chk_pretoinf()
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

void element_check()
{

    /* pre_to_infの実行(element内スカラー変数に対して) */

    element_chk_pretoinf();


    return;
}
    
