# Makefile: a makefile
# Location: $(TOP)/feelfem/src/. 
# Executed-By: $(TOP)/feelfem/src
#

YACC     = bison
LEX      = flex
PLUSPLUS = g++ 
OPTION   =
TOP      = 
INCLUDE  = -I../class
CFLAGS   = -DUSE_PM_AISTPCP90 -DENABLE_NLS=0
CFLAGS += -DYYENABLE_NLS=0 -DENABLE_NLS=0

X11LIB   = ../Xplot++/Xplot++.a -L/usr/X11R6/lib -lX11

.SUFFIXES:    .lex

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) -c $<

CC                      = $(PLUSPLUS)

SUBDIRS  = ../basic  \
            ./Syntax \
	   ../Geometry \
	   ../check    \
           ../Xplot++

PROGRAM  = feelfem

MAKEFILE = Makefile

SRC      = feelfem.tab.c \
           main.cpp \
           makedate.c \
           version.c  \
           debug_execute.cpp
           

OBJ      = feelfem.tab.o  \
           main.o   \
           lex.yy.o \
           version.o \
           makedate.o \
           feelfem_extern_vars.o  \
	   debug_execute.o


SYSINCLUDES  =

INCLUDES     =


#SYSLIB       = -lginac -lm -ll -lstdc++ -lc  // ginac is calling here

FLIB          = -L../lib \
		-lSyntax \
		-lConfigure \
		-lGeometry \
		-lMath \
	       	-lObject \
	       	-lProcedure \
	        -lQuadrature \
		-lGeneralSchemes \
	        -lSolve \
	        -lVariable \
		-lXplot++ \
		-lProgramModel \
		-lcheck \
		-lFiniteElement \
		-lElement \
		-lTermConvert \
 	        -lmain \
		-lSource \
		-lsystem\
                -lbasic 


SYSLIB       = -lm -ll -lstdc++ -lc

LIB          = $(SYSLIB)

FEELLIB     = ../Xplot++/Xplot++.a ../check/check.a ./Syntax/Syntax.a ../Variable/Variable.a ../Procedure/Procedure.a ../Solve/Solve.a ../Math/Math.a ../FiniteElement/FiniteElement.a ../Geometry/Geometry.a ../Object/Object.a ../Quadrature/Quadrature.a ../Configure/Configure.a ../basic/basic.a ../Math/Math.a ../check/check.a

#FEELLIB      =  ../check/check.a Syntax/Syntax.a ../check/check.a ../info/info.a ../Element/Element.a ../Mesh/Mesh.a ../Object/Object.a ../Quadrature/Quadrature.a  ../Geometry/Geometry.a ../Bamg/Bamg.a ../gid/gid.a ../Discretization/Discretization.a ../CodeGenerator/CodeGenerator.a ../MakeMakefile/MakeMakefile.a ../Main/Main.a ../SolverLibrary/SolverLibrary.a ../MatrixModel/MatrixModel.a ../ProgramModel/ProgramModel.a ../Source/Source.a ../Scheme/Scheme.a ../Solve/Solve.a ../Assign/Assign.a ../Variable/Variable.a ../FiniteElement/FiniteElement.a ../Procedure/Procedure.a ../Configure/Configure.a ../Object/Object.a ../SourceLibrary/SourceLibrary.a ../basic/basic.a ../system/system.a ../Object/Object.a ../Math/Math.a  ../Object/Object.a ../TermConvert/TermConvert.a ../Element/Element.a  ../ginac/ginac.a ../check/check.a Syntax/Syntax.a  ../GeneralSchemes/GeneralSchemes.a ../Geometry/Geometry.a ../ginac/ginac.a ../Element/Element.a  ../ginac/ginac.a ../Web/Web.a


all  :  library $(PROGRAM)


$(PROGRAM)   :  $(FEELLIB) $(OBJ)
	touch makedate.sh
	make makedate.o
	$(CC) -o $(PROGRAM) $(OBJ) $(FLIB) $(LIB) $(X11LIB) ./Syntax/Syntax.a  2>&1 |tee /dev/tty| wc -l

library :
	@for i in $(SUBDIRS); \
		do (cd $$i ; make ); \
	done

feelfem.tab.c feelfem.tab.h : feelfem.y
	$(YACC) -dtv  feelfem.y
	cp feelfem.tab.h y.tab.h
#	sed s/getenv\(\)/getenv\(char\*\)/ <y.tab.c >oimo.oimo


feelfem.tab.o :feelfem.tab.c
	$(CC)  $(CFLAGS) $(INCLUDE) -c $< -o $@

lex.yy.o : lex.yy.c lex.h feelfem.tab.h
	$(CC) -c $(CFLAGS) lex.yy.c

lex.yy.c : feelfem.lex
	$(LEX) -8 -L feelfem.lex
	

makedate.c : makedate.sh
	sh makedate.sh >makedate.c


clean     : clean_subdirs
	rm -f oimo.ps $(PROGRAM) *.o *~ core y.output lex.yy.c y.tab.[ch] \
                                      .gdbinit makedate.[co] bamg.mesh bamg.geom \
                                      feelfem.f90
	@echo "feelfem.f90, oimo.ps are deleted."

clean_subdirs :
	@for i in $(SUBDIRS); do \
		(cd $$i ; make clean) \
	done
