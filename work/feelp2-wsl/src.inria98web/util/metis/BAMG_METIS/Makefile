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

PROGRAM  = bamg.metis.exe
OBJS     = read_element.o strindex.o strlen.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	@g++ -o $(PROGRAM) $(OBJS)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

