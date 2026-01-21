#include <stdio.h>

#define PS

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


int ndim,npmax,edats,nsets,numsets;
int dummy;
int argvno;

main(argc,argv)
int argc;
char *argv[];
{
    char buf[BUFSIZ];
    FILE *fp;

    if(argc >= 2)  {
/*      set_size(atoi(argv[1]),atoi(argv[1])); */
    }
    if(argc >= 3)  {
      argvno = atoi(argv[2]);
    }
    else {
      argvno = 0;
    }

    fp = fopen("feel_dat","r");
    if(fp == NULL) {
	fprintf(stderr,"cannot open feel_dat\n");
	exit(1);
    }
    fprintf(stderr,"check end.");

    fgets(buf,sizeof(buf),fp);
    if(!strindex(buf,"FEEL")) {
	fprintf(stderr,"feel_dat may be wrong.(no 'FEEL' keyword on the top)\n");
	fclose(fp);
	exit(1);
    }
    
    fscanf(fp,"%d %d %d %d %d",&ndim,&npmax,&edats,&nsets,&numsets);
    fprintf(stderr,"Space dimension   %8d\n",ndim);
    fprintf(stderr,"Number of nodes   %8d\n",npmax);
    fprintf(stderr,"Number of EDATs   %8d\n",edats);
    if(edats >MAX_EDAT) {
      fprintf(stderr,"Too many EDATs\n");
      exit(1);
    } 
    edats = 0;
    fprintf(stderr,"Number of NSETs %8d\n",nsets);
    fprintf(stderr,"Number of NNUMs %8d\n",numsets);
    
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

    fgets(buf,sizeof(buf),fp);

    sscanf(buf,"%d %d %d",&no,&elems,&np);


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
        char buf[BUFSIZ];
        fgets(buf,sizeof(buf),fp);
	sscanf(buf,"%d %lf %lf",&dummy,x,y);
	x++;
	y++;
	if(dummy != i+1) {
            fprintf(stderr,"dummy = %d  i+1= %d\n",dummy,i+1);
	    fprintf(stderr,"Oh My God! in points!");
	    exit(1);
	}
    }

    return;

}


show()
{
    int i,j,k,num;
    int no,elements,nodes;
    int points;
    int *ptr,*type;

    int is_first;
    
    double *x,*y;
    double xmin,xmax,ymin,ymax;
    double dx,dy;

    char buf[BUFSIZ];

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

#ifdef PS
    openplps("mesh.ps");
    fprintf(stderr,"mesh write into file 'mesh.ps'\n");
#else
    openpl();
#endif 

    fspace(xmin - dx, ymin - dy, xmax + dx , ymax + dy);


    is_first = 0;

    while(1) {
	printf("Input EDAT set no [1-%d](minus no draw node number) :",edats);
       
        if(argvno == 0) {
          scanf("%d",&no);
        } 
        else {
          no = argvno;
        }        

	if(is_first != 0) {  erase();     }
        else              { is_first = 1; }


	if(no < 0) {
	    no = - no;
	    for(i=0;i<points;i++) {
		fnumber(*(x+i),*(y+i),(long)(i+1));
	    }
	}

	elements = edat[no-1].elements;
	nodes    = edat[no-1].nodes;
 	ptr  = edat[no-1].ptr;
	type = edat[no-1].type;

	printf("EDAT No. %d  Elements %d Nodes per Element %d\n"
	       ,no,elements,nodes);

	for(i=0;i<elements;i++) {
	    j = 0;
	    num = *(ptr + i * nodes + j);
	    fmove(*(x + num -1 ) , *(y + num - 1));

	    for(j=1;j<3;j++) {
		num = *(ptr + i * nodes + j);
		fcont (*(x + num -1 ) , *(y + num - 1));
	    }
	    j = 0;
	    num = *(ptr + i * nodes + j);
	    fcont(*(x + num -1 ) , *(y + num - 1));	    

	    for(j=3;j<nodes;j++) {
		num = *(ptr + i * nodes + j);
		fpeke(*(x + num -1 ) , *(y + num - 1));	    
	    }

	}
#ifdef PS
        closepl();
        exit(0);
#else
	plot_flush(0);
        if(argvno != 0) {    xwait();  return; }
#endif
    }
	
}
