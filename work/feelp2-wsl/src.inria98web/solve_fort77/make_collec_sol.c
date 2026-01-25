/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_collec_sol.c
 *      Date:   1996/05/16
 *   
 *   Purpose:   collect solution after solver
 *   Functions: make_collec_sol()
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../solve_comp/solve_comp.h"
#include "../system/system.h"

void make_collec_sol(solve_no,solve_element_ptr)
     int solve_no;
     SolveElement *solve_element_ptr;
{
    FILE *fp;
    char fname[30];
    int  i,j;

    sprintf(fname,"collec_sol%d.f",solve_no);
    
    StoreMakefile( fname , USER_LIBRARY );
    fp  = OpenFileToWrite( fname );

    F77("      subroutine ");
    PUT(fp,"collec_sol%d(rank",solve_no);

    for(j=0;j<solve_element_ptr->unknowns;j++) {
	F77(",");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
    }
    F77(",nloglo,npmaxsub,\n");
    F77("     $           sb,ndsub,rb,nrb,npmax,npe)\n");
    
    CopyRight(fp);
    TimeStamp(fp);
    real8(fp);
    
    PUT(fp,"      include %s\n",MPI_HEADER_FILE);
    

    F77("      integer rank,size,status(mpi_status_size)\n");
    for(j=0;j<solve_element_ptr->unknowns;j++) {
	F77("      dimension ");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
	F77("(*)\n");
    }
    F77("      dimension nloglo(*)\n");
    F77("      dimension ndsub(*)\n");
    F77("      dimension sb(*),rb(*),nrb(*)\n");

    
    comment1(fp);
    F77("* Send the number of nodes in each subdomain\n");
    COM;
    F77("      if(rank .NE.0) then\n");
    F77("        call mpi_send(npmaxsub,1,mpi_integer,\n");
    F77("     $                0,0,mpi_comm_world,ierror)\n");
    F77("      endif\n");

    comment1(fp);
    F77("* Receive the number of nodes in each subdomain\n");
    COM;
    F77("      if(rank .EQ.0) then\n");
    F77("        do 1 ipe = 2, npe\n");
    F77("          call mpi_recv (ndsub(ipe),1,mpi_integer,\n");
    F77("     $                   ipe-1,0,mpi_comm_world,status,ierror)\n");
    F77("    1   continue\n");
    F77("      endif\n");
    COM;
    
    F77("      if(rank .NE. 0) then\n");
    F77("        do 10 i=1,npmaxsub\n");
    /* FEM変数 */
    for(j=0;j<solve_element_ptr->unknowns;j++) {
	PUT(fp,"          sb(i");
	if(j == 0) {
	    PUT(fp,")");
	}
	else {
	    if(j == 1){ PUT(fp,"+npmaxsub)");}
	    else      { PUT(fp,"+npmaxsub*%d)",j); }
	}
	F77(" = ");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
	F77("(nloglo(i))\n");
    }
    F77("10      continue\n");
    F77("***\n");

    F77("        call mpi_send(nloglo,npmaxsub,mpi_integer,\n");
    F77("     $                0,1,mpi_comm_world,ierror)\n");
    COM;

    for(j=0;j<solve_element_ptr->unknowns;j++) {

	switch (j) {
	  case 0:
	    F77("        call mpi_send(sb(1),npmaxsub,\n");
	    break;

	  case 1:
	    F77("        call mpi_send(sb(npmaxsub+1),npmaxsub,\n");
	    break;
	    
	  default:
	    PUT(fp,"        call mpi_send(sb(npmaxsub*%d+1),npmaxsub,\n",j);
	}
	PUT(fp,"     $   mpi_double_precision,0,%d,mpi_comm_world,ierror)\n",
	    j+2);
    }
    COM;
    F77("      endif\n");

    F77("*****\n");

    F77("      if(rank .EQ. 0) then\n");
    F77("        do 20 ipe=2,npe\n");
    COM;

    F77("          call mpi_recv(nrb,ndsub(ipe),mpi_integer,\n");
    F77("     $         ipe-1,1,mpi_comm_world,status,ierror)\n");

    for(j=0;j<solve_element_ptr->unknowns;j++) {

	switch (j) {
	  case 0:
         F77("        call mpi_recv(rb(1),ndsub(ipe),mpi_double_precision,\n");
	   break;

	  case 1:
	   F77("        call mpi_recv(rb(npmax+1),ndsub(ipe),\n");
	   F77("     $       mpi_double_precision,\n");
	   break;
	    
	  default:
	   PUT(fp,"        call mpi_recv(rb(npmax*%d+1),ndsub(ipe),\n",j);
	   F77("     $       mpi_double_precision,\n");
	   break;
	}
	PUT(fp,"     $   ipe-1,%d,mpi_comm_world,status,ierror)\n",
	    j+2);
    }
    F77("*****\n");

    F77("          do 30 j=1,ndsub(ipe)\n");

    for(j=0;j<solve_element_ptr->unknowns;j++) {
	F77("            ");
	PUT(fp,FEM_VAR_NAME77,*(solve_element_ptr->unknown_name + j));
	PUT(fp,"(nrb(j))=rb(j");
	switch(j) {
	  case 0:
	    F77(")\n");
	    break;

	  case 1:
	    F77("+npmax)\n");
	    break;

	  default:
	    PUT(fp,"+npmax*%d)\n",j);
	    break;
	}
    }
    COM;

    F77("30        continue\n");
    F77("20      continue\n");
    F77("      endif\n");
    F77("*****\n");
    F77("      return\n");
    F77("      end\n");

    CloseFile(fp);
    return;
}




