PLUSPLUS = g++
F77      = f77
F90      = f90
CC       = $(PLUSPLUS)
CFLAGS   =  -g -O0 -fno-omit-frame-pointer -fsanitize=address

INCLUDES = -I../class

LINKER   = $(CC)
MAKEFILE = Makefile
RANLIB   = ranlib
HDRS     = 
.SUFFIXES:   .cpp

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

PROGRAM  = Object.a
OBJS     = AssignObject.o ElementObject.o FileObject.o FunctionObject.o LabelObject.o MeshObject.o Object.o OutputObject.o ParametricObject.o PutBamgPtr.o QuadratureObject.o SNfunctionObject.o SolveObject.o VariableObject.o getSpaceDimension.o initObject.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

