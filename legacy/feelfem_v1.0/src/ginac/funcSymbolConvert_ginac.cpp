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
 */
#include <assert.h>

void funcSymbolConvert_ginac(char *cp )
{
  char *wrt= cp;
  while(*cp) {
    
    if(*cp != '_') {
      *wrt = *cp;
      wrt++; 
      cp++;
      continue;
    }

    if(*(cp+1) != 'n' ||
       *(cp+2)  > '9' || *(cp+2)  < '0'    ) {
      *wrt = *cp;
      wrt++; 
      cp++;
      continue;
    }
    
    if(*(cp+3) == '(' &&
       *(cp+4) == 'x' &&
       *(cp+5) == ',' &&
       *(cp+6) == 'y' &&
       *(cp+7) == ',' &&
       *(cp+8) == 'z' &&
       *(cp+9) == ')'   ) {
      
      *wrt = *cp; wrt++;  cp++;   // _ 
      *wrt = *cp; wrt++;  cp++;   // n
      *wrt = *cp; wrt++;  cp++;   // 0-9

      cp += 7;
      continue;
    }

    if(*(cp+3) >= '0' &&
       *(cp+3) <= '9' &&
       *(cp+4) == '(' &&
       *(cp+5) == 'x' &&
       *(cp+6) == ',' &&
       *(cp+7) == 'y' &&
       *(cp+8) == ',' &&
       *(cp+9) == 'z' &&
       *(cp+10) == ')'   ) {
      
      *wrt = *cp; wrt++;  cp++;   // _ 
      *wrt = *cp; wrt++;  cp++;   // n
      *wrt = *cp; wrt++;  cp++;   // 0-9
      *wrt = *cp; wrt++;  cp++;   // 0-9
      

      cp += 7;
      continue;
    }

    if(*(cp+3) >= '0' &&
       *(cp+3) <= '9' &&
       *(cp+4) >= '0' &&
       *(cp+4) <= '9' &&
       *(cp+5) == '(' &&
       *(cp+6) == 'x' &&
       *(cp+7) == ',' &&
       *(cp+8) == 'y' &&
       *(cp+9) == ',' &&
       *(cp+10) == 'z' &&
       *(cp+11) == ')'   ) {
      
      *wrt = *cp; wrt++;  cp++;   // _ 
      *wrt = *cp; wrt++;  cp++;   // n
      *wrt = *cp; wrt++;  cp++;   // 0-9
      *wrt = *cp; wrt++;  cp++;   // 0-9
      *wrt = *cp; wrt++;  cp++;   // 0-9
      cp += 7;

      continue;
    }
    *wrt = *cp;
    wrt++;  cp++;
  }
  *wrt = *cp;
  assert(*wrt== '\0');
  
  return;
}
  
      
      
