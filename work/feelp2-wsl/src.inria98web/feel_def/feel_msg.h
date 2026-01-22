/*
 *  feel_msg.h
 *
 *  function prototype declaration 
 *  2026/01/22 (Ito Komeya)
 *
 */

int streq(char * , char *);
int strindex(char * , char *);

void SystemAbort(char *);
void SystemWarnig(char *);
void SystemStderr(char *);
void SystemWarning(char *);
void SystemParseWarning(char *);

void print_yylineno();

int yylineno_info();

void SystemError_s(char *,char *);
void SystemError_yy(char *,int);
void SystemWarning_yy(char *,int);
void SystemError_yy_s(char *,char *,int);


