/* FORTRAN INTERFACE */

cont_(x,y)
     int *x,*y;
{
    cont(*x,*y);
    return;
}

fcont_(x,y)
     double *x,*y;
{
    fcont(*x,*y);
    return;
}

fcontabs_(x,y)
     int *x,*y;
{
    fcont_abs(*x,*y);
    return;
}
