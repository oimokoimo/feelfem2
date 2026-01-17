/*  expressionParser.y  parser for feelfem
 *  Date      2001/06/18
 *  Modified  
 *
 *
 */ 

%{

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>

#include "../class/feeldef.hpp"
#include "../class/feelfem.hpp" 
#include "../class/list.hpp"          // use list
#include "../class/stack.hpp"         // use stack (list)

// Expression components
#include "../parser/Syntax/SNand.hpp"
#include "../parser/Syntax/SNor.hpp"
#include "../parser/Syntax/SNxor.hpp"

#include "../parser/Syntax/SNequal.hpp"
#include "../parser/Syntax/SNnequal.hpp"

#include "../parser/Syntax/SNgt.hpp"
#include "../parser/Syntax/SNge.hpp"
#include "../parser/Syntax/SNlt.hpp"
#include "../parser/Syntax/SNle.hpp"

#include "../parser/Syntax/SNplus.hpp"     // +
#include "../parser/Syntax/SNsub.hpp"      // -
#include "../parser/Syntax/SNmul.hpp"      // *
#include "../parser/Syntax/SNdiv.hpp"      // /

#include "../parser/Syntax/SNminus.hpp"    // - (single op)
#include "../parser/Syntax/SNname.hpp"
#include "../parser/Syntax/SNsymbol.hpp"
#include "../parser/Syntax/SNint.hpp"
#include "../parser/Syntax/SNdouble.hpp"
#include "../parser/Syntax/SNfunction.hpp"
#include "../parser/Syntax/SNbracket.hpp"
#include "../parser/Syntax/SNexprlist.hpp"
#include "../parser/Syntax/SNidentifierlist.hpp"

#include "../class/Expression.hpp"


extern "C" {
#include "lex.h"
}

// parse trees
stack <SNunit *>   eParseSNunitStack;
stack <SNname *>   eParseSNnameStack;


#define newSNunit1(CLASS,ARG1)            \
        CLASS* cp = new CLASS(ARG1);      \
        cp->LineNumber(numberOfLines);    \
        yyval.asSNunit = cp

#define newSNunit2(CLASS,ARG1,ARG2)       \
        CLASS* cp = new CLASS(ARG1,ARG2); \
        cp->LineNumber(numberOfLines);    \
        yyval.asSNunit = cp


%}

%union {
  char             *asString;
  long              asInteger;
  double            asDouble;
  SNname           *asName; 
  SNunit           *asSNunit;
  SNidentifierlist *asSNidentifierlist;
  Expression       *asExpression;
}

%token Equal			/* == */
%token Nequal			/* != */
%token GE			/* >= */
%token LE			/* =< */
%token Or			/* || */
%token Xor			/* !| */
%token And			/* && */



%token <asInteger> Integer
%token <asDouble>  Double
%token <asString>  Identifier

%type  <asExpression> Expression
%type  <asSNunit>  expression
%type  <asSNunit>  outlet
%type  <asSNunit>  or_expression
%type  <asSNunit>  xor_expression
%type  <asSNunit>  and_expression
%type  <asSNunit>  equality_expression
%type  <asSNunit>  relational_expression
%type  <asSNunit>  additive_expression
%type  <asSNunit>  multiplicative_expression
%type  <asSNunit>  unary_expression
%type  <asSNunit>  postfix_expression
%type  <asSNunit>  minus_expression
%type  <asSNunit>  primary_expression
%type  <asSNunit>  integer
%type  <asSNunit>  double
%type  <asSNunit>  atom
%type  <asSNunit>  function
%type  <asInteger> exprlist
/* %type  <asSNunit>  Exprlist */


%start program

%%

program   :  Expression
          
/*---------------*/
/* expressions   */
/*---------------*/


Expression
  : expression {
                 Expression *exprPtr = new Expression($1);
		 exprPtr->LineNumber(eNumberOfLines);
		 $$ = exprPtr;
               }
  ;

expression
  : outlet
  ;

outlet
  : or_expression
  ;


or_expression
  :  xor_expression
  |  or_expression Or xor_expression
     {  newSNunit2(SNor, $1, $3); }
  ;

xor_expression
  :  and_expression
  |  xor_expression Xor and_expression
     {   newSNunit2(SNxor, $1,$3); }
  ;

and_expression
  : equality_expression
  | and_expression And equality_expression
    {  newSNunit2(SNand, $1,$3); }
  ;


equality_expression
  : relational_expression
  | relational_expression Equal relational_expression
    {   newSNunit2(SNequal , $1,$3); }
  | relational_expression Nequal relational_expression
    {   newSNunit2(SNnequal, $1,$3); }
  ;

relational_expression
  : additive_expression
  | additive_expression '<' additive_expression
    { newSNunit2(SNlt, $1, $3); }
  | additive_expression '>' additive_expression
    { newSNunit2(SNgt, $1, $3); }
  | additive_expression GE  additive_expression
    { newSNunit2(SNge, $1, $3); }
  | additive_expression LE  additive_expression
    { newSNunit2(SNle, $1, $3); }
  ;

additive_expression
  :  multiplicative_expression
  |  additive_expression '+' multiplicative_expression
     { newSNunit2(SNplus, $1, $3); }
  |  additive_expression '-' multiplicative_expression
     { newSNunit2(SNsub , $1, $3); }
  ;

multiplicative_expression
  : unary_expression
  | multiplicative_expression '*' unary_expression
    { newSNunit2(SNmul, $1, $3); }
  | multiplicative_expression '/' unary_expression
    { newSNunit2(SNdiv, $1, $3); }  
  ;

unary_expression
  : postfix_expression
  ;

postfix_expression
  : minus_expression
  ;


minus_expression
  :  primary_expression
  |  '-' primary_expression { newSNunit1(SNminus,$2); }
  ;

primary_expression
  :  integer
  |  double
  |  atom
  |  function
  | '(' outlet ')' { newSNunit1(SNbracket,$2);}
  ;


integer   :  Integer  { newSNunit1(SNint , $1); }
          ;

double    :  Double   { newSNunit1(SNdouble , $1); }
          ;

atom      :  Identifier { newSNunit1(SNsymbol, $1);
                          disposeString($1); }
          ;

function  :  Identifier '(' exprlist ')'  
             { 
               SNexprlist * exprlistPtr = new SNexprlist( $3 );
               exprlistPtr->LineNumber(eNumberOfLines);
               for(int i = $3 -1 ; i >= 0; i--) {
                 (*exprlistPtr)[i] = eParseSNunitStack.pop();
               }
	       newSNunit2(SNfunction,$1,exprlistPtr);
   	       disposeString($1);
             }


          ;

/*Exprlist  :  exprlist              { 
               SNexprlist * exprlistPtr = new SNexprlist( $1 );
               exprlistPtr->LineNumber(eNumberOfLines);
               for(int i = $1 -1 ; i >= 0; i--) {
                 (*exprlistPtr)[i] = eParseSNunitStack.pop();
               }
	       $$ = exprlistPtr;
             }

*/

exprlist  :  expression              { eParseSNunitStack.push($1);
                                       $$ = 1; }
          |  exprlist ',' expression { eParseSNunitStack.push($3);
                                       $$ = $1 + 1; }
          ;

  
%%

void yyerror(char *errmsg)
{
   numberOfErrors++;

   cerr << feelfem_currentFileName << ":";
   cerr << eNumberOfLines   << ":";
   cerr << errmsg          << "\n";

   if(numberOfErrors > MaxNumberOfErrors) {
     cerr << feelfem_currentFileName << ":" << eNumberOfLines << ":" ;
     cerr << "too many errors.\n";
     exit(1);
   }
   return;
}

