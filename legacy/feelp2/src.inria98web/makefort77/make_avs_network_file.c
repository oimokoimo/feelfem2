/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   
 *      Date:   1995/09/1
 *   
 *   Purpose:   
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"

#include "../system/system.h"
#include "../scheme_comp/scheme_comp.h"


static char *avsnetwork_item[] = {
  "isoline",
  "contr",
  "surfplot",
  "gradvect",
  "offset",
  "probe",       /* Caution: probe does not make any scene */
  "vect",
  NULL
};


int is_avsnetwork_member( name )
     char *name;
{
  int i;
  int check_max;

  check_max=0;
  for(i=0;avsnetwork_item[i]!=NULL;i++) {
    check_max++;
    if(check_max>MAX_AVSNETWORK) {
      SystemAbort("Too small MAX_AVSNETWORK parameter in feel_def.h");
    }
    if(strindex(name,avsnetwork_item[i])==1 &&
       strlen(name)==strlen(avsnetwork_item[i]) ) return(YES);
  }
  return(NO);
}

static int get_avsnetwork_member_no( name )
     char *name;
{
  int i;

  for(i=0;avsnetwork_item[i]!=NULL;i++) {
    if(strindex(name,avsnetwork_item[i])==1 &&
       strlen(name)==strlen(avsnetwork_item[i]) ) return(i);
  }
  SystemAbort("Inner Error in get_avsnetwork_member_no");
}


void make_avs_network_file()
{

  int i,j;
  int avsnetworks;
  int parameters;

  char **item_name;
  int itemindex[MAX_AVSNETWORK];

  int no;

  int planes;
  int scene_no = 0;

  FILE *fp;

  AVSnetwork *avsnet_ptr, *get_nth_avsnetwork_ptr();

  for(i=0;avsnetwork_item[i]!=NULL;i++) {
    itemindex[i] = NO;
  }

  avsnetworks = how_many_avsnetworks();
  
  for(i=0;i<avsnetworks;i++) {
    avsnet_ptr = get_nth_avsnetwork_ptr(i);
    item_name  = avsnet_ptr->item_name;
    parameters = avsnet_ptr->parameters;
    
    for(j=0;j<parameters;j++) {
      no = get_avsnetwork_member_no( *(item_name+j) );
      itemindex[no] = YES;
    }
  }


  planes = 0;    /* number of plane in 3D viewer */

  for(i=0;avsnetwork_item[i]!=NULL;i++) {
    if(itemindex[i] == YES) planes++;
  }
  if(itemindex[5] == YES) planes--;  /* probe need not planes */
  
  fp=fopen(AVS_FEELNET_V_FNAME,"w");
  if(fp==NULL) {
    SystemAbort("Cannot write feelnet.v");
  }

  /* Network application declaration */

  F77("APPS.MultiWindowApp MultiWindowApp {\n\n");


  /* Viewer with main displaying the edge */

  F77("GDM.Uviewer3D Uviewer3D <NEx=600,NEy=500>{\n");
  F77("   Scene {\n");
  F77("      Top {\n");
  F77("         child_objs => {\n");


  /* probe is connected to mesh scene */
  if(itemindex[5] == YES) {  /* Use probe */
    F77("            <-.<-.<-.edges.out_obj,<-.<-.<-.probe.out_anno,<-.<-.<-.probe.out_obj};\n");
  }
  else {
    F77("            <-.<-.<-.edges.out_obj};\n");
  }
  F77("      };\n");

  
  F77("      View { ViewUI { ViewPanel {\n");
  F77("       UI{ panel { UIshell { title =><-.title; }; }; };\n");
  F77("      };     };       };\n");



  F77("      View { ViewUI { ViewPanel {\n");

  if(itemindex[5] == YES ) {
    F77("       UI{ option { label = \"mesh with probe\"; }; };\n");
  }
  else {
    F77("       UI{ option { label = \"mesh\"; }; };\n");
  }
  F77("      };     };       };\n");



  F77("   };\n");

  /******************/
  /* Scene selector */
  /******************/
  F77("   Scene_Selector {\n");
  F77("      input_views => {\n");
  F77("        Scene.View.View,\n");
  for(i=0;i<planes;i++) {
    PUT(fp,"        <-.Scene#%d.View.View",i+1);
    if(i== planes-1) { 
      F77("};\n");
    }
    else {
      F77(",\n");
    }
  }
  F77("   };\n");


  /*****************/
  /*  Each scene   */
  /*****************/

  if( itemindex[0] == YES) {  /* isoline */
    scene_no++;
    PUT(fp,"   GDM.Uscene3D Scene#%d {\n",scene_no);
    F77("      Top {\n");
    F77("         child_objs<NEportLevels={4,1}> => {\n");
    F77("            <-.<-.<-.isoline.out_obj,\n");
    F77("            <-.<-.<-.external_edges.out_obj,\n");
    F77("            <-.<-.<-.isoline_legendv.GroupObject.obj};\n");
    F77("      };\n");

    F77("      View { ViewUI { ViewPanel {\n");
    F77("       UI{ option { label = \"isoline\"; }; };\n");
    F77("      };     };       };\n");

    F77("   };\n");

  }


  if( itemindex[1] == YES) {  /* contr */
    scene_no++;
    PUT(fp,"   GDM.Uscene3D Scene#%d {\n",scene_no);
    F77("      Top {\n");
    F77("         child_objs<NEportLevels={4,1}> => {\n");
    F77("            <-.<-.<-.contour.out_obj,\n");
    F77("            <-.<-.<-.external_edges.out_obj,\n");
    F77("            <-.<-.<-.contr_legendv.GroupObject.obj};\n");
    F77("      };\n");

    F77("      View { ViewUI { ViewPanel {\n");
    F77("       UI{ option { label = \"contour\"; }; };\n");
    F77("      };     };       };\n");

    F77("   };\n");
  }

  if( itemindex[2] == YES) {  /* surfplot */
    scene_no++;
    PUT(fp,"   GDM.Uscene3D Scene#%d {\n",scene_no);
    F77("      Top {\n");
    F77("         child_objs<NEportLevels={4,1}> => {\n");
    F77("            <-.<-.<-.surf_plot.out_obj,\n");
    F77("            <-.<-.<-.external_edges.out_obj,\n");
    F77("            <-.<-.<-.surfplot_legendv.GroupObject.obj};\n");
    F77("      };\n");

    F77("      View { ViewUI { ViewPanel {\n");
    F77("       UI{ option { label = \"surfplot\"; }; };\n");
    F77("      };     };       };\n");


    F77("   };\n");
  }


  if( itemindex[3] == YES) {  /* gradvect */
    scene_no++;
    PUT(fp,"   GDM.Uscene3D Scene#%d {\n",scene_no);
    F77("      Top {\n");
    F77("         child_objs<NEportLevels={4,1}> => {\n");
    F77("            <-.<-.<-.gradglyph.out_obj,<-.<-.<-.external_edges.out_obj};\n");
    F77("      };\n");

    F77("      View { ViewUI { ViewPanel {\n");
    F77("       UI{ option { label = \"gradvect\"; }; };\n");
    F77("      };     };       };\n");

    F77("   };\n");
  }


  /*----------------------*/
  if( itemindex[4] == YES) {  /* offset */
    scene_no++;
    PUT(fp,"   GDM.Uscene3D Scene#%d {\n",scene_no);
    F77("      Top {\n");
    F77("         child_objs<NEportLevels={4,1}> => {\n");
    F77("            <-.<-.<-.offset.out_obj,<-.<-.<-.external_edges.out_obj};\n");
    F77("      };\n");


    F77("      View { ViewUI { ViewPanel {\n");
    F77("       UI{ option { label = \"offset\"; }; };\n");
    F77("      };     };       };\n");


    F77("   };\n");
  }

  /*----------------------------------------*/
  /* [5] is porbe, but scene is edge secne  */
  /*----------------------------------------*/

  /*----------------------*/
  if( itemindex[6] == YES) {  /* vect */
    scene_no++;
    PUT(fp,"   GDM.Uscene3D Scene#%d {\n",scene_no);
    F77("      Top {\n");
    F77("         child_objs<NEportLevels={4,1}> => {\n");

    if(itemindex[3] == YES) { /* glyph is already exist */
      F77("            <-.<-.<-.vectglyph.out_obj,<-.<-.<-.external_edges.out_obj};\n");
    }
    else {
      F77("            <-.<-.<-.vectglyph.out_obj,<-.<-.<-.external_edges.out_obj};\n");
    }
    F77("      };\n");

    F77("      View { ViewUI { ViewPanel {\n");
    F77("       UI{ option { label = \"vectglyph\"; }; };\n");
    F77("      };     };       };\n");

    F77("   };\n");
  }

  F77("};\n");

  /*-----------------------------------------------------------*/


  F77("\n");
  F77("WORKSPACE_1.FeelMenu FeelMenu<NEx=11.,NEy=11>;\n");
  F77("MODS.edges edges<NEx=385.,NEy=77.> {\n");
  F77("   in_field => <-.FeelMenu.Feel.feelucd;\n");
  F77("};\n");
  F77("MODS.external_edges external_edges<NEx=539.,NEy=77.> {\n");
  F77("   in_field => <-.FeelMenu.Feel.feelucd;\n");
  F77("};\n");


  if(itemindex[0] == YES) {   /* isoline (NEx=11,NEy=165) */
    
    F77("MODS.extract_component select_iso <NEx=11,NEy=165> {\n");
    F77("   in_field =><-.FeelMenu.Feel.feelucd;\n");
    F77("};\n");
    
    F77("MODS.set_minmax minmax_iso          <NEx=11,NEy=198> {\n");
    F77("   in_field =><-.select_iso.out_fld;\n");
    F77("};\n");

    F77("MODS.isoline isoline                    <NEx=11,NEy=231>{\n");
    F77("   in_field =><-.minmax_iso.out_fld;\n");
    F77("};\n");

    F77("GEOMS.LegendVert isoline_legendv        <NEx=11,NEy=264>{\n");
    F77("   obj_in   =><-.isoline.out_obj;\n");
    F77("};\n");

  }

  if(itemindex[1] == YES) {   /* contr (NEx=161,NEy=165)*/

    F77("MODS.extract_component select_contr <NEx=161,NEy=165> {\n");
    F77("   in_field =><-.FeelMenu.Feel.feelucd;\n");
    F77("};\n");
    
    F77("MODS.set_minmax minmax_contr          <NEx=161,NEy=198> {\n");
    F77("   in_field =><-.select_contr.out_fld;\n");
    F77("};\n");

    F77("MODS.contour contour                      <NEx=161,NEy=231>{\n");
    F77("   in_field => <-.minmax_contr.out_fld;\n");
    F77("};\n");

    F77("GEOMS.LegendVert contr_legendv            <NEx=161,NEy=264>{\n");
    F77("   obj_in   =><-.contour.out_obj;\n");
    F77("};\n");
  }


  if(itemindex[2] == YES) {   /* surfplot (Nex=311,NEy=165)*/

    F77("MODS.extract_component select_surfplot <NEx=311,NEy=165> {\n");
    F77("   in_field =><-.FeelMenu.Feel.feelucd;\n");
    F77("};\n");
    
    F77("MODS.set_minmax minmax_surfplot          <NEx=311,NEy=198> {\n");
    F77("   in_field =><-.select_surfplot.out_fld;\n");
    F77("};\n");

    F77("MODS.surf_plot surf_plot                     <NEx=311,NEy=231>{\n");
    F77("   in_field => <-.minmax_surfplot.out_fld;\n");
    F77("};\n");

    F77("GEOMS.LegendVert surfplot_legendv            <NEx=311,NEy=264>{\n");
    F77("   obj_in   =><-.surf_plot.out_obj;\n");
    F77("};\n");
  }

  /*-----------------------*/
  if(itemindex[3] == YES) {   /* gradvect */

    /* Module gradient */

    F77("MODS.gradient gradient <NEx=461,NEy=165>{\n");
    F77("   in_field => <-.FeelMenu.Feel.feelucd;\n");
    F77("};\n");

    /* Module Arrow1 */

    F77("GEOMS.Arrow1 Arrow1<NEx=461,NEy=200>;\n");


    /* Module glyph for gradglyph*/
    
    F77("MODS.glyph gradglyph <NEx=461,NEy=235>{\n");
    F77("   in_field => <-.gradient.out_fld;\n");
    F77("   in_glyph => <-.Arrow1.out_fld;\n");
    F77("};\n");
  }


  /*-----------------------*/
  if(itemindex[4] == YES) {   /* offset */

    /* Module offset */

    F77("MODS.offset offset <NEx=11,NEy=300>{\n");
    F77("   in_field => <-.FeelMenu.Feel.feelucd;\n");
    F77("};\n");

  }

  /*-----------------------*/
  if(itemindex[5] == YES) {   /* probe */

    /* Module probe */

    F77("MODS.probe probe <NEx=461,NEy=550>{\n");
    F77("   in_field => <-.FeelMenu.Feel.feelucd;\n");
    F77("   in_pick  =><-.Uviewer3D.Scene_Editor.View_Editor.GDobj_sel.cur_obj;\n");
    F77("};\n");

  }

  /*-----------------------*/
  if(itemindex[6] == YES) {   /* vect */

    /* Module glyph */

    if(itemindex[3] == YES) { /* glyph is already exist */
      F77("MODS.glyph vectglyph <NEx=161,NEy=300>{\n");
      F77("   in_field => <-.FeelMenu.Feel.feelucd;\n");
      F77("   in_glyph => <-.Arrow1.out_fld;\n");
      F77("};\n");
    }

    else {

      F77("MODS.glyph vectglyph <NEx=161,NEy=300>{\n");
      F77("   in_field => <-.FeelMenu.Feel.feelucd;\n");
      F77("   in_glyph => <-.Arrow1.out_fld;\n");
      F77("};\n");
      
      /* Module Arrow1 */
      
      F77("GEOMS.Arrow1 Arrow1 <NEx=161,NEy=335>;\n");
    }
  }

  F77("\n};\n");

  fclose(fp);

  return;
}
