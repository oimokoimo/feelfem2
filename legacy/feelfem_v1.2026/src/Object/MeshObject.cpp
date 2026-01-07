/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : MeshObject.hpp
 *  Date     : 2002/03/23
 *  Modified : 
 *  
 *  Purpose  : add used_mesher_code (02/03/23)
 *  
 */

#include "Object.hpp"

void Object::SetMesherCode(int n)
{
  used_mesher_code = n;
  return;
}

int Object::GetMesherCode(void)
{
  return(used_mesher_code);
}
