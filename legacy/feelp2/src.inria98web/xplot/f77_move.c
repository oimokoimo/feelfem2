/* FORTRAN INTERFACE */

move_(x,y)
     int *x,*y;
{
    move(*x,*y);
    return;
}

fmove_(x,y)
     double *x,*y;
{
    fmove(*x,*y);
    return;
}
