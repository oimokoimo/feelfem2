/*


 *  FEEL system   File geom2d.h
 *
 *  Definition file for 2 dimentional geometry functions
 *
 *  Made      1992/08/11
 *  Version   0.0
 *
 */

#define YES 1
#define NO  0

#define  MAX_POLYGON_NODE  1000



typedef struct _POINT {
    int     node;
    char   *name;
    double   x,y;
} POINT_ST;

typedef struct _POLYGON {
    int    n;
    double *x , *y;
} POLYGON_ST;

typedef struct _LINE {
    double x1,y1;
    double x2,y2;
} LINE_ST;

typedef struct _DOMAINST {
    char *name;
} DOMAIN_ST;



extern double sqrt();    
extern double get_polygon_area();
extern double get_triangle_area();    
extern double get_3points_angle();
