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
void SystemAbort_s(char *,char *);
void SystemWarnig(char *);
void SystemStderr(char *);
void SystemWarning(char *);
void SystemParseWarning(char *);
void NotImplement(char *);

void FatalError(char *);

void print_yylineno();

int yylineno_info();

void SystemError_s(char *,char *);
void SystemError_yy(char *,int);
void SystemWarning_yy(char *,int);
void SystemError_yy_s(char *,char *,int);
void SystemError_ss(char *,char *,char *);
void SystemError_s(char *,char *);


void SystemStderr(char *s);

/* Warning 系 */
void SystemWarning(char *s);
void SystemWarning_yy(char *s, int lineno);
void SystemWarning_d(char *s, int d);
void SystemWarning_s(char *s, char *s2);
void SystemWarning_ss(char *s, char *s2, char *s3);

/* パーサ用 Warning */
void SystemParseWarning(char *s);

/* Error 系 */
void SystemError(char *s);
void SystemError_yy(char *s, int lineno);
void SystemError_yy_s(char *s, char *arg1, int lineno);
void SystemError_yy_ss(char *s, char *arg1, char *arg2, int lineno);
void SystemError_s(char *s, char *s2);
void SystemError_sn(char *s, char *s2, int n);
void SystemError_ss(char *s, char *s2, char *s3);

/* 致命的エラー */
void FatalError(char *s);
void SystemAbort(char *s);
void SystemAbort_s(char *s, char *s2);

/* 状態取得 */
int how_many_errors(void);
int how_many_warnings(void);

/* 集計出力 */
void prt_errors_message(void);
void prt_warnings_message(void);


void StoreMakefileWarning(char *);
void OpenFileToReadAbort(char *);
void OpenFileToWriteAbort(char *);
void OpenPipeToReadAbort(char *);
