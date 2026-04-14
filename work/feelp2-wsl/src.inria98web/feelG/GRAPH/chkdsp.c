#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void chkdsp_(iflag)
int	*iflag;
{
	char	str[100];

	sprintf(str,"%s%c",getenv("DISPLAY"),'\0');

	if (strcmp(str,"\0") == 0) {
		*iflag = -1;
	}else{
		*iflag = 1;
	}
}
