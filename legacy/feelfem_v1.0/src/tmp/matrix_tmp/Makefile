PLUSPLUS = g++
F77      = f77
F90      = f90
CC       = $(PLUSPLUS)
CFLAGS   = 

INCLUDES = -I../../class

LINKER   = $(CC)
MAKEFILE = Makefile
RANLIB   = ranlib
HDRS     = 
.SUFFIXES:   .cpp

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

PROGRAM  = mat_test
OBJS     = mat_test.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(LINKER) -o $(PROGRAM) $(OBJS) ../../basic/basic.a -lstdc++ 

clean: ; rm -f $(PROGRAM) *~ *.o core

