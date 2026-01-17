\rm */*.o
mv VIEW/viewcolor.c VIEW/viewcolor.HP800.bak
mv VIEW/viewfort.c  VIEW/viewfort.HP800.bak
mv GRAPH/chkdsp.c   GRAPH/chkdsp.HP800.bak
cd FEEL
f77 -c *.f
cd ../GRAPH
f77 -c *.f
cc  -c *.c
cd ../VIEW
cc  -c *.c
cd ../WEB
f77 -c *.f
cd ../HP800
cc  -c *.c
f77 -c *.f
cd ..
mv VIEW/viewcolor.HP800.bak   VIEW/viewcolor.c
mv VIEW/viewfort.HP800.bak    VIEW/viewfort.c
mv GRAPH/chkdsp.HP800.bak     GRAPH/chkdsp.c
ar rv libfeelG.a */*.o
