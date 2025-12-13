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

PROGRAM  = check.a
OBJS     = SystemError.o SystemErrorFilename.o check.o element_check.o element_create.o element_quadrature_check_conflict.o geom_materialRegion_check.o geom_materialRegion_create.o geometryObject_check.o geometryObject_generate.o geometry_generate.o isDefined.o isEtypeName.o isIntrinsicFunction.o isSystemVariable.o mesh_check_conflict.o mesh_check_dimension.o mesh_check_eval.o mesh_point_conflict.o procedure_create.o quadrature_check.o quadrature_create.o scheme_assign_check.o scheme_assign_create.o scheme_elementType_check.o scheme_elementType_create.o scheme_io_check.o scheme_io_create.o scheme_label_if_check.o scheme_label_if_create.o scheme_parametric_check.o scheme_pm_check.o scheme_solve_check.o scheme_solve_create.o scheme_solve_geom_check.o scheme_solve_geom_create.o scheme_userfunc_arg_check.o scheme_write_check.o scheme_write_create.o set_geometryObject_default.o store_geometry_geometryObject.o user_func_check_create.o var_check_conflict.o var_check_defined.o var_check_initial.o var_check_material.o var_create.o var_material_region_check.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	cp $(PROGRAM) ../lib/lib$(PROGRAM)
	$(RANLIB) ../lib/lib$(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

