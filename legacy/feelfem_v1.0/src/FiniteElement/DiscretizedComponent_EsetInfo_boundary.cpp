/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : DiscretizedComponent_EsetInfo_boundary.cpp
 *  Date     : 2002/04/01
 *  Modified : 2002/04/05
 *  
 *  Purpose  : Generate EsetInformation:
 *             note, element inner node vertex number must be adjusted to
 *             to actual node pattern
 *
 *
 */

#include <iostream.h>

#include "DiscretizedComponent.hpp"
#include "Element.hpp"
#include "list.hpp"
#include "string.hpp"
#include "SolveElement.hpp"
#include "EsetInfo.hpp"

EsetInfo *DiscretizedComponent::
GenerateBoundaryEsetInfo(Neumann *nPtr,
			 Element *parametricElemPtr)
{
  EsetInfo *esetInfoPtr = new EsetInfo;

  //  cerr << "UC: EsetInfo *DiscretizedComponent::GenerateBoundaryEsetInfo()\n";

  return(esetInfoPtr);
}

