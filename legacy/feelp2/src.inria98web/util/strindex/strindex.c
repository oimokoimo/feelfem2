strindex(s,c)
char s[],c[];
{
	int slen,clen,i,j;
	slen = strlen(s);
	clen = strlen(c);
	if(slen < clen ) return (0);
	i=0;
	while( i + clen <= slen) {
		for( j= 0; j < clen; j++) {
			if( s[i+j] != c[j] ) {
				i++;
				break;
			}
		}
		if( j == clen ) return(i+1);
	}
	return(0);
}
