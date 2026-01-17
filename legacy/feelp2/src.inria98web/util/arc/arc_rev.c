#include <stdio.h>
#include <math.h>

void main(argc,argv)
     int argc;
     char *argv[];
{
    /* 第一  arc名称
     * 第二  点数
     * 第三  中心 x
     * 第四  中心 y
     * 第五  開始 x
     * 第六  開始 y
     * 第７  角度 度で
     */

    int   i;

    char *name;
    int   points;
    double cx,cy,x,y,th;
    double dx,dy;
    double r;
    double t;
    char   num[3];

    if(argc != 8) {
	fprintf(stderr,"%s arc-name points cx cy sx sy degree\n",argv[0]);
	exit(1);
    }
    name = argv[1];
    points = atoi(argv[2]);

    if(points>99) {
      fprintf(stderr,"Too many points\n");
    }
    
    sscanf(argv[3],"%lf",&cx);
    sscanf(argv[4],"%lf",&cy);
    sscanf(argv[5],"%lf",&x);
    sscanf(argv[6],"%lf",&y);
    sscanf(argv[7],"%lf",&th);

    dx = x - cx;
    dy = y - cy;
    th = th/180.0 * 3.14159265358979;

    for(i=0;i<points;i++) {
	t = i * th / (double)(points - 1);

	x = cos(t) * dx - sin(t) * dy + cx;
	y = sin(t) * dx + cos(t) * dy + cy;

        sprintf(num,"%c%c",'0'+(i/10),'0'+(i % 10));
 
	printf("  point %s%s(%6.3f,%6.3f);\n",name,num,x,y);
    }

    printf(" edge %s(",name);
    for(i=points-1;i>=0;i--) {
	if(i!= points-1) printf(",");
        sprintf(num,"%c%c",'0'+(i/10),'0'+(i % 10));
	printf("%s%s",name,num);
    }
    printf(");\n");
}

