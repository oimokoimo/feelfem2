/*
 *  xplot system routines
 *
 *
 */

#include "psplot.h"


psplot_error( s )
     char *s;
{
    fprintf(stderr,"psplot error: %s\n",s);
    return;
}

psplot_error_d( s, n)
     char *s;
     int   n;
{
    fprintf(stderr,"psplot error: ");
    fprintf(stderr,s,n);
    fprintf(stderr,"\n");
    return;
}

psplot_error_s( s, s2)
     char *s;
     char *s2;
{
    fprintf(stderr,"psplot error: ");
    fprintf(stderr,s,s2);
    fprintf(stderr,"\n");
    return;
}


/*--------------------------------------------*/

int is_psplot_plane_err( routine_name )
     char *routine_name;
{

    if(PSplot_plane_no < 0 || PSplot_plane_no > MAX_PS_FILES ) {
	psplot_error_s("Bad Screen number (%s)",routine_name);
	return(YES);
    }

    if(PSplot_win[PSplot_plane_no] == NULL) {
	psplot_error_s("Screen is not available (%s)",routine_name);
	return(YES);
    }
    
    return(NO);
}
