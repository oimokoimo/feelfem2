/*
 *   feel p2  Finite Element Equation Language Prototype Version 2
 *            ~      ~       ~        ~
 *      File:   feel.c
 *      Date:   1993/12/2
 *  Modified:   1999/01/14
 *   
 *   Purpose:   feel execution program
 *   Functions: 
 *              modification is for win32 version 
 *              
 */

#define FEEL_DOS_PDE  "$feel.pde"


#include "../feel_def/feel_def.h"
#include "../feel_def/basic_struct.h"
#include "../system/system.h"

#define  DEVELOPPER  "fujio"
#define  DEVELOPPER2 "oimo"


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
#define WEBCHECK    "-webcheck"
#define WEBEXEC     "-webexec"
#define MODULEF     "-modulef"
#define MF_MODULE   "-modulefmodule"
#define NODESET     "-node"
#define AVS64       "-avs64"



void main(argc, argv)
     int argc;
     char *argv[];
{
    int i,j;
    int files;
    int err_flag;

    int array_size = FEEL_ARRAY_SIZE;   /* feel(*) ,A$NBg$-$5 */

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
    int web_check  = 0;
    int web_exec   = 0;
    int modulef    = 0;
    int mf_module  = 0;
    int nodeset    = 0;
    int avs_64bit  = 0;

    int machine;

    int pdeargno;         /* PDE file argument No. in argv[*] */


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
	fprintf(stderr,"%10s   machine name [ews4800,hp700,linux,iris,sparc,dec-alpha,freebsd,win]\n",MACHINE);
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
	fprintf(stderr,"%10s   Modulef data structure\n",MODULEF);
	fprintf(stderr,"%10s   Make just Modulef MODULE\n",MF_MODULE);
	fprintf(stderr,"%10s   Web mode(check only)\n",WEBCHECK);
	fprintf(stderr,"%10s   Web execute mode\n",WEBEXEC);
	fprintf(stderr,"%10s   AVS 64bit code(for feelavsout)\n",AVS64);

	fprintf(stderr,"----------------------------------------------------------------------\n");
	exit(0);
    }

    /* Definition of platform */
#ifdef MSDOS
    machine = Windows;
#else
    machine = Linux;
#endif

    /* ,A$3$3$G%3%^%s%I0z$-?t%A%'%C%/$r9T$&M=Dj */

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

	/* ,AJBNsPE,A$N8D?t$rF~NO */
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


	/* ,AG[Ns$NBg$-$5$N;XDj */
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

	/* ,AG[Ns$NBg$-$5$N;XDj */
	if(streq(argv[i],NODESET)) {
	    i++;
	    if(i == argc) {
		fprintf(stderr,"Usage %s -node [NODE NUMBER]\n",argv[0]);
		exit(1);
	    }
	    nodeset = atoi(argv[i]);
	    if(nodeset <= 0) {
		fprintf(stderr,"Usage %s %s [NODE NUMBER]\n",argv[0],ARRAY_SIZE);
		exit(1);
	    }
	    continue;
	}

	
	/* ,A%a%C%7%e:FJ,3d$N;XDj */
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


	/* ,A%a%C%7%e:FJ,3dHs;XDj */
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


	/* Modulef Version */
	if(streq(argv[i],MODULEF)){
	    modulef = 1;
	    continue;
        }


	/* Modulef Module Version */
	if(streq(argv[i],MF_MODULE)){
	    mf_module = 1;
	    continue;
        }

	/* WEB check only mode */
	if(streq(argv[i],WEBCHECK)) {
	    web_check = 1;
	    continue;
        }

	/* WEB execute mode */
	if(streq(argv[i],WEBEXEC)) {
	    web_exec = 1;
	    continue;
        }

	/* Make Divided source file */
	if(streq(argv[i],DIV)) {
	    not_div = 0;
	    continue;
        }

	/* ,A;HMQ7W;;5!$N;XDj */
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
	    if(streq(argv[i],"linux")) {
		machine = Linux;
		continue;
	    }
	    if(streq(argv[i],"iris")) {
		machine = IRIS;
		continue;
	    }
	    if(streq(argv[i],"hp700")) {
		machine = HP700;
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
	    if(streq(argv[i],"freebsd")) {
	      machine = FreeBSD;
	      continue;
	    }
	    if(streq(argv[i],"win")) {
	      machine = Windows;
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

	if(streq(argv[i],AVS64)) {
	    avs_64bit = 1;
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

    /* ,A$3$30J9_!"@5>o=hM} */

    /* ,A%?%$%H%kI=<( */
    fprintf(stderr,"Finite Element Equation Language P2  Copyright(c) 1994,1995 NEC Corporation\n");

    if(bamg == 1) {
      fprintf(stderr,"BAMG is the mesh generator developed in INRIA/Roquencourt.\n");
    }

    if(modulef == 1 || mf_module == 1) {
      fprintf(stderr,"Modulef is developed in INRIA/France.\n");
    }

    
    if(parallel != 0  && machine != CENJU3) {
	fprintf(stderr,"%s: Warnning: machine type set to cenju3\n",argv[0]);
	machine = CENJU3;
    }
	

    if(err_flag != 0) exit(1);

    /* to pass the pde file name to feel.parse (1999/03/15) */

    pdeargno = 1;  /* default */
    for(i=1;i<argc;i++) {
      if(strindex(argv[i],".pde")) {
	pdeargno = i;
	break;
      }
      if(strindex(argv[i],".PDE")) {
	pdeargno = i;
	break;
      }
    }



    if(web != 1 ) {

    /* who am i */
#ifdef MSDOS
    sscanf("Windows User","%s",whoami);
    

#else
    who_am_i = popen("whoami","r");
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


#endif



    /* Make Log File */
/*    if(strindex(hostname,"csl")) {
	if(!streq(whoami,"fujio"))
        sprintf(com,"echo '%s  %s' >>/home/fujio/feel_log/feel_log",whoami,datetime);
        system(com);
    } */
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

    
    /*==================*/
    /*  FEEL.parse call */
    /*==================*/
#ifdef MSDOS
    sprintf(com,"feel.parse.exe %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %s %d < %s",lisp_debug,no_delete,machine,limit_file,array_size,mesh_only,parallel,not_div,rd,noediv_flag,english,web,bamg,web_check,web_exec,modulef,mf_module,nodeset,argv[pdeargno],avs_64bit,        
                                              FEEL_DOS_PDE);
#else
    sprintf(com,"feel.parse %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %s %d",lisp_debug,no_delete,machine,limit_file,array_size,mesh_only,parallel,not_div,rd,noediv_flag,english,web,bamg,web_check,web_exec,modulef,mf_module,nodeset,argv[pdeargno],avs_64bit);
#endif


#ifdef MSDOS
    fp = fopen(FEEL_DOS_PDE,"w");

    if(fp == NULL) {
	fprintf(stderr,"Cannot open feel temporary file\n");
	exit(1);
    }


    files = 0;
    for(i=1;i<argc;i++) {
	if(*(argv[i]) == '-') continue;    /* パラメータは読み飛ばす */

	if(streq(argv[i-1],"-arraysize")) continue; /* 配列の大きさはskip */
	if(streq(argv[i-1],"-node")) continue; /* node no 大きさはskip */
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
    basic_libraries(fp); 

    fclose(fp);

    system(com);           /* Execute feel.parse.exe */

    remove(FEEL_DOS_PDE);  /* delete temporary file  */

#else
    fp = popen(com,"w");
    if(fp == NULL) {
	fprintf(stderr,"Cannot exec feel parser\n");
	exit(1);
    }

    files = 0;
    for(i=1;i<argc;i++) {
	if(*(argv[i]) == '-') continue;    /* ,A%Q%i%a!<%?$OFI$_Ht$P$9 */

	if(streq(argv[i-1],"-arraysize")) continue; /* ,AG[Ns$NBg$-$5$Oskip */
	if(streq(argv[i-1],"-node")) continue; /* ,AG[Ns$NBg$-$5$Oskip */
	if(streq(argv[i-1],"-machine")) continue; /* ,A%^%7%sL>$OFI$_Ht$P$9 */
	if(streq(argv[i-1],PARALLEL))   continue; /* PE,A;XDj$OFI$_Ht$P$9   */
	if(streq(argv[i-1],RD))   continue; /* -rd ,A;XDj$OFI$_Ht$P$9   */

	fp_pde = fopen(argv[i],"r");
	if(fp_pde == NULL) {
	    fprintf(stderr,"%s: Cannot open PDE file '%s'\n",argv[0],argv[i]);
	    exit(1);
	    /* ,A%(%i!<=hM}$O!"feel.parse,A$G */
	}

	while(fgets(buf,sizeof(buf),fp_pde)) {
	    fprintf(fp,"%s",buf);
	}

	fclose(fp_pde);
    }

    /* ,A4pK\%i%$%V%i%j8F$S=P$7 */
    basic_libraries(fp); 

    pclose(fp);

#endif

}
