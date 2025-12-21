#include <stdio.h>

main()

{
    int x,y;
    int i,j;
    unsigned long *col;
    static char buf[BUFSIZ];
    openpl();

col =(unsigned long *) 	xplot_scale_cmap();    

    for(i=0;i<50;i++) {
	xplot_setfg(*(col + i));
	for(j=0;j<10;j++) line(0,i*10+j,600,i*10+j);
    }
    xwait();
    closepl();
}
