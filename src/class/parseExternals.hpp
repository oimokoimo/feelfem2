/*
 *  parseExternals.hpp
 * 
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes:  declare external variable from parser
 *
 *
 *
 */
#include "list.hpp"

class SNunit;

extern list <SNunit *>      parseGeomLst;
extern list <void *>      parseMeshLst;
extern list <void *>      parseSchemeLst;
extern list <void *>      parseVarLst;
extern list <void *>      parseElementLst;
extern list <void *>      parseQuadratureLst;
