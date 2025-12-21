/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   adaptmesh_fort77.c
 *      Date:   1997/07/25
 *
 *   Purpose:   adaptmesh( fem formula )
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../scheme_comp/scheme_comp.h"
#include "../mesh_comp/mesh_comp.h"
#include "../var_comp/var_comp.h"

static int  adapt_no = 0;

#define MAX_BUF  38

static char *from[MAX_BUF];
static char *to[MAX_BUF];

void adaptmesh_fort77( fp_main ,  adapt_ptr )
     FILE *fp_main;
     Adaptmesh *adapt_ptr;
{
    int i;
    int   max_buf;
    Expression *expr_ptr;
    int term_converts;

    FILE *fp;
    Point *point_ptr;

    char *name;
    char *option;

    char name_buf[80];
    char name_buf2[80];

    max_buf = MAX_BUF;   /* let_fem_femを流用したからこうゆうことをしている */
    adapt_no++;
    
    term_converts = 0;
    expr_ptr = adapt_ptr -> expr;
    option   = adapt_ptr -> option;
    
    /* adapt文対応FORTRANファイルのオープン */
    sprintf(name_buf,ADAPTMESH_FNAME,adapt_no);
    StoreMakefile(name_buf,USER_LIBRARY);
    fp = OpenFileToWrite(name_buf);


    /* main ルーチンでの代入 */
    make_main_adapt_call(fp_main,adapt_no,adapt_ptr);

    /* subroutine文の作成 */
    make_adapt_called(fp,adapt_no,adapt_ptr);
    
    /* 定形処理 */
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);

    common_parameters(fp);
    COM;

    /* 変数宣言               */
    /* dimension 及び integer */
    make_adapt_called_dimension(fp,adapt_no,adapt_ptr);


    CommonBlock(fp);

    /*=======================*/
    /* fem変数式 の          */
    /* term_convertの作成    */
    /*=======================*/
    for(i=0;i<expr_ptr -> identifiers;i++) {
	name = *(expr_ptr->identifier + i);

	switch(get_var_kind( name ) ) {
	  case INT:
	  case DOUBLE:
	  case CONST:
	    /* term_convert用バッファ作成 */
	    if(term_converts == max_buf) {
	      SystemAbort("term_buffer 不足(@adapt_fem_fem)");
	    }

	    sprintf(name_buf,SCALAR_VAR_NAME77,name);
	    to[term_converts] = MakeStringCopy(name_buf);
	    from[term_converts] = name;
	    term_converts++;
	    
	    break;

	  case SYSTEM_VAR:   /* 小文字x,y,z */
	    from[term_converts] = name;

	    /* 節点位置での代入指定 */
	    sprintf(name_buf,"%s(i)",name,name);
	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;

	  case FEM:
	    from[term_converts] = name;
	    sprintf(name_buf2,FEM_VAR_NAME77,name);

	    sprintf(name_buf,"%s(i)",name_buf2);
	    to[term_converts]   = MakeStringCopy(name_buf);
	    term_converts++;

	    break;

	  case EWISE:
	  case MATERIAL:
	    SystemAbort("Illegal code@adapt_fem_fem");
	    break;

	  default:
	    SystemAbort("Unknown code@adpat_fem_fem");
	    break;
	}
    }

    comment1(fp);

    /* norm計算の初期化 */


    /* PUT(fp,"      np_push  = np_work\n");  OLD F_ALLOC */
    /* IN THIS ROUTINE, NO MEMORY ALLOCATED, so NO F_ALLOC_PUSH */

    PUT(fp,"      io_input  = io_fem\n");
    PUT(fp,"      io_output = io_fem+1\n");
    COM;

    PUT(fp,"      open(unit=io_input ,file='%s')\n",BAMG_FTOB_FILE);
    PUT(fp,"      open(unit=io_output,file='");
    PUT(fp,BAMG_ADPT_FILE,adapt_no);
    PUT(fp,                                  "')\n");
    COM;

    PUT(fp,"      read(io_input,*) npmax2\n");
    COM;

    PUT(fp,"      write(io_output,'(4I8)') 2,1,npmax2,2\n");
    COM;


    F77("      do 100 ip=1,npmax2\n");
    COM;

    PUT(fp,"      read(io_input,*) i\n");

    F77("        dat = ");    
    PUT(fp,"%s\n",term_convert(expr_ptr->expr_inf,from,to,term_converts));
    COM;

    PUT(fp,"      write(io_output,*) dat\n");
    
    F77("  100 continue\n");
    COM;
    
    F77("      close(io_input )\n");
    F77("      close(io_output)\n");
    COM;

    if(avs_mode) {

    PUT(fp,"*      write(*,*) 'BAMG remeshing...'\n");

    if(MACHINE==Windows) {
      PUT(fp,"      call system('copy bamg.mesh bamg.mesh.%d')\n",
	  adapt_no);
      PUT(fp,"*      call system('bamg.exe -b bamg.mesh -Mbb ");
      PUT(fp,BAMG_ADPT_FILE,adapt_no);
      PUT(fp," -o r.mesh %s",BAMG_DEFAULT_OPTION);
    } 
    else {
      PUT(fp,"      call system('cp bamg.mesh bamg.mesh.%d')\n",
	  adapt_no);
      PUT(fp,"*      call system('bamg -b bamg.mesh -Mbb ");
      PUT(fp,BAMG_ADPT_FILE,adapt_no);
      PUT(fp," -o r.mesh %s",BAMG_DEFAULT_OPTION);
    }


    if(option == NULL) {
      PUT(fp,"')\n");
    }
    else {
      PUT(fp," %s)\n",option+1);
    }

    /* in avs mode, these commands are executed from UI panel button */
    PUT(fp,"*      call system('cp bamg.mesh org.mesh')\n");
    PUT(fp,"*      call system('cp r.mesh bamg.mesh')\n");
    PUT(fp,"*      call system('feel.bamg.exe')\n");
    COM;

    }     /* AVS mode */

    else {
      if(MACHINE==Windows) {
	PUT(fp,"      call system('copy bamg.mesh bamg.mesh.%d')\n",
	    adapt_no);
	PUT(fp,"      write(*,*) 'BAMG remeshing...'\n");
	PUT(fp,"      call system('bamg.exe -b bamg.mesh.%d -Mbb ",adapt_no);
	PUT(fp,BAMG_ADPT_FILE,adapt_no);
	PUT(fp," -o r.mesh %s",BAMG_ADPT_DEFAULT_OPTION);
      }
      else {
	PUT(fp,"      call system('cp bamg.mesh bamg.mesh.%d')\n",
	    adapt_no);
	PUT(fp,"      write(*,*) 'BAMG remeshing...'\n");
	PUT(fp,"      call system('bamg -b bamg.mesh.%d -Mbb ",adapt_no);
	PUT(fp,BAMG_ADPT_FILE,adapt_no);
	PUT(fp," -o r.mesh %s",BAMG_ADPT_DEFAULT_OPTION);
      }



    if(option == NULL) {
      PUT(fp,"')\n");
    }
    else {
      PUT(fp," %s)\n",option+1);
    }

    /*    PUT(fp,"*      call system('cp bamg.mesh org.mesh')\n"); */

    if(MACHINE==Windows) {
      PUT(fp,"      call system('copy r.mesh bamg.mesh')\n");
    }
    else {
      PUT(fp,"      call system('cp r.mesh bamg.mesh')\n");
    }
      
    PUT(fp,"      call system('feel.bamg.exe')\n");
    COM;
    }
    
    F77("      return\n");
    F77("      end\n");

    CloseFile(fp);

    return;

}
