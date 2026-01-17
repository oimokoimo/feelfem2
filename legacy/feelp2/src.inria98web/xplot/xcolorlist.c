#include <stdio.h>

static char *colorname[] = {
"black",
"snow",
"khaki",
"dark slate gray",
"rosy brown",
"medium blue",
"dark orange",
"pale green",
"light goldenrod yellow",
"dark sea green",
"light grey",
"turquoise",
"light goldenrod",
"orchid",
"MidnightBlue",
"saddle brown",
"medium sea green",
"navy",
"pale goldenrod",
"dark slate blue",
"OrangeRed",
"forest green",
"cornflower blue",
"dim gray",
"light sea green",
"salmon",
"dark green",
"burlywood",
"slate blue",
"olive drab",
"medium blue",
"beige",
"indian red",
"medium aquamarine",
"green yellow",
"blue violet",
"VioletRed",
"SteelBlue",
"spring green",
"wheat",
"dark olive green",
"yellow green",
"RoyalBlue",
"goldenrod",
"blue",
"sandy brown",
"dodger blue",
"firebrick",
"deep sky blue",
"light coral",
"dark goldenrod",
"maroon",
"light grey",
"dark turquoise",
"hot pink",
"medium spring green",
"dark khaki",
"lawn green",
"sienna",
"gold",
"aquamarine",
"cyan",
"chocolate",
"light yellow",
"lime green",
"slate blue",
NULL }  ;
int xcolorlist_(int *n) {
xcolorlist(*n);
return;
}
int xcolorlist(int n)
{
  int i;
  for(i=0;colorname[i] !=NULL;i++) {
/*    fprintf(stderr,"i=%d  n=%d\n",i,n); */
    if(n==i) {
      xcolor(colorname[i]);
      return;
    }
  }
  fprintf(stderr,"xcolorlist : out of color number %d\n",n);
  return;
}

/*****
106  90 205		
  0   0 255		blue
 30 144 255		dodger blue
  0 191 255		deep sky blue
  0 206 209		dark turquoise
 95 158 160		CadetBlue
 85 107  47		
 46 139  87		sea green
  0 255   0		green
127 255   0		chartreuse
  0 250 154		
 50 205  50		
255 255 224		
255 255   0		yellow
184 134  11		
205 133  63		peru
245 245 220		
210 180 140		tan
210 105  30		
165  42  42		brown
233 150 122		dark salmon
233 150 122		DarkSalmon
250 128 114		
255 160 122		light salmon
255 160 122		LightSalmon
255 165   0		orange
255 140   0		
255 127  80		coral
240 128 128		
255  99  71		tomato
255  69   0		
255   0   0		red
255 105 180		
255  20 147		deep pink
255 192 203		pink
255 182 193		light pink
219 112 147		pale violet red
176  48  96		
199  21 133		medium violet red
255   0 255		magenta
238 130 238		violet
221 160 221		plum
218 112 214		
186  85 211		medium orchid
153  50 204		dark orchid
148   0 211		dark violet
138  43 226		
160  32 240		purple
147 112 219		medium purple
216 191 216		thistle

*/
