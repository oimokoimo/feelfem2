/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   data_number.c
 *      Date:   1994/01/12
 *   
 *   Purpose:   feel_datにおけるdata集合に番号を付加する
 *              
 *   Functions: init_data_number()
 *              get_new_XXXXXXno()
 *              current_XXXXXXno()
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

static int edatno = 0;     /* 要素節点集合データ番号 */
static int nodesetno=0;  /* 節点集合データ番号     */
static int numsetno=0;   /* 数値データ集合データ   */
static int window_id=0;  /* ウインドウID番号       */
static int file_window_id=0; /* ファイル出力用windowID */
static int open_files=0; /* データファイルの数     */
static int nsolve_max_edat;  /* solve文に使う最大edat番号
				(feel_exec_main,make_feel_dat_fileにて使用 */

init_data_number()
{
   /* do nothing */

    return;
}

int get_new_edatno()
{
    edatno++;
    
    return(edatno);
}

int current_edatno()
{
    return(edatno);
}


int get_new_nodesetno()
{
    nodesetno++;

    return(nodesetno);
}

int current_nodesetno()
{
    return(nodesetno);
}


int get_new_numsetno()
{
    numsetno++;

    return(numsetno);
}

int current_numsetno()
{
    return(numsetno);
}

int get_new_window_id()
{
     if(window_id == MAX_X_WINDOWS) {
	 SystemError("表示するX-Windowの画面数が多すぎます");
	 return(0);
     }
     window_id++;
     return(window_id - 1);
 }

int get_new_file_window_id()
{
    if(file_window_id == MAX_X_WINDOWS) {
	 SystemError("表示するX-Windowの画面数が多すぎます");
	 return(0);
     }
     file_window_id++;
     return(file_window_id - 1);
 }
     
int get_data_file_number()
{
    open_files++;
    return(open_files);
}

int how_many_open_data_files()
{
    return(open_files);
}


/* solve文に出現する最大edat集合数 */
void set_solve_max_edatno( n )
     int n;
{
    nsolve_max_edat = n;
    return;
}

int how_many_nsolve_edats()
{
    return(nsolve_max_edat);
}
