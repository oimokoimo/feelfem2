CFLAGS = $(ADDITIONALCFLAGS)

# 生成物
YACC_SRCS = fem.tab.c
YACC_HDRS = fem.tab.h
LEX_SRCS  = lex.yy.c

OBJS = yyerror.o \
       YaccExpression.o \
       YaccMain.o \
       expression_term.o \
       lex.yy.o \
       fem.tab.o \
       yylineno.o

# static library
yacc.a: $(OBJS)
	ar rcs $@ $^

# bison: fem.y -> fem.tab.c, fem.tab.h
fem.tab.c fem.tab.h: fem.y
	bison -d fem.y

# compile fem.tab.c
fem.tab.o: fem.tab.c
	$(CC) $(CFLAGS) -c fem.tab.c

# flex: fem_lex.l -> lex.yy.c
lex.yy.c: fem_lex.l fem.tab.h
	flex -l fem_lex.l

# compile lex.yy.c
lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

# generic rule
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# clean
clean:
	rm -f *.o yacc.a fem.tab.c fem.tab.h lex.yy.c

