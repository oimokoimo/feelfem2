/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   mesh_comp.h
 *      Date:   1993/06/04 (Modified)
 *   
 *   Purpose:   mesh関係構文情報に関する構造体等定義ファイル
 *   Functions: 
 *   Caution:   このファイルより先にfeel_def.hをincludeすること
 *              
 */

/*----------------------*/
/* Mesh Data structures */
/*----------------------*/

/* point文の格納データstructure */

typedef struct _Point {
    char     *name;                /* Point name */
    double    x,y;     

    int       node_no;             /* final node number */
    int       mesh_no;             /* メッシュ生成時の一時的番号 */

    int       point_type;          /* 節点のタイプ */

    int       concern_regions;     /* number of concerning region */
                                   /* name of concerning name     */
                                   /* this array used in make_mesh_dat */
    char     *region_name[MAX_CONC_REGIONS];

    int      yylineno;

} Point ;


/* Refine factor structure */
typedef struct {
  char   *name;
  double  factor;
  int     no;          /* Initial mesh no. */
  int     yylineno;
} Refine;


/* line 文の格納データstructure */
typedef struct _Line {
    char     *name;     
    int       points;
    char     *compos[MAX_POINTS_IN_LINE];
    
    int yylineno;

} Line;

/* domain 文の格納データstructure */

typedef struct _Domain {
    char     *name;
    int       domain_no;              /* 登録順番号 */

    int       etype;                  /* 基本要素形状 (region_domain_check.c)*/

    int       regions;                /* domainを構成するregion数   */
    char    **region_name;            /* region名へのポインタ       */
    int      *region_no;

    int       edatno;                 /* 代表的なedatno */

    int yylineno;

} Domain;

/*---------------------------------------------------------------*/
typedef struct _Subdomain {
    char     *name;
    int       subdomain_no;              /* 登録順番号 */

    int       etype;                  /* 基本要素形状 (region_domain_check.c)*/

    int       regions;                /* domainを構成するregion数   */
    char    **region_name;            /* region名へのポインタ       */
    int      *region_no;
    int      *region_matno;           /* matno情報配列              */

    int       edatno;                 /* 代表的なEDAT番号           */
    int       ewise_nset_no;          /* EWISE変数のための節点集合配列番号 */

    int yylineno;

} Subdomain;

/*----------------------*/
typedef struct _Region {      /* Region is simply connected domain. */
    char     *name;
    int       region_no;      /* 登録順に番号付け                   */

    char     *method;         /* Mesh generation method */
    int       etype;          /* 基本要素形状 (region_domain_check.c)*/

    int       edges;    /* if simply connected, edges = 1 */
    int       points[MAX_BOUNDARIES];
    char     *compos[MAX_BOUNDARIES][MAX_POINTS_IN_EDGE];
    double    area;
    int       freedom;
    double    h_size;

    /* 以下のmatnoは、domain-regionの組みに対して定まる物であるから
       ここでは削除する、get_domain_region_noでmatnoを得るようにすること
       1994/01/10の変更 */

/*  int      matno;         */  /* 物質番号 */
/*  int      mesh_matno;    */  /* メッシュ生成時の一時的なmatno */


    int        nodes;                 /* number of nodes            */
    double    *node_x,*node_y;        /* node cordinates            */
    int        elements;              /* number of elements         */
    int       *element;               /* components of each element */

    int  yylineno;

} Region;


/*---------------------------------------------------------*/

extern Point  *get_nth_point_ptr();
extern Point  *get_point_ptr_by_name();
extern Line   *get_nth_line_ptr();
extern Line   *get_line_ptr_by_name();

extern Domain *get_nth_domain_ptr();
extern Domain *get_domain_ptr_by_name();

extern Subdomain *get_nth_subdomain_ptr();
extern Subdomain *get_subdomain_ptr_by_name();

extern Region *get_nth_region_ptr();
extern Region *get_region_ptr_by_name();
extern Region *get_region_ptr_by_domain_matno();
extern double  get_region_area();


/*-----------------------------------------*/
/* ../check/point_check.c で定義される関数 */
/*-----------------------------------------*/

extern int *get_mesh_point_no_order_ptr();
