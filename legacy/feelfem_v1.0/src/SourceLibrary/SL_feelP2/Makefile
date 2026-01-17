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

PROGRAM  = SL_feelP2.a
OBJS     = SL_closefil.o SL_cptime.o SL_dat_edat.o SL_dat_ip.o SL_dat_node.o SL_dat_nodeset.o SL_dat_num.o SL_datinp.o SL_diskio.o SL_f_alloc.o SL_f_free.o SL_feelget.o SL_filset.o SL_get_ielem.o SL_get_inset.o SL_getdate.o SL_inpdat_wrt.o SL_ipd_make.o SL_ipd_nonode.o SL_ipf_nfree.o SL_report.o SL_set.o SL_zero.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../../lib/lib$(PROGRAM)
	$(RANLIB) ../../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core original/*~

