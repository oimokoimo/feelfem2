/*

   Definition file for Making FORT77 file

*/



#define SEP fprintf(fp,"*-------------------------------------------------------\n")
#define F77(x) fprintf(fp,x)
#define COM fprintf(fp,"*\n")
#define PUT fprintf


extern FILE *OpenFile();


