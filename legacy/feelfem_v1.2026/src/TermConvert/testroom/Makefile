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
STDLIBS  = -lstdc++
MYLIBS   = ../TermConvert.a ../../basic/basic.a 
.SUFFIXES:   .cpp

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

PROGRAM  = testtc
OBJS     = test.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS) 
	@echo -n "Making $(PROGRAM) ..."
	$(LINKER) -o $(PROGRAM) $(OBJS) $(MYLIBS) $(STDLIBS)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

