/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_ecal_numintegral2D.c
 *      Date:   1993/11/2
 *   
 *   Purpose:   数値積分版２次元ecalルーチン作成プログラム
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"

void make_ecal_numintegral2D(solve_no,elem_no,     )
     int solve_no;
     int elem_no;
{
    int i;

    FILE *fp;
    char fname[80];

    sprintf(fname,ELEM_CAL_FNAME,solve_no,elem_no);
    fp = OpenFileToWrite( fname );
    
    
