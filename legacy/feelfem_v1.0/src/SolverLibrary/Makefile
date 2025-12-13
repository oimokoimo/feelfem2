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

PROGRAM  = SolverLibrary.a
OBJS     = aistpcp90IT4SLV.o feelP2Achim.o feelP2AchimCG.o feelP2AchimLoc.o feelP2PCG.o feelP2Skyline.o feelP2iwashita.o feelfem90AMG81.o feelfem90AchimCG.o feelfem90Lumping.o feelfem90PAMG.o feelfem90PAMG81.o feelfem90SAMG20c.o feelfem90Skyline.o feelfem90smpiMUMPSCA.o feelfem90vecPCG.o feelfem90wasblk.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

