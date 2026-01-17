#include <X11/Xlib.h>
#include <X11/Xutil.h>


#define PLANES  3
#define PIXELS  16

main()
{
    Display *d;
    Colormap cm;
    Window w;

    unsigned long planes[PLANES];
    unsigned long pixels[PIXELS];
    unsigned int nplanes ,ncolors;

    int ret;

    nplanes = PLANES;
    ncolors = PIXELS;

    d = XOpenDisplay(NULL);

/*
*/
    w = XCreateSimpleWindow(d,DefaultRootWindow(d),50,50,400,300,2,
			    BlackPixel(d,0),WhitePixel(d,0));    


    cm = XCreateColormap(d,w,
			 DefaultVisual(d,0),AllocAll);

    printf("cm = %d\n",cm);

    ret = XAllocColorCells( d , cm, False , planes,nplanes,pixels,ncolors);
    
    printf("ret = %d\n",ret);

    XMapWindow( d , w);

    


    getchar();
}
