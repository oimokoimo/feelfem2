/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   get_mesh_data.c
 *      Date:   1993/12/06
 *   
 *   Purpose:   境界情報を配列に格納する
 *   Functions: 
 *              mesh_book_execから呼ぶ
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"
#include "../var_comp/var_comp.h"

void get_mesh_data()
{
    int i;
    FILE *fpr;
    char *cp;

    char buf[BUFSIZ];

    fpr = OpenFileToRead("MESH.FIN");
    
    while(fgets(buf,sizeof(buf),fpr)) {
	if(strindex(buf,"BOUNDARY")) {
	    get_boundary_info(fpr);
	}
    }
    fclose(fpr);
    return;
}

/*
 *  境界情報を読む
 *  実節点番号の代入 
 */
get_boundary_info( fp )
     FILE *fp;
{
    int i;
    int boundaries;
    int from,to;
    int points;
    int region_no;
    int *iptr;

    fscanf(fp,"%d",&boundaries);
    
    while(boundaries) {
	fscanf(fp,"%d %d %d %d",&from,&to,&points,&region_no);

	iptr = (int *)FEEL_GetMemory(sizeof(int) * points);
	
	for(i=0;i<points;i++) {
	    fscanf(fp,"%d",iptr+i);
	}

	/*----------------------------*/
	/* Boundary2D構造体に代入     */
	/* Point構造体にnode_noの設定 */
	/*----------------------------*/
	store_boundary_data(from,to,points,region_no,iptr);

/*
        DBGWRT:
	fprintf(stderr,"DBG:\n");
	fprintf(stderr,"boundaries = %d\n",boundaries);
	fprintf(stderr,"%d %d %d %d\n",from,to,points,region_no);

	for(i=0;i<points;i++) {
	    fprintf(stderr,"%d ",*(iptr+i));
	}
	fprintf(stderr,"\n");
*/

	boundaries--;
    }

    return;
}
