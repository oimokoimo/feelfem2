#include "SL_feelfem90DRAMA.hpp"
#include "SL_feelfem90.hpp"
#include "SL_feelP2.hpp"
#include "SL_MT_P2CRS.hpp"
#include "SL_MT_P2Skyline.hpp"
#include "SL_MT_ff90PAMGCRS.hpp"
#include "SL_MT_ff90AMGCRS.hpp"
#include "SL_LIB_feelP2Achim.hpp"
#include "SL_LIB_feelP2Skyline.hpp"
#include "SL_LIB_feelfem90SAMG20c.hpp"


void makeSL( int type )
{


  switch( type ) {

  case TYPE_FEELFEM90SAMG20c:
    {
      SL_feelfem90 *slPtr = new SL_feelfem90();
      slPtr ->generateLibrary();

      SL_MT_ff90AMGCRS *slmatPtr = new SL_MT_ff90AMGCRS();
      slmatPtr ->generateLibrary();      

      // Solver code is not available, this generates only user_coo routine
      SL_LIB_feelfem90SAMG20c *sllibPtr = new SL_LIB_feelfem90SAMG20c();
      sllibPtr ->generateLibrary();      


      break;
    }

  case TYPE_FEELFEM90PAMG:
    {
      SL_feelfem90DRAMA *slPtr = new SL_feelfem90DRAMA();
      slPtr ->generateLibrary();


      SL_MT_ff90PAMGCRS *slmatPtr = new SL_MT_ff90PAMGCRS();
      slmatPtr ->generateLibrary();      


      break;
    }


  case TYPE_FEELFEM90ACHIMCG:     
    {
      SL_feelfem90 *slPtr = new SL_feelfem90();
      slPtr ->generateLibrary();

      SL_MT_ff90AMGCRS *slmatPtr = new SL_MT_ff90AMGCRS();
      slmatPtr ->generateLibrary();      


      break;
    }

  case TYPE_FEELP2ACHIM:
    {
      SL_feelP2 *slPtr = new SL_feelP2();
      slPtr ->generateLibrary();

      SL_MT_P2CRS *slmatPtr = new SL_MT_P2CRS();
      slmatPtr ->generateLibrary();      

      SL_LIB_feelP2Achim *sllibPtr = new SL_LIB_feelP2Achim();
      sllibPtr ->generateLibrary();      

      break;
    }

  case TYPE_FEELP2ACHIMCG:
    {
      SL_feelP2 *slPtr = new SL_feelP2();
      slPtr ->generateLibrary();

      SL_MT_P2CRS *slmatPtr = new SL_MT_P2CRS();
      slmatPtr ->generateLibrary();      

      break;
    }


  case TYPE_FEELP2SKYLINE:
    {
      SL_feelP2 *slPtr = new SL_feelP2();
      slPtr ->generateLibrary();

      SL_MT_P2Skyline *slmatPtr = new SL_MT_P2Skyline();
      slmatPtr ->generateLibrary();      

      SL_LIB_feelP2Skyline *sllibPtr = new SL_LIB_feelP2Skyline();
      sllibPtr ->generateLibrary();      

      break;
    }
 

  default:
    cerr << "Now not supported(SourceLibraries)\n";
  }




  //
  Source *makefileObj = new Source();

  makefileObj->makeMakefile(1);


  return;
}

