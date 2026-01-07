/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : check_funcs.hpp
 *  Date     : 2001/03/08
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CHECKFUNC_HEADER
#define FEM_CHECKFUNC_HEADER

template <class T> class list;
class SNunit;
class string;



// Variable is ... series.  defined in isDefined.cpp
int isCoordinate(const char *); 
int isCoordinate(string &);
int isCoordinateX(string &);
int isCoordinateY(string &);
int isCoordinateZ(string &);

int isNormalComponent(string &);
int isSystemNX(string &);        // for boundary integrand
int isSystemNY(string &);        // used in Expression_Infogenerate,
int isSystemNZ(string &);        // AddVariablePtr_Neumann

int isDefinedFEMVariable(string &);
int isDefinedScalarVariable(string &);
int isDefinedEWISEVariable(string &);
int isDefinedMaterialVariable(string &);

// Function
int isIntrinsicFunction(string &);         
int isDifferentialOperator1(string &);     // 1st order operators

// element type
int isEtypeName(string &);

// mesh block check
int mesh_check_dimension(list <void *> &);
int mesh_check_eval(list <void *> &);
int mesh_check_conflict(list <void *> &);
int mesh_point_conflict(list <void *> &);

// making geometry
int geometry_generate(list <void *> &);

// geometry to GeometryObject
void store_geometry_geometryObject(void);

// makeing GeometryObject
int geometryObject_check(list <SNunit *> &);
int geometryObject_generate(list <SNunit *> &);
int geom_materialRegion_check(list <SNunit *> &);
int geom_materialRegion_create(list <SNunit *> &);

// set dimension, mesh generator
int set_geometryObject_default(list <void *> &, list <SNunit *> &);

// COMMON ELEMENT&QUADRATURE  definition
int element_quadrature_check_conflict(list <void *> &,list <void *> &);


// ELEMENT definition
int element_check(list <void *> &);
int element_create(list <void *> &);

// Quadrature definition
int quadrature_check(list <void *> &);
int quadrature_create(list <void *> &);


// VAR block
int var_check_conflict(list <void *> &);
int var_check_defined(list <void *> &);
int var_check_initial(list <void *> &);// check initial value is num and set
int var_check_material(list <void *> &,list <SNunit *> &);
int user_func_check_create(list <void *> &);
int var_create(list <void *> &);

// VAR-GEOM check
int var_material_region_check(void);


// SCHEME block

int scheme_elementType_check(list <void *>&);     // for integral() normal
void scheme_elementType_create(list <void *>&);   // for integral() normal

int scheme_userfunc_arg_check(void);         // 2002/09/17
int scheme_pm_check(list <void *> &);
int scheme_label_if_check(list <void *> &);  // label related check
int scheme_if_check(list <void *>&);         // if expression check
int scheme_write_check(list <void *>&);      // write check
int scheme_parametric_check(list <void *> &);
int scheme_solve_check(list <void *> &);
int scheme_solve_geom_check(list <void *> &);
int scheme_assign_check(list <void *> &);
int scheme_io_check(list <void *> &);

int scheme_solve_create(list <void *> &);   // generate
int scheme_solve_geom_create(list <void *> &);
int scheme_assign_create(list <void *> &);
int scheme_write_create(list <void *>&);      // write check
int scheme_io_create(list <void *> &);
int scheme_label_if_create(list <void *> &);

// System functions
void SystemError_A(char *);  // without SNunit

void SystemErrorA(SNunit *,char *);
void SystemErrorAA(SNunit *,const char *,const char *);
void SystemErrorAAA(SNunit *,const char *,const char *,const char *);
void SystemErrorNameA( SNunit *,char *);
void SystemErrorStrA( SNunit *, string &, char *);
void SystemErrorAStr( SNunit *, char *,string &);
void SystemErrorAStrA( SNunit *,char *, string &, char *);
void SystemErrorNameNOA( SNunit *,int,char *);    // NameNO series of above
void SystemErrorANameA( SNunit *,char *,char *);
void SystemErrorAIA(SNunit *,char *,int , char *);
void SystemErrorANameStrA( SNunit *,string &,char *,char *);
void SystemErrorANameAStr( SNunit *,string &,char *,char *);
void SystemErrorANameADataA(SNunit *,char *,char *,char *);
void SystemWarningA(SNunit *,char *);
void SystemWarningANameA(SNunit *,char *,char *);

void SystemErrorAAAA(char *,char *,char *,char *);

#endif
