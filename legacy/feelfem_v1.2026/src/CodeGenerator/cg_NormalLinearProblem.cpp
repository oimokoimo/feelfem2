/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : cg_NormalLinearProblem.cpp
 *  Date     : 2001/07/11
 *  Modified : 
 *  
 *  Purpose  : code generator for the scheme NormalLinearProblem
 *  
 */

#include "feeldef.hpp"

#include "Configure.hpp"   // for LIBS  (2003/01/16)
#include "feelfuncs.hpp"

#include "Source.hpp"

#include "Solve.hpp"
#include "Dirichlet.hpp"
#include "Neumann.hpp"
#include "Main.hpp"

#include "ElemGeneratorTemplate.hpp"
#include "DirichletGeneratorTemplate.hpp"
#include "NeumannGeneratorTemplate.hpp"
#include "EcalGeneratorTemplate.hpp"

//=======================
// ProgramModel [feelP2]
//=======================
#include "PM_feelP2.hpp"

// P2Skyline(Skyline)
#include "MT_P2Skyline.hpp"
#include "LIB_feelP2Skyline.hpp"

// P2PCG(PCG)
#include "MT_P2PCG.hpp"
#include "LIB_feelP2PCG.hpp"

// P2CRS(Achim,AchimCG)
#include "MT_P2CRS.hpp"
#include "LIB_feelP2Achim.hpp"
#include "LIB_feelP2AchimCG.hpp"

// P2SID(Iwashita)
#include "MT_P2SID.hpp"
#include "LIB_feelP2iwashita.hpp"

/////////////////////////////////////////

//=======================
// ProgramModel [feelP2]
//=======================
#include "PM_feelP2DRAMA.hpp"

// P2CRSLOC(AchimLoc)
#include "MT_P2CRSLOC.hpp"
#include "LIB_feelP2AchimLoc.hpp"

/////////////////////////////////////////

//==============================
// ProgramModel [feelfem90DRAMA]
//==============================
#include "PM_feelfem90DRAMA.hpp"
#include "SL_MT_ff90PAMGCRS.hpp"

// ff90PAMGCRS(PAMG,PAMG81,AchimCG)
#include "MT_ff90PAMGCRS.hpp"
#include "LIB_feelfem90PAMG.hpp"
#include "LIB_feelfem90PAMG81.hpp"
#include "LIB_feelfem90AchimCG.hpp"

/////////////////////////////////////////

//=========================
// ProgramModel [feelfem90]
//=========================
#include "PM_feelfem90.hpp"

// AMGCRS(SAMG20c)
#include "MT_ff90AMGCRS.hpp"
#include "LIB_feelfem90SAMG20c.hpp"
#include "SL_MT_ff90AMGCRS.hpp"

// SKYLINE
#include "MT_ff90SKYLINE.hpp"
#include "LIB_feelfem90Skyline.hpp"
#include "SL_MT_ff90SKYLINE.hpp"
#include "SL_LIB_feelfem90Skyline.hpp"

// LUMPING

#include "MT_ff90LUMPING.hpp"
#include "LIB_feelfem90Lumping.hpp"

// MUMPSCA
#include "PM_feelfem90smpi.hpp"
#include "MT_ff90smpiMUMPSCA.hpp"
#include "LIB_feelfem90smpiMUMPSCA.hpp"
#include "SL_MT_ff90smpiMUMPSCA.hpp" 

//=========================
// ProgramModel [aistpcp90]
//=========================
#include "PM_aistpcp90.hpp"

// IT4SLV
#include "MT_aist90PCP.hpp"
#include "LIB_aistpcp90IT4SLV.hpp"




void cg_NormalLinearProblem( Solve *solvePtr )
{
  // for ecal routine
  switch(  solvePtr->GetProgramModelType() ) {
  case TYPE_FEELFEM90:
    {
      EcalGeneratorTemplate <PM_feelfem90> *ptr =
	new       EcalGeneratorTemplate <PM_feelfem90>();
      
      ptr->NormalElementStiffness(solvePtr,
				  solvePtr->GetIthSolveElementPtr(0));
    }
    break;


  case TYPE_AISTPCP90:
    {
      EcalGeneratorTemplate <PM_aistpcp90> *ptr =
	new       EcalGeneratorTemplate <PM_aistpcp90>();
      
      ptr->NormalElementStiffness(solvePtr,
				  solvePtr->GetIthSolveElementPtr(0));
    }
    break;

  case TYPE_FEELFEM90SMPI:
    {
      EcalGeneratorTemplate <PM_feelfem90smpi> *ptr =
	new       EcalGeneratorTemplate <PM_feelfem90smpi>();
      
      ptr->NormalElementStiffness(solvePtr,
				  solvePtr->GetIthSolveElementPtr(0));
    }
    break;

  case TYPE_FEELFEM90DRAMA:
    {
      EcalGeneratorTemplate <PM_feelfem90DRAMA> *ptr =
	new       EcalGeneratorTemplate <PM_feelfem90DRAMA>();
      
      ptr->NormalElementStiffness(solvePtr,
				  solvePtr->GetIthSolveElementPtr(0));
    }
    break;


  default:
    cerr << "********************************************************" << endl;
    cerr << "*GENERATION ECAL ROUTINE in cg_NormalLinearProblem.cpp *" << endl;
    cerr << "*Not support ProgramModel.                             *" << endl;
    cerr << "********************************************************" << endl;
    break;
  }



  // fore elem,solve, dcond etc.
  switch(  solvePtr->GetLibraryType() ) {
    //
//  case TYPE_FEELP2SKYLINE:
//    {
//      LIB_feelP2Skyline<MT_P2Skyline>  *ptr = 
//	new LIB_feelP2Skyline<MT_P2Skyline> ();
//  //         ptr ->NormaLinearProblem();
//      ptr ->NormalNonlinearProblem(solvePtr);
//    }
//    break;

//  case TYPE_FEELP2PCG:
//    {
//      LIB_feelP2PCG<MT_P2PCG>  *ptr = 
//	new LIB_feelP2PCG<MT_P2PCG> ();
//      ptr ->NormalLinearProblem(solvePtr);
//    }
//    break;
//
//  case TYPE_FEELP2ACHIM:
//    {
//      LIB_feelP2Achim<MT_P2CRS>  *ptr = 
//	new LIB_feelP2Achim<MT_P2CRS> ();
//      ptr ->NormalLinearProblem(solvePtr);
//
//      ElemGeneratorTemplate<MT_P2CRS> *ptrEG =
//	new ElemGeneratorTemplate<MT_P2CRS>();
//      ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));
//
//      int dconds;
//      dconds = solvePtr->GetDconds();
//      for(int i=0;i<dconds;i++) {
//	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
//	DirichletGeneratorTemplate<MT_P2CRS> *ptrDG =
//	  new DirichletGeneratorTemplate<MT_P2CRS>();
//	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
//      }
//
//      int nconds;
//      nconds = solvePtr->GetNconds();
//      for(int i=0;i<nconds;i++) {
//	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
//	NeumannGeneratorTemplate<MT_P2CRS> *ptrNG =
//	  new NeumannGeneratorTemplate<MT_P2CRS>();
//	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
//      }
//
//    }
//    break;
//
//  case TYPE_FEELP2ACHIMCG:                // No. 10
//    {
//      LIB_feelP2AchimCG<MT_P2CRS>  *ptr = 
//	new LIB_feelP2AchimCG<MT_P2CRS> ();
//      ptr ->NormalLinearProblem(solvePtr);
//
//      ElemGeneratorTemplate<MT_P2CRS> *ptrEG =
//	new ElemGeneratorTemplate<MT_P2CRS>();
//      ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));
//
//      int dconds;
//      dconds = solvePtr->GetDconds();
//      for(int i=0;i<dconds;i++) {
//	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
//	DirichletGeneratorTemplate<MT_P2CRS> *ptrDG =
//	  new DirichletGeneratorTemplate<MT_P2CRS>();
//	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
//      }

//      int nconds;
//      nconds = solvePtr->GetNconds();
//      for(int i=0;i<nconds;i++) {
//	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
//	NeumannGeneratorTemplate<MT_P2CRS> *ptrNG =
//	  new NeumannGeneratorTemplate<MT_P2CRS>();
//	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
//      }
//
//    }
//    break;


//  case TYPE_FEELP2IWASHITA:
//    {
//      LIB_feelP2iwashita<MT_P2SID>  *ptr = 
//	new LIB_feelP2iwashita<MT_P2SID> ();
//      ptr ->NormalLinearProblem(solvePtr);
//
//      ElemGeneratorTemplate<MT_P2SID> *ptrEG =
//	new ElemGeneratorTemplate<MT_P2SID>();
//      ptrEG->NormalAssembly(solvePtr,solvePtr->GetIthSolveElementPtr(0));
//
//      int dconds;
//      dconds = solvePtr->GetDconds();
//      for(int i=0;i<dconds;i++) {
//	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
//	DirichletGeneratorTemplate<MT_P2SID> *ptrDG =
//	  new DirichletGeneratorTemplate<MT_P2SID>();
//	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
//      }
//
//      int nconds;
//      nconds = solvePtr->GetNconds();
//      for(int i=0;i<nconds;i++) {
//	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
//	NeumannGeneratorTemplate<MT_P2SID> *ptrNG =
//	  new NeumannGeneratorTemplate<MT_P2SID>();
//	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
//      }
//
//    }
//    break;

//  case TYPE_FEELP2ACHIMLOC:
//    {
//      LIB_feelP2AchimLoc<MT_P2CRSLOC>  *ptr = 
//	new LIB_feelP2AchimLoc<MT_P2CRSLOC> ();
//      ptr ->NormalLinearProblem(solvePtr);
//
//      int dconds;
//      dconds = solvePtr->GetDconds();
//      for(int i=0;i<dconds;i++) {
//	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
//	DirichletGeneratorTemplate<MT_P2CRSLOC> *ptrDG =
//	  new DirichletGeneratorTemplate<MT_P2CRSLOC>();
//	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
//      }
//
//      int nconds;
//      nconds = solvePtr->GetNconds();
//      for(int i=0;i<nconds;i++) {
//	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
//	NeumannGeneratorTemplate<MT_P2CRSLOC> *ptrNG =
//	  new NeumannGeneratorTemplate<MT_P2CRSLOC>();
//	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
//      }
//
//
//    }
//  
//
//    break;

  case TYPE_FEELFEM90PAMG:
    {
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
      SL_MT_ff90PAMGCRS        *slmatPtr = new SL_MT_ff90PAMGCRS();
      slmatPtr ->generateLibrary();

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

      SL_MT_ff90AMGCRS        *slmatPtr = new SL_MT_ff90AMGCRS();
      slmatPtr ->generateLibrary();

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

  case TYPE_FEELFEM90ACHIMCG:    // No. 9
    {
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


  case TYPE_FEELFEM90SKYLINE:    // No. 13
    {
      SL_MT_ff90SKYLINE        *slmatPtr = new SL_MT_ff90SKYLINE();
      SL_LIB_feelfem90Skyline  *sllibPtr = new SL_LIB_feelfem90Skyline();
      slmatPtr ->generateLibrary();
      sllibPtr ->generateLibrary();

 

      // solve
      LIB_feelfem90Skyline<MT_ff90SKYLINE>  *ptr = 
	new LIB_feelfem90Skyline<MT_ff90SKYLINE> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90SKYLINE> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90SKYLINE>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
      	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
      	NeumannGeneratorTemplate<MT_ff90SKYLINE> *ptrNG =
      	  new NeumannGeneratorTemplate<MT_ff90SKYLINE>();
      	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }

    }
      break;


  case TYPE_AISTPCP90IT4SLV:    // No. 14  aist PCP IT4SLV
    {
      //   SL_MT_ff90SKYLINE        *slmatPtr = new SL_MT_ff90SKYLINE();
      //   SL_LIB_feelfem90Skyline  *sllibPtr = new SL_LIB_feelfem90Skyline();
      //      slmatPtr ->generateLibrary();
      //      sllibPtr ->generateLibrary();

      LIB_aistpcp90IT4SLV<MT_aist90PCP>  *ptr = 
	new LIB_aistpcp90IT4SLV<MT_aist90PCP> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_aist90PCP> *ptrDG =
	  new DirichletGeneratorTemplate<MT_aist90PCP>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
	NeumannGeneratorTemplate<MT_aist90PCP> *ptrNG =
	  new NeumannGeneratorTemplate<MT_aist90PCP>();
	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }


    }
      break;

  case TYPE_FEELFEM90LUMPING:    // No. 15
    {

      // no outer library required.
      //    SL_MT_ff90LUMPING        *slmatPtr = new SL_MT_ff90LUMPING();
      //    SL_LIB_feelfem90Lumping  *sllibPtr = new SL_LIB_feelfem90Lumping();
      //    slmatPtr ->generateLibrary();
      //    sllibPtr ->generateLibrary();

      // solve
      LIB_feelfem90Lumping<MT_ff90LUMPING>  *ptr = 
	new LIB_feelfem90Lumping<MT_ff90LUMPING> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90LUMPING> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90LUMPING>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
      	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
      	NeumannGeneratorTemplate<MT_ff90LUMPING> *ptrNG =
      	  new NeumannGeneratorTemplate<MT_ff90LUMPING>();
      	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }

    }
      break;


  case TYPE_FEELFEM90SMPIMUMPSCA:    // No. 16
    {

      // matrix related fixed library
      SL_MT_ff90smpiMUMPSCA    *slmatPtr = new SL_MT_ff90smpiMUMPSCA();
      slmatPtr ->generateLibrary(); 

      // library necessary for MUMPSCA
      feelfemconf.UseSolverLibrary( TYPE_FEELFEM90SMPIMUMPSCA );


      // solve
      LIB_feelfem90smpiMUMPSCA<MT_ff90smpiMUMPSCA>  *ptr = 
	new LIB_feelfem90smpiMUMPSCA<MT_ff90smpiMUMPSCA> ();
      ptr ->NormalLinearProblem(solvePtr);

      int dconds;
      dconds = solvePtr->GetDconds();
      for(int i=0;i<dconds;i++) {
	Dirichlet *dPtr = solvePtr->GetIthDirichletDataPtr( i );
	DirichletGeneratorTemplate<MT_ff90smpiMUMPSCA> *ptrDG =
	  new DirichletGeneratorTemplate<MT_ff90smpiMUMPSCA>();
	ptrDG->DirichletNormalLinear(solvePtr,dPtr);
      }

      int nconds;
      nconds = solvePtr->GetNconds();
      for(int i=0;i<nconds;i++) {
      	Neumann *nPtr = solvePtr->GetIthNeumannDataPtr( i );
      	NeumannGeneratorTemplate<MT_ff90smpiMUMPSCA> *ptrNG =
      	  new NeumannGeneratorTemplate<MT_ff90smpiMUMPSCA>();
      	ptrNG->NeumannNormalLinear(solvePtr,nPtr);
      }

    }
      break;
      
  default:

    cerr << "ILLEGAL MATRIX TYPE\n";
    assert(1==0);
    break;
  }

  return;

}
