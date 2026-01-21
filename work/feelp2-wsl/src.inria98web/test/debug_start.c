/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: feel_exec.c
 *      Date: 1993/06/04
 *   
 *   Purpose: テストプログラム
 *            
 */
#include <stdio.h>
#include <stdlib.h>

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../mesh_comp/mesh_comp.h"
#include "../var_comp/var_comp.h"
#include "../system/system.h"
#include "../scheme_comp/scheme_comp.h"
#include "../solve_comp/solve_comp.h"


#include "../makefort77/Extern.h"

int strindex(char *,char *);
void show_element_structure();
void show_var_dat();
void scheme_data_debug();
void show_solve_statement();
void show_mesh_dat();
int how_many_points();
int how_many_lines();
int how_many_regions();
int how_many_domains();
int make_inp_dat_file();
int streq(char *,char*);
void get_point_xy_by_name(char *,double *, double *);
int get_region_nodes(char *);
int how_many_int_vars();
int how_many_double_vars();
int how_many_const_vars();
int how_many_fem_types();
int how_many_material_vars();
int how_many_ewise_types();
int how_many_schemes();
int how_many_solves();


void debug_start()
{
FILE *fp;
char buf[BUFSIZ];
    fp = fopen("DEBUG_MODE","r");
    if(fp == NULL) {
      fprintf(stderr,"FILE DEBUG_MODE CAN NOT BE FIND.\n");
      return;
    }
    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"yes")) {
       printf("DEBUG_MODE file 's setting IS NO, so no debug write.\n");
       return;
    } 

    fclose(fp);




    printf("come to debug_start()\n");
    show_element_structure();
    show_mesh_dat();
    show_var_dat();

    scheme_data_debug();
    show_solve_statement();
}



void show_mesh_dat()
{
    int i,j,k,max;
    Region *region;
    Domain *domain;
    Line   *line;
    Point  *point;
    
    max = how_many_points();
    printf("-----------\npoints = %d\n",max);
    for(i=0;i<max;i++) {
	point = get_nth_point_ptr(i);
	printf("name : %s\n",point->name);
	printf("x,y  : (%lf,%lf)\n",point->x,point->y);
    }

    max = how_many_lines();
    printf("-----------\nlines = %d\n",max);
    for(i=0;i<max;i++) {
	line = get_nth_line_ptr(i);
	printf("name : %s\n",line->name);
	printf("connect: ");
	for(j=0;j<line->points;j++) {
	    printf("%s",line->compos[j]);
	    if(j != line->points-1) printf("-");
	    else                    printf("\n");
	}
    }

    max = how_many_regions();
    printf("-----------\nregions = %d\n",max);
    for(i=0;i<max;i++) {
	region = get_nth_region_ptr(i);
	printf("name : %s\n",region->name);
	printf("connect: ");
	for(k=0;k<region->edges;k++) {
	    for(j=0;j<region->points[k];j++) {
		printf("%s",region->compos[k][j]);
		if(j != region->points[k]-1) printf("-");
		else                    printf("\n");
	    }
	}
    }


    
    max = how_many_domains();
    printf("-----------\ndomains = %d\n",max);
    for(i=0;i<max;i++) {
	domain = get_nth_domain_ptr(i);
	printf("name : %s\n",domain->name);
	printf("regions(%d) ",domain->regions);
	for(k=0;k<domain->regions;k++) {
	    char *reg_name;
	    reg_name = *(domain->region_name + k);
	    printf("[%s] ", reg_name);
	}
	printf("\n");
    }


    make_inp_dat_file();
}

static int   pts =   0;

int point_number( name )
     char *name;
{
    int i;
    static char *ptr[1000];


    for(i=0;i<pts;i++) {
	if(streq(name,ptr[i])) return(i);
    }
    ptr[pts] = MakeStringCopy(name);
    pts++;
    return (pts);
}


int make_inp_dat_file()
{
    int i,j,pts;
    FILE *fp;
    Region *region;
    double x,y;

    if(how_many_regions() != 1) return 0;
    region = get_nth_region_ptr( 0 );

    fp = fopen("inp.dat","w");
    if(fp == NULL) {fprintf(stderr,"cannot make inp.dat\n"); exit(1);}
    fprintf(fp,"%5d%5d\n",1,region->edges-1);  /* 外部、内部境界の数 */
    fprintf(fp,"%5d\n",region->points[0]);     /* 外部境界の点の数   */
    if(region->edges == 1) {
	fprintf(fp,"%5d\n",0);
    }
    else {
	for(i=1;i<region->edges;i++) {
	    fprintf(fp,"%5d",region->points[i]);
	}
	fprintf(fp,"\n");
    }

    for(i=0;i<region->points[0];i++) {
	fprintf(fp,"%5d",i+1);
    }
    fprintf(fp,"\n");

    pts = 0;
    for(i=0;i<region->edges;i++) {
	pts = pts + region->points[i];
    }

    fprintf(fp,"%5d%5d\n",pts,0);

    for(i=0;i<region->points[0];i++) {
	get_point_xy_by_name( region->compos[0][region->points[0]-1-i],
			     &x,&y);
	fprintf(fp,"%10.5lf%10.5lf\n",x,y);
    }

    for(i=1;i<region->edges;i++) {
	for(j=0;j<region->points[i];j++) {
	    get_point_xy_by_name( region->compos[i][j],
				 &x,&y);
	    fprintf(fp,"%10.5lf%10.5lf\n",x,y);
	}
    }

    pts = get_region_nodes( region->name );
    
    if(pts == 0) pts = DEFAULT_NODES;

    fprintf(fp,"%5d\n",pts);

    fclose(fp);

    /* graphics disabled
    system("/home/fujio/feel_p2/src/mesh_book/egmesh");
    system("/home/fujio/feel_p2/src/tool/showmesh_exec");
    */


}
	

void show_var_dat()
{
    int i,j,max,max2;
    Var *var_ptr;

    max =how_many_int_vars();
    printf("int 変数の数 %d\n",max);
    for(i=0;i<max;i++) {
	var_ptr = get_nth_int_ptr(i);
	printf("変数名 %s ",var_ptr->name);
	if(var_ptr->initial) {
	    printf("初期値 %s\n",var_ptr->val);
	}
	else {
	    printf("\n");
	}
    }

    max =how_many_double_vars();
    printf("double 変数の数 %d\n",max);
    for(i=0;i<max;i++) {
	var_ptr = get_nth_double_ptr(i);
	printf("変数名 %s ",var_ptr->name);
	if(var_ptr->initial) {
	    printf("初期値 %s\n",var_ptr->val);
	}
	else {
	    printf("\n");
	}
    }

    max =how_many_const_vars();
    printf("const 変数の数 %d\n",max);
    for(i=0;i<max;i++) {
	var_ptr = get_nth_const_ptr(i);
	printf("変数名 %s ",var_ptr->name);
	if(var_ptr->initial) {
	    printf("初期値 %s\n",var_ptr->val);
	}
	else {
	    printf("\n");
	}
    }

    max = how_many_fem_types();
    printf("fem 変数の数 %d\n",max);
    for(i=0;i<max;i++) {
	FEM_type *fem_ptr;
	fem_ptr = get_nth_fem_type_ptr(i);
	printf("変数名 %s ",fem_ptr->name);
	printf("変数タイプ %s ",fem_ptr->type);
	max2 =fem_ptr->restrictions;
	if(max2 != 0) {
	    printf("制約条件 ");
	    for(j = 0;j<max2;j++) {
		printf("[%s] ",*(fem_ptr->restrict_var + j));
	    }
	}
	printf("\n");
    }
    max = how_many_material_vars();
    printf("material 変数の数 %d\n",max);
    for(i=0;i<max;i++) {
	MATERIAL_var *material_ptr;
	var_ptr = get_nth_material_ptr(i);
	printf("変数名 %s ",var_ptr->name);
	material_ptr = (MATERIAL_var *)(var_ptr->val);
	printf("定義物質種数 : %d  ",material_ptr->materials);
	for(j=0;j<material_ptr->materials;j++) {
	    printf("[%d]=%lf ",j+1,*(material_ptr->val + j));
	}

	printf("\n");
    }

    max = how_many_ewise_types();
    printf("ewise 変数の数 %d\n",max);
    for(i=0;i<max;i++) {
	EWISE_type *ewise_ptr;
	ewise_ptr = get_nth_ewise_type_ptr(i);
	printf("変数名 %s ",ewise_ptr->name);
	printf("定義領域名 :%s",ewise_ptr->domain_name);

	max2 =ewise_ptr->points;
	if(max2 != 0) {
	    printf("指定節点 ");
	    for(j = 0;j<max2;j++) {
		printf("(%lf,%lf) ",ewise_ptr->r[j],ewise_ptr->s[j]);
	    }
	}
	else {
	    if(ewise_ptr -> quadrature != NULL) {
		printf("評価点に用いる積分点名称 :%s",ewise_ptr->quadrature);
	    }
	}
	printf("\n");
    }
}


void scheme_data_debug()
{
    int i,j,k,l;
    Scheme *var;
    int schemes;
    
    Goto  *goto_ptr;
    Label *label;
    Showvec *showvec;
    Contour *contour;
    Perspect *perspect;
    AVScontour *avscontour;
    Read  *read;
    Write *write;
    Expression *expr;

    char **char_ptrptr;


    schemes = how_many_schemes();

    for(i=0;i<schemes;i++) {
	var = get_nth_scheme_struct(i);

	switch(var->type) {
	  case GOTO:
	    goto_ptr = (Goto *)(var->ptr);
	    printf("%3d行 goto文\n     goto %s\n",goto_ptr->yylineno,goto_ptr->label);
	    break;

	  case LABEL:
	    label = (Label *)(var->ptr);
	    printf("%3d行 label文\n     label %s\n",label->yylineno,label->label);
	    break;
	    
	  case SHOWVEC:
	    showvec = (Showvec *)(var->ptr);
	    printf("%3d行 showvec文\n     showvec(%s,%s)\n",showvec->yylineno,
		   showvec->x,showvec->y);
	    break;

	  case CONTOUR:
	    contour = (Contour *)(var->ptr);
	    printf("%3d行 contour文\n     contour(%s)\n",contour->yylineno,
		   contour->var);
	    break;

	  case PERSPECT:
	    perspect = (Perspect *)(var->ptr);
	    printf("%3d行 perspect文\n     perspect(%s)\n",perspect->yylineno,
		   perspect->var);
	    break;

	  case AVS_CONTOUR:
	    avscontour = (AVScontour *)(var->ptr);
	    printf("%3d行 AVScontour文\n     avscontour(%s)\n",avscontour->yylineno,
		   avscontour->var);
	    break;

	  case READ:
	    read = (Read *)(var->ptr);
	    printf("%3d行 read文\n",read->yylineno);
	    char_ptrptr = read->var_name;
	    for(j=0;j<read->args;j++) {
		printf("     第%d 引き数  %s\n",j+1,*(char_ptrptr+j));
	    }
	    break;

	  case WRITE:
	    write = (Write *)(var->ptr);
	    printf("%3d行 write文\n",write->yylineno);
	    k = 0; l = 0;
	    expr = write->expr;
	    for(j=0;j<write->args;j++) {
		printf("     第%d 引き数  ",j+1);
		if(*((write->kind)+j) == EXPR) {
		    printf("数式引数 %s\n",(expr+k)->expr);
		    k++;
		}
		else {
		    printf("文字列   %s\n",*(write->string + l));
		    l++;
		}
	    }
	    break;

	  default:
	    printf("なんやねん。var->type = %d\n",var->type);
	    exit(1);
	}
    }


}


void show_solve_statement()
{
    int i,j,k,l;
    int solves;
    Solve *solve_ptr;
    SolveElement *solve_element_ptr;
    Equation   *equation_ptr;
    Expression   *expr_ptr;
    DirichletData *dirichlet_ptr;
    NeumannData *neumann_ptr;

    solves = how_many_solves();
    
    for(i=0;i<solves;i++) {
	printf("==========================\n");
	printf("第%d番目のsolve文\n",i+1);

	solve_ptr = get_nth_solve_ptr(i);

	printf("未知変数 %d :",solve_ptr->unknowns);
	
	for(j=0;j<solve_ptr->unknowns;j++) {
	    printf("%s ",*(solve_ptr->unknown_name + j));
	}
	printf("\n");

	printf("要素グループの数  %d\n",solve_ptr->solve_elements);
	printf("ディリクレ境界条件の数 %d\n",solve_ptr->d_conditions);
	printf("ノイマン境界条件の数 %d\n",solve_ptr->n_conditions);

	for(j=0;j<solve_ptr->solve_elements;j++) {
	    solve_element_ptr = *(solve_ptr->solve_elem_dat + j);
	    printf("---------------------\n");
	    printf("第%d要素グループ情報\n",j+1);
	    printf("方程式の数  %d\n",solve_element_ptr->equations);

	    switch(solve_element_ptr->type) {
	      case DIFFEQ:
		printf("偏微分方程式問題\n");
		break;
	      case WEAKEQ:
		printf("弱形式問題\n");
		break;
	      case FUNCTIONAL:
		printf("汎関数停留値問題\n");
		break;
	      default:
		printf("おーまいがぁ(show_solve)\n");
	    }

	    printf("既知fem変数    %d :",solve_element_ptr->fem_knowns);
	    for(k=0;k<solve_element_ptr->fem_knowns;k++) {
		printf("%s ",*(solve_element_ptr->fem_known_name + k));
	    }
	    printf("\n");

	    printf("既知ewise変数  %d :",solve_element_ptr->ewise_knowns);
	    for(k=0;k<solve_element_ptr->ewise_knowns;k++) {
		printf("%s ",*(solve_element_ptr->ewise_known_name + k));
	    }
	    printf("\n");

	    printf("既知scalar変数 %d :",solve_element_ptr->scalar_knowns);
	    for(k=0;k<solve_element_ptr->scalar_knowns;k++) {
		printf("%s ",*(solve_element_ptr->scalar_known_name + k));
	    }
	    printf("\n");
	    
	    for(k=0;k<solve_element_ptr->equations;k++) {
		equation_ptr = *((solve_element_ptr->eq_data)+k);

		
		printf("  No.%2d(領域項)[%2d]  ",k+1,equation_ptr->equation_terms);
		for(l=0;l<equation_ptr->equation_terms;l++) {
		    expr_ptr = *(equation_ptr->eq_term+l);
		    printf(": %s ",expr_ptr->expr);
		}
		printf("\n");

		printf("       (境界項)[%2d]  ",equation_ptr->boundary_terms);
		for(l=0;l<equation_ptr->boundary_terms;l++) {
		    expr_ptr = *(equation_ptr->bd_term+l);
		    printf(": %s ",expr_ptr->expr);
		}
		printf("\n");
	    }
	}
    }
}

