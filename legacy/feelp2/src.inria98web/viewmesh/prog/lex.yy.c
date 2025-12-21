# include "stdio.h"
#if defined(__cplusplus)
   extern "C" {
#endif
#if (defined(__cplusplus) || defined(__STDC__))
     extern int yyreject();
     extern int yywrap();
     extern int yylook();
     extern int yyback(int *, int);
     extern int yyinput();
     extern void yyoutput(int);
     extern void yyunput(int);
     extern int yylex();
     extern int yyless(int);
#ifdef LEXDEBUG
     extern void allprint();
     extern void sprint();
#endif
#if defined(__cplusplus)
   }
#endif
#endif	/* __cplusplus or __STDC__ */
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng;
int yylenguc;
extern unsigned char yytextarr[];
# ifdef YYCHAR_ARRAY
extern char yytext[];
# else
extern unsigned char yytext[];
# endif
int yyposix_point=0;
int yynls16=0;
int yynls_wchar=0;
char *yylocale = "C C C C C C";
int yymorfg;
extern unsigned char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	int yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
/*    FESL lex program
 * 
 *    Filename             fem_lex.l
 *    Made                 1991/12/24
 *    LastModified         1992/01/24
 *    Version              0.2
 */

#ifdef DEBUG

#include <assert.h>
main()
{
char *p;
assert(sizeof(int) >= sizeof (char *));
while(p=(char *)yylex())
printf("%-10.10s is \"%s\"\n",p,yytext);
}

s_lookup(){}
int yynerrs = 0;
#define token(x) (int) "x"


#else

#include "y.tab.h"
#define token(x)  x

#endif DEBUG

#define END(v) (v-1 + sizeof v / sizeof v[0])
extern push();

# define YYNEWLINE 10
yylex(){
   int nstr; extern int yyprevious;
   while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
   if(yywrap()) return(0); break;
case 1:
            return token(ATMARK);
break;
case 2:
         return token(MESH);
break;
case 3:
        return token(POINT);
break;
case 4:
       return token(REFINE);
break;
case 5:
        return token(CURVE);
break;
case 6:
       return token(DOMAIN);
break;
case 7:
       return token(REGION);
break;
case 8:
         return token(EDGE);
break;
case 9:
    return token(RECTANGLE);
break;
case 10:
        return token(NODES);
break;
case 11:
     return token(SHOWMESH);
break;
case 12:
       return token(NUMBER);
break;
case 13:
    return token(DIMENSION);
break;
case 14:
    return token(SUBDOMAIN);
break;
case 15:
      return token(ELEMENT);
break;
case 16:
   return token(QUADRATURE);
break;
case 17:
     return token(BOUNDARY);
break;
case 18:
          return token(VAR);
break;
case 19:
          return token(INT);
break;
case 20:
        return token(CONST);
break;
case 21:
          return token(FEM);
break;
case 22:
       return token(DOUBLE);
break;
case 23:
        return token(EWISE);
break;
case 24:
     return token(MATERIAL);
break;
case 25:
     return token(FUNCTION);
break;
case 26:
       return token(SCHEME);
break;
case 27:
        return token(SOLVE);
break;
case 28:
       return token(METHOD);
break;
case 29:
       return token(LINEAR);
break;
case 30:
return token(ISOPARAMETRIC);
break;
case 31:
    return token(NONLINEAR);
break;
case 32:
     return token(STRATEGY);
break;
case 33:
      return token(INITIAL_VALUE);
break;
case 34:
      return token(EPS);
break;
case 35:
    return token(NEWTON_FACTOR);
break;
case 36:
 return token(DISPLACEMENT);
break;
case 37:
        return token(SHAPE);
break;
case 38:
     return token(SYMMETRY);
break;
case 39:
          return token(EQ);
break;
case 40:
         return token(WEQ);
break;
case 41:
        return token(FUNC);
break;
case 42:
       return token(EIGEN);
break;
case 43:
         return token(DBC);
break;
case 44:
         return token(NBC);
break;
case 45:
           return token(AT);
break;
case 46:
           return token(ON);
break;
case 47:
           return token(IN);
break;
case 48:
         return token(GOTO);
break;
case 49:
          return token(LET);
break;
case 50:
      return token(SHOWVEC);
break;
case 51:
 return token(SHOWVEC_FILE);
break;
case 52:
      return token(CONTOUR);
break;
case 53:
 return token(CONTOUR_FILE);
break;
case 54:
     return token(PERSPECT);
break;
case 55:
        return token(WRITE);
break;
case 56:
         return token(READ);
break;
case 57:
        return token(XPLOT);
break;
case 58:
    return token(PLOT_FILE);
break;
case 59:
           return token(IF);
break;
case 60:
         return token(THEN);
break;
case 61:
         return token(ELSE);
break;
case 62:
        return token(ENDIF);
break;
case 63:
       return token(FILE_WRITE);
break;
case 64:
   return token(TIME_PLOT_FILE);
break;
case 65:
       return token(L2NORM);
break;
case 66:
      return token(MAXNORM);
break;
case 67:
    return token(ADAPTMESH);
break;
case 68:
            return token(lp);
break;
case 69:
            return token(rp);
break;
case 70:
            return token(lk);
break;
case 71:
            return token(rk);
break;
case 72:
            return token(lb);
break;
case 73:
            return token(rb);
break;
case 74:
           return token(equal);
break;
case 75:
           return token(le);
break;
case 76:
            return token(lt);
break;
case 77:
           return token(ge);
break;
case 78:
            return token(gt);
break;
case 79:
           return token(ne);
break;
case 80:
            return token(eq);
break;
case 81:
            return token(sc);
break;
case 82:
            return token(cc);
break;
case 83:
            return token(co);
break;
case 84:
            return token(pl);
break;
case 85:
            return token(mi);
break;
case 86:
            return token(mu);
break;
case 87:
            return token(di);
break;
case 88:
         {  push(yytext);
                                       return token(IDENTIFIER);
                                    }
break;
case 89:
                        {  push(yytext);
                                       return token(STRING);
                                    }
break;
case 90:
     ;
break;
case 91:
{          push(yytext);
				       return token(num);
                                    }
break;
case 92:
         {          push(yytext);
				       return token(num);
                                    }
break;
case 93:
         {          push(yytext);
				       return token(num);
                                    }
break;
case 94:
{          push(yytext);
				       return token(num);
                                    }
break;
case 95:
                      ;
break;
case -1:
break;
default:
   fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

#ifndef __cplusplus
static void __yy__unused() { main(); }
#endif
int yyvstop[] = {
0,

95,
0,

88,
0,

72,
0,

73,
0,

86,
0,

84,
0,

83,
0,

85,
0,

87,
0,

92,
0,

82,
0,

81,
0,

76,
0,

80,
0,

78,
0,

1,
0,

88,
0,

88,
0,

70,
0,

71,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

68,
0,

69,
0,

79,
0,

89,
0,

93,
0,

91,
0,

75,
0,

74,
0,

77,
0,

88,
0,

88,
0,

88,
0,

45,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

59,
88,
0,

47,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

46,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

94,
0,

91,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

39,
0,

88,
0,

21,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

19,
88,
0,

88,
0,

49,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

18,
88,
0,

88,
0,

88,
0,

88,
0,

94,
0,

90,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

43,
0,

88,
0,

88,
0,

88,
0,

88,
0,

8,
88,
0,

88,
0,

88,
0,

61,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

48,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

2,
88,
0,

88,
0,

44,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

56,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

60,
88,
0,

88,
0,

40,
0,

88,
0,

88,
0,

90,
0,

91,
0,

88,
0,

88,
0,

88,
0,

88,
0,

20,
88,
0,

88,
0,

5,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

62,
88,
0,

23,
88,
0,

41,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

10,
88,
0,

88,
0,

88,
0,

88,
0,

3,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

37,
88,
0,

88,
0,

88,
0,

27,
88,
0,

88,
0,

88,
0,

88,
0,

55,
88,
0,

57,
88,
0,

94,
0,

65,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

6,
88,
0,

22,
88,
0,

42,
0,

88,
0,

88,
0,

63,
88,
0,

88,
0,

88,
0,

29,
88,
0,

88,
0,

28,
88,
0,

88,
0,

88,
0,

12,
88,
0,

88,
0,

88,
0,

88,
0,

4,
88,
0,

7,
88,
0,

26,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

66,
88,
0,

88,
0,

88,
0,

52,
88,
0,

88,
0,

88,
0,

15,
88,
0,

88,
0,

33,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

34,
0,

88,
0,

50,
88,
0,

88,
0,

88,
0,

88,
0,

88,
0,

17,
88,
0,

88,
0,

88,
0,

25,
88,
0,

88,
0,

24,
88,
0,

88,
0,

54,
88,
0,

88,
0,

88,
0,

11,
88,
0,

32,
88,
0,

88,
0,

38,
88,
0,

67,
88,
0,

13,
88,
0,

88,
0,

88,
0,

31,
88,
0,

58,
0,

88,
0,

9,
88,
0,

14,
88,
0,

88,
0,

88,
0,

16,
88,
0,

88,
0,

88,
0,

53,
0,

36,
88,
0,

88,
0,

51,
0,

30,
88,
0,

35,
0,

64,
0,
0};
# define YYTYPE int
struct yywork { YYTYPE verify, advance; } yycrank[] = {
{0,0},	{0,0},	{0,0},	{0,0},	
{0,0},	{0,0},	{0,0},	{0,0},	
{0,0},	{0,0},	{1,3},	{1,3},	
{3,3},	{3,3},	{0,0},	{0,0},	
{0,0},	{0,0},	{0,0},	{0,0},	
{0,0},	{0,0},	{0,0},	{0,0},	
{0,0},	{0,0},	{0,0},	{0,0},	
{0,0},	{0,0},	{0,0},	{0,0},	
{0,0},	{1,3},	{1,4},	{3,3},	
{0,0},	{1,5},	{0,0},	{0,0},	
{1,6},	{1,7},	{1,8},	{1,9},	
{1,10},	{1,11},	{1,12},	{13,50},	
{1,13},	{1,14},	{1,14},	{1,14},	
{1,14},	{1,14},	{1,14},	{1,14},	
{1,14},	{1,14},	{1,14},	{1,15},	
{1,16},	{1,17},	{1,18},	{1,19},	
{4,47},	{1,20},	{1,5},	{1,5},	
{1,5},	{1,5},	{1,5},	{1,5},	
{1,5},	{1,5},	{1,5},	{1,5},	
{1,5},	{1,21},	{1,22},	{1,5},	
{1,5},	{1,5},	{1,5},	{1,5},	
{1,5},	{1,5},	{1,5},	{1,5},	
{1,5},	{1,5},	{1,5},	{1,5},	
{1,23},	{17,52},	{1,24},	{18,53},	
{1,5},	{19,54},	{1,25},	{1,26},	
{1,27},	{1,28},	{1,29},	{1,30},	
{1,31},	{1,5},	{1,32},	{1,5},	
{1,5},	{1,33},	{1,34},	{1,35},	
{1,36},	{1,37},	{1,38},	{1,39},	
{1,40},	{1,41},	{1,5},	{1,42},	
{1,43},	{1,44},	{1,5},	{1,5},	
{1,45},	{5,5},	{1,46},	{12,49},	
{12,49},	{12,49},	{12,49},	{12,49},	
{12,49},	{12,49},	{12,49},	{12,49},	
{12,49},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{21,55},	
{22,56},	{26,59},	{31,74},	{36,86},	
{38,90},	{39,91},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{42,101},	{33,78},	{41,99},	{41,100},	
{5,5},	{33,79},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{5,5},	{5,5},	{5,5},	{5,5},	
{6,6},	{34,80},	{44,104},	{25,57},	
{49,105},	{34,81},	{30,71},	{14,51},	
{6,6},	{14,14},	{14,14},	{14,14},	
{14,14},	{14,14},	{14,14},	{14,14},	
{14,14},	{14,14},	{14,14},	{25,58},	
{27,60},	{28,62},	{30,72},	{32,75},	
{30,73},	{55,110},	{27,61},	{56,111},	
{28,63},	{57,112},	{35,82},	{32,76},	
{29,65},	{35,83},	{28,64},	{6,6},	
{32,77},	{29,66},	{6,48},	{59,113},	
{29,67},	{6,6},	{29,68},	{35,84},	
{60,114},	{29,69},	{6,6},	{6,6},	
{37,87},	{35,85},	{43,102},	{29,70},	
{40,92},	{50,106},	{40,93},	{37,88},	
{61,115},	{40,94},	{37,89},	{62,116},	
{63,117},	{50,106},	{65,121},	{43,103},	
{40,95},	{64,119},	{63,118},	{6,6},	
{66,122},	{40,96},	{40,97},	{67,123},	
{68,125},	{64,120},	{40,98},	{51,109},	
{51,109},	{51,109},	{51,109},	{51,109},	
{51,109},	{51,109},	{51,109},	{51,109},	
{51,109},	{67,124},	{69,126},	{70,127},	
{50,106},	{71,128},	{72,129},	{50,106},	
{73,130},	{74,131},	{50,107},	{76,132},	
{77,134},	{78,135},	{79,136},	{50,108},	
{50,106},	{80,137},	{81,138},	{81,139},	
{82,140},	{83,141},	{76,133},	{84,142},	
{85,144},	{87,145},	{88,146},	{89,147},	
{90,148},	{91,149},	{92,153},	{91,150},	
{93,154},	{84,143},	{91,151},	{91,152},	
{50,106},	{94,155},	{95,157},	{96,158},	
{97,159},	{98,160},	{99,161},	{100,162},	
{101,163},	{102,164},	{103,165},	{104,166},	
{106,106},	{109,171},	{109,171},	{94,156},	
{105,167},	{105,167},	{105,167},	{105,167},	
{105,167},	{105,167},	{105,167},	{105,167},	
{105,167},	{105,167},	{107,168},	{110,172},	
{111,173},	{112,174},	{113,175},	{114,176},	
{114,177},	{115,178},	{107,168},	{116,179},	
{117,180},	{118,181},	{119,182},	{120,183},	
{121,184},	{122,185},	{123,186},	{124,187},	
{125,188},	{109,171},	{109,171},	{127,189},	
{129,190},	{130,191},	{131,192},	{132,193},	
{134,194},	{136,195},	{137,196},	{138,197},	
{139,198},	{140,199},	{141,200},	{142,201},	
{143,202},	{107,168},	{144,203},	{145,204},	
{107,168},	{146,205},	{147,206},	{107,169},	
{148,207},	{149,208},	{150,209},	{151,210},	
{107,170},	{107,168},	{152,211},	{153,212},	
{154,213},	{155,214},	{156,215},	{157,216},	
{158,217},	{159,218},	{160,219},	{161,220},	
{162,221},	{164,222},	{165,223},	{166,224},	
{167,225},	{167,225},	{168,226},	{169,227},	
{171,228},	{107,168},	{172,230},	{171,229},	
{171,229},	{171,229},	{171,229},	{171,229},	
{171,229},	{171,229},	{171,229},	{171,229},	
{171,229},	{173,231},	{174,232},	{175,233},	
{176,234},	{177,235},	{178,236},	{180,237},	
{181,238},	{182,239},	{183,240},	{185,241},	
{186,242},	{188,243},	{189,244},	{190,245},	
{167,225},	{167,225},	{191,247},	{193,248},	
{194,249},	{195,250},	{196,251},	{198,252},	
{200,253},	{201,254},	{202,255},	{203,256},	
{204,257},	{205,258},	{206,259},	{207,260},	
{209,261},	{210,262},	{211,263},	{212,264},	
{213,265},	{214,266},	{215,267},	{216,269},	
{217,270},	{218,271},	{219,272},	{221,273},	
{223,274},	{224,275},	{225,276},	{215,268},	
{226,168},	{225,277},	{225,277},	{225,277},	
{225,277},	{225,277},	{225,277},	{225,277},	
{225,277},	{225,277},	{225,277},	{228,229},	
{228,229},	{228,229},	{228,229},	{228,229},	
{228,229},	{228,229},	{228,229},	{228,229},	
{228,229},	{230,278},	{231,279},	{232,280},	
{233,281},	{190,246},	{235,282},	{237,283},	
{238,284},	{239,285},	{240,286},	{241,287},	
{242,288},	{246,289},	{247,290},	{248,291},	
{249,292},	{250,293},	{251,294},	{252,295},	
{253,296},	{255,297},	{256,298},	{257,299},	
{258,300},	{260,301},	{261,302},	{262,303},	
{263,304},	{264,305},	{265,306},	{267,307},	
{268,308},	{270,309},	{271,310},	{272,311},	
{273,312},	{276,277},	{276,277},	{276,277},	
{276,277},	{276,277},	{276,277},	{276,277},	
{276,277},	{276,277},	{276,277},	{279,313},	
{280,314},	{281,315},	{282,316},	{283,317},	
{284,318},	{288,319},	{289,320},	{291,321},	
{292,322},	{294,323},	{296,324},	{297,325},	
{299,326},	{300,327},	{301,328},	{302,329},	
{306,330},	{307,331},	{308,332},	{309,333},	
{310,334},	{311,335},	{312,336},	{314,337},	
{315,338},	{316,339},	{317,340},	{318,341},	
{320,342},	{322,343},	{323,344},	{324,345},	
{325,346},	{326,347},	{327,348},	{328,349},	
{329,350},	{331,351},	{332,352},	{333,353},	
{334,354},	{335,355},	{336,356},	{337,357},	
{339,358},	{340,359},	{341,360},	{343,361},	
{345,362},	{346,363},	{348,364},	{349,365},	
{350,366},	{352,367},	{354,368},	{356,369},	
{358,370},	{360,371},	{361,372},	{362,373},	
{365,374},	{367,375},	{369,376},	{370,377},	
{371,378},	{372,379},	{373,380},	{375,381},	
{376,382},	{377,383},	{378,384},	{379,385},	
{380,386},	{381,387},	{382,388},	{385,389},	
{386,390},	{388,391},	{391,392},	{0,0},	
{0,0}};
struct yysvf yysvec[] = {
{0,	0,	0},
{1,	0,		0},	
{0,	yysvec+1,	0},	
{3,	0,		yyvstop+1},
{3,	0,		0},	
{89,	0,		yyvstop+3},
{-211,	0,		0},	
{0,	0,		yyvstop+5},
{0,	0,		yyvstop+7},
{0,	0,		yyvstop+9},
{0,	0,		yyvstop+11},
{0,	0,		yyvstop+13},
{79,	0,		yyvstop+15},
{5,	0,		yyvstop+17},
{173,	0,		yyvstop+19},
{0,	0,		yyvstop+21},
{0,	0,		yyvstop+23},
{32,	0,		yyvstop+25},
{34,	0,		yyvstop+27},
{36,	0,		yyvstop+29},
{0,	0,		yyvstop+31},
{97,	yysvec+5,	yyvstop+33},
{83,	yysvec+5,	yyvstop+35},
{0,	0,		yyvstop+37},
{0,	0,		yyvstop+39},
{115,	yysvec+5,	yyvstop+41},
{38,	yysvec+5,	yyvstop+43},
{121,	yysvec+5,	yyvstop+45},
{135,	yysvec+5,	yyvstop+47},
{144,	yysvec+5,	yyvstop+49},
{117,	yysvec+5,	yyvstop+51},
{39,	yysvec+5,	yyvstop+53},
{133,	yysvec+5,	yyvstop+55},
{80,	yysvec+5,	yyvstop+57},
{116,	yysvec+5,	yyvstop+59},
{144,	yysvec+5,	yyvstop+61},
{41,	yysvec+5,	yyvstop+63},
{159,	yysvec+5,	yyvstop+65},
{35,	yysvec+5,	yyvstop+67},
{52,	yysvec+5,	yyvstop+69},
{165,	yysvec+5,	yyvstop+71},
{78,	yysvec+5,	yyvstop+73},
{83,	yysvec+5,	yyvstop+75},
{161,	yysvec+5,	yyvstop+77},
{102,	yysvec+5,	yyvstop+79},
{0,	0,		yyvstop+81},
{0,	0,		yyvstop+83},
{0,	0,		yyvstop+85},
{0,	0,		yyvstop+87},
{170,	yysvec+12,	yyvstop+89},
{-264,	0,		0},	
{239,	0,		yyvstop+91},
{0,	0,		yyvstop+93},
{0,	0,		yyvstop+95},
{0,	0,		yyvstop+97},
{127,	yysvec+5,	yyvstop+99},
{151,	yysvec+5,	yyvstop+101},
{144,	yysvec+5,	yyvstop+103},
{0,	yysvec+5,	yyvstop+105},
{134,	yysvec+5,	yyvstop+108},
{146,	yysvec+5,	yyvstop+110},
{154,	yysvec+5,	yyvstop+112},
{172,	yysvec+5,	yyvstop+114},
{163,	yysvec+5,	yyvstop+116},
{168,	yysvec+5,	yyvstop+118},
{171,	yysvec+5,	yyvstop+120},
{177,	yysvec+5,	yyvstop+122},
{182,	yysvec+5,	yyvstop+124},
{184,	yysvec+5,	yyvstop+126},
{240,	yysvec+5,	yyvstop+128},
{194,	yysvec+5,	yyvstop+130},
{192,	yysvec+5,	yyvstop+132},
{192,	yysvec+5,	yyvstop+134},
{190,	yysvec+5,	yyvstop+136},
{189,	yysvec+5,	yyvstop+138},
{0,	yysvec+5,	yyvstop+140},
{202,	yysvec+5,	yyvstop+143},
{197,	yysvec+5,	yyvstop+146},
{193,	yysvec+5,	yyvstop+148},
{200,	yysvec+5,	yyvstop+150},
{197,	yysvec+5,	yyvstop+152},
{199,	yysvec+5,	yyvstop+154},
{217,	yysvec+5,	yyvstop+156},
{198,	yysvec+5,	yyvstop+158},
{219,	yysvec+5,	yyvstop+160},
{211,	yysvec+5,	yyvstop+162},
{0,	yysvec+5,	yyvstop+164},
{207,	yysvec+5,	yyvstop+167},
{211,	yysvec+5,	yyvstop+169},
{218,	yysvec+5,	yyvstop+171},
{227,	yysvec+5,	yyvstop+173},
{228,	yysvec+5,	yyvstop+175},
{222,	yysvec+5,	yyvstop+177},
{212,	yysvec+5,	yyvstop+179},
{236,	yysvec+5,	yyvstop+181},
{226,	yysvec+5,	yyvstop+183},
{221,	yysvec+5,	yyvstop+185},
{238,	yysvec+5,	yyvstop+187},
{228,	yysvec+5,	yyvstop+189},
{237,	yysvec+5,	yyvstop+191},
{230,	yysvec+5,	yyvstop+193},
{226,	yysvec+5,	yyvstop+195},
{228,	yysvec+5,	yyvstop+197},
{237,	yysvec+5,	yyvstop+199},
{235,	yysvec+5,	yyvstop+201},
{300,	0,		yyvstop+203},
{-297,	yysvec+50,	0},	
{-357,	0,		0},	
{0,	yysvec+50,	0},	
{277,	yysvec+51,	yyvstop+205},
{248,	yysvec+5,	yyvstop+207},
{250,	yysvec+5,	yyvstop+209},
{249,	yysvec+5,	yyvstop+211},
{252,	yysvec+5,	yyvstop+213},
{248,	yysvec+5,	yyvstop+215},
{247,	yysvec+5,	yyvstop+217},
{309,	yysvec+5,	yyvstop+219},
{267,	yysvec+5,	yyvstop+221},
{257,	yysvec+5,	yyvstop+223},
{273,	yysvec+5,	yyvstop+225},
{273,	yysvec+5,	yyvstop+227},
{271,	yysvec+5,	yyvstop+229},
{272,	yysvec+5,	yyvstop+231},
{265,	yysvec+5,	yyvstop+233},
{274,	yysvec+5,	yyvstop+235},
{271,	yysvec+5,	yyvstop+237},
{0,	0,		yyvstop+239},
{264,	yysvec+5,	yyvstop+241},
{0,	yysvec+5,	yyvstop+243},
{281,	yysvec+5,	yyvstop+246},
{276,	yysvec+5,	yyvstop+248},
{271,	yysvec+5,	yyvstop+250},
{267,	yysvec+5,	yyvstop+252},
{0,	yysvec+5,	yyvstop+254},
{272,	yysvec+5,	yyvstop+257},
{0,	yysvec+5,	yyvstop+259},
{284,	yysvec+5,	yyvstop+262},
{285,	yysvec+5,	yyvstop+264},
{283,	yysvec+5,	yyvstop+266},
{284,	yysvec+5,	yyvstop+268},
{331,	yysvec+5,	yyvstop+270},
{274,	yysvec+5,	yyvstop+272},
{290,	yysvec+5,	yyvstop+274},
{284,	yysvec+5,	yyvstop+276},
{296,	yysvec+5,	yyvstop+278},
{280,	yysvec+5,	yyvstop+280},
{281,	yysvec+5,	yyvstop+282},
{288,	yysvec+5,	yyvstop+284},
{300,	yysvec+5,	yyvstop+286},
{301,	yysvec+5,	yyvstop+288},
{286,	yysvec+5,	yyvstop+290},
{298,	yysvec+5,	yyvstop+292},
{301,	yysvec+5,	yyvstop+294},
{306,	yysvec+5,	yyvstop+296},
{363,	yysvec+5,	yyvstop+298},
{297,	yysvec+5,	yyvstop+300},
{291,	yysvec+5,	yyvstop+302},
{293,	yysvec+5,	yyvstop+304},
{315,	yysvec+5,	yyvstop+306},
{313,	yysvec+5,	yyvstop+308},
{305,	yysvec+5,	yyvstop+310},
{305,	yysvec+5,	yyvstop+312},
{315,	yysvec+5,	yyvstop+314},
{0,	yysvec+5,	yyvstop+316},
{359,	yysvec+5,	yyvstop+319},
{302,	yysvec+5,	yyvstop+321},
{308,	yysvec+5,	yyvstop+323},
{352,	yysvec+105,	yyvstop+325},
{-375,	yysvec+50,	0},	
{-376,	yysvec+50,	0},	
{0,	0,		yyvstop+327},
{379,	0,		0},	
{312,	yysvec+5,	yyvstop+329},
{326,	yysvec+5,	yyvstop+331},
{322,	yysvec+5,	yyvstop+333},
{339,	yysvec+5,	yyvstop+335},
{324,	yysvec+5,	yyvstop+337},
{330,	yysvec+5,	yyvstop+339},
{341,	yysvec+5,	yyvstop+341},
{0,	0,		yyvstop+343},
{333,	yysvec+5,	yyvstop+345},
{336,	yysvec+5,	yyvstop+347},
{340,	yysvec+5,	yyvstop+349},
{338,	yysvec+5,	yyvstop+351},
{0,	yysvec+5,	yyvstop+353},
{337,	yysvec+5,	yyvstop+356},
{347,	yysvec+5,	yyvstop+358},
{0,	yysvec+5,	yyvstop+360},
{347,	yysvec+5,	yyvstop+363},
{349,	yysvec+5,	yyvstop+365},
{393,	yysvec+5,	yyvstop+367},
{338,	yysvec+5,	yyvstop+369},
{0,	yysvec+5,	yyvstop+371},
{350,	yysvec+5,	yyvstop+374},
{359,	yysvec+5,	yyvstop+376},
{360,	yysvec+5,	yyvstop+378},
{344,	yysvec+5,	yyvstop+380},
{0,	yysvec+5,	yyvstop+382},
{348,	yysvec+5,	yyvstop+385},
{0,	0,		yyvstop+387},
{349,	yysvec+5,	yyvstop+389},
{346,	yysvec+5,	yyvstop+391},
{357,	yysvec+5,	yyvstop+393},
{362,	yysvec+5,	yyvstop+395},
{352,	yysvec+5,	yyvstop+397},
{420,	yysvec+5,	yyvstop+399},
{350,	yysvec+5,	yyvstop+401},
{353,	yysvec+5,	yyvstop+403},
{0,	yysvec+5,	yyvstop+405},
{371,	yysvec+5,	yyvstop+408},
{359,	yysvec+5,	yyvstop+410},
{359,	yysvec+5,	yyvstop+412},
{362,	yysvec+5,	yyvstop+414},
{371,	0,		0},	
{372,	yysvec+5,	yyvstop+416},
{365,	yysvec+5,	yyvstop+418},
{374,	yysvec+5,	yyvstop+420},
{360,	yysvec+5,	yyvstop+422},
{366,	yysvec+5,	yyvstop+424},
{377,	yysvec+5,	yyvstop+426},
{0,	yysvec+5,	yyvstop+428},
{434,	yysvec+5,	yyvstop+431},
{0,	0,		yyvstop+433},
{379,	yysvec+5,	yyvstop+435},
{365,	yysvec+5,	yyvstop+437},
{437,	0,		0},	
{437,	0,		0},	
{0,	yysvec+226,	yyvstop+439},
{447,	0,		0},	
{0,	yysvec+228,	yyvstop+441},
{396,	yysvec+5,	yyvstop+443},
{392,	yysvec+5,	yyvstop+445},
{398,	yysvec+5,	yyvstop+447},
{411,	yysvec+5,	yyvstop+449},
{0,	yysvec+5,	yyvstop+451},
{393,	yysvec+5,	yyvstop+454},
{0,	yysvec+5,	yyvstop+456},
{396,	yysvec+5,	yyvstop+459},
{415,	yysvec+5,	yyvstop+461},
{403,	yysvec+5,	yyvstop+463},
{413,	yysvec+5,	yyvstop+465},
{457,	yysvec+5,	yyvstop+467},
{406,	yysvec+5,	yyvstop+469},
{0,	yysvec+5,	yyvstop+471},
{0,	yysvec+5,	yyvstop+474},
{0,	0,		yyvstop+477},
{412,	yysvec+5,	yyvstop+479},
{417,	yysvec+5,	yyvstop+481},
{422,	yysvec+5,	yyvstop+483},
{406,	yysvec+5,	yyvstop+485},
{407,	yysvec+5,	yyvstop+487},
{417,	yysvec+5,	yyvstop+489},
{423,	yysvec+5,	yyvstop+491},
{414,	yysvec+5,	yyvstop+493},
{0,	yysvec+5,	yyvstop+495},
{415,	yysvec+5,	yyvstop+498},
{412,	yysvec+5,	yyvstop+500},
{426,	yysvec+5,	yyvstop+502},
{426,	0,		0},	
{0,	yysvec+5,	yyvstop+504},
{432,	yysvec+5,	yyvstop+507},
{420,	yysvec+5,	yyvstop+509},
{430,	yysvec+5,	yyvstop+511},
{422,	yysvec+5,	yyvstop+513},
{432,	yysvec+5,	yyvstop+515},
{422,	0,		0},	
{0,	yysvec+5,	yyvstop+517},
{434,	yysvec+5,	yyvstop+520},
{435,	yysvec+5,	yyvstop+522},
{0,	yysvec+5,	yyvstop+524},
{436,	yysvec+5,	yyvstop+527},
{429,	yysvec+5,	yyvstop+529},
{423,	yysvec+5,	yyvstop+531},
{428,	0,		0},	
{0,	yysvec+5,	yyvstop+533},
{0,	yysvec+5,	yyvstop+536},
{493,	0,		0},	
{0,	yysvec+276,	yyvstop+539},
{0,	yysvec+5,	yyvstop+541},
{442,	yysvec+5,	yyvstop+544},
{451,	yysvec+5,	yyvstop+546},
{439,	yysvec+5,	yyvstop+548},
{440,	yysvec+5,	yyvstop+550},
{450,	yysvec+5,	yyvstop+552},
{457,	yysvec+5,	yyvstop+554},
{0,	yysvec+5,	yyvstop+556},
{0,	yysvec+5,	yyvstop+559},
{0,	0,		yyvstop+562},
{441,	yysvec+5,	yyvstop+564},
{447,	yysvec+5,	yyvstop+566},
{0,	yysvec+5,	yyvstop+568},
{451,	yysvec+5,	yyvstop+571},
{463,	yysvec+5,	yyvstop+573},
{0,	yysvec+5,	yyvstop+575},
{464,	yysvec+5,	yyvstop+578},
{0,	yysvec+5,	yyvstop+580},
{517,	yysvec+5,	yyvstop+583},
{462,	yysvec+5,	yyvstop+585},
{0,	yysvec+5,	yyvstop+587},
{465,	yysvec+5,	yyvstop+590},
{460,	0,		0},	
{450,	yysvec+5,	yyvstop+592},
{464,	yysvec+5,	yyvstop+594},
{0,	yysvec+5,	yyvstop+596},
{0,	yysvec+5,	yyvstop+599},
{0,	yysvec+5,	yyvstop+602},
{453,	0,		0},	
{454,	yysvec+5,	yyvstop+605},
{471,	yysvec+5,	yyvstop+607},
{468,	yysvec+5,	yyvstop+609},
{475,	yysvec+5,	yyvstop+611},
{459,	yysvec+5,	yyvstop+613},
{466,	0,		0},	
{0,	yysvec+5,	yyvstop+615},
{460,	yysvec+5,	yyvstop+618},
{455,	yysvec+5,	yyvstop+620},
{532,	yysvec+5,	yyvstop+622},
{467,	yysvec+5,	yyvstop+625},
{478,	yysvec+5,	yyvstop+627},
{0,	yysvec+5,	yyvstop+629},
{470,	yysvec+5,	yyvstop+632},
{0,	yysvec+5,	yyvstop+634},
{472,	yysvec+5,	yyvstop+637},
{474,	yysvec+5,	yyvstop+639},
{481,	0,		0},	
{487,	yysvec+5,	yyvstop+641},
{469,	yysvec+5,	yyvstop+643},
{478,	0,		0},	
{470,	yysvec+5,	yyvstop+645},
{480,	yysvec+5,	yyvstop+647},
{0,	0,		yyvstop+649},
{485,	yysvec+5,	yyvstop+651},
{545,	yysvec+5,	yyvstop+653},
{470,	yysvec+5,	yyvstop+656},
{487,	yysvec+5,	yyvstop+658},
{472,	yysvec+5,	yyvstop+660},
{483,	0,		0},	
{491,	yysvec+5,	yyvstop+662},
{0,	yysvec+5,	yyvstop+664},
{494,	0,		0},	
{487,	yysvec+5,	yyvstop+667},
{489,	yysvec+5,	yyvstop+669},
{0,	yysvec+5,	yyvstop+671},
{498,	yysvec+5,	yyvstop+674},
{0,	yysvec+5,	yyvstop+676},
{503,	0,		0},	
{487,	yysvec+5,	yyvstop+679},
{0,	yysvec+5,	yyvstop+681},
{501,	0,		0},	
{489,	yysvec+5,	yyvstop+684},
{503,	yysvec+5,	yyvstop+686},
{0,	yysvec+5,	yyvstop+688},
{503,	0,		0},	
{0,	yysvec+5,	yyvstop+691},
{496,	yysvec+5,	yyvstop+694},
{0,	yysvec+5,	yyvstop+696},
{491,	0,		0},	
{0,	yysvec+5,	yyvstop+699},
{503,	0,		0},	
{0,	yysvec+5,	yyvstop+702},
{508,	yysvec+5,	yyvstop+705},
{494,	yysvec+5,	yyvstop+707},
{512,	0,		0},	
{0,	yysvec+5,	yyvstop+709},
{0,	0,		yyvstop+712},
{511,	yysvec+5,	yyvstop+714},
{0,	yysvec+5,	yyvstop+716},
{508,	0,		0},	
{0,	yysvec+5,	yyvstop+719},
{569,	0,		0},	
{507,	0,		0},	
{506,	yysvec+5,	yyvstop+722},
{503,	yysvec+5,	yyvstop+724},
{502,	0,		0},	
{0,	yysvec+5,	yyvstop+726},
{511,	0,		0},	
{518,	0,		0},	
{520,	0,		0},	
{506,	yysvec+5,	yyvstop+729},
{518,	yysvec+5,	yyvstop+731},
{513,	0,		0},	
{524,	0,		0},	
{521,	0,		0},	
{0,	0,		yyvstop+733},
{0,	yysvec+5,	yyvstop+735},
{528,	yysvec+5,	yyvstop+738},
{514,	0,		0},	
{0,	0,		yyvstop+740},
{521,	0,		0},	
{0,	yysvec+5,	yyvstop+742},
{0,	0,		yyvstop+745},
{529,	0,		0},	
{0,	0,		yyvstop+747},
{0,	0,	0}};
struct yywork *yytop = yycrank+630;
struct yysvf *yybgin = yysvec+1;
unsigned char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,011 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,01  ,01  ,'$' ,01  ,01  ,047 ,
01  ,01  ,'*' ,01  ,01  ,01  ,01  ,'/' ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,'$' ,'$' ,'$' ,'D' ,'D' ,'$' ,'$' ,
'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,
'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,
'$' ,'$' ,'$' ,01  ,01  ,01  ,01  ,'$' ,
01  ,'$' ,'$' ,'$' ,'D' ,'D' ,'$' ,'$' ,
'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,
'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,'$' ,
'$' ,'$' ,'$' ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
0};
unsigned char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/* @(#) A.10.32.03 HP C LANGUAGE TOOL (NCFORM) 960517 $      */
int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
 
#ifdef YYNLS16_WCHAR
unsigned char yytextuc[YYLMAX * sizeof(wchar_t)];
# ifdef YY_PCT_POINT /* for %pointer */
wchar_t yytextarr[YYLMAX];
wchar_t *yytext;
# else               /* %array */
wchar_t yytextarr[1];
wchar_t yytext[YYLMAX];
# endif
#else
unsigned char yytextuc;
# ifdef YY_PCT_POINT /* for %pointer */
unsigned char yytextarr[YYLMAX];
unsigned char *yytext;
# else               /* %array */
unsigned char yytextarr[1];
# ifdef YYCHAR_ARRAY
char yytext[YYLMAX];
# else
unsigned char yytext[YYLMAX];
# endif
# endif
#endif

struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
unsigned char yysbuf[YYLMAX];
unsigned char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
/*	char *yylastch;
 * ***** nls8 ***** */
	unsigned char *yylastch, sec, third, fourth;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
#ifdef YYNLS16_WCHAR
		yylastch = yytextuc;
#else
# ifdef YYCHAR_ARRAY
		yylastch = (unsigned char *)yytext;
# else
		yylastch = yytext;
# endif
#endif
	else {
		yymorfg=0;
#ifdef YYNLS16_WCHAR
		yylastch = yytextuc+yylenguc;
#else
# ifdef YYCHAR_ARRAY
		yylastch = (unsigned char *)yytext+yyleng;
# else
		yylastch = yytext+yyleng;
# endif
#endif
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = &yycrank[yystate->yystoff];
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == 0)break;
				}
			*yylastch++ = yych = input();
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt = &yycrank[yystate->yystoff]) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
#ifdef YYNLS16_WCHAR
				yylenguc = yylastch-yytextuc+1;
				yytextuc[yylenguc] = 0;
#else
# ifdef YYCHAR_ARRAY
				yyleng = yylastch-(unsigned char*)yytext+1;
# else
				yyleng = yylastch-yytext+1;
# endif
				yytext[yyleng] = 0;
#endif
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
#ifdef YYNLS16_WCHAR
					sprint(yytextuc);
#else
					sprint(yytext);
#endif
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
#ifdef YYNLS16_WCHAR
		if (yytextuc[0] == 0  /* && feof(yyin) */)
#else
		if (yytext[0] == 0  /* && feof(yyin) */)
#endif
			{
			yysptr=yysbuf;
			return(0);
			}
#ifdef YYNLS16_WCHAR
		yyprevious = yytextuc[0] = input();
#else
		yyprevious = yytext[0] = input();
#endif
		if (yyprevious>0) {
			output(yyprevious);
#ifdef YYNLS16
                        if (yynls16) {
			int noBytes;
                        sec = input();
                        third = input();
                        fourth = input();
#ifdef YYNLS16_WCHAR
                        noBytes = MultiByte(yytextuc[0],sec,third,fourth);
#else 
                        noBytes = MultiByte(yytext[0],sec,third,fourth);
#endif          
     					switch(noBytes) {
     					case 2:
#ifdef YYNLS16_WCHAR
 						output(yyprevious=yytextuc[0]=sec);
#else
 						output(yyprevious=yytext[0]=sec);
#endif
                                                 unput(fourth);
                                                 unput(third);
                                                 break;
     					case 3:
#ifdef YYNLS16_WCHAR
 						output(yyprevious=yytextuc[0]=sec);
 						output(yyprevious=yytextuc[0]=third);
#else
 						output(yyprevious=yytext[0]=sec);
 						output(yyprevious=yytext[0]=third);
#endif
                                                 unput(fourth);
                                                 break; 
                                         case 4:
#ifdef YYNLS16_WCHAR
 						output(yyprevious=yytextuc[0]=sec);
 						output(yyprevious=yytextuc[0]=third);
 						output(yyprevious=yytextuc[0]=fourth);
#else
 						output(yyprevious=yytext[0]=sec);
 						output(yyprevious=yytext[0]=third);
 						output(yyprevious=yytext[0]=fourth);
#endif
                                                 break;                                                                                            
					default:
					        unput(fourth);
					        unput(third);
						unput(sec);
						break;
						}
					}
#endif
                }
#ifdef YYNLS16_WCHAR
		yylastch=yytextuc;
#else
# ifdef YYCHAR_ARRAY
		yylastch=(unsigned char*)yytext;
# else
		yylastch=yytext;
# endif
#endif
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}

# ifdef __cplusplus
yyback(int *p, int m)
# else
yyback(p, m)
	int *p;
# endif
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	
	}

#if (defined(__cplusplus) || defined(__STDC__))
void yyoutput(int c)
#else
yyoutput(c)
  int c;
# endif
{
	output(c);
}

#if (defined(__cplusplus) || defined(__STDC__))
void yyunput(int c)
#else
yyunput(c)
   int c;
#endif
{
	unput(c);
}
