/*
 * FEEL system Prototype Version 2
 * 
 * File     mesh_interface.h
 * Made     1992/08/20
 * Modified 
 * Version  0.0
 *
 * Purpose:
 *
 */

#define MAX_FACELINES  100

#define YES 1
#define NO  0


typedef struct _FaceLine {
    int    regions;           /* number of regions */
    int    remake_flag;       /* if yes REMAKED */

    char   *from,*to;         /* point name  */
    double x1,y1,x2,y2;

    char   *first,*second;    /* region name */

    int    points;            /* it contains its both ends */

    int    nodeno_first;      /* from -> to   */
    int    nodeno_second;      /* to   -> from */

    double *x,*y;
    double len;

} FaceLine;


typedef struct _RegionData {
    char *name;                /* region name */

    int   points;              /* number of points (defined in point 
				  statement                          */
    char **point_name;

    int  *point_node;          /* node number of above points */

    int      nodes;            /* number of node   */
    double      *x;            /* its x coordinate */
    double      *y;            /* its y coordinate */

    int   elements;            /* number of element   */
    int   element_type;        /* element type        */
    int   e_nodes;             /* nodes in an element */
    
    int  *element;
    
} RegionData ;



extern FaceLine * get_nth_face_line_ptr();
extern FaceLine * get_face_line_ptr_by_2names();
extern double     get_region_mesh_size_by_name();

extern double     sqrt();


