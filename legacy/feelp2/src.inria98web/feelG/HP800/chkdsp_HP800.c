#include <stdio.h>
#include <stdlib.h>

chkdsp(iflag)
int	*iflag;
{
	char	str[100];

	sprintf(str,"%s",getenv("DISPLAY"));

	if (strcmp(str,"\0") == 0) {
		*iflag = -1;
	}else{
		*iflag = 1;
	}
}
