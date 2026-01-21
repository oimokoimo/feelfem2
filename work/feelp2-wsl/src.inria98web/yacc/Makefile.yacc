all : YaccMain.o YaccExpression.o y.tab.o lex.yy.o
	
y.tab.c : fem.y
	yacc -d fem.y
lex.yy.c : fem_lex.l
	lex fem_lex.l
