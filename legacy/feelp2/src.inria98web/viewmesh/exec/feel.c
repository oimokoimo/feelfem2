/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   feel.c
 *      Date:   1993/12/2
 *   
 *   Purpose:   feelコマンド
 *   Functions: 
 *              
 *              
 */

#include "../../feel_def/feel_def.h"
#include "../../feel_def/basic_struct.h"
#include "../../system/system.h"

#define  DEVELOPPER  "fujio"
#define  DEVELOPPER2 "rlogin"

#define  DEFAULT_FEEL_MAX 2000000

#include <stdio.h>

/* options */
#define LISP_DEBUG  "-lispdebug"
#define NO_DELETE   "-nodelete"
#define ARRAY_SIZE  "-arraysize"
#define MESH_ONLY   "-meshonly"
#define MACHINE     "-machine"
#define LIMIT_FILE  "-limitfile"
#define PARALLEL    "-pe"
#define DIV         "-div"
#define RD          "-rd"
#define NOEDIV      "-noediv"
#define ENGLISH     "-e"
#define JAPANESE    "-j"
#define WEB         "-web"
#define BAMG        "-bamg"


void main(argc, argv)
     int argc;
     char *argv[];
{
    int i,j;
    int files;
    int err_flag;

    int array_size = DEFAULT_FEEL_MAX;   /* feel(*) の大きさ */

    int lisp_debug = 0;
    int no_delete  = 0;
    int limit_file = 0;
    int mesh_only  = 0;
    int parallel   = 0;
    int not_div    = 1;
    int rd         = 0;
    int noediv_flag= 0;
    int english    = 1;   /* default is   0:Japanese  1:English */
    int web        = 0;
    int bamg       = 0;   /* default is   inner mesh generator  */

    int machine;

    FILE *fp,*fp_pde;
    FILE *who_am_i;
    FILE *host_name;
    FILE *date_fp;
    
    char buf[BUFSIZ];
    char hostname[128];
    char datetime[128];
    char whoami[128];

    char com[BUFSIZ];

    if(argc == 1) {
	fprintf(stderr,"Usage: %s [parameters] [pde files]\n",argv[0]);
	exit(1);
    }

    
    if(argc == 2 && streq(argv[1],"-h")) {
	fprintf(stderr,"\n");
	fprintf(stderr,"%s has following command options.\n",argv[0]);
	fprintf(stderr,"----------------------------------------------------------------------\n");
	fprintf(stderr,"%10s   generate data only\n",MESH_ONLY);
	fprintf(stderr,"%10s   machine name [ews4800,r4000ews,sx2,sx3,cenju3,convex,iris]\n",MACHINE);
	fprintf(stderr,"%10s   size of feel array\n",ARRAY_SIZE);
	fprintf(stderr,"%10s   don't make system library file\n",LIMIT_FILE);
	fprintf(stderr,"%10s   produce divided source file\n",DIV);
	fprintf(stderr,"%10s   number of PE parameter 2^n<- kono n\n",PARALLEL);
	fprintf(stderr,"%10s   write lisp_procedure to file 'feel.l'\n",LISP_DEBUG);
	fprintf(stderr,"%10s   don't delete temporary files\n",NO_DELETE);
	fprintf(stderr,"%10s   recursive mesh division\n",RD);
	fprintf(stderr,"%10s   not divide line in ecal routines\n",NOEDIV);
	fprintf(stderr,"%10s   English version(Error Messages)\n",ENGLISH);
	fprintf(stderr,"%10s   Japanese version(Error Messages)\n",JAPANESE);
	fprintf(stderr,"%10s   Web mode\n",WEB);
	fprintf(stderr,"%10s   Use BAMG mesh generator\n",BAMG);

	fprintf(stderr,"----------------------------------------------------------------------\n");
	exit(0);
    }

    /* 計算機タイプの指定 */
    machine = FreeBSD;

    /* ここでコマンド引き数チェックを行う予定 */

    err_flag = 0;
    for(i=1;i<argc;i++) {
	if(*(argv[i]) != '-') continue;

	if(streq(argv[i],LISP_DEBUG)) {

            /*	    
	    if(!strindex(whoami,DEVELOPPER) && !strindex(whoami,DEVELOPPER2)) {
		fprintf(stderr,"lispdebug option is the DEVELOPPER only option.\n");
		exit(1);
	    }
            */

	    lisp_debug = 1;
	    continue;
	}

	/* 並列PEの個数を入力 */
	if(streq(argv[i],PARALLEL)) {
	    i++;
	    if(i == argc) {
		fprintf(stderr,"Usage %s -pe [PE unit factor = 2^n <- kono n]\n",argv[0]);
		exit(1);
	    }
	    parallel = atoi(argv[i]);
	    if(parallel < 1 || parallel > 6) {
		fprintf(stderr,"Usage %s -pe [PE unit factor = 2^n <- kono n (n must be 1 to 6)]\n",argv[0]);
		exit(1);
	    }
	    continue;
	}


	/* 配列の大きさの指定 */
	if(streq(argv[i],ARRAY_SIZE)) {
	    i++;
	    if(i == argc) {
		fprintf(stderr,"Usage %s -arraysize [ARRAY SIZE]\n",argv[0]);
		exit(1);
	    }
	    array_size = atoi(argv[i]);
	    if(array_size <= 0) {
		fprintf(stderr,"Usage %s %s [ARRAY SIZE]\n",argv[0],ARRAY_SIZE);
		exit(1);
	    }
	    continue;
	}
	
	/* メッシュ再分割の指定 */
	if(streq(argv[i],RD)) {
	    i++;
	    if(i == argc) {
		fprintf(stderr,"Usage %s -rd [RECURSIVE TIMES]\n",argv[0]);
		exit(1);
	    }
	    rd = atoi(argv[i]);
	    if(rd <= 0) {
		fprintf(stderr,"Usage %s %s [1-3]\n",argv[0],RD);
		exit(1);
	    }
	    continue;
	}


	/* メッシュ再分割非指定 */
	if(streq(argv[i],NOEDIV)) {
	    noediv_flag = 1;
	    continue;
        }

	/* English Version */
	if(streq(argv[i],ENGLISH)) {
	    english = 1;
	    continue;
        }

	/* Japanese Version */
	if(streq(argv[i],JAPANESE)){
	    english = 0;
	    continue;
        }


	/* WEB Version */
	if(streq(argv[i],WEB)){
	    web = 1;
	    continue;
        }

	/* BAMG Version */
	if(streq(argv[i],BAMG)){
	    bamg = 1;
	    continue;
        }


	/* Make Divided source file */
	if(streq(argv[i],DIV)) {
	    not_div = 0;
	    continue;
        }

	/* 使用計算機の指定 */
	if(streq(argv[i],MACHINE)) {
	    i++;
	    if(i == argc) {
		fprintf(stderr,"Usage %s %s [MACHINE NAME]\n",argv[0],MACHINE);
		exit(1);
	    }
	    if(streq(argv[i],"ews4800")) {
		machine = EWS4800;
		continue;
	    }
	    if(streq(argv[i],"r4000ews")) {
		machine = EWS4800_R4000;
		continue;
	    }
	    if(streq(argv[i],"sx2")) {
		machine = SX2;
		continue;
	    }
	    if(streq(argv[i],"sx3")) {
		machine = SX3;
		continue;
	    }
	    if(streq(argv[i],"cenju3")) {
		machine = CENJU3;
		continue;
	    }
	    if(streq(argv[i],"convex")) {
		machine = CONVEX;
		continue;
	    }
	    if(streq(argv[i],"iris")) {
		machine = IRIS;
		continue;
	    }
	    if(streq(argv[i],"sparc")) {
		machine = SPARC;
		continue;
            }
	    if(streq(argv[i],"dec-alpha")) {
		machine = DEC_ALPHA;
		continue;
            }
	    
	    fprintf(stderr,"%s : Unknown machine name %s\n",argv[i]);
	    exit(1);
	}
		
	if(streq(argv[i],NO_DELETE)) {
	    /*
	    if(!strindex(whoami,DEVELOPPER) && !strindex(whoami,DEVELOPPER2)) {
		fprintf(stderr,"nodelete option is the DEVELOPPER only option.\n");
		exit(1); 
	    }
	    */


	    no_delete = 1;
	    continue;
	}

	if(streq(argv[i],MESH_ONLY)) {
	    mesh_only = 1;
	    continue;
	}

	if(streq(argv[i],LIMIT_FILE)) {
	    limit_file = 1;
	    continue;
	}

	fprintf(stderr,"%s: Unknown command line parameter '%s'\n",argv[0],
		argv[i]);
	err_flag = 1;
    }

    if(machine == CENJU3 && parallel == 0) {
	fprintf(stderr,"%s: PE units is not specified\n",argv[0]);
	exit(1);
    }

    /* ここ以降、正常処理 */

    /* タイトル表示 */
    fprintf(stderr,"Finite Element Equation Language P2  Copyright(c) 1994,1995 NEC Corporation\n");

    if(bamg == 1) {
      fprintf(stderr,"BAMG is the mesh generator developed in INRIA/Roquencourt.\n");
    }

    
    if(parallel != 0  && machine != CENJU3) {
	fprintf(stderr,"%s: Warnning: machine type set to cenju3\n",argv[0]);
	machine = CENJU3;
    }
	

    if(err_flag != 0) exit(1);



    if(web != 1 ) {

    /* who am i */
    who_am_i = popen("who am i","r");
    fgets(buf,sizeof(buf),who_am_i);
    pclose(who_am_i);
    sscanf(buf,"%s",whoami);


    /* host name */
    host_name = popen("hostname","r");
    fgets(hostname,sizeof(hostname),host_name);
    pclose(host_name);

    /* date name */
    date_fp = popen("date","r");
    fgets(datetime,sizeof(datetime),date_fp);
    pclose(date_fp);
    datetime[strlen(datetime)-1] = '\0';


    /* Make Log File */
    if(strindex(hostname,"csl")) {
	if(!streq(whoami,"fujio"))
        sprintf(com,"echo '%s  %s' >>/home/fujio/feel_log/feel_log",whoami,datetime);
        system(com);
    }
    if(no_delete == 1 ) {
	    if(!strindex(whoami,DEVELOPPER) && !strindex(whoami,DEVELOPPER2)) {
		fprintf(stderr,"nodelete option is the DEVELOPPER only option.\n");
		exit(1);
	    }
    }
    if(lisp_debug == 1) {
	    if(!strindex(whoami,DEVELOPPER) && !strindex(whoami,DEVELOPPER2)) {
		fprintf(stderr,"lispdebug option is the DEVELOPPER only option.\n");
		exit(1);
	    }
    }

    }

    
    /*=================*/
    /*  FEEL本体の実行 */
    /*=================*/

    sprintf(com,"feel.meshview %d %d %d %d %d %d %d %d %d %d %d %d %d",lisp_debug,no_delete,machine,limit_file,array_size,mesh_only,parallel,not_div,rd,noediv_flag,english,web,bamg);
    fp = popen(com,"w");

    if(fp == NULL) {
	fprintf(stderr,"Cannot exec feel parser\n");
	exit(1);
    }


    files = 0;
    for(i=1;i<argc;i++) {
	if(*(argv[i]) == '-') continue;    /* パラメータは読み飛ばす */

	if(streq(argv[i-1],"-arraysize")) continue; /* 配列の大きさはskip */
	if(streq(argv[i-1],"-machine")) continue; /* マシン名は読み飛ばす */
	if(streq(argv[i-1],PARALLEL))   continue; /* PE指定は読み飛ばす   */
	if(streq(argv[i-1],RD))   continue; /* -rd 指定は読み飛ばす   */

	fp_pde = fopen(argv[i],"r");
	if(fp_pde == NULL) {
	    fprintf(stderr,"%s: Cannot open PDE file '%s'\n",argv[0],argv[i]);
	    exit(1);
	    /* エラー処理は、feel.parseで */
	}

	while(fgets(buf,sizeof(buf),fp_pde)) {
	    fprintf(fp,"%s",buf);
	}

	fclose(fp_pde);
    }

    /* 基本ライブラリ呼び出し */

    pclose(fp);
}
