/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : feeldef.hpp
 *  Date     : 1999/07/20
 *  Modified : 1999/07/20
 *  
 *  Purpose  : General header file for feelfem system
 *  
 */

//#define FEELFEM_PREDEFINED_PDE    "/home/fujio/feelfem/lib/feelfem_basic.pde"

#define FEELFEM_PREDEFINED_PDE    "/usr/local/feelfem/feelfem_basic.pde"

#define DEFAULT_F90_COMPILER  "ifc"    // intel fortran compiler
#define DEFAULT_F77_COMPILER  "ifc"    // intel fortran compiler
#define DEFAULT_C_COMPILER    "gcc"    // GNU C compiler
#define DEFAULT_CPP_COMPILER  "g++"    // GNU C++ compiler

#define DEFAULT_MPIF90_COMPILER  "mpif90"  // mpif90 script
#define DEFAULT_MPIF77_COMPILER  "mpif77"  // mpif90 script
#define DEFAULT_MPIC_COMPILER    "mpicc"
#define DEFAULT_MPICPP_COMPILER  "mpic++"

// this is setting for aist
#define ADDITIONAL_AISTPCP90   "MPIROOT = /usr/local/mpich-1.2.2-ifc"





#define YES      1
#define OUI      1
#define YA       1               // used for error return in check routines
#define NO       0
#define NON      0
#define NICHT    0               // used for no error return in check routines

#define UNDEFINED_DOUBLE    911.0   // initialization value for error check
                                    // SNpoint.hpp
#define DUMMY_CODE          99999

// Limitations

#define GID_LIMIT_REDAT      1     // GiD_BAS.cpp, GiD_solv_dat.cpp
#define GID_LIMIT_REDATNO    1
#define GID_LIMIT_BEDATNO    1


// Languages (For messages)

#define ENGLISH  1
#define FRANCAIS 2
#define DEUTSCHE 3
#define NIHONGO  4
#define ESPANA   5


// Computer Languages
#define LANG_F77       1
#define LANG_F90       2
#define LANG_C         3
#define LANG_CPLUSPLUS 4
#define LANG_HPF       5
#define LANG_JAVA      6
#define LANG_BASIC     7


// FEELFEM basic default filenames

#define FEELFEM_SRC_FNAME  "feelfem.f"

// LIBRARIES
#define PCP90_SOURCE_NAME  "pcp90.f90"

#define FNAME_SOLV_DAT     "solv_dat"      // used in GiD_solv_dat.cpp



// PROGRAM MODEL type
#define PROC_DEFAULT_PROGRAM_MODEL   3     // default program model *oimo*

#define TYPE_FEELP2               1
#define TYPE_FEELP2DRAMA          2
#define TYPE_FEELFEM90            3        // P2 restriction
#define TYPE_FEELFEM90DRAMA       4        // P2 restriction
#define TYPE_FEELFEM90VEC         5        // vector processing with P2
#define TYPE_AISTPCP90            6        // Aist PCP model
#define TYPE_FEELFEM90SMPI        7        // P2 restriction, with host mpi

#define TYPE_FEELP2_AVS         501        // main as avs subroutine
#define TYPE_FEELFEM90_AVS      502        // main as avs subroutine

// SOLVER type (FOR SOLVE sentence)
#define TYPE_FEELP2SKYLINE      1
#define TYPE_FEELP2PCG          2
#define TYPE_FEELP2ACHIM        3         // file version
#define TYPE_FEELP2ACHIMLOC     4
#define TYPE_FEELFEM90PAMG      5
#define TYPE_FEELP2IWASHITA     6
#define TYPE_FEELFEM90PAMG81    7
#define TYPE_FEELFEM90SAMG20c   8         // Single AMG v20c
#define TYPE_FEELFEM90ACHIMCG   9
#define TYPE_FEELP2ACHIMCG     10         // use parallel code in single
#define TYPE_FEELFEM90VECPCG   11         // single vector
#define TYPE_FEELFEM90WASBLK   12         // washio-san's block solver
#define TYPE_FEELFEM90SKYLINE  13
#define TYPE_AISTPCP90IT4SLV   14         // aist-pcp  IT4SLV (iterative)
#define TYPE_FEELFEM90LUMPING  15
#define TYPE_FEELFEM90SMPIMUMPSCA  16 

// feelfem ProgramModel names
#define NAME_PM_FEELP2               "feelp2"
#define NAME_PM_FEELP2DRAMA          "feelp2drama"
#define NAME_PM_FEELFEM90            "feelfem90"
#define NAME_PM_FEELFEM90DRAMA       "feelfem90drama"
#define NAME_PM_UGF77                "ugf77"
#define NAME_PM_UGF90                "ugf90"
#define NAME_PM_UGCPP                "ugcpp"
#define NAME_PM_AISTPCP90            "aistpcp90"         // 2002/06/28
#define NAME_PM_FEELFEM90SMPI        "feelfem90smpi"     // 2003/01/04

// General name (Used for default solver)
#define NAME_LIB_SKYLINE             "skyline"
#define NAME_LIB_AMG                 "amg"
#define NAME_LIB_PCG                 "pcg"
#define NAME_LIB_BICGSTAB            "bicgstab"
#define NAME_LIB_LUMPING             "lumping"
#define NAME_LIB_MUMPS               "mumps"


// Special name for solvers (Not for the default...)
#define NAME_LIB_ASLPCG              "aslpcg"
#define NAME_LIB_ACHIMFILE           "achimfile"
#define NAME_LIB_GMDAMG              "gmdamg"
#define NAME_LIB_IWASHITA            "iwashita"
#define NAME_LIB_MUMPS               "mumps"
#define NAME_LIB_IT4SLV              "it4slv"
#define NAME_LIB_MUMPSCA             "mumpsca" // centralized assembled matrix


// Name for 
#define NAME_MESHER_BAMG             "bamg"
#define NAME_MESHER_GID              "gid"

// FEELFEM Scheme type definitions
#define SC_TYPE_SOLVE        1
#define SC_TYPE_LET_FEM      2
#define SC_TYPE_LET_EWISE    3
#define SC_TYPE_LET_SCALAR   4


// FEELFEM ELEMENT type             // must not be -1, -1 used as error
#define ELEMENT_TYPE_POINT    1
#define ELEMENT_TYPE_LINE     2
#define ELEMENT_TYPE_TRI      3
#define ELEMENT_TYPE_RECT     4
#define ELEMENT_TYPE_TETRA    5
#define ELEMENT_TYPE_CUBE     6

#define ETYPE_POINT_NAME   "point"
#define ETYPE_LINE_NAME    "line"
#define ETYPE_TRI_NAME     "tri"
#define ETYPE_RECT_NAME    "rect"
#define ETYPE_TETRA_NAME   "tetra"
#define ETYPE_CUBE_NAME    "hex"

// parametric element (Configure/Configure_Parametric.cpp)
#define DEFAULT_PARAMETRIC_ELEMENT_POINT    "n/a"
#define DEFAULT_PARAMETRIC_ELEMENT_LINE     "L1"
#define DEFAULT_PARAMETRIC_ELEMENT_TRI      "P1"
#define DEFAULT_PARAMETRIC_ELEMENT_RECT     "Q1"
#define DEFAULT_PARAMETRIC_ELEMENT_TETRA    "T1"
#define DEFAULT_PARAMETRIC_ELEMENT_CUBE     "C1"

// FEELFEM SYSTEM VARIABLES (used in element defition, boundary condition...)
#define NAME_COORD_X           "x"
#define NAME_COORD_Y           "y"
#define NAME_COORD_Z           "z"

// caution: independently defined in check/isDefined.cpp
#define NAME_NORMAL_X          "nx"   
#define NAME_NORMAL_Y          "ny"
#define NAME_NORMAL_Z          "nz"

#define NAME_TANGENTIAL_X_2D   "tx"
#define NAME_TANGENTIAL_Y_2D   "ty"
#define NAME_TANGENTIAL_Z_2D   "tz"

#define NAME_TANGENTIAL_X_3D1  "t1x"
#define NAME_TANGENTIAL_Y_3D1  "t1y"
#define NAME_TANGENTIAL_Z_3D1  "t1z"

#define NAME_TANGENTIAL_X_3D2  "t2x"
#define NAME_TANGENTIAL_Y_3D2  "t2y"
#define NAME_TANGENTIAL_Z_3D2  "t2z"

#define TYPE_DIFF_ZERO      0
#define TYPE_DIFF_X         1
#define TYPE_DIFF_Y         2
#define TYPE_DIFF_Z         3
#define TYPE_DIFF_XX        4
#define TYPE_DIFF_YY        5
#define TYPE_DIFF_ZZ        6
#define TYPE_DIFF_XY        7
#define TYPE_DIFF_YZ        8
#define TYPE_DIFF_ZX        9



// FEELFEM Variable Type varType definitions
#define VAR_FEM       1
#define VAR_VFEM      2           // add (2001/03/29) may cause .....
#define VAR_EWISE     3
#define VAR_EWISE_A   4           // with attribute
#define VAR_DOUBLE    5
#define VAR_INT       6
#define VAR_CONST     7
#define VAR_MATERIAL  8           // add(2002/08/29)

//for Element::elementType
#define FEM_TYPE_NODAL           1
#define FEM_TYPE_HELMITE         2
#define FEM_TYPE_EDGE            3
#define FEM_TYPE_FACE            4

//for Element Interpolation type
#define INTERP_TYPE_NODAL        1
#define INTERP_TYPE_DX           2
#define INTERP_TYPE_DY           3
#define INTERP_TYPE_DZ           4
#define INTERP_TYPE_DN           5     // 2-dimensional???

#define INTERP_NAME_NODAL        "nodal"
#define INTERP_NAME_DX           "dx"
#define INTERP_NAME_DY           "dy"
#define INTERP_NAME_DZ           "dz"
#define INTERP_NAME_DN           "dn"  // 2-dimensional???

// for Assignment
// value for SNassignment::integralType 
#define ASSIGNMENT_TYPE_ORIGINAL         0   
#define ASSIGNMENT_TYPE_INTEGRAL        10   // identifier=integral(expr);
#define ASSIGNMENT_TYPE_BINTEGRAL       11   // identifier=bintegral(expr);
#define ASSIGNMENT_TYPE_MAX             12
#define ASSIGNMENT_TYPE_MIN             13


// value for Assign::geometryType
#define ASSIGN_TYPE_NORMAL      1     // no geometry information needed
#define ASSIGN_TYPE_ELEM        2     // over element
#define ASSIGN_TYPE_NSET        3     // over nodes
#define ASSIGN_TYPE_NODE        4     // at a specific point
#define ASSIGN_TYPE_INTEGRAL    5     // over element
#define ASSIGN_TYPE_BINTEGRAL   6

#define AS_VAR_TYPE_SCALAR      1     // scalar, 
#define AS_VAR_TYPE_INTEGER     1     // scalar, integer (Not use integer info)
#define AS_VAR_TYPE_DOUBLE      1     // scalar, double  (Not use double  info)
#define AS_VAR_TYPE_EWISE_M     3     // ewise,  material
#define AS_VAR_TYPE_EWISE_G     4     // ewise,  gauss point
#define AS_VAR_TYPE_EWISE_I     5     // ewise,  integerpolation
#define AS_VAR_TYPE_FEM_NODE    6     // fem,    node based 
#define AS_VAR_TYPE_FEM_HELMITE 7     // fem,    helmite
#define AS_VAR_TYPE_VFEM_V      8     // vfem,   variant
#define AS_VAR_TYPE_VFEM_CV     9     // vfem,   contravariant
#define AS_VAR_TYPE_DOUBLE_INTEGRAL  10
#define AS_VAR_TYPE_DOUBLE_BINTEGRAL 11
#define AS_VAR_TYPE_DOUBLE_MAX       12
#define AS_VAR_TYPE_DOUBLE_MIN       13

// INTERPOLATION TYPE
//#define INTERPOLATION_UNKNOWN 0
//#define INTERPOLATION_NODAL   1
//#define INTERPOLATION_DX      2
//#define INTERPOLATION_DY      3
//#define INTERPOLATION_DZ      4
//#define INTERPOLATION_DN      5

//for Variable::ewiseType
#define EWISE_TYPE_MATERIAL      1   // constant in element
#define EWISE_TYPE_INTERPOLATION 2   // element
#define EWISE_TYPE_GAUSSPOINT    3   // quadrature


// Parameter flag for Parallel computation
#define MY_ELEMENT    1
#define OTHER_ELEMENT 2


// Default Parameters
#define FEEL_MAX_P2   "10000000"
#define FEEL_MAX_PROCS     "256"

#define DEFAULT_DIMENSION     2
#define DEFAULT_VERTICES    500
#define DEFAULT_NINTERVALS_FOR_PEDGE   100    // to evaluation for xmin,xmax 
                                              // on pedge (used in SNpedge)

#define DEFAULT_STRING   "default"         // used in SNsolve constructor
                                           //  for solverName, quadratureName
    
#define PEDGE_GENERATE_MINRATE   0.95
#define PEDGE_GENERATE_MAXRATE   1.05
#define PEDGE_GENERATE_MAX_FAIL  100
        
// 
#define FNAME_FEELP2DRAMA_MAIN     "feelfem.f"
#define FNAME_FEELFEM90DRAMA_MAIN  "feelfem.f90"


#define SRCTYPE_SYSTEM    1
#define SRCTYPE_SOLVER    2


// Platforms
#define Linux      0
#define Windows    1
#define Irix       2
#define Aix        3
#define HPUX       4
#define SXUX       5
#define Solaris    6
#define Linux64    7
#define Irix64     8
#define Solaris64  9
#define Windows64 10


// default value is set in parser/feelfem_extern_vars.cpp
// external declaration in feelfem.hpp
#define OPTION_MESHONLY             "-meshonly"    

// for web service
#define OPTION_WEB                  "-web"

// debug routine added into generated program code
#define OPTION_WRTDEBUGCODE         "-wrtdebugcode"

// debug for developer
#define OPTION_DEBUG                "-debug"
#define OPTION_DEBUG_FULL           "-fulldebug"
#define OPTION_DISPDEBUG            "-dispdebug"


#define DEBUG_MSG_NORMAL    1       // debug to detect the fault point
#define DEBUG_MSG_MEDIUM    5       // debug to follow the proccess
#define DEBUG_MSG_FULL     10       // debug for development


// 2D & 3D mesh generator
#define MESH_GENERATOR_BAMG 1
#define MESH_GENERATOR_GID  2



// Mesh generator related constant variable
#define BAMG_GEOMETRY_FILENAME      "bamg.geom"
#define BAMG_MESH_FILENAME          "bamg.mesh"


// related to makefile 

#define MAKEFILE_NAME               "Makefile.feelfem"
#define FEELFEM_EXEC_NAME           "feelgo"

// GiD problemtype
#define DEFAULT_GOBJ_PROBLEM_NAME   "feelfem"

// Linkage level (For making 'makefile')
#define OBJLEVEL_BASIC                   1     // LINKLEVEL   1- 29
#define OBJLEVEL_LIBRARY                 2     // LINKLEVEL  30- 49
#define OBJLEVEL_MODEL                   3     // LINKLEVEL  50- 99
#define OBJLEVEL_PROBLEM                 4     // LINKLEVEL 100-999
#define OBJLEVEL_MAIN                    5     // LINKLEVEL    1000

#define UPTO_OBJLEVEL_BASIC             29     // LINKLEVEL   1- 29
#define UPTO_OBJLEVEL_LIBRARY           49     // LINKLEVEL  30- 49
#define UPTO_OBJLEVEL_MODEL             99     // LINKLEVEL  50- 99
#define UPTO_OBJLEVEL_PROBLEM          999     // LINKLEVEL 100-999
#define UPTO_OBJLEVEL_MAIN            1000     // LINKLEVEL    1000


#define LINKLEVEL_USERFUNC               5
#define LINKLEVEL_LIBRARY                3
#define LINKLEVEL_LIBRARY2               9
#define LINKLEVEL_ESET                 100
#define LINKLEVEL_ECAL                 150
#define LINKLEVEL_ELEM                 200
#define LINKLEVEL_DCOND                300
#define LINKLEVEL_NCOND                300
#define LINKLEVEL_EDEV                 300
#define LINKLEVEL_SUBSOLVE_DEPENDENT   300
#define LINKLEVEL_LIBRARY_DEPENDENT    300
#define LINKLEVEL_SOLVE                500

#define LINKLEVEL_COASSIGN             550
#define LINKLEVEL_ASSIGN               600
#define LINKLEVEL_OUTPUT               600


#define LINKLEVEL_COROUTINE_MAIN       900
#define LINKLEVEL_MAIN                1000


// Allocation report
#define TYPE_INTEGER4                    1
#define TYPE_REAL4                       2
#define TYPE_REAL8                       3
#define TYPE_COMPLEX4                    4
#define TYPE_COMPLEX8                    5


// Syntax class 

// GEOM block
#define SN_GEOMMESHER                 8001
#define SN_GEOMDIMENSION              8002
#define SN_GEOMPROBLEM                8003
#define SN_GEOMPOINT                  8004
#define SN_GEOMEDGE                   8005
#define SN_GEOMSURFACE                8006
#define SN_GEOMREGION                 8007
#define SN_GEOMMATERIALREGION         8008

// MESH block
#define SN_DIMENSION                  1001   // sentence
#define SN_POINT                      1002
#define SN_EDGE                       1003
#define SN_PEDGE                      1004
#define SN_REGION                     1005
#define SN_DOMAIN                     1006
#define SN_VERTICES                   1007

#define SN_MESHDOUBLEVAR              1011
#define SN_MESHASSIGNMENT             1012

// ELEMENT definition
#define SN_ELEMENT                    1200 
#define SN_ELEMENTDOUBLEVAR           1201
#define SN_ELEMENTASSIGNMENT          1202
#define SN_ELEMENTINTP                1203

// QUADRATURE definition
#define SN_QUADRATURE                 1210
#define SN_QUADRATUREDOUBLEVAR        1211
#define SN_QUADRATUREASSIGNMENT       1212
#define SN_QUADRATUREGAUSSP           1213

// VAR block
#define SN_DOUBLEVAR                  1101
#define SN_INTVAR                     1102
#define SN_CONSTVAR                   1103
#define SN_FEMVAR                     1104
#define SN_VFEMVAR                    1105
#define SN_EWISEVAR                   1106
#define SN_MATERIALVAR                1107
#define SN_FUNCTIONDEF                1108


#define SN_PROGRAMMODEL               2001   // sentence
#define SN_ASSIGNMENT                 2002
#define SN_ASSIGNMENT_NORMAL             0
#define SN_ASSIGNMENT_AT                 1
#define SN_ASSIGNMENT_ON                 2
#define SN_ASSIGNMENT_IN                 3
#define SN_ASSIGNMENT_WHERE              4

#define SN_LABEL                      2003
#define SN_PARAMETRIC                 2004
#define SN_IF                         2005
#define SN_ELEMENTTYPE                2006

#define SN_SOLVE                      3000
#define SN_SOLVEQUADRATURE            3001   // solve block
#define SN_SOLVESOLVER                3002
#define SN_SOLVENONLINEAR             3003
#define SN_WEQTERM                    3004   // integrand of weak formulation
#define SN_WEQTERMS                   3005   // expression of weqTerm-s
#define SN_SOLVEWEQ                   3006
#define SN_SOLVEDIRICHLET             3007
#define SN_SOLVENEUMANN               3008
#define SN_SOLVENEUMANNPAIRS          3009
#define SN_SOLVEPARAMETRIC            3010   // for transformation

#define SN_OPTION                     4000

#define SN_PERSPECT                   4100
#define SN_OUTPUT                     4101   // general output routine
#define SN_WRITE                      4102



#define SN_DOUBLE                      101   // element in expr
#define SN_INT                         102   // element in expr
#define SN_SYMBOL                      103
#define SN_FUNCTION                    104
#define SN_BRACKET                     105
#define SN_EXPRLIST                    106
#define SN_IDENTIFIERLIST              107
#define SN_STRING                      108    // for write statement(02/11/22)
#define SN_EXPR                        109    // for write statement(02/11/22)


#define SN_XOR                         201
#define SN_OR                          202
#define SN_AND                         203
#define SN_EQUAL                       204
#define SN_NEQUAL                      205
#define SN_GE                          206
#define SN_GT                          207
#define SN_LE                          208
#define SN_LT                          209

#define SN_PLUS                        251
#define SN_SUB                         252
#define SN_MUL                         253
#define SN_DIV                         254

#define SN_MINUS                       275

// Geometry
#define TYPE_POINT_NORMAL                1
#define TYPE_POINT_PARAMETRICEDGE        2    // used SNpedge

#define TYPE_EDGE_NORMAL                 1
#define TYPE_EDGE_PARAMETRIC             2

#define TYPE_POLYGON_NORMAL              1
#define TYPE_POLYGON_HOLE                2

// GeometryObject

#define GOBJ_POINT                       1
#define GOBJ_EDGE                        2
#define GOBJ_SURFACE                     3
#define GOBJ_VOLUME                      4

#define GOBJ_REGION                      5

#define BGEOM_DIRICHLET                  1
#define BGEOM_NEUMANN                    2


// Solve
#define TYPE_REGIONAL_INTEGRAND          1    // Used in weqTerm
#define TYPE_BOUNDARY_INTEGRAND          2    // Used in weqTerm

#define TYPE_QUADRATURE_DEFAULT          0    // use default quadrature
#define TYPE_QUADRATURE_SPECIFIED        1    // quadrature specified

// default quadrature rule
#define DEFAULT_QUADRATURE_LINE   "gauss3"
#define DEFAULT_QUADRATURE_TRI    "tri4"
#define DEFAULT_QUADRATURE_RECT   "gauss3x3"
#define DEFAULT_QUADRATURE_TETRA  "tet2"
#define DEFAULT_QUADRATURE_CUBE   "oimocube"

// default boundary quadrature rule
#define DEFAULT_BOUNDARY_QUADRATURE_LINE   "n/a"
#define DEFAULT_BOUNDARY_QUADRATURE_TRI    "gauss3"
#define DEFAULT_BOUNDARY_QUADRATURE_RECT   "gauss3"
#define DEFAULT_BOUNDARY_QUADRATURE_TETRA  "tri4"
#define DEFAULT_BOUNDARY_QUADRATURE_CUBE   "gauss3x3"

// Variable name length
#define MAX_VARNAME_LENGTH             128
#define VARIABLE_TERMCONVERT_BUFSIZ    256

// Ginac buffer
#define MAX_EXPRPRINT_BUF             4096
#define MAX_FORMULA_BUF               8192

#define EXPRPRINT_NORMAL                 0
#define EXPRPRINT_SIMPLE                 3    // with smaller letters (for GiD)
#define EXPRPRINT_REPLACE_EVAL           1    // ptr1 is list<string>*ptr;
#define EXPRPRINT_REPLACE_EVALPAIR       2    // used for point coordinate eval
                                              // ptar is ptrList <evalPair>

#define REPLACE_EVAL_HEADER_LENGTH       1    // a01 the length of 'a'
#define REPLACE_EVAL_NUMBER_LENGTH       2    // a01 the length of '01'

// GiNaC ginac related constants
#define MAX_GINAC_VARIABLES             12

#define ERROR_EVALVAL                 -999

// User functions (arguments must be 1 to 3)
#define MAX_ARGS_FOR_USERFUNC            3
#define MAX_USER_FUNCTIONS1              5
#define MAX_USER_FUNCTIONS2              5
#define MAX_USER_FUNCTIONS3              5


// LIBS arguments for Makefile

#define LIB_FOR_FEELFEM90SMPIMUMPSCA "-L/usr/local/lib -ldmumps /usr/local/lib/libscalapack.a /usr/local/lib/blacs_MPI-LINUX-0.a  /usr/local/lib/blacsF77init_MPI-LINUX-0.a  /usr/local/lib/blacs_MPI-LINUX-0.a  /usr/local/lib/blacsF77init_MPI-LINUX-0.a  /usr/local/lib/libscalapack.a -lf77blas -latlas -L/usr/local/mpich/lib/ -lmpichf90 -lmpich /usr/intel/ia32/lib/libPEPCF90.a -lpord"

