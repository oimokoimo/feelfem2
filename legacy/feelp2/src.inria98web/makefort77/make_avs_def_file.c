/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_avs_def_file.c
 *      Date:   1998/09/10
 *    Update:   1999/02/23
 *              1999/03/12 (add UI panel to invoke mesh generation)
 *              1999/03/26 (node,etc)
 *   
 *   Purpose:   make control file for avs
 *              modified for macro position, default value(99/02/22)
 *              initial value(99/02/23)
 *              
 */
#include <stdlib.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../var_comp/var_comp.h"
#include "../system/system.h"

extern char *AVSExpress_dir;
extern char *current_dir;

void make_avs_def_file()
{
  int i;
  int avsvariables;
  int type;
  

  Var *var_ptr;

  FILE *fp;
  
  /* templ.v */
  fp = fopen(AVS_TEMPLATE_V_NAME,"w");
  if(fp == NULL) {
    SystemAbort("Cannot write AVS templ.v type file");
  }  
  F77(   "\"$XP_PATH<0>\\\\v\\\\templ.v\" Templates {\n");
  F77(   "  WORKSPACE_1{\n");
  PUT(fp,"    $include %s\n",AVS_UCD_V_FNAME);
  PUT(fp,"    $include %s\n",AVS_FEELMESH_V_FNAME);

  if(how_many_adaptmesh()>0) {
  PUT(fp,"    $include %s\n",AVS_ADAPTMESH_V_FNAME);
  }
  PUT(fp,"    $include %s\n",AVS_MACRO_V_FNAME);

  F77(   "  };\n");
  F77(   "};\n");

  fclose(fp);


  /* feelmesh.v */
  fp = fopen(AVS_FEELMESH_V_FNAME,"w");
  if(fp == NULL) {
    SystemAbort("Cannot write AVS UCD.V type file");
  }
  PUT(fp,"module Feelmesh<src_file=\"feelmesh.c\",process=\"express\"> {\n");
  PUT(fp,"   omethod+req meshupdate( .startmesh+read+notify,\n");
  PUT(fp,"                           .node+read,\n");
  PUT(fp,"                           .out+write) = \"feelmesh\";\n");
  PUT(fp,"   float  startmesh<export=2,NEportLevels={2,0}>;\n");
  PUT(fp,"   int node<export=2,NEportLevels={2,0}>;\n");
  PUT(fp,"   int out<export=2,NEportLevels={0,2}>;\n");
  PUT(fp,"};\n");
  fclose(fp);

  /*-------------*/
  /* feeladapt.v */
  /*-------------*/
  if(how_many_adaptmesh()>0) {
  fp = fopen(AVS_ADAPTMESH_V_FNAME,"w");
  if(fp == NULL) {
    SystemAbort("Cannot write AVS feeladapt.v type file");
  }
  PUT(fp,"module Feeladapt<src_file=\"feelmesh.c\",process=\"express\"> {\n");
  PUT(fp,"   omethod+req adaptupdate( .adaptmesh+read+notify,\n");
  PUT(fp,"                            .err+read,\n");
  PUT(fp,"                            .option+read,\n");
  PUT(fp,"                            .out+write) = \"feeladapt\";\n");
  PUT(fp,"   float adaptmesh<export=2,NEportLevels={2,0}>;\n");
  PUT(fp,"   string err<export=2,NEportLevels={2,0}>;\n");
  PUT(fp,"   string option<export=2,NEportLevels={2,0}>;\n");
  PUT(fp,"   int out<export=2,NEportLevels={0,2}>;\n");
  PUT(fp,"};\n");
  fclose(fp);
  } /* end of how many string */


  /* ucd.v */
  fp = fopen(AVS_UCD_V_FNAME,"w");
  if(fp == NULL) {
    SystemAbort("Cannot write AVS UCD.V type file");
  }

  avsvariables = how_many_avs_variables();

  PUT(fp,"module %s<src_file=\"%s\",",DEFAULT_AVS_VMODULE_NAME,
	                                  DEFAULT_AVS_FORT77_NAME);
  fprintf(fp,"process=\"express\"> {\n");
  fprintf(fp,"   fmethod+req update(\n");
  fprintf(fp,"      .start+read+notify,.cputime+read,.node+read,\n");
  fprintf(fp,"      .mesgbox+read,.meshonly+read");

  for(i=0;i<avsvariables;i++) {
    fprintf(fp,",.");
    put_nth_avs_real_name_fp(fp,i);
    fprintf(fp,"+read");
  }
  fprintf(fp,",\n");
  fprintf(fp,"      .%s+write) = \"%s\";\n",DEFAULT_AVS_OUTPUT_PORT,
                                            DEFAULT_AVS_MODULENAME);
  fprintf(fp,"   float start<export=2,NEportLevels={2,0}>;\n");
  fprintf(fp,"   float cputime<export=2,NEportLevels={2,0}>;\n");
  fprintf(fp,"   string mesgbox<export=2,NEportLevels={0,2}>;\n");
  fprintf(fp,"   int node<export=2,NEportLevels={2,0}>;\n");
  fprintf(fp,"   int meshonly<export=2,NEportLevels={2,0}>;\n");
  for(i=0;i<avsvariables;i++) {
    type = get_nth_avs_feel_var_type(i);
    switch(type) {
    case INT:
      fprintf(fp,"int   ");
      break;
    case DOUBLE:
      fprintf(fp,"float ");
      break;
    default:
      SystemAbort("Illegal type in make_avs_def_file");
    }
    put_nth_avs_real_name_fp(fp,i);
    fprintf(fp,"<export=2,NEportLevels={2,0}>;\n");
  }

  fprintf(fp,"   Field %s<export=2,NEportLevels={0,2}>;\n",
	  DEFAULT_AVS_OUTPUT_PORT);

  fprintf(fp,"};\n");

  /*
  fprintf(fp,"module FeelMain<src_file=\"feel_main.f\",process=\"express\">\n");
  fprintf(fp,"{};\n");

  fprintf(fp,"module FeelAvsInterface<src_file=\"feelavs.f\",process=\"express\">\n");
  fprintf(fp,"{};\n");
  */
    

  fclose(fp);



  /* Macro files 1998/11/01 */
  fp = fopen(AVS_MACRO_V_FNAME,"w");
  if(fp == NULL) {
    SystemError("Cannot create AVS macrofile");
    return;
  }

  F77("macro FeelMenu<NEx=132.,NEy=55.> {\n");

  /*------------------*/
  /* WORKSPACE_1.Feel */
  /*------------------*/
  F77("  WORKSPACE_1.Feel Feel<NEx=616.,NEy=429.> {\n");
/*  F77("    start=><-.START.do;\n");                            */
  F77("    node=><-.node.value;\n");
  F77("    mesgbox=><-.mesgbox.text;\n");
  F77("    cputime=><-.cputime.value;\n");
  for(i=0;i<avsvariables;i++) {
  F77("    "); put_nth_avs_real_name_fp(fp,i);
  PUT(fp,       " =><-.no%d_field.value;\n",i+1);
  }
  F77("    feelucd<NEportLevels={0,3}>;\n");
  F77("  };\n");


  /*----------------------*/
  /* WORKSPACE_1.Feelmesh */
  /*----------------------*/
  F77("  WORKSPACE_1.Feelmesh Feelmesh<NEx=33,NEy=400> {\n");
  F77("    startmesh =><-.MESH.do;\n");
  F77("    node =><-.node.value;\n");
  F77("  };\n");

  /*-----------------------*/
  /* WORKSPACE_1.Feeladapt */
  /*-----------------------*/
  if(how_many_adaptmesh()>0) {
  F77("  WORKSPACE_1.Feeladapt Feeladapt<NEx=33,NEy=433> {\n");
  F77("    adaptmesh =><-.ADAPT.do;\n");
  F77("    err =><-.bamgerr.text;\n");
  F77("    option=><-.bamgoption.text;\n");
  F77("  };\n");
  } /*end of how many adapt */


  /*------------------------*/
  /*  Parser for start      */
  /*------------------------*/
  F77("  GMOD.parse_v parse_v {\n");
  F77("     v_commands = \"Feel.start=1; Feel.meshonly= 0;\";\n");
  F77("     trigger    => <-.START.do;\n");
  F77("     relative => <-.<-;\n");
  F77("     on_inst = 0;\n");
  F77("  };\n");

  /*------------------------*/
  /*  Parser for mesh       */
  /*------------------------*/
  F77("  GMOD.parse_v parse_v#1 {\n");
  F77("     v_commands = \"Feel.start=1; Feel.meshonly= 999;\";\n");
  F77("     trigger    => <-.Feelmesh.out;\n");
  F77("     relative => <-.<-;\n");
  F77("     on_inst = 0;\n");
  F77("  };\n");

  /*------------------------*/
  /*  Parser for adapt      */
  /*------------------------*/
  if(how_many_adaptmesh()>0) {
  F77("  GMOD.parse_v parse_v#2 {\n");
  F77("     v_commands = \"Feel.start=1; Feel.meshonly= 999;\";\n");
  F77("     trigger    => <-.Feeladapt.out;\n");
  F77("     relative => <-.<-;\n");
  F77("     on_inst = 0;\n");
  F77("  };\n");
  }




  /*---------------*/
  /* Control Panel */
  /*---------------*/

  F77("  UImod_panel Feel_Control<NEx=11.,NEy=11.>;\n");
  
  /*----------------------*/
  /* Push botton to start */
  /*----------------------*/  
  F77("  UIbutton START<NEx=33.,NEy=60> {\n");   /* 60 is base */
  F77("    parent => <-.Feel_Control;\n");
  F77("    y =   0;\n");
  F77("    x =  10;\n");
  F77("    fontAttributes {\n");
  F77("       height = 20;\n");
  F77("    };\n");
  F77("  };\n");


  /* cputime field */
  PUT(fp,"  UIfield cputime<NEx=33.,NEy=93.> {\n");
  PUT(fp,"    y =   0;\n");
  PUT(fp,"    x = 120;\n");
  PUT(fp,"    width = 100;\n");
  PUT(fp,"    value = 0.0;\n");
  PUT(fp,"    fontAttributes { height         = 20;     };\n");
  PUT(fp,"    parent => <-.Feel_Control;\n");
  PUT(fp,"  };\n");


  /* (KILLED) START LABEL */                                        /* KILL */
  /*  F77("  UIlabel Push_to_Exec<NEx=33., NEy=93.> {\n");
  F77("    parent =><-.Feel_Control;\n");
  F77("    y = 5;\n");
  F77("    x = 100;\n");
  F77("    width = 120;\n");
  F77("    color          { foregroundColor=\"red\"; };\n");
  F77("    fontAttributes { height         = 15;     };\n");
  F77("  };\n");   */



  /*----------------------*/
  /* Push botton to mesh */
  /*----------------------*/  
  F77("  UIbutton MESH<NEx=33,NEy=200> {\n");    /* start 200 */
  F77("    parent => <-.Feel_Control;\n");
  F77("    y =  33;\n");
  F77("    x =  10;\n");
  F77("    fontAttributes {\n");
  F77("       height = 20;\n");
  F77("    };\n");
  F77("  };\n");


  /* Node Field */
  PUT(fp,"  UIfield node<NEx=33,NEy=233>  {\n");  /* 126=93+33 */
  PUT(fp,"    y = 33;\n");
  PUT(fp,"    x = 120;\n");
  PUT(fp,"    width = 100;\n");

  PUT(fp,"    value = %d;\n",get_final_nodes());
  PUT(fp,"    fontAttributes { height         = 20;     };\n");
  PUT(fp,"    updateMode = 2;\n");
  PUT(fp,"    decimalPoints = 0;\n");           /* UIfield for integer */
  PUT(fp,"    parent => <-.Feel_Control;\n");
  PUT(fp,"  };\n");


  if(how_many_adaptmesh()>0) {

  /*--------------------------*/
  /* Push botton to adaptmesh */
  /*--------------------------*/  
  F77("  UIbutton ADAPT<NEx=33,NEy=300> {\n");    /* start 300 */
  F77("    parent => <-.Feel_Control;\n");
  F77("    y =  66;\n");
  F77("    x =  10;\n");
  F77("    fontAttributes {\n");
  F77("       height = 20;\n");
  F77("    };\n");
  F77("  };\n");


  /* Err Field */
  PUT(fp,"  UItext bamgerr<NEx=33,NEy=333>  {\n");  /* 333 */
  PUT(fp,"    y = 66;\n");
  PUT(fp,"    x = 120;\n");

  if(MACHINE != Windows) {
    PUT(fp,"    height = 38;\n");
  }

  PUT(fp,"    width = 100;\n");
  PUT(fp,"    text = \"%s\";\n",BAMG_DEFAULT_ERR);

  PUT(fp,"    fontAttributes { height         = 20;     };\n");
  PUT(fp,"    updateMode = 2;\n");
  PUT(fp,"    parent => <-.Feel_Control;\n");
  PUT(fp,"  };\n");

  /* Command Text */
  PUT(fp,"  UItext bamgoption<NEx=33,NEy=366>  {\n");  /* 366 */
  PUT(fp,"    y = 99;\n");
  PUT(fp,"    x = 10;\n");

  if(MACHINE != Windows) {
    PUT(fp,"    height = 38;\n");
  }

  PUT(fp,"    width = 230;\n");
  PUT(fp,"    text = \"%s\";\n",BAMG_ADAPT_DEFAULT);
  PUT(fp,"    updateMode = 2;\n");
  PUT(fp,"    parent => <-.Feel_Control;\n");
  PUT(fp,"  };\n");

  } /* end of if_how_many_adaptmesh */

  /* UItext panel for OUTPUT Message */
  PUT(fp,"  UItext mesgbox<NEx=33,NEy=399>  {\n");  /* 399 */
  PUT(fp,"    y = 132;\n");
  PUT(fp,"    x = 10;\n");

  if(MACHINE != Windows) {
    PUT(fp,"    height = 38;\n");
  }

  PUT(fp,"    width = 230;\n");
  PUT(fp,"    text  = \"No ERROR\";\n");
  PUT(fp,"    parent => <-.Feel_Control;\n");
  PUT(fp,"  };\n");

  { /* x,y for panels; */
  int yinit= 133;  /* initial step in y  (for MESH button)  */ /* because mesgbox..*/
  int y_F       ;  /* calculation for y      */
  int y_L       ;  /* calculation for y      */
  int dy   =  50;  /* displacement           */
  int ddy  =   5;  /* displacement for label */

  int x_F  = 100;  /* x for field, this is constant */
  int x_L  =   0;  /* x for label, this is constant */

  int NEx  = 220;  /* this is constant */

  int NEy_F;
  int NEy_L;

  int NEy_F0=  66;
  int NEy_L0=  33;
  int dNEy  =  77;


  for(i=0;i<avsvariables;i++) {
 
  NEy_F = NEy_F0 + i*dNEy;
  NEy_L = NEy_L0 + i*dNEy;
  y_F   = dy * (i+1)        + yinit;
  y_L   = dy * (i+1) + ddy  + yinit;


  var_ptr = get_nth_avs_feel_var_ptr(i);

  /* FIELD */
  PUT(fp,"  UIfield no%d_field<NEx=%d.,NEy=%d.> {\n",i+1,NEx,NEy_F);
  PUT(fp,"    y = %d;\n",y_F);
  PUT(fp,"    x = %d;\n",x_F);
  PUT(fp,"    width = 150;\n");
  PUT(fp,"    updateMode = 2;\n");
  PUT(fp,"    format = 0;\n");

  if(var_ptr->initial == YES) {
    PUT(fp,"    value = %s;\n",var_ptr->val);
  }

  PUT(fp,"    fontAttributes { height         = 20;     };\n");

  PUT(fp,"    parent => <-.Feel_Control;\n");
  PUT(fp,"  };\n");

  /* LABEL (Cut Input_ at the first 99/03/23)*/
  PUT(fp,"  UIlabel "); put_nth_avs_real_name_fp(fp,i);
  PUT(fp,                   "<NEx=%d.,NEy=%d.> {\n",
            NEx, NEy_L);
  PUT(fp,"    y = %d;\n",y_L);
  PUT(fp,"    x = %d;\n",x_L);
  PUT(fp,"    fontAttributes { height         = 20;     };\n");  

  PUT(fp,"    parent => <-.Feel_Control;\n");
  PUT(fp,"  };\n");

  }
  }
  PUT(fp,"};\n");
  fclose(fp);

  /* End of making macro file */


  /* make feelmesh.c */
  fp = fopen(AVS_FEELMESH_FNAME,"w");
  if(fp == NULL) {
    SystemError("Cannot create AVS feelmesh.c");
    return;
  }

  F77("#include <stdio.h>\n");
  F77("#include \"express.h\"\n");
  F77("int\n");
  F77("feelmesh(OMobj_id feelmesh_id,OMevent_mask event_mask,int seq_num)\n");
  F77("{\n");
  F77("    int node;\n");
  F77("    char buf[BUFSIZ];\n");
  F77("   /***********************/\n");
  F77("   /* Function's Body     */\n");
  F77("   /***********************/\n");
  F77("   if(OMget_name_int_val(\n");
  F77("      feelmesh_id,OMstr_to_name(\"node\"),&node) != 1) { \n");
  F77("      ERRverror(\"\",ERR_NO_HEADER | ERR_INFO,\n");
  F77("     \"Specified node date is not valid.\\n\");\n");
  F77("       return(-1);\n");
  F77("   }\n");
  PUT(fp,"   sprintf(buf,\"feel -meshonly -bamg -node %%d %s\",node);\n",
      pde_src_name);
  F77("\n");
  F77("   system(buf);\n");
  F77("   OMset_name_int_val(feelmesh_id,OMstr_to_name(\"out\"),1);\n");
  F77("   return(1);\n");
  F77("}\n");


  if(how_many_adaptmesh()>0) {
  F77("int\n");
  F77("feeladapt(OMobj_id feeladapt_id,OMevent_mask event_mask,int seq_num)\n");
  F77("{\n");
  F77("    char *err;\n");
  F77("    char *option;\n");
  F77("    char  buf[BUFSIZ];\n");


  /* READ ERR */

  F77("   /***********************/\n");
  F77("   /* Function's Body     */\n");
  F77("   /***********************/\n");
  F77("   if(OMget_name_str_val(\n");
  F77("      feeladapt_id,OMstr_to_name(\"err\"),&err,0) != 1) { \n");
  F77("      ERRverror(\"\",ERR_NO_HEADER | ERR_INFO,\n");
  F77("     \"Specified Err parameter is not valid.\\n\");\n");
  F77("       return(-1);\n");
  F77("   }\n");

  /* READ OPTION text */
  F77("   if(OMget_name_str_val(\n");
  F77("      feeladapt_id,OMstr_to_name(\"option\"),&option,0) != 1) { \n");
  F77("      ERRverror(\"\",ERR_NO_HEADER | ERR_INFO,\n");
  F77("     \"Specified option parameter is not valid.\\n\");\n");
  F77("       return(-1);\n");
  F77("   }\n");


  if(avs_mesh_ref == 3) {
    PUT(fp,"   sprintf(buf,\"bamg -b bamg.mesh.1 -Mbb bamg.adpt.1 -o r.mesh %s -err %%s %%s\",err,option);\n",BAMG_DEFAULT_OPTION);
  } 
  if(avs_mesh_ref == 4) {
    PUT(fp,"   sprintf(buf,\"bamg -b bamg.mesh.1 -Mbb bamg.adpt.1 -o r.mesh %s %s -err %%s %%s\",err,option);\n",BAMG_DEFAULT_OPTION,BAMG_RECT_OPTION);
  }

  F77("\n");
  F77("   system(buf);\n");

  if(MACHINE==Windows) {
  F77("   system(\"copy r.mesh bamg.mesh\");\n");
  F77("   system(\"feel.bamg.exe\");\n");
  }
  else {
  F77("   system(\"cp r.mesh bamg.mesh\");\n");
  F77("   system(\"feel.bamg.exe\");\n");
  }

  F77("   OMset_name_int_val(feeladapt_id,OMstr_to_name(\"out\"),1);\n");

  F77("   return(1);\n");
  F77("}\n");
  }  /* end of adapt mesh */


  if(MACHINE != Windows) {
    
    
    F77("#include <sys/types.h>\n");
    F77("#include <sys/times.h>\n");
    F77("#include <time.h>\n");
    F77("\n");
    F77("static long  user_time,total_user_time;\n");
    F77("static long   sys_time,total_sys_time;\n");
    F77("static long  c_user_time,total_c_user_time;\n");
    F77("static long   c_sys_time,total_c_sys_time;\n");
    F77("static struct tms cpu_time;\n");
    F77("\n");


    F77("void timeinit_()\n");
    F77("{\n");
    F77("    if( -1 == times( &cpu_time )) {\n");
    F77("	fprintf(stderr,\"Cannot call times routine\\n\");\n");
    F77("    }\n");
    F77("    \n");
    F77("    user_time    = cpu_time.tms_utime;\n");
    F77("    sys_time     = cpu_time.tms_stime;\n");
    F77("    \n");
    F77("    c_user_time  = cpu_time.tms_cutime;\n");
    F77("    c_sys_time   = cpu_time.tms_cstime;\n");
    F77("\n");
    F77("    total_user_time = 0;\n");
    F77("    total_sys_time  = 0;\n");
    F77("\n");
    F77("    total_c_user_time = 0;\n");
    F77("    total_c_sys_time  = 0;\n");
    F77("\n");
    F77("    return;\n");
    F77("}\n");
    F77("\n");
    F77("double erapstime_()\n");
    F77("{\n");
    F77("    long ut,st;\n");
    F77("    long cut,cst;\n");
    F77("    double ret_value;\n");
    F77("\n");
    F77("    if( -1 == times( &cpu_time )) {\n");
    F77("	fprintf(stderr,\"Cannot call times routine\\n\");\n");
    F77("    }\n");
    F77("    \n");
    F77("    ut = cpu_time.tms_utime - user_time;\n");
    F77("    st = cpu_time.tms_stime - sys_time ;\n");
    F77("    total_user_time += ut;\n");
    F77("    total_sys_time  += st;\n");
    F77("\n");
    F77("    cut = cpu_time.tms_cutime - c_user_time;\n");
    F77("    cst = cpu_time.tms_cstime - c_sys_time ;\n");
    F77("    total_c_user_time += cut;\n");
    F77("    total_c_sys_time  += cst;\n");
    F77("\n");
    F77("    user_time = cpu_time.tms_utime;\n");
    F77("    sys_time  = cpu_time.tms_stime;\n");
    F77("\n");
    F77("    c_user_time = cpu_time.tms_cutime;\n");
    F77("    c_sys_time  = cpu_time.tms_cstime;\n");
    F77("\n");
    F77("\n");
    F77("    ret_value = (double)(total_user_time + total_sys_time)/(double)CLK_TCK;\n");
    F77("\n");
    F77("\n");
    F77("    return(ret_value);\n");
    F77("}\n");


    F77("/*\n");
    F77(" *  getdat.c function for UNIX system to get current date by 'date' command\n");
    F77(" *\n");
    F77(" *  Date          1997/10/09 16:30\n");
    F77(" *  Programmed by Hidehiro FUJIO\n");
    F77(" *\n");
    F77(" *  It returns character*16 pointer, and this is allocated local memory\n");
    F77(" *  in this file.\n");
    F77(" *\n");
    F77(" */ \n");
    F77("\n");
    F77("#include <stdlib.h>\n");
    F77("\n");
    F77("\n");
    F77("/* Format \n");
    F77("   1234567890123456X  \n");
    F77("   1965/09/11 17:45   */\n");
    F77("\n");


    F77("void getdate_(datebuf)        /* Returns 16byte string */\n");
    F77("char *datebuf;\n");
    F77("{\n");
    F77("  FILE *pfp;\n");
    F77("  char  buf[BUFSIZ];\n");
    F77("\n");
    F77("  char  whatday[11];\n");
    F77("  char  month[11];\n");
    F77("  int   imonth;\n");
    F77("  int   day;\n");
    F77("  char  time[11];\n");
    F77("  char  timezone[11];\n");
    F77("  int   year;\n");
    F77("\n");
    F77("  int   ret;\n");
    F77("\n");
    F77("\n");
    F77("  /* use date command to get date */\n");
    F77("  pfp = (FILE *)popen(\"date\",\"r\");\n");
    F77("  fgets(buf,sizeof(buf),pfp);\n");
    F77("  ret = pclose(pfp);\n");
    F77("\n");
    F77("\n");
    F77("  if(pfp == NULL || ret != 0) {\n");
    F77("    sprintf(datebuf,\"----/--/-- --:--\");\n");
    F77("    return;\n");
    F77("  }\n");
    F77("\n");

    F77("  /* Read buffer */\n");
    F77("  sscanf(buf,\"%%s %%s %%d %%s %%s %%d\",whatday,month,&day,time,timezone,&year);\n");
    F77("\n");

    F77("  /*  Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec */\n");
    F77("  switch(month[0]) {\n");
    F77("  case 'J': \n");
    F77("    if(month[1] == 'a') {\n");
    F77("      imonth = 1;\n");
    F77("    }\n");
    F77("    else if(month[2] == 'n') {\n");
    F77("      imonth = 6;\n");
    F77("    }\n");
    F77("    else {\n");
    F77("      imonth = 7;\n");
    F77("    }\n");
    F77("    break;\n");
    F77("\n");
    F77("  case 'F':\n");
    F77("    imonth = 2;\n");
    F77("    break;\n");
    F77("\n");
    F77("  case 'M':\n");
    F77("    if(month[2] == 'r') {\n");
    F77("      imonth = 3;\n");
    F77("    }\n");
    F77("    else {\n");
    F77("      imonth = 5;\n");
    F77("    }\n");
    F77("    break;\n");
    F77("\n");
    F77("  case 'A':\n");
    F77("    if(month[1] == 'p') {\n");
    F77("      imonth = 4;\n");
    F77("    }\n");
    F77("    else {\n");
    F77("      imonth = 8;\n");
    F77("    }\n");
    F77("    break;\n");
    F77("\n");
    F77("  case 'S':\n");
    F77("    imonth = 9;\n");
    F77("    break;\n");
    F77("\n");
    F77("  case 'O':\n");
    F77("    imonth = 10;\n");
    F77("    break;\n");
    F77("    \n");
    F77("  case 'N':\n");
    F77("    imonth = 11;\n");
    F77("    break;\n");
    F77("    \n");
    F77("  case 'D':\n");
    F77("    imonth = 12;\n");
    F77("    break;\n");
    F77("\n");
    F77("  }\n");
    F77("\n");
    F77("  /* time */\n");
    F77("  time[5] = '\\0';\n");
    F77("\n");

    F77("  /*   Again, the format is\n");
    F77("       1234567890123456X  \n");
    F77("       1965/09/11 17:45     */\n");
    F77("  \n");
    F77("  sprintf(datebuf,\"%%4d/%%2d/%%2d %%s\",year,imonth,day,time);\n");
    F77("\n");
    F77("\n");
    F77("  /* add 0 if space in month and day */\n");
    F77("  if(*(datebuf+5) == ' ') *(datebuf+5) = '0';\n");
    F77("  if(*(datebuf+8) == ' ') *(datebuf+8) = '0';\n");
    F77("\n");
    F77("  /* return */\n");
    F77("  return;\n");
    F77("}\n");

  }   /* for UNIX, add cptime and getdate to feelmesh.c */



  fclose(fp);  /* end of making feelmesh.c */


  /* make avsenv file */
  fp = fopen("avsenv","r");
  if(fp == NULL) {
    fp = fopen("avsenv","w");
    if(fp == NULL) {
      SystemAbort("Cannot make avsenv file");
    }
    F77("# Warning: this file is generated by FEEL\n");
    F77("# XP_PATH=[Project directory]  [Express installed directory]\n");
    F77("# **Example**\n");
    if(MACHINE==Windows) {
      F77("# XP_PATH=c:\\user\\foo  c:\\Express\n");
    }
    else {
      F77("# XP_PATH=/home/foo/  /usr/AVSExp/express\n");
    }
    F77("#\n");


#ifdef MSDOS
    if(MACHINE==Windows) {
      PUT(fp,"XP_PATH=%s %s\n",current_dir,AVSExpress_dir);
    }
    else {
      PUT(fp,"XP_PATH=%s %s\n",DEFAULT_CURRENT_DIR,DEFAULT_UNIX_EXPRESS_DIR);
    }
#else
    if(MACHINE==Windows) {
      PUT(fp,"XP_PATH=%s %s\n",DEFAULT_CURRENT_DIR,DEFAULT_DOS_EXPRESS_DIR);
    }
    else {
      PUT(fp,"XP_PATH=%s %s\n",current_dir,AVSExpress_dir);
    }    
#endif
  }  /* end of avsenv */



  return;
}


