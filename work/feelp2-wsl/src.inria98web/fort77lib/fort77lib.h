/*
 *  prototype declaration for fort77lib make
 *
 *
 *
 */

void lib_cal_ht();    /* �������饤��ι⤵�����ץ����� */
void lib_sol();       /* ϢΩ�켡�������롼���� */
void lib_scal();      /* subprogram for sol routine */
void lib_get_ielem(); /* ielem�ǡ������ϥ롼���� */
void lib_ipd_make();  /* IPD(����������ͳ������)�����롼���� */
void lib_make_KLD();  /* KLD����롼���� */
void lib_set();       /* �ͤ���������롼���� */
void lib_zero();      /* ������������롼���� */
void lib_f_alloc();   /* f_alloc�롼����      */
void lib_f_free();    /* f_free�롼����       */
void lib_inpdat_wrt(); /* INPUT�ǡ��������å��롼���� */
void lib_ipf_nfree();  /* �����輫ͳ�٤���������롼���� */
void lib_ipd_nonode(); /* ����̵����ͳ�٤˴ؤ������ */
void lib_get_inset();  /* read inset data array from file */
void lib_edatrange();  /* ���󥿡��Ѥ�edat�ǡ�����xmin,xmax,ymin,ymax����� */
void lib_diskio();     /* disk io subroutines */
void lib_closefil();   /* close all files */
void parallel_lib_make();    /*  ../parallel_lib�ǥ��쥯�ȥ�����ѿ� */
void lib_parallel_report();  /* report program for parallel library  */
void lib_report();     /* CPU���ַ�¬����ӡ�REPORT���� */
void lib_mk_subdomain_edat();
void lib_mk_subdomain_nset();
void lib_ews4800_erapse_time();
void lib_convex_erapse_time();
void lib_alpha_erapse_time();
void lib_sparc_erapse_time();
void lib_MSFortran_erapse_time();
