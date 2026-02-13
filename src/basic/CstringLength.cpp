/*
 *  CstringLength.cpp
 *
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *
 *  Notes: count the length of the string in C style
 *
 *
 */
int CstringLength( const char *str)
{
  unsigned int length = 0;

  while(*str) {
   length++;
   str++;
  }

  return(length);
}
