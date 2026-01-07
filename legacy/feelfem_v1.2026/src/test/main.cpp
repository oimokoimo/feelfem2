#include <stdlib.h>

int wrtDEBUGcodeFlag = 0;

#include "feeldef.hpp"
#include "Source.hpp"
#include "Solve.hpp"
#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "Main.hpp"

#include "MainGeneratorTemplate.hpp"

#include "ElemGeneratorTemplate.hpp"
#include "DirichletGeneratorTemplate.hpp"
#include "NeumannGeneratorTemplate.hpp"

// feelP2 version
#include "PM_feelP2.hpp"

#include "MT_P2Skyline.hpp"
#include "LIB_feelP2Skyline.hpp"

#include "MT_P2PCG.hpp"
#include "LIB_feelP2PCG.hpp"

#include "MT_P2CRS.hpp"
#include "LIB_feelP2Achim.hpp"
#include "LIB_feelP2AchimCG.hpp"

// Iwashita solver
#include "MT_P2SID.hpp"
#include "LIB_feelP2iwashita.hpp"

// Baserman's parallel solver
#include "MT_P2CRSLOC.hpp"
#include "LIB_feelP2AchimLoc.hpp"

// PAMG Solver
#include "PM_feelfem90DRAMA.hpp"
#include "MT_ff90PAMGCRS.hpp"
#include "LIB_feelfem90PAMG.hpp"
#include "LIB_feelfem90PAMG81.hpp"

#include "LIB_feelfem90AchimCG.hpp"

// AMG Solver (single processor)
#include "PM_feelfem90.hpp"
#include "MT_ff90AMGCRS.hpp"
#include "LIB_feelfem90SAMG20c.hpp"

// Washio-san's solver
#include "LIB_feelfem90wasblk.hpp"

// CRS/vector
#include "PM_feelfem90vec.hpp"
#include "MT_ff90vecCRS.hpp"
#include "LIB_feelfem90vecPCG.hpp"


#include "Object.hpp"

extern Object feelfemobj;

void ReadCtrl77dat(Solve &);

void TestSolveGenerator( Solve *solvePtr )
{
  void makeSL(int);

  // change to testMainGenerator........
  Main   *mainPtr = new Main;
  //  Scheme *schemePtr=new Scheme(&solve, SC_TYPE_SOLVE);

  //  mainPtr->AddScheme(schemePtr);


  solvePtr->MakeVariablePtrLst();

  switch(  solvePtr->GetLibraryType() ) {


  case TYPE_FEELP2SKYLINE:
    {
      LIB_feelP2Skyline<MT_P2Skyline>  *ptr = 
	new LIB_feelP2Skyline<MT_P2Skyline> ();
      //     ptr ->NormaLinearProblem();
      ptr ->NormalNonlinearProblem(solvePtr);
    }
    break;

  case TYPE_FEELP2PCG:
    {
      LIB_feelP2PCG<MT_P2PCG>  *ptr = 
	new LIB_feelP2PCG<MT_P2PCG> ();
      ptr ->NormalLinearProblem(solvePtr);
    }
    break;

  case TYPE_FEELP2ACHIM:      // No. 10
    {
      LIB_feelP2Achim<MT_P2CRS>  *ptr = 
	new LIB_feelP2Achim<MT_P2CRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      ElemGeneratorTemplate<MT_P2CRS> *ptrEG =
	new ElemGeneratorTemplate<MT_P2CRS>();
      ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_P2CRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_P2CRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_P2CRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_P2CRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }

    }
    break;

  case TYPE_FEELP2ACHIMCG:                // No. 10
    {
      LIB_feelP2AchimCG<MT_P2CRS>  *ptr = 
	new LIB_feelP2AchimCG<MT_P2CRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      ElemGeneratorTemplate<MT_P2CRS> *ptrEG =
	new ElemGeneratorTemplate<MT_P2CRS>();
      ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_P2CRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_P2CRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_P2CRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_P2CRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }

    }
    break;


  case TYPE_FEELP2IWASHITA:
    {
      LIB_feelP2iwashita<MT_P2SID>  *ptr = 
	new LIB_feelP2iwashita<MT_P2SID> ();
      ptr ->NormalLinearProblem(solvePtr);

      ElemGeneratorTemplate<MT_P2SID> *ptrEG =
	new ElemGeneratorTemplate<MT_P2SID>();
      ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_P2SID> *ptrDG =
	  new DirichletGeneratorTemplate<MT_P2SID>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_P2SID> *ptrNG =
	  new NeumannGeneratorTemplate<MT_P2SID>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }

    }
    break;

  case TYPE_FEELP2ACHIMLOC:
    {

      MainGeneratorTemplate<PM_feelP2DRAMA> *mPtr =
	new MainGeneratorTemplate<PM_feelP2DRAMA>();
      
      mPtr->NormalMainProgram(mainPtr);


      LIB_feelP2AchimLoc<MT_P2CRSLOC>  *ptr = 
	new LIB_feelP2AchimLoc<MT_P2CRSLOC> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_P2CRSLOC> *ptrDG =
	  new DirichletGeneratorTemplate<MT_P2CRSLOC>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_P2CRSLOC> *ptrNG =
	  new NeumannGeneratorTemplate<MT_P2CRSLOC>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
      break;

  case TYPE_FEELFEM90PAMG:
    {

      MainGeneratorTemplate<PM_feelfem90DRAMA> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90DRAMA>();
      
      mPtr->NormalMainProgram(mainPtr);


      LIB_feelfem90PAMG<MT_ff90PAMGCRS>  *ptr = 
	new LIB_feelfem90PAMG<MT_ff90PAMGCRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90PAMGCRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90PAMGCRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_ff90PAMGCRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_ff90PAMGCRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
      break;


  case TYPE_FEELFEM90PAMG81:
    {

      MainGeneratorTemplate<PM_feelfem90DRAMA> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90DRAMA>();
      
      mPtr->NormalMainProgram(mainPtr);


      LIB_feelfem90PAMG81<MT_ff90PAMGCRS>  *ptr = 
	new LIB_feelfem90PAMG81<MT_ff90PAMGCRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90PAMGCRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90PAMGCRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_ff90PAMGCRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_ff90PAMGCRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
      break;

  case TYPE_FEELFEM90SAMG20c:    // No. 8   single processor AMG solver
    {

      MainGeneratorTemplate<PM_feelfem90> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90>();
      
      mPtr->NormalMainProgram(mainPtr);


      LIB_feelfem90SAMG20c<MT_ff90AMGCRS>  *ptr = 
	new LIB_feelfem90SAMG20c<MT_ff90AMGCRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90AMGCRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90AMGCRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_ff90AMGCRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_ff90AMGCRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
      break;


  case TYPE_FEELFEM90WASBLK:    // No. 8   single processor AMG solver
    {

      MainGeneratorTemplate<PM_feelfem90> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90>();
      
      mPtr->NormalMainProgram(mainPtr);


      LIB_feelfem90wasblk<MT_ff90AMGCRS>  *ptr = 
	new LIB_feelfem90wasblk<MT_ff90AMGCRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90AMGCRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90AMGCRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_ff90AMGCRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_ff90AMGCRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
      break;

  case TYPE_FEELFEM90ACHIMCG:    // No. 9
    {
      MainGeneratorTemplate<PM_feelfem90> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90>();
      
      mPtr->NormalMainProgram(mainPtr);


      LIB_feelfem90AchimCG<MT_ff90AMGCRS>  *ptr = 
	new LIB_feelfem90AchimCG<MT_ff90AMGCRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90AMGCRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90AMGCRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_ff90AMGCRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_ff90AMGCRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
    break;


  case TYPE_FEELFEM90VECPCG:    // No. 11   single PE vector processing
    {

      MainGeneratorTemplate<PM_feelfem90vec> *mPtr =
	new MainGeneratorTemplate<PM_feelfem90vec>();
      
      mPtr->NormalMainProgram(mainPtr);


      LIB_feelfem90vecPCG<MT_ff90vecCRS>  *ptr = 
	new LIB_feelfem90vecPCG<MT_ff90vecCRS> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90vecCRS> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90vecCRS>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_ff90vecCRS> *ptrNG =
	  new NeumannGeneratorTemplate<MT_ff90vecCRS>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
      break;


      
  default:
    break;
  }

  makeSL(   solvePtr->GetLibraryType()  );


  return;

}
void SetSolve(Solve *solvePtr)
{
  cout << "INPUT library type\n" 
       << " 1: Fortran90/Drama data model/Distributed CRS/Parallel AMG \n"
       << " 2: Fortran77/Drama data model/Distributed CRS/Achim Loc    \n"
       << " 3: Fortran77/P2 data model   /CRS            /Achim single \n"
       << " 4: Fortran77/P2 data model   /PCG            /PCG          \n"
       << " 5: Fortran77/P2 data model   /Skyline        /Skyline direct\n"
       << " 6: Fortran77/P2 data model   /SID            /Iwashita\n" 
       << " 7: Fortran90/Drama data model/Distributed CRS/Parallel AMG81\n"
       << " 8: Fortran90/P2f90 data model/CRS/Single SAMG20c\n"
       << " 9: Fortran90/P2f90 data model/CRS/Single Achim CG\n"
       << "10: Fortran90/P2    data model/CRS/Single Achim CG(F77!!!)\n"
       << "11: Fortran90/P2    data model/vecCRS         /Vector PCG\n"
       << "12: Fortran90/P2    data model/CRS/washio block\n"
    ;
  

  int input;
  cout << "? =";
  cin  >> input;
  switch(input) {
  case 1:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELFEM90PAMG); 
    break;
  case 2:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELP2ACHIMLOC); 
    break;
  case 3:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELP2ACHIM); 
    break;
  case 4:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELP2PCG);
    break;
  case 5:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELP2SKYLINE);
    break;

  case 6:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELP2IWASHITA);
    break;

  case 7:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELFEM90PAMG81); 
    break;

  case 8:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELFEM90SAMG20c); 
    break;

  case 9:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELFEM90ACHIMCG); 
    break;

  case 10:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELP2ACHIMCG); 
    break;

  case 11:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELFEM90VECPCG);
    break;

  case 12:
    cout <<"No. " << input << " selected.\n";
    solvePtr->testSetLibraryType(TYPE_FEELFEM90WASBLK);
    break;


  default:
    cout << "Illegal number, abort.\n";
    exit(1);
  }

  return;
}


void main()
{
  Source init("oimo.f");  // Just for initialize File pointer
  Solve solve;

  //  Variable c = feelfemobj.GetVariableWithNameType( "b",VAR_EWISE);
  cout << "goto SetSolve\n";
  SetSolve( &solve );

  cout << "goto ReadCtrl77dat\n";
  ReadCtrl77dat(solve);

  cout << "goto TestSolveGenerator\n";
  TestSolveGenerator(&solve);

}



int getSpaceDimension(void)
{
  return ( 2 );
}
