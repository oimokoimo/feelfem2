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

PROGRAM  = Syntax.a
OBJS     = SNassignment.o SNassignment_CHECK.o SNassignment_CHECKvalidExpr.o \
     SNassignment_CodeGenerator.o SNassignment_CodeGeneratorMain.o SNassignment_InfoGenerate.o \
     SNbracket.o SNconstVar.o SNconstVar_CHECK.o \
     SNdiv.o SNdouble.o SNdoubleVar.o \
     SNdoubleVar_CHECK.o SNedge.o SNelement.o \
     SNelementAssignment.o SNelementDoubleVar.o SNelementDoubleVar_CHECK.o \
     SNelementIntp.o SNelementIntp_CHECK.o SNelementIntp_InfoGenerate.o \
     SNelementType.o SNelementType_CHECK.o SNelementType_CodeGenerator.o \
     SNelementType_InfoGenerate.o SNelement_CHECK.o SNelement_InfoGenerate.o \
     SNequal.o SNewiseVar.o SNewiseVar_CHECK.o \
     SNexpr.o SNexpr_CHECK.o SNexprlist.o \
     SNfemVar.o SNfemVar_CHECK.o SNfunction.o \
     SNfunctionDef.o SNfunctionDef_CHECK.o SNfunctionDef_InfoGenerate.o \
     SNge.o SNgeomDimension_CHECK.o SNgeomDimension_InfoGenerate.o \
     SNgeomEdge_Check.o SNgeomEdge_InfoGenerate.o SNgeomMaterialRegion.o \
     SNgeomMaterialRegion_CHECK.o SNgeomMaterialRegion_InfoGenerate.o SNgeomMesher_CHECK.o \
     SNgeomMesher_InfoGenerate.o SNgeomPoint_Check.o SNgeomPoint_InfoGenerate.o \
     SNgeomProblem_CHECK.o SNgeomProblem_InfoGenerate.o SNgeomRegion_Check.o \
     SNgeomRegion_InfoGenerate.o SNgeomSurface_Check.o SNgeomSurface_InfoGenerate.o \
     SNgt.o SNidentifierlist.o SNif_CHECK.o \
     SNif_CodeGenerate.o SNif_CodeGenerateMain.o SNif_InfoGenerate.o \
     SNint.o SNintVar.o SNintVar_CHECK.o \
     SNlabel_CHECK.o SNlabel_CodeGenerate.o SNlabel_CodeGenerateMain.o \
     SNlabel_InfoGenerate.o SNle.o SNlt.o \
     SNmaterialVar.o SNmaterialVar_CHECK.o SNmeshAssignment.o \
     SNmeshDoubleVar.o SNminus.o SNmul.o \
     SNname.o SNnequal.o SNoption.o \
     SNoutput.o SNoutput_CHECK.o SNoutput_CodeGenerator.o \
     SNoutput_CodeGeneratorMain.o SNoutput_InfoGenerate.o SNparametric.o \
     SNparametric_CHECK.o SNparametric_CodeGenerator.o SNpedge.o \
     SNperspect.o SNperspect_CHECK.o SNplus.o \
     SNpoint.o SNprogramModel_CHECK.o SNprogramModel_CodeGenerator.o \
     SNquadrature.o SNquadratureAssignment.o SNquadratureDoubleVar.o \
     SNquadratureGaussP.o SNquadrature_CHECK.o SNquadrature_InfoGenerate.o \
     SNregion.o SNsolve.o SNsolveDirichlet_CHECK.o \
     SNsolveDirichlet_InfoGenerate.o SNsolveNeumann.o SNsolveNeumannPairs_InfoGenerate.o \
     SNsolveNeumann_CHECK.o SNsolveNeumann_InfoGenerate.o SNsolveWeq.o \
     SNsolveWeq_CHECK.o SNsolveWeq_Infogenerate.o SNsolveWeq_WEAKEQ.o \
     SNsolve_CHECK.o SNsolve_CodeGenerate.o SNsolve_CodeGenerateMain.o \
     SNsolve_InfoGenerate.o SNsolve_InfoGenerate_BGeom.o SNsolve_InfoGenerate_Dirichlet.o \
     SNsolve_InfoGenerate_Neumann.o SNsolve_InfoGenerate_SE.o SNsolve_WEAKEQ.o \
     SNstring.o SNsub.o SNsymbol.o \
     SNunit.o SNweqTerm.o SNweqTerm_CHECK.o \
     SNweqTerm_Infogenerate.o SNweqTerm_WEAKEQ.o SNweqTerms.o \
     SNweqTerms_CHECK.o SNweqTerms_Infogenerate.o SNweqTerms_WEAKEQ.o \
     SNwrite.o SNwrite_CHECK.o SNwrite_CodeGenerate.o \
     SNwrite_CodeGenerateMain.o SNwrite_InfoGenerate.o 

all : $(PROGRAM)

$(PROGRAM): $(OBJS)
	@echo -n "Making $(PROGRAM) ..."
	ar rv $(PROGRAM) $(OBJS)
	$(RANLIB) $(PROGRAM)
	@echo "done."

clean: ; rm -f $(PROGRAM) *~ *.o core

