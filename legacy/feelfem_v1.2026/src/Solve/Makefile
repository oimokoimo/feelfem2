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

PROGRAM  = Solve.a
OBJS     = Dirichlet.o Neumann.o Neumann_CodeGenerateSub.o Neumann_InfoGenerate.o Neumann_discretize.o Neumann_print.o Solve.o SolveElement.o SolveElement_CodeGenerateSub.o SolveElement_InfoGenerate.o SolveElement_discretize.o SolveElement_print.o Solve_InfoGenerate.o Solve_print.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

