/*
 * prototypes for scheme_comp.c
 *
 * 2026/01/24 modernize
 * 
 *
 */

#include "../scheme_comp/scheme_comp.h"

void label_fort77(FILE *,void *);
void goto_fort77(FILE *,void *);
void read_fort77(FILE *,void *);
void write_fort77(FILE *,void *,int);
void solve_fort77(FILE *,void *);
typedef struct _Contour Contour;
void contour_fort77(FILE *,Contour *);
typedef struct _Displacement Displacement;
void displacement_fort77(FILE *,Displacement *);
void perspect_fort77(FILE *,Displacement *);
void showvec_fort77(FILE *,void *);
void showvec_file_fort77(FILE *,void *);
void contour_file_fort77(FILE *,Contour *);
void plot_file_fort77(FILE *,void *);
void xplot_fort77(FILE *,void *);
void time_plot_file_fort77(FILE *,void *);
void let_fort77(FILE *,void *);
void norm_fort77(FILE *,void *);
void if_fort77(FILE *,IFblock *);

typedef struct _Adaptmesh Adaptmesh;
void adaptmesh_fort77( FILE * ,  Adaptmesh * );
