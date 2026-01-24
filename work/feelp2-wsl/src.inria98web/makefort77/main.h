/*
 *  prototypes for make_main 
 *
 *  modernize 2026/01/24
 *
 */

void make_filset();
void make_datinp();
void main_declare(FILE *);      /* �ᥤ��ץ�����������ʬ                 */
void main_prepare(FILE *);      /* �ե��������ꡢ�ǡ����ɤ߹��ߡ�feel()������ */
void main_const_let(FILE *);    /* ����ѿ������ʸ */
void main_subdomain(FILE *);    /* subdomain������ν��� */
void main_variable(FILE *);     /* fem�ѿ��ewise�ѿ���������                 */
void main_scheme(FILE *);       /* ��������֥�å��Υɥ饤�֥롼����         */
void close_let_fp();           /* ñ��letʸ�ξ��       */
void close_file_fort77(FILE *);    /* close data �ե�����   */
int is_x11_flag();
void listup_avsoutput_in_main_fp(FILE *);

/* for parallel version */
void para_block_data();

