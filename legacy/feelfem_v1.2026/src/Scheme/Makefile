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

PROGRAM  = Scheme.a
OBJS     = AssignScheme.o AssignSchemeVirtuals.o Assign_NormalAssignment.o Assign_NormalAssignmentEwiseQuad.o Assign_NormalAssignmentIntegral.o DirichletNormalLinear.o DirichletScheme.o DirichletSchemeVirtuals.o DoElemVirtuals.o EcalNormalElementStiffness.o EcalScheme.o EcalSchemeVirtuals.o ElemDistributedAssembly.o ElemNormalAssembly.o ElemNormalVectorAssembly.o ElemScheme.o ElemSchemeVirtuals.o MainNormalMainProgram.o MainScheme.o MainSchemeVirtuals.o NeumannNormalLinear.o NeumannScheme.o NeumannSchemeVirtuals.o OutputScheme.o OutputSchemeVirtuals.o Output_GiD.o SolveNormalLinearProblem.o SolveNormalNonlinearProblem.o SolveScheme.o SolveSchemeVirtuals.o initial.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

