/************************************************************************/
/*                                                                      */
/* View ver 2.0                                                         */
/* viewfunc.h                                                           */
/* Copy rights - all rights reserved by NEC                             */
/*                                                                      */
/************************************************************************/

/*	£Ö£é£å£÷ ´ðËÜ¥é¥¤¥Ö¥é¥ê		*/
int     ViewOpenWindow();
int     ViewConnectWindow();
int     ViewDeleteWindow();
int     ViewAllocWindow();
int     ViewInitializeColor();
int     ViewInitialize();
int     ViewSetBackgorund();
int     ViewSetLight();
int     ViewSetColor();
int     ViewSetZbuffer();
int     ViewSetShading();
int     ViewSetViewportWindow();
void    ViewWindowPoint();
int     ViewSetRotateWindow();
int     ViewClearWindow();
int     ViewSetPoint();
int     ViewDrawPoint();
int     ViewSetArc();
int     ViewDrawArc();
int     ViewSetLine();
int     ViewDrawLine();
int     ViewSetPolygon();
int     ViewDrawPolygon();
int     ViewSetText();
int     ViewDrawText();
void    ViewCreateZbuffer();
int     ViewUpdate();
int     ViewSetZoom();
int     ViewSetMove();
int     ViewSetClip();
int     ViewClipPoint();

/*	£Ö£é£å£÷ »Ù±ç¥é¥¤¥Ö¥é¥ê		*/
void    ViewUtilVector();
void    ViewUtilRotatePoint();
void    ViewUtilRotateXYZ();
float   ViewUtilDistance();
float   ViewUtilMax();
float   ViewUtilMin();
float   ViewUtilInnerAngle();
float   ViewUtilInnerProduct();
void    ViewUtilNormal();
void    ViewUtilQuickSort();
int     ViewUtilArcCenter();
int     ViewUtilCheckLine();
void    ViewUtilVpoint();
float	ViewUtilLagrange();

/*	£Ö£é£å£÷ ³ÈÄ¥¥é¥¤¥Ö¥é¥ê		*/
int     ViewExtMessage();
int     ViewExtAxis();
int     ViewExtTriangleStrip();
int     ViewExtTriangleContour();
int     ViewExtQuadrateStrip();
int     ViewExtQuadrateContour();
int     ViewExtSphere();
int     ViewExtColorBar();
int     ViewExtVector();
int     ViewExtWait();

void    ViewContour();

extern  Vwindow             viewdisp[VIEW_MAX_DISP];
extern  Vcolor_struct       viewcolor[VIEW_MAX_DISP][VIEW_MAX_COLOR];

extern  Vviewport_struct    viewport[VIEW_MAX_DISP];
extern  Vdraw_struct        *viewdraw[VIEW_MAX_DISP];

extern  int                 viewdraw_num[VIEW_MAX_DISP];
extern  int                 viewdraw_size[VIEW_MAX_DISP];
extern  Vattr_struct        viewattr[VIEW_MAX_DISP];
extern  Vlight_struct       viewlight[VIEW_MAX_DISP];

