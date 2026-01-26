/*
 * Portable CPU-time timer for Linux/WSL (and BSD-like systems)
 * Provides Fortran-callable entry points:
 *   void   timeinit_(void);
 *   double erapstime_(void);
 *
 * Notes:
 * - Uses times(2) and returns accumulated (user+sys) CPU time in seconds.
 * - On Linux, use sysconf(_SC_CLK_TCK) instead of obsolete CLK_TCK.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/times.h>
#include <unistd.h>     /* sysconf */
#include <errno.h>

static long user_time,  sys_time;
static long c_user_time, c_sys_time;

static long total_user_time, total_sys_time;
static long total_c_user_time, total_c_sys_time;

static struct tms cpu_time;

/* clock ticks per second */
static long ticks_per_sec(void)
{
    long t = sysconf(_SC_CLK_TCK);
    if (t <= 0) {
        /* last resort: common default, but should not happen */
        t = 100;
    }
    return t;
}

void timeinit_(void)
{
    if ((clock_t)-1 == times(&cpu_time)) {
        fprintf(stderr, "Cannot call times() routine (errno=%d)\n", errno);
        return;
    }

    user_time   = cpu_time.tms_utime;
    sys_time    = cpu_time.tms_stime;
    c_user_time = cpu_time.tms_cutime;
    c_sys_time  = cpu_time.tms_cstime;

    total_user_time = 0;
    total_sys_time  = 0;
    total_c_user_time = 0;
    total_c_sys_time  = 0;
}

double erapstime_(void)
{
    long ut, st, cut, cst;

    if ((clock_t)-1 == times(&cpu_time)) {
        fprintf(stderr, "Cannot call times() routine (errno=%d)\n", errno);
        return 0.0;
    }

    ut = cpu_time.tms_utime  - user_time;
    st = cpu_time.tms_stime  - sys_time;
    total_user_time += ut;
    total_sys_time  += st;

    cut = cpu_time.tms_cutime - c_user_time;
    cst = cpu_time.tms_cstime - c_sys_time;
    total_c_user_time += cut;
    total_c_sys_time  += cst;

    user_time   = cpu_time.tms_utime;
    sys_time    = cpu_time.tms_stime;
    c_user_time = cpu_time.tms_cutime;
    c_sys_time  = cpu_time.tms_cstime;

    return (double)(total_user_time + total_sys_time) / (double)ticks_per_sec();
}

