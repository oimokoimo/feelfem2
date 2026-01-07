/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : check.cpp
 *  Date     : 2001/03/08
 *  Modified : 
 *  
 *  Purpose  : Check routine main
 *  
 */
#include <stream.h>
#include "feelfem.hpp"              // for command options
#include "parseExternals.hpp"       // for parser  trees
#include "check_funcs.hpp"          // this file is in check directory
#include "feelfuncs.hpp"


void check()
{


  NOTE("Welcome to check");

  //===============================================================
  // MESH block
  //===============================================================

  /* check dimension and point dimension matches */
  // set feelfemobj.spaceDimension
  int ret_mesh_check_dimension = mesh_check_dimension(parseMeshLst);

  /* check evaluation dependencies (assignment, point coordinate)
     and variable declaration (including duplication check)       */
  int ret_mesh_check_eval      = mesh_check_eval(parseMeshLst);

  /* check object name (point,edge,surface,volume,region,domain) conflict */
  int ret_mesh_check_conflict  = mesh_check_conflict(parseMeshLst);

  int ret_mesh_point_conflict;   // check the coordinates;
  if(ret_mesh_check_eval      == 0  &&
     ret_mesh_check_dimension == 0     ) {
    // check different points are really different points(coord check)
    ret_mesh_point_conflict = mesh_point_conflict(parseMeshLst);
  }


  if(ret_mesh_check_eval      != 0 ||
     ret_mesh_check_dimension != 0 || 
     ret_mesh_check_conflict  != 0 ||
     ret_mesh_point_conflict  != 0    ) {
    abortExit("Mesh block error.");
  }

  // make geometry data
  NOTE("goto geometry_generate");
  int ret_geometry_generate=geometry_generate(parseMeshLst);
  if(ret_geometry_generate != 0) {
    abortExit("Geometry error.");
  }

  // store geometry data into geometry object
  NOTE("goto store_geometry_geometryObject");
  store_geometry_geometryObject();

  // make geometryObject
  NOTE("goto geometryObject_check");
  int ret_geometryObject_check = geometryObject_check(parseGeomLst);
  if(ret_geometryObject_check != 0) {
    abortExit("GeometryObject check error");
  }

  NOTE("goto geometryObject_generate");
  int ret_geometryObject_generate = geometryObject_generate(parseGeomLst);
  if(ret_geometryObject_generate != 0) {
    abortExit("GeometryObject generate error");
  }

  NOTE("goto set_geometryObject_default");
  if(set_geometryObject_default(parseMeshLst,parseGeomLst) != 0) {
    abortExit("mesher must be explicitly specified.");
  }

  //material region 
  NOTE("goto geom_materialRegion_check");
  int ret_geom_materialRegion_check = geom_materialRegion_check(parseGeomLst);
  if(ret_geom_materialRegion_check != 0) {
    abortExit("geom Material region check failed.");
  }


  NOTE("goto geom_materialRegion_create");
  int ret_geom_materialRegion_create =geom_materialRegion_create(parseGeomLst);
  if(ret_geom_materialRegion_create != 0) {
    abortExit("geom Material region create failed.");
  }

  


  //===============================================================
  // Element block
  //===============================================================

  // check name conflict (element and quadrature)
  NOTE("goto element_quadrature_check_conflict");
  int ret_element_quadrature_conflict = 
    element_quadrature_check_conflict(parseElementLst,parseQuadratureLst);
  if(ret_element_quadrature_conflict) {
    abortExit("due to element name conflict.");
  }

  // element check
  NOTE("goto element_check");
  int ret_element_check = element_check(parseElementLst);
  if(ret_element_check) {
    abortExit("due to element check.");
  }

  NOTE("goto element_create");
  int ret_element_create = element_create(parseElementLst);

  //===============================================================
  // Quadrature block
  //===============================================================
  NOTE("goto quadrature_check");
  int ret_quadrature_check = quadrature_check(parseQuadratureLst);
  if(ret_quadrature_check != 0) {
    abortExit("due to quadrature check.");
  }

  NOTE("quadrature_create");
  int ret_quadrature_create = quadrature_create(parseQuadratureLst);
  if(ret_quadrature_create != 0) {
    abortExit("due to quadrature create.");
  }

  //===============================================================
  // VAR block (must be after element, quadrature (making feelfemobj)
  //===============================================================

  // check conflict
  NOTE("goto var_check_conflict");
  int ret_var_check_conflict = var_check_conflict(parseVarLst);
  if(ret_var_check_conflict) {
    abortExit("due to var block check.");
  }

  // check specified type is alredy defined, for vfem, fem and ewise variables
  NOTE("goto var_check_defined");
  int ret_var_check_defined = var_check_defined(parseVarLst);
  if(ret_var_check_defined) {
    abortExit("due to var block defined.");
  }

  NOTE("goto var_check_initial");
  int ret_var_check_initial = var_check_initial(parseVarLst);
  if(ret_var_check_initial) {
    abortExit("due to check initial values.");
  }

  NOTE("goto var_check_material");
  int ret_var_check_material = var_check_material(parseVarLst,
						  parseGeomLst);
  if(ret_var_check_material) {
    abortExit("due to check material vars.");
  }

  //user defined function
  NOTE("goto user_func_check_create");
  int ret_ufc = user_func_check_create(parseVarLst);
  if(ret_ufc) {
    abortExit("due to user func check create");
  }


  //make variable object 
  NOTE("goto var_create");
  int ret_var_create = var_create(parseVarLst);
  if(ret_var_create) {
    abortExit("due to var block check.");
  }

  // if there is material var, check all region is assigned
  NOTE("goto var_material_region_check");
  int ret_var_material_region_check = var_material_region_check();
  if( ret_var_material_region_check ) {
    abortExit("due to material/region check.");
  }


  //===============================================================
  // scheme block check
  //===============================================================

  // at first, etype must be defined.  (for default integral() functions)
  NOTE("goto scheme_elementType_check");
  int ret_scheme_elementType_check = 
    scheme_elementType_check(parseSchemeLst);
  if( ret_scheme_elementType_check ) {
    abortExit("due to scheme_elementType_check");
  }
  else {
    scheme_elementType_create(parseSchemeLst);
  }

  // user function check (check number of arguments is valid)
  NOTE("goto scheme_userfunc_arg_check");
  int ret_scheme_userfunc_arg_check =scheme_userfunc_arg_check();
  if(ret_scheme_userfunc_arg_check) {
    abortExit("due to user function argument mismatch");
  }


  // scheme program model check    pm stands for program model
  // if no program model is specified, default program model is applied.
  NOTE("goto scheme_pm_check");
  int ret_scheme_pm_check=scheme_pm_check(parseSchemeLst);
  if(ret_scheme_pm_check) {
    abortExit("due to scheme block programModel check.");
  }

  NOTE("goto scheme_label_if_check");
  int ret_scheme_label_if_check=scheme_label_if_check(parseSchemeLst);
  if(ret_scheme_label_if_check) {
    abortExit("due to scheme label check.");
  }

  NOTE("goto scheme_write_check");
  int ret_scheme_write_check=scheme_write_check(parseSchemeLst);
  if(ret_scheme_write_check) {
    abortExit("due to scheme write check.");
  }

  // parametric check  (Before assign check is necessary)
  NOTE("goto scheme_parametric_check");
  int ret_scheme_parametric_check = scheme_parametric_check(parseSchemeLst);
  if(ret_scheme_parametric_check) {
    abortExit("due to scheme block parametric check.");
  }

  // SOLVE check
  NOTE("goto scheme_solve_check");
  int ret_scheme_solve_check=scheme_solve_check(parseSchemeLst);
  if( ret_scheme_solve_check ) {
    abortExit("due to scheme block solve check.");
  }

  // SOLVE Boundary check  (generate BoundaryGeometry)
  NOTE("goto scheme_solve_geom_check");
  int ret_scheme_solve_geom_check = scheme_solve_geom_check(parseSchemeLst);
  if(ret_scheme_solve_geom_check) {
    abortExit("due to solve geometry check");
  }

  // Assignment check
  NOTE("goto assignment check");
  int ret_scheme_assign_check = scheme_assign_check(parseSchemeLst);
  if(ret_scheme_assign_check) {
    abortExit("due to assign check");
  }

  // Another scheme routine check
  NOTE("goto scheme_io_check");
  int ret_scheme_io_check = scheme_io_check(parseSchemeLst);
  if(ret_scheme_io_check) {
    abortExit("due to scheme io check.");
  }

  //===============================================================
  // scheme block create
  //===============================================================
  NOTE("goto scheme_solve_create");
  int ret_scheme_solve_create = scheme_solve_create(parseSchemeLst);
  assert(ret_scheme_solve_create == 0);

  NOTE("goto scheme_solve_geom_create");
  int ret_scheme_solve_geom_create = scheme_solve_geom_create(parseSchemeLst);
  assert(ret_scheme_solve_geom_create == 0);
  
  NOTE("goto scheme_solve_assign_create");
  int ret_scheme_assign_create = scheme_assign_create(parseSchemeLst);
  assert(ret_scheme_assign_create == 0);

  NOTE("goto scheme_io_create");
  int ret_scheme_io_create = scheme_io_create(parseSchemeLst);
  assert(ret_scheme_io_create == 0);

  NOTE("goto scheme_label_if_create");
  int ret_scheme_label_if_create = scheme_label_if_create(parseSchemeLst);
  assert(ret_scheme_label_if_create== 0);

  NOTE("goto scheme_write_create");
  int ret_scheme_write_create = scheme_write_create(parseSchemeLst);
  assert(ret_scheme_write_create == 0);

  return;
}
