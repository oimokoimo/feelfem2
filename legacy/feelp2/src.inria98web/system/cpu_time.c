#include <stdio.h>
#include "../feel_def/feel_def.h"

#ifdef MSDOS

#else

#include <sys/types.h>
#include <sys/times.h>

static long  user_time,total_user_time;
static long   sys_time,total_sys_time;
static long  c_user_time,total_c_user_time;
static long   c_sys_time,total_c_sys_time;
static struct tms cpu_time;

#endif

void init_cptime()
{

#ifdef MSDOS

    return;

#else

    if( -1 == times( &cpu_time )) {
	fprintf(stderr,"Cannot call times routine\n");
    }
    
    user_time    = cpu_time.tms_utime;
    sys_time     = cpu_time.tms_stime;
    
    c_user_time  = cpu_time.tms_cutime;
    c_sys_time   = cpu_time.tms_cstime;

    total_user_time = 0;
    total_sys_time  = 0;

    total_c_user_time = 0;
    total_c_sys_time  = 0;

    return;

#endif

}

void rep_time(s)
     char *s;
{
#ifdef MSDOS

    fprintf(stderr,"[%s](time:UNKNOWN in MS-DOS)\n",s);
    return;

#else

    long ut,st;
    long cut,cst;
    if( -1 == times( &cpu_time )) {
	fprintf(stderr,"Cannot call times routine\n");
    }
    
    ut = cpu_time.tms_utime - user_time;
    st = cpu_time.tms_stime - sys_time ;
    total_user_time += ut;
    total_sys_time  += st;

    cut = cpu_time.tms_cutime - c_user_time;
    cst = cpu_time.tms_cstime - c_sys_time ;
    total_c_user_time += cut;
    total_c_sys_time  += cst;

    user_time = cpu_time.tms_utime;
    sys_time  = cpu_time.tms_stime;

    c_user_time = cpu_time.tms_cutime;
    c_sys_time  = cpu_time.tms_cstime;

    fprintf(stderr,"[%s]\n",s);
    fprintf(stderr,"User   %5d (Total %5d)  [%5d](%5d) \n",ut,total_user_time,
	    cut,total_c_user_time);
    fprintf(stderr,"System %5d (Total %5d)  [%5d](%5d) \n",st,total_sys_time ,
	    cst,total_c_sys_time );

    return;

#endif
}

void rep_proc( s )
  char *s;
{
    extern int status_no_delete;
    if(status_no_delete) {
      fprintf(stderr,"%s\n",s);
    }
    return;
}
void rep_proc_no( s ,no)
  char *s;
  int  no;
{
    extern int status_no_delete;
    if(status_no_delete) {
      fprintf(stderr,"Procedure %s [%d]\n",s,no);
    }
    return;
}
