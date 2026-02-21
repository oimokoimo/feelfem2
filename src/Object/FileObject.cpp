/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : FileObject.cpp
 *  Date     : 2002/08/23
 *  Modified : 
 *  
 *  Purpose  :
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:
 *  
 */

#include "Object.hpp"

void Object::StoreFileObject(const char *fname)
{
  fileObjectStrLst.add( fname );
  fileObjects++;
  return;
}

int Object::GetFileObjects(void)
{
  return(fileObjects);
}



void Object::StoreTmpFileObject(const char *fname)
{
  tmpFileObjectStrLst.add( fname );
  tmpFileObjects++;
  return;
}

int Object::GetTmpFileObjects(void)
{
  return(tmpFileObjects);
}


