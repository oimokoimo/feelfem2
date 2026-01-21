/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   mesh_exec.h
 *      Date:   1993/08/23
 *   
 *   Purpose:   中間節点生成に関する情報配列
 *   Functions: 
 *              
 *              
 */


typedef struct {
    int edge_points;                  /* 境界の点数 */
    double edge[MAX_MID_POINTS];      /* 端からの座標値 */
    double edge_val[MAX_MID_POINTS];  /* 点の評価値(デバッグ用) */

    int inner_points;                 /* 内部節点の数 */
    double mid_x[MAX_MID_POINTS];     /* その座標     */
    double mid_y[MAX_MID_POINTS];  
    double mid_val[MAX_MID_POINTS];   /* 点の評価値(デバッグ用) */

} MidPoint2D;
