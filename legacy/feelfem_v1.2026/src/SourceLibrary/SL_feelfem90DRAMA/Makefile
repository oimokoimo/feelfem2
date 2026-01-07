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

PROGRAM  = SL_feelfem90DRAMA.a
OBJS     = SL_abortmodule.o SL_datatrans.o SL_dramaDataModel.o SL_feelfem90mp.o SL_femDataType.o SL_fileread.o SL_numeric.o SL_preport90.o SL_probInfoDistribute.o SL_subSolveDrama.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../../lib/lib$(PROGRAM)
	$(RANLIB) ../../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core original/*~

