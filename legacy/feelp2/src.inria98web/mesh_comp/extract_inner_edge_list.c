/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   extract_inner_edge_list.c
 *      Date:   1993/06/04 (Modified)
 *   
 *   Purpose:   region文、domain文での穴領域指定部分の処理
 *   Functions: extract_inner_edge_list()
 *              domain_st,region_stから呼ばれる
 *              
 */
#include "../feel_def/feel_def.h"
#include "../system/system.h"
#include "mesh_comp.h"

int extract_inner_edge_list( s , compos)
     char *s;
     char *compos[];
{
    int i;
    char *cp,*cpe;
    char inp[BUFSIZ];

    i = 0;
    cp = s+1;   /*   skip first '[' */

    cpe = cp;


    while(1) {
	while(*cpe != ',' && *cpe != ']') cpe++;
	
	if(*cpe == ']') {
	    *cpe = '\0';
	    sscanf(cp,"%s",inp);
	    compos[i] = MakeStringCopy(inp);
	    i++;
	    break;
	}
	else {
	    *cpe = '\0';
	    sscanf(cp,"%s",inp);
	    compos[i] = MakeStringCopy(inp);
	    i++;
	    cp = cpe+1;
	    cpe++;
	}
    }

    ReverseStringArray(i,compos);

    return(i);
}

	    
	

	
    

    



