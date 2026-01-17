#include <stdio.h>
#include <sys/types.h>
#include <sys/times.h>
#include <time.h>

static long  user_time,total_user_time;
static long   sys_time,total_sys_time;
static long  c_user_time,total_c_user_time;
static long   c_sys_time,total_c_sys_time;
static struct tms cpu_time;

void timeinit()
{
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
}

double erapstime()
{
    long ut,st;
    long cut,cst;
    double ret_value;

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


    ret_value = (double)(total_user_time + total_sys_time)/(double)CLK_TCK;


    return(ret_value);
}
