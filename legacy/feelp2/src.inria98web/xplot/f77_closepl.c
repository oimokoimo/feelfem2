/* FORTRAN INTERFACE */

closepl_()
{
    closepl();
    return;
}


closeplv_( n )
     int *n;
{
    closeplv( *n );
    return;
}
