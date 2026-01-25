/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   solve_fort77.h
 *      Date:   1993/07/12
 *   
 *   Purpose:   solve文に対応するFORTRANプログラム生成のための
 *              定義ファイル
 *              
 */

#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "../yacc/YaccExpression.h"
#include "../solve_comp/solve_comp.h"

/*-----------------------
 *  構造体 ElementFORT77
 *
 *  FORTRANプログラムを生成する為に作る情報構造体
 *      各要素単位
 */

