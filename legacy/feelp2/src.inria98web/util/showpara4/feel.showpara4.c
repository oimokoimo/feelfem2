#include <stdio.h>

#define MAX_EDAT 100

typedef struct {
    int no;
    int elements;
    int nodes;

    int *ptr;
    int *type;
} Edat;


Edat edat[MAX_EDAT];

typedef struct {
    int no;
    int points;
    double *x;
    double *y;
} Point;

Point pts;

int *pe_no;

int ndim,npmax,edats,nsets,numsets;
int dummy;

main(argc,argv)
int argc;
char *argv[];
{
    char buf[BUFSIZ];
    FILE *fp;

    /* additon */
    int i;
    int pes,elems,dummy;

    fp = fopen("MESH.PARA","r");
    if(fp == NULL) {
       fprintf(stderr,"Use feel -pe option to produce parallel data\n");
       exit(1);
    }
    fscanf(fp,"%d",&pes);
    if(pes <0 || pes >5) {
      fprintf(stderr,"Too many or too few PEs\n");
      exit(1);
    }
    switch(pes) {
      case 0:
	pes = 1;
	break;
      case 1:
	pes = 2;
	break;
      case 2:
	pes = 4;
	break;
      case 3:
	pes = 8;
	break;
      case 4:
	pes = 16;
	break;
      case 5:
	pes = 32;
	break;

    }
    for(i=0;i<pes;i++) fscanf(fp,"%d",&dummy); 
    fscanf(fp,"%d",&elems);

    for(i=0;i<elems;i++) fscanf(fp,"%d",&dummy);

    pe_no = (int *)malloc(sizeof(int)*elems);

    for(i=0;i<elems;i++) fscanf(fp,"%d",pe_no+i);


    fclose(fp);


    if(argc == 2)  {
      set_size(atoi(argv[1]),atoi(argv[1]));
    }

    fp = fopen("feel_dat","r");
    if(fp == NULL) {
	fprintf(stderr,"cannot open feel_dat\n");
	exit(1);
    }

    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"FEEL")) {
	fprintf(stderr,"feel_dat may be wrong.(no 'FEEL' keyword on the top)\n");
	fclose(fp);
	exit(1);
    }
    
    fscanf(fp,"%d %d %d %d %d",&ndim,&npmax,&edats,&nsets,&numsets);
    fprintf(stderr,"%d次元\n",ndim);
    fprintf(stderr,"節点数   %8d\n",npmax);
    fprintf(stderr,"要素集合 %8d\n",edats);
    if(edats > MAX_EDAT) {
     fprintf(stderr,"要素集合の数が多すぎます\n");
     exit(1);
    }
    edats = 0;
    fprintf(stderr,"境界集合 %8d\n",nsets);
    fprintf(stderr,"数値集合 %8d\n",numsets);
    
    while(fgets(buf,sizeof(buf),fp)) {
	if(strindex(buf,"EDAT")) {
	    read_edat(fp);
	}

	if(strindex(buf,"NODE")) {
	    read_point(fp);
	}
    }
    fclose(fp);

    show();
}

read_edat(fp)
     FILE *fp;
{
    int no,elems,np;
    int i,j;
    int dummy;

    int *ptr;
    int *type;

    char buf[BUFSIZ];
    char fmt[BUFSIZ];

    fscanf(fp,"%d %d %d",&no,&elems,&np);


    edat[edats].no = no;
    edat[edats].elements = elems;
    edat[edats].nodes    = np;

    ptr  = (int *)malloc(sizeof(int) * np * elems);
    type = (int *)malloc(sizeof(int) * elems);

    edat[edats].ptr      = ptr;
    edat[edats].type     = type;


    for(i=0;i<elems;i++) {
	for(j=0;j<np;j++) {
	    fscanf(fp,"%d",ptr);
	    ptr++;
	}
	fscanf(fp,"%d",type);
	type++;
	
    }

    edats++;
    return;
}



read_point(fp)
     FILE *fp;
{
    int i;
    int dummy;
    int points;
    double *x;
    double *y;

    points     = npmax;
    pts.points = npmax;
    
    x = (double *)malloc(sizeof(double)*points);
    y = (double *)malloc(sizeof(double)*points);

    pts.x = x;
    pts.y = y;
    
    for(i=0;i<points;i++) {
	fscanf(fp,"%d",&dummy);
	fscanf(fp,"%lf",x);
	fscanf(fp,"%lf",y);
	x++;
	y++;
	if(dummy != i+1) {
	    fprintf(stderr,"Oh My God! in points!");
	    exit(1);
	}
    }

    return;

}


show()
{
    int noflag;
    int i,j,k,num;
    int no,elements,nodes;
    int points;
    int *ptr,*type;
    
    double *x,*y;
    double xmin,xmax,ymin,ymax;
    double dx,dy;

    points = pts.points;
    x = pts.x;
    y = pts.y;
    
    xmax = xmin = *x;
    ymax = ymin = *y;

    for(i=0;i<npmax;i++) {
	if(xmax < *(x + i)) xmax = *(x + i);
	if(xmin > *(x + i)) xmin = *(x + i);
	if(ymax < *(y + i)) ymax = *(y + i);
	if(ymin > *(y + i)) ymin = *(y + i);
    }

    dx = (xmax - xmin ) / 20.0;
    dy = (ymax - ymin ) / 20.0;

    openpl();
    fspace(xmin - dx, ymin - dy, xmax + dx , ymax + dy);

    while(1) {
	printf("要素データ集合の数は %d です。番号を入れて下さい。\n",edats);
	scanf("%d",&no);

	erase();

	noflag = 0;
	if(no < 0) {
	    no = - no;
	    noflag = 1;
	    for(i=0;i<points;i++) {
/*		fnumber(*(x+i),*(y+i),(long)(i+1)); */
	    }
	}

	elements = edat[no-1].elements;
	nodes    = edat[no-1].nodes;
 	ptr  = edat[no-1].ptr;
	type = edat[no-1].type;

	printf("要素番号 %d  要素数 %d  要素内節点数 %d\n",no,elements,nodes);

	for(i=0;i<elements;i++) {
	    double xx[4],yy[4];
	    set256color(*(pe_no+i));

	    for(j=0;j<4;j++) {
		num = *(ptr + i * nodes + j);
		xx[j] = *(x + num -1 );
		yy[j] = *(y + num - 1);
	    }
	    draw_rect(xx[0],yy[0],xx[1],yy[1],xx[2],yy[2],xx[3],yy[3]);

	}

	if(noflag == 1) {
	plot_color("tomato4");
	for(i=0;i<elements;i++) {
	    j = 0;
	    num = *(ptr + i * nodes + j);
	    fmove(*(x + num -1 ) , *(y + num - 1));

	    for(j=1;j<4;j++) {
		num = *(ptr + i * nodes + j);
		fcont (*(x + num -1 ) , *(y + num - 1));
	    }
	    j = 0;
	    num = *(ptr + i * nodes + j);
	    fcont(*(x + num -1 ) , *(y + num - 1));	    

	    for(j=4;j<nodes;j++) {
		num = *(ptr + i * nodes + j);
		fpeke(*(x + num -1 ) , *(y + num - 1));	    
	    }

	}
        }

	plot_flush(0);
    }
	
}

