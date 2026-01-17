/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   make_feel_data_file.c 
 *      Date:   1993/11/24
 *      Modified: 1998/07/17  web extension
 *   
 *   Purpose:   feel処理系が読み込むデータファイルを作成する
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../solve_comp/solve_comp.h"
#include "../mesh_comp/mesh_comp.h"
#include "../var_comp/var_comp.h"

extern int feel_dim;
extern int web_mode;

void make_feel_data_file()
{
    int i;
    FILE *fpr,*fp;
    char *cp;

    char buf[BUFSIZ];

    int ndim,npmax,nedat,nodeset,numset,nip;
    int nvars_fem,nvars_ewise;
    int mode_output,mode_ex;
    int nsolve_edats;           /* solve文のための最大edat番号     */
    EWISE_type *ewise_type_ptr; /* 対応するElemDatの代表番号を得る */

    if(feel_dim != 2) {
      SystemAbort("make_feel_data_file is for 2D only.");
    }

    ndim = 2;                       /* 基本定数   */
    nodeset = current_nodesetno();  /* main/data_number.c内の関数 */
    numset  = 0;

    /* 要素節点データ数は、
     * solve文に関するelemdatはMESH.FINに、
     * ノイマン型境界条件は、MESH.FINの情報から、このルーチン群で作成する
     * current_edatno() はこの両者の合算になっているはず
     */

    nedat   = current_edatno();   

    /* nipはmesh生成時節点数 */
    nip         = how_many_points();
    nsolve_edats= how_many_nsolve_edats();
    
    mode_ex = 0;                    /* 実行モード */;
    mode_output = 0;

    nvars_fem   = how_many_fem_vars();
    nvars_ewise = how_many_ewise_types();
    
    /* npmaxの数を調べる為の先読み */
    fpr = OpenFileToRead("MESH.FIN");
    StoreDeletefile("MESH.FIN");

    while(fgets(buf,sizeof(buf),fpr)) {

	if(strindex(buf,"POINT")) {
	    fscanf(fpr,"%d",&npmax);
	}
    }
    fclose(fpr);

    
    fp = OpenFileToWrite(INPUT_FILE);
    fprintf(fp,"FEEL\n");
    fprintf(fp,"%8d%8d%8d%8d%8d%8d%8d\n"
	    ,ndim,npmax,nedat,nodeset,numset,nip,nsolve_edats);
    fprintf(fp,"%8d%8d\n",mode_ex,mode_output);
    fprintf(fp,"%8d%8d\n",nvars_fem,nvars_ewise);
    for(i=0;i<nvars_ewise;i++) {
	ewise_type_ptr = get_nth_ewise_type_ptr(i);

	fprintf(fp,"%8d%8d\n", 
		get_domain_edatno_by_name(ewise_type_ptr->domain_name),
		ewise_type_ptr ->points );

    }

    
    fpr = OpenFileToRead("MESH.FIN");

    
    while(fgets(buf,sizeof(buf),fpr)) {
	if(strindex(buf,"MESH")) {
	    make_feel_data_edat(fpr,fp);
	}

	if(strindex(buf,"POINT")) {
	    make_feel_data_point(fpr,fp);
	}
	
/*	if(strindex(buf,"BOUNDARY") {
	    make_feel_data_boundary(fpr,fp);
	}
*/
    }

    /*======================*/
    /* 境界条件データの作成 */
    /*======================*/
    make_boundary_data_for_bc_main( fp );  /* 境界条件のための境界データ作成 */

    make_boundary_plot_data_main( fp );    /* PLOT文のための境界データ作成 */
    
    make_ip_data( fp );                    /* mesh生成時節点番号と実節点番号
					      対応データ作成                */

    cp = MakeStringCopy(KEY_END);
    cp++;
    *(cp + strlen(cp) -1) = '\0';

    fprintf(fp,"%s\n",cp);
    fclose(fp);
    fclose(fpr);    /* win extension 1998/09/17 */
}


make_feel_data_edat(fpr,fp)
     FILE *fpr; /* 読み込み用 */
     FILE *fp;  /* 書き込み用 */
{
    char buf[BUFSIZ];

    int i,j;
    char *cp;
    
    int no,elements,nodes;
    int edatno;
    
    int ielem,matno;
    int dummy;
    
    ElemDat *edat_ptr;

    fscanf(fpr,"%d %d %d",&no,&elements,&nodes);

    cp = MakeStringCopy(KEY_EDAT);
    cp++;
    *(cp + strlen(cp) -1) = '\0';
    fprintf(fp,"%s\n",cp);

    /*===============================================================*/
    /* noはsolve文用メッシュデータの作成番号、ここから、edatnoを得る */
    /*===============================================================*/
    edat_ptr = get_nth_mesh_edat_ptr(no - 1);
    edatno = edat_ptr->edatno;


    if(web_mode) {  /* web extension */
      fprintf(fp,"%8d%8d%8d%8d\n",edatno,elements,nodes,is_rect()+3);
    }
    else {
      fprintf(fp,"%8d%8d%8d\n",edatno,elements,nodes);
    }
    for(i=0;i<elements;i++) {
	for(j=0;j<nodes;j++) {
	    fscanf(fpr,"%d",&ielem);
	    fprintf(fp,"%8d",ielem);
	}
	fscanf(fpr,"%d",&matno);
	fscanf(fpr,"%d",&dummy);
	fprintf(fp,"%8d\n",matno);
    }
    return;
}

make_feel_data_point(fpr,fp)
     FILE *fpr;
     FILE *fp;
{
    int i;
    int points;
    char *cp;

    int no;
    double x,y;
    
    fscanf(fpr,"%d",&points);

    cp = MakeStringCopy(KEY_NODE);
    cp++;
    *(cp + strlen(cp) -1) = '\0';
    fprintf(fp,"%s\n",cp);
    
    for(i=0;i<points;i++) {
	fscanf(fpr,"%lf",&x);
	fscanf(fpr,"%lf",&y);
	fscanf(fpr,"%d",&no);

	fprintf(fp,"%8d",no);
	fprintf(fp,"%12.5e%12.5e\n",x,y);
    }
    fprintf(fp,"       0\n");

    return;
}

