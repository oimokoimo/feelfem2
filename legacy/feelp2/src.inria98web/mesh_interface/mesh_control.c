/*
 * FEEL system Prototype Version 2
 * 
 * File     mesh_control.c
 * Made     1992/09/24
 * Modified 
 * Version  0.0
 *
 * Purpose: control file for making mesh data
 *
 *          the variable is flag to generate special mesh data
 */
#include "mesh_interface.h"

static int region_let_flag = NO;    /* regionwise let sentence */


mesh_control_region_let_on()
{
    region_let_flag = YES;
    return;
}

