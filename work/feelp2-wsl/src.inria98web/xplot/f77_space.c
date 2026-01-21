/* FORTRAN INTERFACE */
space_( x1,y1 , x2,y2 )
     int *x1,*y1;
     int *x2,*y2;
{
    space(*x1,*y1,*x2,*y2);
    return;
}

fspace_( x1,y1 , x2,y2 )
     double *x1,*y1;
     double *x2,*y2;
{
    fspace(*x1,*y1,*x2,*y2);
    return;
}

