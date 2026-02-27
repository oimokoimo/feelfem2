#include <stdio.h>
main()
{
  char str[3];
  int i;
  for(i=0;i<12;i++) {
    if(i<9) {
      str[0] = '0';
      str[1] = '1' + i;
    }
    else {
      str[0] = '1';
      str[1] = '0'+(i-9);
    }
    str[2] = '\0';

    printf("    case %d:\n",i);
    printf("      e = e.subs(a%s == itr()->getValue());\n",str);
    printf("      break;\n");
    printf("\n");
  }
}
 
