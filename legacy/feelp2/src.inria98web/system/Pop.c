/*
 *   FEEL system   Pop.c
 *  
 *   System Pop function
 *
 */

extern char *pop();

double PopDouble()
{
    double x;
    
    if(sscanf(pop(),"%lf",&x) != 1) {
	SystemError("Double number systax error");
	return(x);
    }

    return(x);
}

int PopInt()
{
    int x;
    
    if(sscanf(pop(),"%d",&x) != 1) {
	SystemError("Integer number systax error");
	return(x);
    }
    return(x);
}

char *PopString()
{
    char *cp;
    char *MakeStringCopy();
    
    cp = MakeStringCopy(pop());

    return(cp);
}


    
