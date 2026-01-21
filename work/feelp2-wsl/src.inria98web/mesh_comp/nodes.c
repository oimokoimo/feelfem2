/*
 *   feel p2  Finite Element Simulation Language Prototype Version 2
 *            ~      ~       ~          ~
 *      File: nodes.c
 *      Date: 1993/06/03
 *   
 * Last Modified : 1999/03/12  finalnodes (for AVS panel)
 *                             node number 
 *   
 *   Purpose: 各領域の節点数を定義するnodes文の処理
 *            
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/pop.h"    /* modernize 2026/01/21 */
#include "../system/system.h"

typedef struct Nodes_ {
    char *name;
    int   nodes;
} Nodes;

static Nodes node[MAX_NODES];
static int   nodes = 0;
static int   finalnodes = 0;

extern int web_exec;
extern int command_nodeset;


void nodes_st()
{
    int i;
    if(nodes == MAX_NODES) {
	if(english_mesg) {
	    SystemWarning("Too many nodes statements.");
	}
	else {
	    SystemWarning("nodes文が多すぎる");
	}

	pop(); pop();
	return;
    }

    node[nodes].nodes = PopInt();
    node[nodes].name  = PopString();


    if(command_nodeset >0) node[nodes].nodes = command_nodeset;
    if(web_exec) {
      if(node[nodes].nodes > 300) {
	node[nodes].nodes = 300;
      }
    }

    finalnodes = node[nodes].nodes;

    /* 節点数エラー検出 */
    if(node[nodes].nodes < 1) {
	
	if(english_mesg) {
	    SystemWarning_s("nodes %s statement has illegal nodes number.",
			    node[nodes].name);
	}
	else {
	    SystemWarning_s("nodes %s 文に不正な節点数を指定した",node[nodes].name);
	}

	

	FEEL_FreeMemory(node[nodes].name);
	return;
    }

    /* 重複定義エラー検出 */
    for(i=0;i<nodes;i++) {
	if(streq(node[i].name,node[nodes].name)) {

	    if(english_mesg) {
		SystemWarning_s("nodes %s declared again.",node[nodes].name);
	    }
	    else {
		SystemWarning_s("%sに対するnodes文は既に定義されている",
				node[nodes].name);
	    }



	    FEEL_FreeMemory(node[nodes].name);
	    return;
	}
    }

    nodes++;
    return;
}

int get_region_nodes( name )   /* 領域名からnodesによって指定された
				  節点数を返す関数                  */
     char *name;
{
    int i;
    for(i = 0; i< nodes ; i++ ) {
	if(streq(node[i].name,name)) {
	    return( node[i].nodes);
	}
    }
    return( 0 );               /* 定義されて無い場合は 0 を返す */
}

int get_final_nodes()    /* for avs */
{
  return (finalnodes);
}
