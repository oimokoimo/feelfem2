/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   mesh_names.c
 *      Date:   1993/12/3
 *   
 *   Purpose:   形状定義に関する名前の一覧を作成する
 *   Functions: int get_mesh_name_type_by_name( name )  指定した名称の型を返す
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../feel_def/feel_msg.h"
#include "../system/system.h"

static char *mesh_name[MAX_MESH_NAMES];
static int   mesh_name_type[MAX_MESH_NAMES];
static int   mesh_names = 0;


void store_mesh_name( name , type )
     char *name;
     int   type;
{
    if(mesh_names == MAX_MESH_NAMES) {
	if(english_mesg) {
	    SystemAbort("Too many names in mesh define");
	}
	else {
	    SystemAbort("メッシュ定義の名前が多すぎる");
	}
    }
    
    mesh_name[mesh_names] = name;
    mesh_name_type[mesh_names] = type;

    mesh_names++;

    return;
}

int how_many_mesh_names()
{
    return(mesh_names);
}

/* 指定された名称が定義されていない場合、０を返す */
int get_mesh_name_type_by_name( name )
     char *name;
{
    int i;
    for(i=0;i<mesh_names;i++) {
	if(streq(name,mesh_name[i])) {
	    return(mesh_name_type[i]);
	}
    }

    return(0);
}
