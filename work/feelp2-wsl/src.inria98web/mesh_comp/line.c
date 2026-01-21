/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File:   line.c
 *      Date:   1993/06/03 (Modified)
 *   
 *   Purpose:   line文の処理
 *   Functions: line_st()
 *              how_many_lines()
 *              is_defined_line
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../system/system.h"
#include "mesh_comp.h"


static Line *line[MAX_LINES];
static int   lines = 0;

line_st(points)
     int points;
{
    int i;
    char *cp;
    
    if(lines == MAX_LINES) {
	if(english_mesg) {
	    SystemError("Too many edges specified.");
	}
	else {
	    SystemError("edge文が多すぎる");
	}


	for(i=0;i<points;i++) pop();   /* clean stack for point definitions */
	pop();                         /* clean stack for line name */

	return;
    }

    line[lines] = (Line *)FEEL_GetMemory( sizeof (Line) );


    for(i=0;i<points;i++) {
	line[lines]->compos[points-1-i] = PopString();
    }

    line[lines]->points = points;

    line[lines]->name   = PopString();


    if(get_mesh_name_type_by_name( line[lines]->name)) {
	SystemError_s("line name %s is already defined for other object's name.");
    }
    store_mesh_name( line[lines]->name , MESH_LINE );
    
    lines ++;
    return;
}



int how_many_lines()
{
    return(lines);
}

Line *get_nth_line_ptr( n )
     int n;
{
    if(n < 0 || n >= lines) {
	SystemAbort("get_nth_line_ptr ERROR");
    }

    return(line[n]);
}

Line *get_line_ptr_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<lines;i++) {
	if(streq(line[i]->name,name)) {
	    return(line[i]);
	}
    }
    
    SystemAbort("get_line_ptr_by_name:No such line");
}

