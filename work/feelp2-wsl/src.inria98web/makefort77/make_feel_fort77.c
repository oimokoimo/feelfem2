/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *
 *  1995: Parallel version:
 *
 *  1998/09/03  AVS extension
 *  1999/03/17  AVSnetwork extension
 *
 *
 *  FORTRAN generate program drive routine
 */



#include "../system/system.h"
#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../parallel/parallel.h"

make_feel_fort77()
{


    rep_proc("goto data_initialize in make_feel_fort77");
    data_initialize(); /* データイニシャライズ   */

    rep_proc("goto system_default in make_feel_fort77");
    system_default();  /* 次元の設定も行う       */


    if(parallel) {
	para_make_main();  /* 並列処理用のmain program作成 */
    }
    else {
        rep_proc("goto make_main in make_feel_fort77");
	make_main();       /* メインプログラムの作成 
			      メインプログラム上のCALL文はこのルーチンで
			      作成する
            	            */

	if(avs_mode) {
	  FILE *fpw;
	  fpw = fopen(DEFAULT_AVS_MODULE_FILE, "w" ); /* not OpenFileToWrite */
	  if(fpw== NULL) {
	    SystemAbort("Cannot open file to write for avs interface code");
	  }

          rep_proc("goto make_avs_interface_routine");
	  make_avs_interface_routine(fpw);

          rep_proc("goto make_avs_output_routine");
	  make_avs_output_routine(fpw);

          rep_proc("goto make_avs_coroutine");
	  make_avs_coroutine(fpw);

	  fclose(fpw);

          rep_proc("goto make_avs_def_file");
	  make_avs_def_file();


	  rep_proc("goto make_avs_network_file");
	  make_avs_network_file();

	}

    }


    /* ※ これは、モードによってはやったり、やらなかったりする */
    /*  mode 1  すべてのソースファイルを生成する */
    /*  mode 2  ライブラリを利用する             */

    rep_proc("goto fort77lib_make");
    fort77lib_make();  /* ライブラリ関係プログラムの作成 */

                   
    rep_proc("goto make_solve_fort77");
    make_solve_fort77();        /* solve_fort77 ディレクトリ内の関数 */
    

    return;
}
