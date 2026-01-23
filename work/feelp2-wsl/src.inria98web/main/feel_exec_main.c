/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   feel_exec_main.c
 *      Date:   1993/06/08(Modified)
 *  Modified:   1995/01/17(一次元メッシュ作成のため)
 *              1999/02/23(AVS mode (feelavs.f))
 *              2000/04/26(solve_dat generation)
 *   
 *   Purpose:   feelの構文解析後のメインルーチン
 *   Functions: 
 *              
 *              
 */

#include <stdio.h>
#include <stdlib.h>
#include "../system/system.h"
#include "../feel_def/feel_msg.h"

#ifdef  _MSC_VER       /* Microsoft Visual C++ only */
#define MSDOS          /* Win32 version */
#endif


#define YES  1
#define NO   0

extern int mesh_only;
extern int feel_dim;
extern int one_file;
extern int parallel;     /* パラレルオプション */
extern int recursive_mesh_div;
extern int noediv_flag;
extern int english_mesg;
extern int web_mode;
extern int bamg_mode;
extern int web_check;     /* check for semantics only          */
extern int web_exec;      /* test exec (no goto, winsiz = 100) */   
extern int modulef_mode;  /* modulef version 1998/11/02        */
extern int avs_mode;
extern int avs_64bit;     /* avs 64 bit mode flag */

#ifdef MSDOS
#define STRESS  if(1==2)fprintf(stderr,"%c[5m",27)
#define NORMAL  if(1==2)fprintf(stderr,"%c[0m",27)
#else
#define STRESS  if(!web_mode)fprintf(stderr,"%c[5m",27)
#define NORMAL  if(!web_mode)fprintf(stderr,"%c[0m",27)
#endif


char *feel_user;
char *feel_date;
char *feel_dir;
char *AVSExpress_dir;
char *current_dir;

void feel_exec_main()
{

    extern int status_no_delete;

    if(status_no_delete) {
	init_cptime();         /* 時間レポート */
    }
    
    /* 【注意】 */
    if( how_many_errors() ) {
	prt_errors_message();
	if(english_mesg) {
	    SystemAbort("There are fatal syntax errors.\n");
	}
	else {
	    SystemAbort("構文上重大なエラーがあるので処理を中止します。\n");
	}
    }


    /* web check mode */
    if(web_check) {
      if(how_many_errors()== 0) fprintf(stderr,"There is no severe error.\n");
      exit(0);
    }
    
    init_data_number();    /* feel_datファイル等で使用する番号の初期化 */
    if(status_no_delete ) {
	rep_time("init_data_number");
    }
    
    InitMakeDeletefile();  /* 一時ファイル消去用リスト作成の初期化 */
    if(status_no_delete ) {
	rep_time("InitMakeDeletefile");
    }

    
    get_user_info();       /* set feel_user and feel_date */
    if(status_no_delete ) {
	rep_time("get_user_info");
    }
    
    /* 【注意】 */
    pre_to_inf_init();   /* 前置記法から中間置記法への変換ルーチン準備 
			    pre_to_infは check系ルーチン実行時に行う  */
    if(status_no_delete ) {
	rep_time("pre_to_inf_init");
    }

    
    feel_data_check();   /* 宣言の依存関係 */
    if(status_no_delete ) {
	rep_time("feel_data_check");
    }

    
    if( how_many_warnings() ) { /* Warningの報告 */
	prt_warnings_message();
    }
    
/*
    STRESS;
    printf("ステップ デバッグの為の関数呼び出し(debug_start)\n");
    NORMAL;
*/
    
   debug_start();  /* CAUTION: ここに移しました。 */
    
    if( how_many_errors() ) {
	prt_errors_message();
	
	exit(1);                /* エラーの場合は処理を中止する */
    }
    
    /*========================================*/
    /* スカラー変数に関するterm_convertの作成 */
    /*========================================*/
    init_scalar_term_convert();
    if(status_no_delete ) {
	rep_time("init_scalar_term_convert");
    }


    /*===============*/
    /* solve文の処理 */
    /*===============*/
    /* solve文に対してデータの作成 */
    
    solve_dat_make_main();
    if(status_no_delete ) {
	rep_time("solve_dat_make_main");
    }

    
    /* 各SolveElement内で、要素の局所節点と基底関数番号との
       対応配列等を作成する  solve_comp内の関数、dataはElementFORT77に作成
       */
    make_fem_varinfo(); 
    if(status_no_delete ) {
	rep_time("make_fem_varinfo");
    }

    /*=========================*/
    /*  Project subdomain      */
    /*  複数domainプロジェクト */
    /*=========================*/
    make_subdomain_info();


    /* solve文に使う最大edat番号をセーブする(並列処理用)*/
    set_solve_max_edatno( current_edatno() );

    
    set_boundary_no();    /* 境界節点集合番号
			     境界要素節点集合番号の番号を付加する
			     directory solve_comp内の関数
			   */
    if(status_no_delete ) {
	rep_time("set_boundary_no");
    }

    
    /*=============*/
    /* let文の処理 */
    /*=============*/
    
    
    /* 【注意】 */
    /* 中間置記法数式の取得 */
    do_pre_to_inf();
    if(status_no_delete ) {
	rep_time("do_pre_to_inf");
    }
    
    
    /*==========================*/
    /* meshに関するデータの作成 */
    /*==========================*/
    make_mesh_ctrl_data();      /* solve_comp directoryに存在 
				 * このプログラム内でメッシュ生成を実行
				 */
    if(status_no_delete ) {
	rep_time("make_mesh_ctrl_dat");
    }


    /* 最初は make_feel_fort77の後にあったが、
       feel_fort77内で、節点番号を参照している所が
       あるので移動した   94/02/02                   

   註  さらに、ノイマン境界条件の設定をmesh_exec内でやってしまっている
       ので、feel_fort77より feel_data作成が前に無いといけない 94/02/08   */

    /*======================*/
    /* データファイルの作成 */
    /*======================*/
    fprintf(stderr,"Making 'feel_dat' file...");
    switch(feel_dim) {

      case 1:                          /* 一次元版 mesh_exec_1D内の関数 */
	make_feel_data_file_1D();
	break;

      case 2:

	if(bamg_mode == 1) {
	  make_feel_data_file_bamg();  /* for BAMG */
	}
	else {
	  make_feel_data_file();         /* 二次元版 mesh_exec内の関数 */
	}

	break;
	
      case 3:
	SystemAbort("３次元メッシュには未対応(feel_exec_main)");
	break;
	
      default:
	SystemAbort("Inner ERROR(Illegal feel_dim number(feel_exec_main))");
    }
    fprintf(stderr,"done\n");


    /* 並列化指示時の処理 */
    if(parallel != 0) {
	make_parallel_data(parallel);
    }

    if(status_no_delete ) {
	rep_time("make_feel_data_file");
    }


    /* Make solv_dat   feelfem */
    fprintf(stderr,"Making 'solv_dat' file...");
    make_solv_dat();
    fprintf(stderr,"done\n");    



    /* skip code generation if mesh only option is specified */
    if(mesh_only != YES) {
      
      if(modulef_mode == YES) {

	/****************/
	/* MODULEF MODE */
	/****************/

        rep_proc("make_modulef_F77(feel_exec_main)");
	make_feel_fort77_modulef();
	if(status_no_delete ) {
	    rep_time("make_feel_fort77(modulef mode)");
	}

	fprintf(stderr,"done\n");
 
      }
      else {

	/********************/
	/* NOT MODULEF MODE */
	/********************/

	/* Initialize MakeMakefile routine */
        if(status_no_delete) {
          rep_time("InitMakMakefile");
        }
	InitMakeMakefile();


	/*  feel fort77 CODE generate */
        rep_proc("make_feel_fort77");
	make_feel_fort77();
	if(status_no_delete ) {
	    rep_time("make_feel_fort77");
	}

      }

    }


    /* if mesh only mode, skip code modifier, making makefile */

    if(mesh_only != YES) {

	if(modulef_mode) {
	  /****************/
	  /* MODULEF MODE */
	  /****************/

	  fprintf(stderr,"Formatting FORT77 src ...");

	  fprintf(stderr,"NOT NOW!(I'm in feel_exec_main.c)\n");

#ifdef MSDOS   /* because modulef.mk is not made now... */

#else
	  mfMakeMakefile();  
#endif

	}

	else {


	  /********************/
	  /* NOT MODULEF MODE */
	  /********************/	  

	/**********************/
	/* 72 column modifier */
	/**********************/

        if(one_file == YES) {
  	    CloseOneFile();
        }

	fprintf(stderr,"Formatting FORT77 src ...");

	/* CAUTION, IT MUST BE DONE BEFORE MAKEMAKEFILE.
	   (AS IN MAKEMAKEFILE, IT BREAK THE FILENAME 
	    TABLE)
	*/
	JustifyFORTfile();          
				    
				    

	if(avs_mode) {
#ifdef MSDOS
	  system("type feelavs.f    >feel.f");
	  system("type feel_main.f >>feel.f");
	  system("type feelgo.f    >>feel.f");
	  system("del feelavs.f");
	  system("del feel_main.f");
	  system("del feelgo.f");
#else
	  system("cat feelavs.f    >feel.f");
	  system("cat feel_main.f >>feel.f");
	  system("cat feelgo.f    >>feel.f");
	  system("rm feelavs.f");
	  system("rm feel_main.f");
	  system("rm feelgo.f");
#endif
	}


	fprintf(stderr,"done\n");

	if(status_no_delete ) {
	    rep_time("JustifyFORTfile");
	}

	/*  Makefile generate */

	  MakeMakefile();

	}  /* end of not modulef mode */
    }
	/* 一時ファイルの消去 */
    if(!status_no_delete) {
	DoDeletefile();
    }
    else {
	fprintf(stderr,"一時ファイルの消去はしません(debug)\n");
    }

    return;
}
