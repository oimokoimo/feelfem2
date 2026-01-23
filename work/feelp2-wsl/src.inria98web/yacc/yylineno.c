#include <stdio.h>

/* flexが用意してる/あなたが管理してる行番号 */
extern int yylineno;

int yylineno_info(void)
{
    static char buf[64];
    /* snprintfを使わずに、固定の体裁だけにする */
    return 9999; /* 返り値を使ってる箇所があるなら、とりあえず空文字で返す */
}

void print_yylineno(void)
{
    fprintf(stderr, "(line %d) ", yylineno);
}

