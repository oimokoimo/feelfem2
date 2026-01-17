PLUSPLUS = g++
F77      = f77
F90      = f90
CC       = $(PLUSPLUS)
CFLAGS   = 

INCLUDES = -I../class

LINKER   = $(CC)
MAKEFILE = Makefile
RANLIB   = ranlib
HDRS     = 
.SUFFIXES:   .cpp

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

PROGRAM  = Configure.a
OBJS     = Configure.o Configure_CHECK.o Configure_GeomObj.o Configure_InfoGenerate.o Configure_Makefile.o Configure_Parametric.o Configure_Quadrature.o initConfigure.o init_DefaultSolveParameters.o init_MakefileParameters.o init_StoreGeomObj.o init_StoreProgramModels.o init_StoreSolverLibraries.o read_ResourceFile.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

