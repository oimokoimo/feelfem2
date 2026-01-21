/* FORTRAN INTERFACE */

openpl_( )
{
    openpl();
    return;
}

openplv_( n )
     int *n;
{
    openplv( *n );
    return;
}

openplps_( s )
char *s;
{
    openplps( s );
    return;
}

openplvps_( n )
     int *n;
{
    openplvps( *n );
    return;
}

closeplps_( )
{ 
closepl_ps();
}
