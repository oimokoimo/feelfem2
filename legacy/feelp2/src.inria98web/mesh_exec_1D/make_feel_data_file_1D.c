/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_feel_data_file_1D.c
 *      Date:   1995/01/17
 *   
 *   Purpose:   一次元データファイルの作成
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../var_comp/var_comp.h"


extern int feel_dim;

void make_feel_data_file_1D()
{

    int i;
    FILE *fpr,*fp;
    char *cp;

    char buf[BUFSIZ];

    int ndim,npmax,nedat,nodeset,numset,nip;
    int nvars_fem,nvars_ewise;
    int mode_output,mode_ex;
    EWISE_type *ewise_type_ptr; /* 対応するElemDatの代表番号を得る */

    fprintf(stderr,"現在一次元data file作成routineを製作中\n");
    exit(1);

    /* 次元の設定 */
    ndim = 1;
    nodeset = current_nodesetno();
    numset  = 0;
    nedat   = current_edatno();
    nip     = how_many_points();

    mode_ex     = 0;
    mode_output = 0;

    nvars_fem   = how_many_fem_vars();
    nvars_ewise = how_many_ewise_types();

/*    npmax  = get_npmax_1D(); */

    SystemAbort("make_feel_data_file_1D.cは製作途上");
    
}

