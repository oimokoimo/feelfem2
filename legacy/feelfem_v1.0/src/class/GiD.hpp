/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : GiD.hpp
 *  Date     : 2002/03/14
 *  Modified : 
 *  
 *  Purpose  :
 *  
 */

#ifndef FEM_CLASS_GID
#define FEM_CLASS_GID

#include "string.hpp"
#include "list.hpp"

#include "Mesher.hpp"

class PointObject;
class EdgeObject;
class SurfaceObject;
class VolumeObject;
class RegionObject;

class GiD  : public Mesher {
public:
  GiD();
  ~GiD();

  void GenerateCND();   // condition file
  void GenerateMAT();   // material file
  void GeneratePRB();   // problem file
  void GenerateBAS();   // output control file

  void GenerateSolvDat();  // solv_dat file generator

private:
  string problemTypeName;
  int    dimension;

  // Dirichlet
  

  // Neumann

};

#endif
