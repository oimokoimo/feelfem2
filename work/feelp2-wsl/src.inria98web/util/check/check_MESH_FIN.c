#include <stdio.h>

typedef struct {
    int no;
    int elements;
    int nodes;

    int *ptr;
    int *type;
} Edat;


Edat edat[10];
int  edats= 0;

typedef struct {
    int no;
    int points;
    double *x;
    double *y;
} Point;

Point pst;


main()
{
    char buf[BUFSIZ];
    FILE *fp;

    fprintf(stderr,"start...");
    fp = fopen("MESH.FIN","r");
    if(fp == NULL) {
	fprintf(stderr,"cannot open MESH.FIN\n");
	exit(1);
    }
    fprintf(stderr,"check end.");

    
    while(gets(buf)) {
	puts(buf);
	if(strindex(buf,"MESH")) {
	    read_mesh(fp);
	}

	if(strindex(buf,"POINT")) {
	    read_point(fp);
	}
    }
    fclose(fp);

    show();
}

read_mesh(fp)
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

    for(i=0;i<elems;i++) {
	for(j=0;j<np;j++) {
	    fscanf(fp,"%d",ptr);
	    ptr++;
	}
	fscanf(fp,"%d",type);
	type++;

	fscanf(fp,"%d",&dummy);
	if(dummy != i+1) {
	    fprintf(stderr,"Oh my God! in read mesh\n");
	    exit(1);
	}
    }

    edats++;
    return;
}


read_point(fp)
     FILE *fp;
{
}


show()
{
    int i,j,k;
    int no,elements,nodes;
    int *ptr,*type;

    for(i=0;i<edats;i++) {
	elements = edat[i].elements;
	nodes    = edat[i].nodes;
 	ptr  = edat[i].ptr;
	type = edat[i].type;

	for(j=0;j<elements;j++) {
	    for(k=0;k<np;k++) {
		printf("%5d",*ptr);
		ptr++;
	    }
	    printf("%5d\n",*type);
	    type++;
	}
    }
	
}
