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

PROGRAM  = Element.a
OBJS     = BoundaryElement.o Element.o GetBoundaryInterp_cube.o GetBoundaryInterp_rect.o GetBoundaryInterp_tetra.o GetBoundaryInterp_tri.o Interpolation.o Interpolation_print.o MakeBoundaryElement_cube.o MakeBoundaryElement_rect.o MakeBoundaryElement_tetra.o MakeBoundaryElement_tri.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

