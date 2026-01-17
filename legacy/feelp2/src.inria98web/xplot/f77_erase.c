/* FORTRAN INTERFACE */

erase_()
{
    erase();
    return;
}

erasev_( n )
     int  *n;
{
    erasev(*n);
    return;
}
