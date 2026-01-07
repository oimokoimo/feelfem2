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

PROGRAM  = SolveGenerator.a
OBJS     = GenerateSolve_feelfem90achimcg.o GenerateSolve_feelfem90pamg.o GenerateSolve_feelfem90pamg81.o GenerateSolve_feelfem90samg20c.o GenerateSolve_feelp2achim.o GenerateSolve_feelp2achimloc.o GenerateSolve_feelp2iwashita.o GenerateSolve_feelp2pcg.o GenerateSolve_feelp2skyline.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	$(RANLIB) $(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

