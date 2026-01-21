#include <stdio.h>

main()
{
    FILE *pfp;
    FILE *fp;

    char pwd[BUFSIZ];
    char echo[BUFSIZ];
    char *cp,*cpwd;

    char fname[BUFSIZ];


    pfp = popen("pwd","r");
    fgets(pwd,sizeof(pwd),pfp);
    pclose(pfp);

    cp = pwd+strlen(pwd)-2;
    while(*cp != '/') cp--;
    cp++;
    cpwd = cp;
    *(cpwd+strlen(cpwd)-1) = '\0';

    printf("CFLAGS = -g\n");
    printf("%s.a :",cpwd);

    pfp = popen("echo *.f *.c","r");
    fgets(echo,sizeof echo,pfp);
    pclose(pfp);
    cp = echo;

    while(1 == sscanf(cp,"%s",fname)) {
	cp = cp + strindex(cp,fname)+strlen(fname);
	fname[strlen(fname)-1] = 'o';
	printf("%s.a(%s) ",cpwd,fname);
    }
    printf("\n");

}



