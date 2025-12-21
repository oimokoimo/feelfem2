#include <stdio.h>


char *get_date()
{
    char *cp;
    char *get_com_from_pipe();

    cp = get_com_from_pipe("date");
    *(cp+strlen(cp)-1) = '\0';

    return(cp);
    
}


    char *get_user_name();

char *get_com_from_pipe(command)
     char *command;
{
    FILE *pfp;
    char buf[BUFSIZ];
    char *cp;

    pfp = popen(command,"r");
    if(pfp == NULL) {
	fprintf(stderr,"cannot open pipe(get_com_from_pipe)\n");
	exit(1);
    }
    
    fgets(buf,sizeof buf,pfp);
    pclose(pfp);

    cp = (char *)malloc(strlen(buf)+1);
    if(cp == NULL) {
	fprintf(stderr,"Cannot allocate memory(get_com_from_pipe)\n");
	exit(1);
    }
    strcpy( buf, cp);
    return(cp);
}

char *get_user_name()
{
    int uid,i;
    char buf[BUFSIZ];
    char name[38];
    char uid_buf[10];
    char *cp,*np;
    FILE *fp;
    char *retp;

    uid = getuid();

    fp = fopen("/etc/passwd","r");

    if(fp == NULL) {
	fprintf(stderr,"cannot read /etc/passwd(get_user_name).");
    }
    
    np = name;
    *np = '\0';

    while(fgets(buf,sizeof buf,fp)) {
	cp = buf;
	i  = 0;

	while(i < 2) {
	    if(*cp == ':') i++;
	    cp++;
	}

	np = uid_buf;
	while(*cp != ':') {
	    *np = *cp;
	    np++;
	    cp++;
	}
	*np = '\0';
	
	if(atoi(uid_buf) != uid) continue;

	cp++;
	while(*cp != ':') cp++;

	cp++;
	np = name;

	while(*cp != ':') {
	    *np = *cp;
	    cp++;
	    np++;
	}
	*np = '\0';

	break;
    }

    fclose(fp);

	    
    retp = (char *)malloc(strlen(name)+1);
    strcpy( retp , name );
    return(retp);

}
    
    
    
