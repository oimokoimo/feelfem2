
# line 13 "fem_view.y"
#include <stdio.h>

    extern int parameters;   /* to count the number of  parameter */
    extern int expressions;  /* to count the items in expression  */
    extern int settings;
    extern int inner_parameters; /* to count the number of inner points */
    extern int condition_type;   /* condition type */

    char *tmp_pop;               /* debug for DEC/Alpha AXP/ OSF/1(941024) */
    extern char *get_expr_structure();
    extern char *if_left_ptr;
#ifdef __cplusplus
#  include <stdio.h>
#  include <yacc.h>
#endif	/* __cplusplus */ 
# define IDENTIFIER 257
# define STRING 258
# define DIMENSION 259
# define MESH 260
# define POINT 261
# define REFINE 262
# define EDGE 263
# define CURVE 264
# define DOMAIN 265
# define REGION 266
# define RECTANGLE 267
# define NODES 268
# define SHOWMESH 269
# define BOUNDARY 270
# define NUMBER 271
# define SUBDOMAIN 272
# define ELEMENT 273
# define QUADRATURE 274
# define VAR 275
# define CONST 276
# define DOUBLE 277
# define FEM 278
# define EWISE 279
# define INT 280
# define MATERIAL 281
# define FUNCTION 282
# define SCHEME 283
# define SOLVE 284
# define ISOPARAMETRIC 285
# define SHAPE 286
# define SYMMETRY 287
# define NONLINEAR 288
# define EPS 289
# define STRATEGY 290
# define INITIAL_VALUE 291
# define EQ 292
# define WEQ 293
# define EIGEN 294
# define FUNC 295
# define ATMARK 296
# define METHOD 297
# define LINEAR 298
# define DBC 299
# define NBC 300
# define AT 301
# define IN 302
# define ON 303
# define GOTO 304
# define LET 305
# define SHOWVEC 306
# define SHOWVEC_FILE 307
# define CONTOUR 308
# define CONTOUR_FILE 309
# define XPLOT 310
# define PLOT_FILE 311
# define PERSPECT 312
# define WRITE 313
# define READ 314
# define IF 315
# define THEN 316
# define ELSE 317
# define ENDIF 318
# define FILE_WRITE 319
# define TIME_PLOT_FILE 320
# define NEWTON_FACTOR 321
# define DISPLACEMENT 322
# define MAXNORM 323
# define L2NORM 324
# define ADAPTMESH 325
# define lp 326
# define rp 327
# define lk 328
# define rk 329
# define lb 330
# define rb 331
# define num 332
# define co 333
# define sc 334
# define cc 335
# define eq 336
# define pl 337
# define mi 338
# define mu 339
# define di 340
# define equal 341
# define le 342
# define lt 343
# define ge 344
# define gt 345
# define ne 346
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif

/* __YYSCLASS defines the scoping/storage class for global objects
 * that are NOT renamed by the -p option.  By default these names
 * are going to be 'static' so that multi-definition errors
 * will not occur with multiple parsers.
 * If you want (unsupported) access to internal names you need
 * to define this to be null so it implies 'extern' scope.
 * This should not be used in conjunction with -p.
 */
#ifndef __YYSCLASS
# define __YYSCLASS static
#endif
#ifndef YYSTYPE
#define YYSTYPE int
#endif
YYSTYPE yylval;
__YYSCLASS YYSTYPE yyval;
typedef int yytabelem;
# define YYERRCODE 256
__YYSCLASS yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 36
# define YYLAST 165
__YYSCLASS yytabelem yyact[]={

    40,    39,    37,    36,    34,    33,    31,    30,    95,    89,
    76,    82,    94,    65,    67,    75,    65,    66,    64,    65,
    65,    11,    12,    13,    87,    14,    16,    79,    10,    60,
    85,    72,    15,    71,    70,    69,    50,    48,    46,    88,
    86,    81,    80,    78,    62,    58,    77,    63,    61,    59,
    57,    43,    42,    41,    38,    35,    32,    74,    68,    44,
     7,    96,    11,    12,    13,     5,    14,    16,    93,    10,
    53,    74,    56,    15,    51,    49,    47,    45,    29,    28,
    27,    26,    24,    22,    20,     9,    52,    17,     3,    -1,
    90,     6,    92,    -1,    18,    83,    25,    23,    21,    19,
     8,     4,     2,     1,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    91,    54,
    55,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    84 };
__YYSCLASS yytabelem yypact[]={

  -195, -3000,  -195, -3000, -3000,  -266, -3000,  -199,  -240, -3000,
  -173,  -174,  -175,  -176,  -177,  -178,  -179, -3000, -3000,  -327,
  -274,  -329,  -275,  -331,  -276,  -333,  -277,  -278,  -279,  -269,
 -3000,  -180,  -294, -3000,  -181,  -295, -3000,  -182,  -296, -3000,
  -183,  -187,  -187,  -187,  -185,  -280,  -286,  -281,  -304,  -282,
  -287,  -283,  -313, -3000,  -314,  -317,  -271,  -297, -3000,  -298,
  -299,  -301, -3000,  -187, -3000,  -186,  -319,  -324,  -284,  -288,
  -306,  -289,  -290,  -320, -3000, -3000, -3000,  -187, -3000,  -302,
 -3000, -3000, -3000,  -291,  -309,  -292,  -325,  -200, -3000, -3000,
 -3000,  -189,  -321, -3000,  -196, -3000, -3000 };
__YYSCLASS yytabelem yypgo[]={

     0,   103,   102,    88,   101,   100,    85,    99,    98,    97,
    96,    86,    95,    93,    92,    90,    89 };
__YYSCLASS yytabelem yyr1[]={

     0,     1,     1,     2,     2,     3,     4,     5,     5,     6,
     6,     6,     6,     6,     6,     6,     6,     7,     7,     8,
     8,     9,     9,    10,    10,    11,    11,    13,    13,    14,
    14,    15,    16,    16,    12,    12 };
__YYSCLASS yytabelem yyr2[]={

     0,     0,     3,     2,     4,     2,     8,     2,     4,     0,
     6,     6,     6,     6,    13,    13,    19,     9,    13,    13,
    17,     9,    13,     9,    13,     3,     7,     3,     7,     3,
     7,     7,     3,     7,     2,     6 };
__YYSCLASS yytabelem yychk[]={

 -3000,    -1,    -2,    -3,    -4,   260,    -3,   326,    -5,    -6,
   268,   261,   262,   263,   265,   272,   266,   327,    -6,    -7,
   257,    -8,   257,    -9,   257,   -10,   257,   257,   257,   257,
   334,   333,   330,   334,   333,   330,   334,   333,   330,   334,
   333,   330,   330,   330,   328,   257,   332,   257,   332,   257,
   332,   257,   -11,   257,   -11,   -11,   257,   330,   331,   330,
   333,   330,   331,   330,   331,   333,   331,   331,   329,   332,
   332,   332,   332,   -11,   257,   334,   334,   330,   331,   333,
   331,   331,   331,   -12,   -11,   332,   331,   333,   331,   334,
   -15,   328,   -14,   257,   333,   329,   257 };
__YYSCLASS yytabelem yydef[]={

     1,    -2,     2,     3,     5,     0,     4,     9,     0,     7,
     0,     0,     0,     0,     0,     0,     0,     6,     8,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    10,     0,     0,    11,     0,     0,    12,     0,     0,    13,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    25,     0,     0,     0,     0,    17,     0,
     0,     0,    21,     0,    23,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    26,    14,    15,     0,    18,     0,
    19,    22,    24,     0,    34,     0,     0,     0,    20,    16,
    35,     0,     0,    29,     0,    31,    30 };
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

__YYSCLASS yytoktype yytoks[] =
{
	"IDENTIFIER",	257,
	"STRING",	258,
	"DIMENSION",	259,
	"MESH",	260,
	"POINT",	261,
	"REFINE",	262,
	"EDGE",	263,
	"CURVE",	264,
	"DOMAIN",	265,
	"REGION",	266,
	"RECTANGLE",	267,
	"NODES",	268,
	"SHOWMESH",	269,
	"BOUNDARY",	270,
	"NUMBER",	271,
	"SUBDOMAIN",	272,
	"ELEMENT",	273,
	"QUADRATURE",	274,
	"VAR",	275,
	"CONST",	276,
	"DOUBLE",	277,
	"FEM",	278,
	"EWISE",	279,
	"INT",	280,
	"MATERIAL",	281,
	"FUNCTION",	282,
	"SCHEME",	283,
	"SOLVE",	284,
	"ISOPARAMETRIC",	285,
	"SHAPE",	286,
	"SYMMETRY",	287,
	"NONLINEAR",	288,
	"EPS",	289,
	"STRATEGY",	290,
	"INITIAL_VALUE",	291,
	"EQ",	292,
	"WEQ",	293,
	"EIGEN",	294,
	"FUNC",	295,
	"ATMARK",	296,
	"METHOD",	297,
	"LINEAR",	298,
	"DBC",	299,
	"NBC",	300,
	"AT",	301,
	"IN",	302,
	"ON",	303,
	"GOTO",	304,
	"LET",	305,
	"SHOWVEC",	306,
	"SHOWVEC_FILE",	307,
	"CONTOUR",	308,
	"CONTOUR_FILE",	309,
	"XPLOT",	310,
	"PLOT_FILE",	311,
	"PERSPECT",	312,
	"WRITE",	313,
	"READ",	314,
	"IF",	315,
	"THEN",	316,
	"ELSE",	317,
	"ENDIF",	318,
	"FILE_WRITE",	319,
	"TIME_PLOT_FILE",	320,
	"NEWTON_FACTOR",	321,
	"DISPLACEMENT",	322,
	"MAXNORM",	323,
	"L2NORM",	324,
	"ADAPTMESH",	325,
	"lp",	326,
	"rp",	327,
	"lk",	328,
	"rk",	329,
	"lb",	330,
	"rb",	331,
	"num",	332,
	"co",	333,
	"sc",	334,
	"cc",	335,
	"eq",	336,
	"pl",	337,
	"mi",	338,
	"mu",	339,
	"di",	340,
	"equal",	341,
	"le",	342,
	"lt",	343,
	"ge",	344,
	"gt",	345,
	"ne",	346,
	"-unknown-",	-1	/* ends search */
};

__YYSCLASS char * yyreds[] =
{
	"-no such reduction-",
	"program : /* empty */",
	"program : sections",
	"sections : section",
	"sections : sections section",
	"section : mesh_definition",
	"mesh_definition : MESH lp mesh_statements rp",
	"mesh_statements : mesh_statement",
	"mesh_statements : mesh_statements mesh_statement",
	"mesh_statement : /* empty */",
	"mesh_statement : NODES nodes_definitions sc",
	"mesh_statement : POINT point_definitions sc",
	"mesh_statement : REFINE refine_definitions sc",
	"mesh_statement : EDGE line_definitions sc",
	"mesh_statement : DOMAIN IDENTIFIER lb parameter_list rb sc",
	"mesh_statement : SUBDOMAIN IDENTIFIER lb parameter_list rb sc",
	"mesh_statement : REGION IDENTIFIER lk IDENTIFIER rk lb edge_point_lists rb sc",
	"nodes_definitions : IDENTIFIER lb num rb",
	"nodes_definitions : nodes_definitions co IDENTIFIER lb num rb",
	"point_definitions : IDENTIFIER lb num co num rb",
	"point_definitions : point_definitions co IDENTIFIER lb num co num rb",
	"refine_definitions : IDENTIFIER lb num rb",
	"refine_definitions : refine_definitions co IDENTIFIER lb num rb",
	"line_definitions : IDENTIFIER lb parameter_list rb",
	"line_definitions : line_definitions co IDENTIFIER lb parameter_list rb",
	"parameter_list : IDENTIFIER",
	"parameter_list : parameter_list co IDENTIFIER",
	"num_parameter_list : num",
	"num_parameter_list : num_parameter_list co num",
	"inner_point_list : IDENTIFIER",
	"inner_point_list : inner_point_list co IDENTIFIER",
	"inner_edge_lists : lk inner_point_list rk",
	"edge_list : IDENTIFIER",
	"edge_list : edge_list co IDENTIFIER",
	"edge_point_lists : parameter_list",
	"edge_point_lists : parameter_list co inner_edge_lists",
};
#endif /* YYDEBUG */
#define YYFLAG  (-3000)
/* @(#) $Revision: 70.7 $ */    

/*
** Skeleton parser driver for yacc output
*/

#if defined(NLS) && !defined(NL_SETN)
#include <msgbuf.h>
#endif

#ifndef nl_msg
#define nl_msg(i,s) (s)
#endif

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab

#ifndef __RUNTIME_YYMAXDEPTH
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#else
#define YYACCEPT	{free_stacks(); return(0);}
#define YYABORT		{free_stacks(); return(1);}
#endif

#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( (nl_msg(30001,"syntax error - cannot backup")) );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
/* define for YYFLAG now generated by yacc program. */
/*#define YYFLAG		(FLAGVAL)*/

/*
** global variables used by the parser
*/
# ifndef __RUNTIME_YYMAXDEPTH
__YYSCLASS YYSTYPE yyv[ YYMAXDEPTH ];	/* value stack */
__YYSCLASS int yys[ YYMAXDEPTH ];		/* state stack */
# else
__YYSCLASS YYSTYPE *yyv;			/* pointer to malloc'ed value stack */
__YYSCLASS int *yys;			/* pointer to malloc'ed stack stack */

#if defined(__STDC__) || defined (__cplusplus)
#include <stdlib.h>
#else
	extern char *malloc();
	extern char *realloc();
	extern void free();
#endif /* __STDC__ or __cplusplus */


static int allocate_stacks(); 
static void free_stacks();
# ifndef YYINCREMENT
# define YYINCREMENT (YYMAXDEPTH/2) + 10
# endif
# endif	/* __RUNTIME_YYMAXDEPTH */
long  yymaxdepth = YYMAXDEPTH;

__YYSCLASS YYSTYPE *yypv;			/* top of value stack */
__YYSCLASS int *yyps;			/* top of state stack */

__YYSCLASS int yystate;			/* current state */
__YYSCLASS int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
__YYSCLASS int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */

	/*
	** Initialize externals - yyparse may be called more than once
	*/
# ifdef __RUNTIME_YYMAXDEPTH
	if (allocate_stacks()) YYABORT;
# endif
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
# ifndef __RUNTIME_YYMAXDEPTH
			yyerror( (nl_msg(30002,"yacc stack overflow")) );
			YYABORT;
# else
			/* save old stack bases to recalculate pointers */
			YYSTYPE * yyv_old = yyv;
			int * yys_old = yys;
			yymaxdepth += YYINCREMENT;
			yys = (int *) realloc(yys, yymaxdepth * sizeof(int));
			yyv = (YYSTYPE *) realloc(yyv, yymaxdepth * sizeof(YYSTYPE));
			if (yys==0 || yyv==0) {
			    yyerror( (nl_msg(30002,"yacc stack overflow")) );
			    YYABORT;
			    }
			/* Reset pointers into stack */
			yy_ps = (yy_ps - yys_old) + yys;
			yyps = (yyps - yys_old) + yys;
			yy_pv = (yy_pv - yyv_old) + yyv;
			yypv = (yypv - yyv_old) + yyv;
# endif

		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( (nl_msg(30003,"syntax error")) );
				yynerrs++;
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 2:
# line 142 "fem_view.y"
{ /* debug_start(); (注意！feel_exec_mainの中に移しました。)*/
	          viewmesh();  } break;
case 14:
# line 218 "fem_view.y"
{ domain_st(parameters); parameters = 0;} break;
case 15:
# line 220 "fem_view.y"
{ subdomain_st(parameters); parameters = 0;} break;
case 16:
# line 222 "fem_view.y"
{ region_with_meshmethod_st(parameters); parameters = 0;} break;
case 17:
# line 225 "fem_view.y"
{nodes_st(); } break;
case 18:
# line 226 "fem_view.y"
{nodes_st(); } break;
case 19:
# line 229 "fem_view.y"
{ point_2d_st();} break;
case 20:
# line 230 "fem_view.y"
{ point_2d_st();} break;
case 21:
# line 233 "fem_view.y"
{ refine_st(); } break;
case 22:
# line 234 "fem_view.y"
{ refine_st();} break;
case 23:
# line 237 "fem_view.y"
{ line_st(parameters); parameters = 0;} break;
case 24:
# line 239 "fem_view.y"
{ line_st(parameters); parameters = 0; } break;
case 25:
# line 241 "fem_view.y"
{ parameters++;} break;
case 26:
# line 242 "fem_view.y"
{parameters++;} break;
case 27:
# line 245 "fem_view.y"
{ parameters++;} break;
case 28:
# line 246 "fem_view.y"
{parameters++;} break;
case 29:
# line 249 "fem_view.y"
{ inner_parameters++;} break;
case 30:
# line 250 "fem_view.y"
{inner_parameters++;} break;
case 31:
# line 254 "fem_view.y"
{ pop_push_inner_points(inner_parameters); parameters++;
       inner_parameters = 0;                                  } break;
case 32:
# line 258 "fem_view.y"
{parameters++;} break;
case 33:
# line 259 "fem_view.y"
{parameters++;} break;
	}
	goto yystack;		/* reset registers in driver code */
}

# ifdef __RUNTIME_YYMAXDEPTH

static int allocate_stacks() {
	/* allocate the yys and yyv stacks */
	yys = (int *) malloc(yymaxdepth * sizeof(int));
	yyv = (YYSTYPE *) malloc(yymaxdepth * sizeof(YYSTYPE));

	if (yys==0 || yyv==0) {
	   yyerror( (nl_msg(30004,"unable to allocate space for yacc stacks")) );
	   return(1);
	   }
	else return(0);

}


static void free_stacks() {
	if (yys!=0) free((char *) yys);
	if (yyv!=0) free((char *) yyv);
}

# endif  /* defined(__RUNTIME_YYMAXDEPTH) */

