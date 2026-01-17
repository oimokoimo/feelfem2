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

PROGRAM  = MatrixModel.a
OBJS     = MT_P2CRS.o MT_P2CRSLOC.o MT_P2CRSLOCdirichlet.o MT_P2CRSLOCelem.o MT_P2CRSLOCneumann.o MT_P2CRSdirichlet.o MT_P2CRSelem.o MT_P2CRSneumann.o MT_P2PCG.o MT_P2SID.o MT_P2SIDdirichlet.o MT_P2SIDelem.o MT_P2SIDneumann.o MT_P2Skyline.o MT_aist90PCP.o MT_aist90PCPdirichlet.o MT_aist90PCPelem.o MT_aist90PCPneumann.o MT_ff90AMGCRS.o MT_ff90AMGCRSdirichlet.o MT_ff90AMGCRSelem.o MT_ff90AMGCRSneumann.o MT_ff90LUMPING.o MT_ff90LUMPINGdirichlet.o MT_ff90LUMPINGelem.o MT_ff90LUMPINGneumann.o MT_ff90PAMGCRS.o MT_ff90PAMGCRSdirichlet.o MT_ff90PAMGCRSelem.o MT_ff90PAMGCRSneumann.o MT_ff90SKYLINE.o MT_ff90SKYLINEdirichlet.o MT_ff90SKYLINEelem.o MT_ff90SKYLINEneumann.o MT_ff90smpiMUMPSCA.o MT_ff90smpiMUMPSCAdirichlet.o MT_ff90smpiMUMPSCAelem.o MT_ff90smpiMUMPSCAneumann.o MT_ff90vecCRS.o MT_ff90vecCRSdirichlet.o MT_ff90vecCRSelem.o MT_ff90vecCRSneumann.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

