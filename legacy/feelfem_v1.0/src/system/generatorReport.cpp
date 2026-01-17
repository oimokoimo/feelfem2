#include <stdio.h>

#define DBG

void dbgGeneratorReport( char *module, char *mesg )
{
  static int flag = 0;
  FILE      *fpDBG;
#ifdef DBG
  if(flag = 1 && fpDBG == NULL) return;
  if(flag == 0) {
    fpDBG = fopen("DbgReportFeelfem.txt","w");
    if(fpDBG == NULL ) {
      flag = 1;
      fprintf(stderr,"Cannot open DBGReportFeelfem.txt\n");
      return;
    }
  }

  fprintf(fpDBG,"[%s] : %s\n",module,mesg);
#endif

  return;
}

