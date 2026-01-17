PLUSPLUS = gcc
F77      = f77
F90      = f90
CC       = $(PLUSPLUS)
CFLAGS   = 

INCLUDES = -I../class

LINKER   = $(CC)
MAKEFILE = Makefile
RANLIB   = ranlib
HDRS     = 
.SUFFIXES:   .c

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

PROGRAM  = feelfem.a
OBJS     = solvegen.o elemgen.o GetFEELFEMFP.o dcondgen.o ncondgen.o

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	$(RANLIB) $(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

