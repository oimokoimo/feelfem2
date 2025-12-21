/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1994/02/0
 *   
 *   Purpose:   close_file.c
 *   Functions: 関数close_fileを作成する。
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

void close_file_fort77(fp) 
     FILE *fp;
{
    int i;
    int open_files;
    FILE *wfp;

    open_files = how_many_open_data_files();

    
    if(open_files == 0) return;

    /* メインルーチン上に書く */
    PUT(fp,"       call %s\n",PROG_CLOSE_FILE);

    /* ファイル出力制限 */
    StoreMakefile( CLOSE_FILE , USER_LIBRARY );


    wfp = OpenFileToWrite( CLOSE_FILE );
    
    PUT(wfp,"      subroutine %s\n",PROG_CLOSE_FILE);

    /* 定形処理 */
    CopyRight(wfp);
    TimeStamp(wfp);

    common_parameters(wfp);
    CommonBlock(wfp);
    comment1(wfp);

    for(i=0;i<open_files;i++) {
	PUT(wfp,"      close(unit=io_tmp+%d)\n",i+1);
    }
    
    PUT(wfp,"      return\n");
    PUT(wfp,"      end\n");

    CloseFile(wfp);
}

    
