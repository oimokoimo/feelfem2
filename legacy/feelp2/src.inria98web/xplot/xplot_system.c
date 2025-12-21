/*
 *  xplot system routines
 *
 *
 */

#include "xplot.h"


xplot_error( s )
     char *s;
{
    fprintf(stderr,"xplot error: %s\n",s);
    return;
}

xplot_error_d( s, n)
     char *s;
     int   n;
{
    fprintf(stderr,"xplot error: ");
    fprintf(stderr,s,n);
    fprintf(stderr,"\n");
    return;
}

xplot_error_s( s, s2)
     char *s;
     char *s2;
{
    fprintf(stderr,"xplot error: ");
    fprintf(stderr,s,s2);
    fprintf(stderr,"\n");
    return;
}


/*--------------------------------------------*/

int is_xplot_plane_err( routine_name )
     char *routine_name;
{

    if(Xplot_plane_no < 0 || Xplot_plane_no > MAX_WINDOWS ) {
	xplot_error_s("Bad Screen number (%s)",routine_name);
	return(YES);
    }

    if(Xplot_win[Xplot_plane_no] == NULL) {
	xplot_error_s("Screen is not available (%s)",routine_name);
	return(YES);
    }
    
    return(NO);
}


