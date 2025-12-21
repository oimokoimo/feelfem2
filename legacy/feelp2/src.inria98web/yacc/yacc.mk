yacc.lib :: YaccExpression.c YaccMain.c expression_term.c lex.yy.c y.tab.c
	cl /c YaccExpression.c YaccMain.c expression_term.c lex.yy.c y.tab.c
	lib /OUT:yacc.lib YaccExpression.obj YaccMain.obj expression_term.obj lex.yy.obj y.tab.obj
