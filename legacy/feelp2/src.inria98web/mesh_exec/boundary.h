/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   boundary.h
 *      Date:   1993/12/06
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"


typedef struct {
    int points;            /* この境界の最大点数        */
    int from;              /* 開始点の初期節点番号      */
    char *from_name;
    int to;                /* 終了点の初期節点番号      */
    char *to_name;

    int *node_no;          /* 境界点の節点番号 */
    int mid_points;        /* 中間節点の数     */
    double *mid_address;   /* 各中間点の座標   */
    
    int region_no;         /* region番号       */
    

} Boundary2D;

extern Boundary2D *get_b2d_ptr_by_both_ends();
