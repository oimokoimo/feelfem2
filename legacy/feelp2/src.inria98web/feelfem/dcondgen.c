/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : dcondgen.c
 *  Date     : 1999/12/21
 *  Modified : 1999/12/21
 *  
 *  Purpose  : write out dcond data from P2 feel
 *  
 */


#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"


FILE *GetFEELFEMFP();

void dcondgen(solve_no,dcond_no,d_ptr)
     int            solve_no;  
     int            dcond_no;  
     DirichletData *d_ptr;
{
    int i;
    int dimension;

    int terms;
    char *from[MAX_TERM_VARS];
    char *to[MAX_TERM_VARS];

    FILE *fp;
    char fname[FNAME_SIZE];
    char name_buf[38];
    char name_buf2[38];


    terms = 0;
    
    fp = GetFEELFEMFP();

    fprintf(fp,"%8d%8d  ***dcond(dcondgen)\n",solve_no,dcond_no);


    dimension = 2;

    switch(dimension) {
      case 3:
	from[terms] = "z";
	to[terms]   = "z(ip)";
	terms++;

      case 2:
	from[terms] = "y";
	to[terms]   = "y(ip)";
	terms++;

      case 1:
	from[terms] = "x";
	to[terms]   = "x(ip)";
	terms++;
	break;

      default:
	break;
    }

    for(i=0;i<d_ptr->fem_vars;i++) {
	sprintf(name_buf2,FEM_VAR_NAME77,*(d_ptr->fem_var_name + i));
	sprintf(name_buf,"%s(ip)",name_buf2);

	from[terms] = *(d_ptr->fem_var_name + i);
	to[terms]   = MakeStringCopy(name_buf);

	terms++;
    }


    for(i=0;i<d_ptr->scalar_vars;i++) {
	sprintf(name_buf,SCALAR_VAR_NAME77,*(d_ptr->scalar_var_name + i));

	from[terms] = *(d_ptr->scalar_var_name + i);
	to[terms]   = MakeStringCopy(name_buf);
	terms++;
    }

    /* fprintf(stderr,"terms=%d\n",terms); */
    
    fprintf(fp,"%s\n",
	term_convert(d_ptr->expr->expr_inf,from,to,terms));


    fprintf(fp,"*** end of dcond (%d/%d)***\n",solve_no,dcond_no);

    return;
}


