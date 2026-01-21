/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_avs_output_routine.c
 *      Date:   1998/09/03
 *   
 *   Purpose:   make output function for avs interface
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

void make_avs_output_routine( fp )
     FILE *fp;
{
  int i,j;

  char *get_ijth_avsout_femname();
  int avsoutputs,parameters;

  int avsparams,type;
  
  avsoutputs = how_many_avsoutputs();


  PUT(fp,"      subroutine %s",AVS_OUTPUT_SUBFUNC);
  F77("(feel,UCD_id,event_mask,seq_num,IARGSIZ,imode,\n");
  F77("     $     x,y");
  listup_avsoutput_in_sub_fp(fp);
  fprintf(fp,")\n");

  real8(fp);
  common_parameters(fp);

  /* Include files */
  F77("* Include statements may need to be modified\n");
  COM;
  F77("      include 'avs/omf.inc'\n");
  F77("      include 'avs/fldf.inc'\n");
  COM;


  /* dimensions */
  F77("      integer UCD_id(IARGSIZ),event_mask,seq_num\n");
  F77("      real*4 feel(*)\n");
  listup_avsoutput_declare_fp(fp);

  /* AVS interface variables */
  F77("* AVS interface variables\n");
  F77("      INTEGER o_id(OIDSIZ)\n");
  F77("C\n");
  F77("      CHARACTER*32 o_cell_name\n");
  F77("      real*8      CPUTM\n");
  F77("*\n");
  F77("      INTEGER o_nnodes,      o_size,        o_nspace\n");
  F77("      INTEGER o_nsets ,      o_set,         o_ncells\n");


  /*   OIMO ,oimo  this oimo 
  if(avs_64bit == YES) {
    F77("      INTEGER *8 ARRFoffset\n");
    } */

  /* Memory allocation for coord,node_connect */
  if(avs_64bit == YES) {
    F77("      INTEGER o_cell_nnodes\n");
    F77("      INTEGER *8 o_node_connect\n");
    F77("      INTEGER *8 o_crd_off,     o_con_off\n");
    F77("      INTEGER *4 o_con_base(1)\n");
    F77("      INTEGER *8 o_coord\n");
    F77("      REAL*4  o_crd_base(1)\n");
  }
  else {
    F77("      INTEGER o_cell_nnodes, o_node_connect\n");
    F77("      INTEGER o_crd_off,     o_con_off\n");    /* node must be r8??*/
    F77("      INTEGER o_con_base(1), o_coord\n");
    F77("      REAL*4  o_crd_base(1)\n");
  }

  F77("      INTEGER o_cell_set(OIDSIZ)\n");
  F77("C\n");
  F77("      INTEGER o_ncomp,     o_comp,       o_veclen\n");
  F77("      INTEGER o_data_type, o_ndata\n");


  /* Memory allocation for o_data */
  if(avs_64bit == YES) {
    F77("      INTEGER *8  o_data,      o_data_offset\n");
  }
  else {
    F77("      INTEGER o_data,      o_data_offset\n");
  }


  F77("C  !!! The type of the o_data_base array should be changed\n");
  F77("C   to the type of node data\n");
  F77("      REAL*4  o_data_base(1)\n");
  F77("      CHARACTER*32 labelname,unitname\n");
  F77("      character mesg*38\n");

  /* FEEL common */
  CommonBlock(fp);
  comment1(fp);

  F77("* Get Element-Node array\n");
  /*  F77("      np_push  = np_work\n"); OLD F_ALLOC */
  F77("      call f_alloc_push\n");

  F77("      iedat_no = 1\n");
  F77("      neelem = n_edat(iedat_no,1)\n");
  F77("      nenode = n_edat(iedat_no,2)\n");
  F77("      call f_alloc(np_ielem,'avsout',neelem*nenode,0,0)\n");
  F77("      call f_alloc(np_matno,'avsout',neelem       ,0,0)\n");
  F77("      iunit = iedat_no + io_edat - 1\n");
  F77("      call get_ielem(iunit,feel(np_ielem),feel(np_matno),neelem,nenode)\n");
  COM;
  

  F77("* [AVS]Get meh ID\n");
  F77("      IF (OMFfind_subobj(UCD_id, \n");
  PUT(fp,"     $    OMFstr_to_name('%s'),\n",DEFAULT_AVS_OUTPUT_PORT);
  F77("     $    OM_OBJ_RW, o_id) .NE. 1)\n");
  F77("     $                            PRINT*,'Error getting mesh'\n");

  F77("C  Set mesh nspace, o_nspace can be 1,2 or 3\n");
  F77("      o_nspace = 3\n");
  F77("      IF (FLDFset_nspace (o_id, o_nspace) .NE. 1)\n");
  F77("     $                            PRINT*,'Error getting nspace'\n");

  F77("C  Set mesh nodes\n");
  F77("      o_nnodes = npmax\n");
  F77("      IF (FLDFset_nnodes (o_id, o_nnodes) .NE. 1)\n");
  F77("     $                            PRINT*,'Error getting nnodes'\n");

  F77("C  Now, that nspace and nnodes are set,\n");
  F77("C  just get pointer to coordinate array\n");
  F77("      IF (FLDFget_coord(o_id, o_coord,\n");
  F77("     $   o_nnodes, OM_GET_ARRAY_RW) .NE. 1)\n");
  F77("     $      PRINT*,'Error getting coordinates'\n");
  F77("      o_crd_off = ARRFoffset(o_coord,\n");
  F77("     $   o_crd_base,DTYPE_FLOAT)\n");
  COM;
  F77("C  Fill in o_crd_base array with coordinates x,y,z,x,y,z....\n");
  F77("C  starting with o_crd_base(1+o_crd_off)\n");
  F77("      call feelavsoutnode(x,y,npmax,o_crd_base(1+o_crd_off))\n");
  COM;



  F77("C  Set number of cell sets o_nsets variable\n");
  F77("      o_nsets = 1\n");
  F77("      IF (FLDFset_ncell_sets(o_id, o_nsets) .NE. 1)\n");
  F77("     $      PRINT*,'Error getting ncell sets' \n");
  F77("C   For each cell_set set information  about cells \n");
  F77("C   do it for each o_set from 0 to o_nsets-1\n");
  F77("* [feel: currently only one type of cell set\n");
  F77("      o_set = 0\n");
  F77("      IF (FLDFget_cell_set(o_id, o_set,o_cell_set) .NE. 1)\n");
  F77("     $        PRINT*,'Error getting cell set'\n");

  F77("C   Set cell set to say, Tri\n");
  if(avs_mesh_ref == 3) {
    F77("      o_cell_name = 'Tri'\n");
  }
  else {
    F77("      o_cell_name = 'Quad'\n");
  }
  F77("      IF (FLDFset_cell_set(o_cell_set, \n");
  F77("     $  o_cell_name) .NE. 1)\n");
  F77("     $      PRINT*,'Error setting cell set'\n");

  F77("C   Set number of cells\n");
  F77("      o_ncells = neelem\n");
  F77("      IF (FLDFset_ncells(o_cell_set, o_ncells).NE. 1)\n");
  F77("     $    PRINT*,'Error getting ncells'\n");

  F77("C   Get node connectivity list\n");
  F77("      IF (FLDFget_node_connect(o_cell_set, \n");
  F77("     $      o_node_connect,o_size,OM_GET_ARRAY_RW)\n");
  F77("     $    .NE. 1)\n");
  F77("     $      PRINT*,'Error getting node connectivity' \n");
  F77("      o_con_off = ARRFoffset(o_node_connect,\n");
  F77("     $   o_con_base,DTYPE_INT)\n");

  F77("C   Fill in  o_con_base array with node indecies for each cell\n");
  F77("C  starting with o_con_base(1+o_con_off)\n");
  PUT(fp,"      call feelavsoutielem(feel(np_ielem),nenode,neelem,%d,\n",
      avs_mesh_ref);
  F77("     $    o_con_base(1+o_con_off))\n");
  COM;

  F77("C\n");
  F77("C NOTE: for POLY cell_sets such as Polyline, Polytri and Polhedron,\n");
  F77("C       if you want to get non-tesselated cells \n");
  F77("C use:\n");
  F77("C     FLDFset_npolys ()         instead of  FLDFset_ncells ()\n");
  F77("C     FLDFget_poly_connect ()   instead of  FLDFget_node_connect ()\n");
  F77("C     \n");
  F77("C     To check if a cell set is POLY type \n");
  F77("C use:\n");
  F77("C     FLDFget_poly_flag(o_cell_set, poly_flag)\n");
  COM;


  F77("C  Set output's node data\n");
  F77("C  Get field id\n");
  F77("      IF (OMFfind_subobj(UCD_id, \n");
  PUT(fp,"     $   OMFstr_to_name('%s'),\n",DEFAULT_AVS_OUTPUT_PORT);
  F77("     $   OM_OBJ_RW, o_id) .NE. 1)\n");
  F77("     $      PRINT*,'Error getting data'\n");

  F77("C  Get number of node data components\n");
  PUT(fp,"      o_ncomp = %d\n",avsoutputs);
  F77("      IF (FLDFset_node_data_ncomp (o_id, o_ncomp) .NE. 1)\n");
  F77("     $      PRINT*,'Error setting ndata comp'\n");

  F77("C  For each node data component set veclen, type and data arry itself\n");
  F77("C  do it for each o_comp from 0 to o_ncomp-1\n");

  /* LOOP for avsoutput */
  for(i=0;i<avsoutputs;i++) {
    parameters = get_nth_avsoutput_parameters(i);

    /* Make label name */
    PUT(fp,"      unitname = 'feelucd field Data set No.%d'\n",i+1);

    F77(   "      labelname= '[");

								      
    for(j=0;j<parameters;j++) {
      if(j) F77(",");
      PUT(fp," %s ",get_ijth_avsoutput_femname(i,j));
    }
    F77("]'\n");


    COM;
    PUT(fp,"      o_comp = %d\n",i);
    PUT(fp,"C  Set veclen & Label name\n");
    PUT(fp,"      o_veclen = %d\n",parameters);
    F77("      IF (FLDFset_node_data_comp (o_id, o_comp, o_veclen,\n");
    F77("     $    labelname,unitname) .NE. 1)\n");
    F77("     $      PRINT*,'Error setting data veclen'\n");
    F77("C  Set data array and data_type which is one of the following: \n");
    F77("C         DTYPE_BYTE, DTYPE_CHAR, DTYPE_SHORT, \n");
    F77("C         DTYPE_INT, DTYPE_FLOAT, DTYPE_DOUBLE \n");
    F77("      o_data_type = DTYPE_FLOAT\n");
    F77("      IF (FLDFget_node_data (o_id, o_comp, \n");
    F77("     $     o_data_type, o_data,\n");
    F77("     $   o_ndata, OM_GET_ARRAY_WR) .NE. 1)\n");
    F77("     $      PRINT*,'Error setting data'\n");
    F77("      o_data_offset = ARRFoffset(o_data,\n");
    F77("     $   o_data_base,o_data_type)\n");
    F77("C  Fill in o_data_base array with values\n");
    F77("C  starting with o_data_base(1+o_data_offset)\n");
    F77("C  Other useful calls:\n");
    F77("C          CALL FLDFset_node_data_id()\n");
    F77("C          CALL FLDFset_node_null_data()\n");
    F77("C          CALL FLDFset_node_data_minmax()\n");
    PUT(fp,"      call feelavsoutdat%d(npmax",parameters);
    
    for(j=0;j<parameters;j++) {
      F77(",");
      PUT(fp,FEM_VAR_NAME77,get_ijth_avsoutput_femname(i,j));
    }
    F77(",o_data_base(1+o_data_offset))\n");
    COM;
    F77("* Set to Free list output data area\n");
    F77("      CALL ARRFfree(o_data)\n");
    COM;
  }
  F77("C\n");
  F77("C  Free output variables \n");
  F77("C\n");
  F77("      CALL ARRFfree(o_coord)\n");
  F77("      CALL ARRFfree(o_node_connect)\n");
  COM;


  /* return values to UI Panel */
  avsparams = how_many_avs_variables();

  for(i=0;i<avsparams;i++) {
    type = get_nth_avs_feel_var_type(i);
    switch(type) {
    case INT:
      F77("      if(OMFset_name_int_val(UCD_id,OMFstr_to_name('");
      put_nth_avs_real_name_fp(fp,i);
      F77("'),\n");
      F77("     $    ");
      put_nth_avs_feel_name_fp(fp,i);
      F77(") .NE. 1) write(*,*) 'Error to set ");
      put_nth_avs_real_name_fp(fp,i);
      F77("'\n");

      break;

    case DOUBLE:
      F77("      if(OMFset_name_real8_val(UCD_id,OMFstr_to_name('");
      put_nth_avs_real_name_fp(fp,i);
      F77("'),\n");
      F77("     $    ");
      put_nth_avs_feel_name_fp(fp,i);
      F77(") .NE. 1) write(*,*) 'Error to set ");
      put_nth_avs_real_name_fp(fp,i);
      F77("'\n");

      break;
    default:
      SystemAbort("Illegal type in AVSoutput.c(avs variable declare)");
    }
  }
  COM;

  /* return mesh */
  F77("      if(OMFset_name_int_val(UCD_id,OMFstr_to_name('node'),\n");
  F77("     $   npmax) .NE. 1) write(*,*) 'set node err'\n");
  COM;
  
  /* return erapsetime */
  F77("      CPUTM = erapstime()\n");
  F77("      if(OMFset_name_real8_val(UCD_id,OMFstr_to_name('cputime'),\n");
  F77("     $   CPUTM) .NE. 1) write(*,*) 'set cputime err'\n");
  COM;


  /* return status to UI Panel for mesgbox */
  F77("      if(imode .EQ.  0) write(mesg,9501)\n");
  PUT(fp,"      if(imode .EQ. %d) write(mesg,9502)\n",ERROR_IMODE_NONLINEAR_DIVERGENT);
  F77(" 9501 format('NORMAL')\n");
  F77(" 9502 format('ERR: Divergent Newton iteration')\n");
  COM;
  F77("      if(OMFset_name_str_val(UCD_id,OMFstr_to_name('mesgbox'),\n");
  F77("     $                       mesg) .NE. 1) write(*,*) imode,' short'\n");


  COM;
  F77("      call f_alloc_pop\n");
  COM;


  F77("      return\n");
  F77("      end\n");

  F77("      subroutine avserrmsgalloc(UCD_id,IARGSIZ,imode)\n");
  F77("      integer UCD_id(IARGSIZ)\n");
  F77("      include 'avs/omf.inc'\n");
  F77("      include 'avs/fldf.inc'\n");
  F77("      character mesg*38\n");
  F77("      write(mesg,1000) imode\n");
  F77("1000  format('ERR: More',i8,' words required.')\n");
  F77("      if(OMFset_name_str_val(UCD_id,OMFstr_to_name('mesgbox'),\n");
  F77("     $                       mesg) .NE. 1) write(*,*) imode,' short'\n");
  F77("      return\n");
  F77("      end\n");

  COM;

  return;
}

