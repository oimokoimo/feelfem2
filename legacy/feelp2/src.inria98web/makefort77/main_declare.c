/*
 *  feel prototype version 2   Copyright(C) NEC Corporation 1993
 *
 *  Modified 1998/09/03  for avs extension
 */

#include <stdio.h>
#include "Extern.h"

#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "../parallel/parallel.h"


main_declare( fp )
     FILE *fp;
{
  int i,avsparams;

  if(avs_mode) {
    PUT(fp,"      subroutine %s(UCD_id,event_mask,seq_num,IARGSIZ,meshonly",
	main_dat.prog_name);
    avsparams = how_many_avs_variables();
    if(avsparams == 0) {
       fprintf(fp,")\n"); 
    }
    else {
      for(i=0;i<avsparams;i++) {
	fprintf(fp,",");
	put_nth_avs_feel_name_fp(fp,i);
      }
      fprintf(fp,")\n");
    }
    
  }

  else {
    fprintf(fp,"      program %s\n",main_dat.prog_name);
  }
    
    CopyRight(fp);

    TimeStamp(fp);

    real8(fp);


    if(parallel) {  /* MPIライブラリのインクルード文挿入 */
	fprintf(fp,"*\n");
	fprintf(fp,"      include %s\n",MPI_HEADER_FILE);
    }

    common_parameters(fp);

    /* AVS definitions */
    if(avs_mode) {  /* AVS routine */
      fprintf(fp,"      integer UCD_id(IARGSIZ),event_mask,seq_num\n");
      fprintf(fp,"*\n");
    }
    
    /*--------------------------*/
    /* dimension block          */
    /*--------------------------*/    
    fprintf(fp,"      real*4  feel(MAX_FEEL)\n");
    fprintf(fp,"      real*8 dfeel\n");
    
    if(subdomain_flag) {
	fprintf(fp,"      integer  matnos(%d)\n",MAX_REGIONS);
    }

    /*--------------------*/
    /* スカラー変数の宣言 */
    /*--------------------*/
    rep_proc("goto main_declare_scalar");
    main_declare_scalar(fp);


    /* 配列feelの先頭をdouble-word境界にする為 */
    fprintf(fp,"      equivalence (feel, dfeel)\n*\n");

    /*--------------------------*/
    /* common block             */
    /*--------------------------*/
    CommonBlock(fp);

    return;
}

common_parameters(fp)    /* commonブロックに関するPARAMETER宣言 */
     FILE *fp;
{
    /*--------------------------*/
    /* parameter block          */
    /*--------------------------*/
    comment1(fp);
    fprintf(fp,"      parameter (MAX_FEEL = %d)\n",main_dat.max_feel_size);
    fprintf(fp,"      parameter (MAX_DOMAIN = %d)\n",main_dat.max_domain);
    fprintf(fp,"      parameter (MAX_EDATSET = %d)\n",main_dat.max_edatset);
    fprintf(fp,"      parameter (MAX_NODESET = %d)\n",main_dat.max_nodeset);
    fprintf(fp,"      parameter (MAX_NUMSET = %d)\n",main_dat.max_numset);
    fprintf(fp,"      parameter (MAX_EWISE  = %d)\n",main_dat.max_ewise);
/*    fprintf(fp,"      parameter (MAX_EWISE_INFO = %d)\n",main_dat.max_ewise_info);
*/
    fprintf(fp,"      parameter (MAX_IP    = %d)\n",how_many_points());
    fprintf(fp,"      parameter (MAX_SOLVE = %d)\n",how_many_solves());

    if(parallel) {
	fprintf(fp,"      parameter (MAX_PE = %d)\n",CENJU_MAX_PE);	
    }
    comment1(fp);
}

