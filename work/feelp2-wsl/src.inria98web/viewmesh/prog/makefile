CFLAGS = -g -I/usr/X11R6/include
feel.meshview : viewmesh.o YaccMain.o YaccExpression.o y.tab.o lex.yy.o 
	cc -o feel.meshview YaccMain.o YaccExpression.o y.tab.o lex.yy.o -ll ../../mesh_comp/mesh_comp.a viewmesh.o ../../system/system.a ../../xplot/xplot.a -L/usr/X11R6/lib -lX11 
