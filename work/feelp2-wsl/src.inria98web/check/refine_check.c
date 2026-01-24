/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   refine_check.c
 *      Date:   1997/07/28
 *   
 *   Purpose:   refine statement check
 *   Functions: 
 *              
 *              
 */

#include "../feel_def/feel_def.h"
#include "../feel_def/feel_msg.h"
#include "../feel_def/basic_struct.h"
#include "../parallel/parallel.h"
#include "../system/system.h"

#include "../mesh_comp/mesh_comp.h"

void refine_check()
{
  int    i;
  int    refines;
  int    no;
  Point *point_ptr;
  Refine *refine_ptr, *get_nth_refine_ptr();
  int   *mesh_no_order_ptr,*get_mesh_point_no_order_ptr();


  refines = how_many_refine_points();

  if(refines >0 && bamg_mode != 1) {
    SystemError("refine statement can be used only in bamg mode.");
    return;
  }

  mesh_no_order_ptr = get_mesh_point_no_order_ptr();

  for(i=0;i<refines;i++) {
    refine_ptr = get_nth_refine_ptr(i);

    point_ptr  = get_point_ptr_by_name(refine_ptr->name);

    if(point_ptr == NULL) {
      SystemError_s("Specified point %s is not defined. (refine)",
		    refine_ptr->name);
    }
    else {
      no =  get_point_number_by_name(point_ptr->name);
      refine_ptr->no = point_nth_to_point_order_no(no);
    }

  }

  return;
}

