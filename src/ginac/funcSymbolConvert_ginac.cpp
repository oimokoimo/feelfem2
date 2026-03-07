/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2002
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : funcConvert.cpp
 *  Date     : 2002/02/18
 *  Modified : 
 *  
 *  Purpose  :   _n12(x,y,z) -> _n12   function symbol modifier
 *  
 *  limitation    not support   oimo_n12(x,y,z) etc.
 *  
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
#include <assert.h>
#include <iostream>

static int is_digit(char c) { return (c >= '0' && c <= '9'); }
static int is_ident_char(char c)
{
  return ( (c >= 'A' && c <= 'Z') ||
           (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') ||
           (c == '_') );
}

static int match_xy_or_xyz(const char *p)
{
  /* (x,y) */
  if (p[0] == '(' &&
      p[1] == 'x' &&
      p[2] == ',' &&
      p[3] == 'y' &&
      p[4] == ')') return 5;

  /* (x,y,z) */
  if (p[0] == '(' &&
      p[1] == 'x' &&
      p[2] == ',' &&
      p[3] == 'y' &&
      p[4] == ',' &&
      p[5] == 'z' &&
      p[6] == ')') return 7;

  return 0;
}

void funcSymbolConvert_ginac(char *cp)
{
  char *start = cp;
  char *wrt   = cp;

  std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
  std::cerr << "Welcome to funcSymbolConvert_ginac\n";
  std::cerr << "buf(before) = " << start << "\n";

  while (*cp) {

    /* "ff_n" を安全にチェック（cp[3] まで読めることを保証） */
    if (!(cp[0] == 'f' &&
          cp[1] != '\0' && cp[1] == 'f' &&
          cp[2] != '\0' && cp[2] == '_' &&
          cp[3] != '\0' && cp[3] == 'n')) {
      *wrt++ = *cp++;
      continue;
    }

    /* boundary: 直前が識別子文字なら対象外（oimo_ff_n... を除外） */
    if (cp != start && is_ident_char(cp[-1])) {
      *wrt++ = *cp++;
      continue;
    }

    /* ff_n の後の数字列 */
    int d = 0;
    while (is_digit(cp[4 + d])) d++;

    if (d < 1 || d > 3) {   /* ここを (d < 1) にすると桁数無制限 */
      *wrt++ = *cp++;
      continue;
    }

    /* 直後が (x,y) or (x,y,z) なら削る */
    int consumed = match_xy_or_xyz(cp + 4 + d);
    if (consumed == 0) {
      *wrt++ = *cp++;
      continue;
    }

    /* "ff_n" + digits だけコピーして、引数部分をスキップ */
    for (int i = 0; i < 4 + d; i++) {
      *wrt++ = *cp++;
    }
    cp += consumed;  /* "(x,y)" or "(x,y,z)" を捨てる */
  }

  *wrt = '\0';              /* 先に終端してから表示 */
  std::cerr << "buf(after ) = " << start << "\n";
  std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

  assert(*wrt == '\0');
}
