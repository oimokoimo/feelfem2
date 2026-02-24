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

PROGRAM  = ProgramModel.a
OBJS     = aistpcp90.o aistpcp90_assign.o aistpcp90_coroutine.o aistpcp90_dirichlet.o aistpcp90_ecal.o aistpcp90_elem.o aistpcp90_eset.o aistpcp90_ewquad.o aistpcp90_integral.o aistpcp90_main.o aistpcp90_mainScheme.o aistpcp90_main_coroutine.o aistpcp90_main_write.o aistpcp90_neumann.o aistpcp90_output.o aistpcp90_solve.o feelP2.o feelP2DRAMA.o feelP2DRAMA_main.o feelP2DRAMA_mainScheme.o feelP2DRAMA_main_coroutine.o feelfem90.o feelfem90DRAMA.o feelfem90DRAMA_assign.o feelfem90DRAMA_coroutine.o feelfem90DRAMA_dirichlet.o feelfem90DRAMA_ecal.o feelfem90DRAMA_elem.o feelfem90DRAMA_eset.o feelfem90DRAMA_ewquad.o feelfem90DRAMA_integral.o feelfem90DRAMA_main.o feelfem90DRAMA_mainScheme.o feelfem90DRAMA_main_coroutine.o feelfem90DRAMA_neumann.o feelfem90DRAMA_output.o feelfem90DRAMA_solve.o feelfem90_assign.o feelfem90_coroutine.o feelfem90_dirichlet.o feelfem90_ecal.o feelfem90_elem.o feelfem90_eset.o feelfem90_ewquad.o feelfem90_integral.o feelfem90_main.o feelfem90_mainScheme.o feelfem90_main_coroutine.o feelfem90_main_write.o feelfem90_neumann.o feelfem90_output.o feelfem90_solve.o feelfem90smpi.o feelfem90smpi_assign.o feelfem90smpi_coroutine.o feelfem90smpi_dirichlet.o feelfem90smpi_ecal.o feelfem90smpi_elem.o feelfem90smpi_eset.o feelfem90smpi_ewquad.o feelfem90smpi_integral.o feelfem90smpi_main.o feelfem90smpi_mainScheme.o feelfem90smpi_main_coroutine.o feelfem90smpi_main_write.o feelfem90smpi_neumann.o feelfem90smpi_output.o feelfem90smpi_solve.o feelfem90vec.o feelfem90vec_coroutine.o feelfem90vec_dirichlet.o feelfem90vec_elem.o feelfem90vec_main.o feelfem90vec_mainScheme.o feelfem90vec_neumann.o feelfem90vec_solve.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

