/***********************************************************************
*                                                                      *
* viewvect.c ver 1.0                                                   *
* Copy rights - all rights reserved by NEC Cooroperation 1994.4.1      *
*                                                                      *
************************************************************************/

#include "view.h"

#define VECT_ZERO       1.0e-01
#define VECT_MIN_SIZE   1.0e-02

int    ViewVector(vt,len,rx,ry,rz)
Vpoint *vt;
float  len,*rx,*ry,*rz;
{
    double   l,m,n;

    l = (double)(vt->x) / len;
    m = (double)(vt->y) / len;
    n = (double)(vt->z) / len;

    if (fabs(l) < VECT_ZERO) l = 0.0;
    if (fabs(m) < VECT_ZERO) m = 0.0;
    if (fabs(n) < VECT_ZERO) n = 0.0;

    if (fabs(l) < VECT_ZERO && fabs(m) < VECT_ZERO && n > 0.0) {
        *rx =   0.0;
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(l) < VECT_ZERO && fabs(m) < VECT_ZERO && n < 0.0) {
        *rx =   VIEW_PI;
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(l) < VECT_ZERO && fabs(n) < VECT_ZERO && m > 0.0) {
        *rx = - VIEW_PI / 2.0;
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(l) < VECT_ZERO && fabs(n) < VECT_ZERO && m < 0.0) {
        *rx =   VIEW_PI / 2.0;
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(m) < VECT_ZERO && fabs(n) < VECT_ZERO && l > 0.0) {
        *rx =   0.0;
        *ry =   VIEW_PI / 2.0;
        *rz =   0.0;
    }else if (fabs(m) < VECT_ZERO && fabs(n) < VECT_ZERO && l < 0.0) {
        *rx =   0.0;
        *ry = - VIEW_PI / 2.0;
        *rz =   0.0;
    }else if (fabs(l) < VECT_ZERO && m > 0.0 && n > 0.0) {
        *rx = - acos(fabs(n) / sqrt(m * m + n * n));
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(l) < VECT_ZERO && m < 0.0 && n > 0.0) {
        *rx =   acos(fabs(n) / sqrt(m * m + n * n));
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(l) < VECT_ZERO && m > 0.0 && n < 0.0) {
        *rx =   acos(fabs(n) / sqrt(m * m + n * n)) + VIEW_PI;
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(l) < VECT_ZERO && m < 0.0 && n < 0.0) {
        *rx = - acos(fabs(n) / sqrt(m * m + n * n)) + VIEW_PI;
        *ry =   0.0;
        *rz =   0.0;
    }else if (fabs(m) < VECT_ZERO && l > 0.0 && n > 0.0) {
        *rx =   0.0;
        *ry =   acos(fabs(n) / sqrt(l * l + n * n));
        *rz =   0.0;
    }else if (fabs(m) < VECT_ZERO && l < 0.0 && n > 0.0) {
        *rx =   0.0;
        *ry = - acos(fabs(n) / sqrt(l * l + n * n));
        *rz =   0.0;
    }else if (fabs(m) < VECT_ZERO && l > 0.0 && n < 0.0) {
        *rx =   0.0;
        *ry = - acos(fabs(n) / sqrt(l * l + n * n)) + VIEW_PI;
        *rz =   0.0;
    }else if (fabs(m) < VECT_ZERO && l < 0.0 && n < 0.0) {
        *rx =   0.0;
        *ry =   acos(fabs(n) / sqrt(l * l + n * n)) + VIEW_PI;
        *rz =   0.0;
    }else if (fabs(n) < VECT_ZERO && l > 0.0 && m > 0.0) {
        *rx =   0.0;
        *ry =   VIEW_PI / 2.0;
        *rz =   acos(fabs(l) / sqrt(l * l + m * m));
    }else if (fabs(n) < VECT_ZERO && l < 0.0 && m > 0.0) {
        *rx =   0.0;
        *ry = - VIEW_PI / 2.0;
        *rz = - acos(fabs(l) / sqrt(l * l + m * m));
    }else if (fabs(n) < VECT_ZERO && l > 0.0 && m < 0.0) {
        *rx =   0.0;
        *ry =   VIEW_PI / 2.0;
        *rz = - acos(fabs(l) / sqrt(l * l + m * m));
    }else if (fabs(n) < VECT_ZERO && l < 0.0 && m < 0.0) {
        *rx =   0.0;
        *ry = - VIEW_PI / 2.0;
        *rz =   acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l > 0.0 && m > 0.0 && n > 0.0) {
        *rx =   0.0;
        *ry =   acos(fabs(n) / sqrt(l * l + n * n));
        *rz =   acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l < 0.0 && m > 0.0 && n > 0.0) {
        *rx =   0.0;
        *ry = - acos(fabs(n) / sqrt(l * l + n * n));
        *rz = - acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l > 0.0 && m < 0.0 && n > 0.0) {
        *rx =   0.0;
        *ry =   acos(fabs(n) / sqrt(l * l + n * n));
        *rz = - acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l < 0.0 && m < 0.0 && n > 0.0) {
        *rx =   0.0;
        *ry = - acos(fabs(n) / sqrt(l * l + n * n));
        *rz =   acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l > 0.0 && m > 0.0 && n < 0.0) {
        *rx =   0.0;
        *ry = - acos(fabs(n) / sqrt(l * l + n * n)) + VIEW_PI;
        *rz =   acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l < 0.0 && m > 0.0 && n < 0.0) {
        *rx =   0.0;
        *ry =   acos(fabs(n) / sqrt(l * l + n * n)) + VIEW_PI;
        *rz = - acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l > 0.0 && m < 0.0 && n < 0.0) {
        *rx =   0.0;
        *ry = - acos(fabs(n) / sqrt(l * l + n * n)) + VIEW_PI;
        *rz = - acos(fabs(l) / sqrt(l * l + m * m));
    }else if (l < 0.0 && m < 0.0 && n < 0.0) {
        *rx =   0.0;
        *ry =   acos(fabs(n) / sqrt(l * l + n * n)) + VIEW_PI;
        *rz =   acos(fabs(l) / sqrt(l * l + m * m));
    }else{
        return ( - 1 );
    }

   return( 1 );
}


