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

PROGRAM  = FiniteElement.a
OBJS     = BoundaryElementEquationNo.o BoundaryElementNodePattern.o BoundaryElementNodePattern_EqNo.o BoundaryElementNodePattern_MakeNodeInfo.o BoundaryGalerkinMethod.o BoundaryGalerkinMethod_discretize.o BoundaryIntegrandSet.o DiscretizedComponent.o DiscretizedComponent_EcalInfo.o DiscretizedComponent_EcalInfo_boundary.o DiscretizedComponent_EsetInfo.o DiscretizedComponent_EsetInfo_boundary.o EcalEvalPair.o EcalInfo.o ElementEquationNo.o ElementNodePattern.o ElementNodePattern_EqNo.o ElementNodePattern_MakeNodeInfo.o ElementNodePattern_print.o EsetInfo.o EwiseQuadEcalInfo.o GalerkinMethod.o GalerkinMethod_discretize.o IntegrandSet.o Node.o Node_print.o VariableEvalPair.o evalNodeOrder.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

