/*  feelfem.y  parser for feelfem
 *  Date      1999/07/19
 *  Modified  1999/07/19
 *  Restart
 *  Re-Restart 2001/01/15
 *
 *
 *  Ported 2026/01/16
 *
 *  feelfem2 (modernized/ported)
 *  Copyright (C) 2025-2026 Hidehiro Fujio and contributors
 *  SPDX-License-Identifier: BSD-3-Clause
 *  Repository: https://github.com/oimokoimo/feelfem2
 *
 *  Notes:
 *   - Parser and language spec are carried over from feelfem 1.0.
 *   - Back-end and build system are updated for modern C++ toolchains.
 *
 *
 */ 

%{

#include <iostream>
#include <stdlib.h>

#include "../class/feeldef.hpp"
#include "../class/feelfem.hpp" 
#include "../class/list.hpp"          // use list
#include "../class/stack.hpp"         // use stack (list)

// Geom sentences
#include "Syntax/SNgeomDimension.hpp"
#include "Syntax/SNgeomEdge.hpp"
#include "Syntax/SNgeomMesher.hpp"
#include "Syntax/SNgeomPoint.hpp"
#include "Syntax/SNgeomProblem.hpp"
#include "Syntax/SNgeomRegion.hpp"
#include "Syntax/SNgeomSurface.hpp"
#include "Syntax/SNgeomMaterialRegion.hpp"


// Mesh sentences
#include "Syntax/SNdimension.hpp"
#include "Syntax/SNpoint.hpp"
#include "Syntax/SNedge.hpp"
#include "Syntax/SNpedge.hpp"
#include "Syntax/SNregion.hpp"
#include "Syntax/SNdomain.hpp"
#include "Syntax/SNvertices.hpp"

#include "Syntax/SNmeshDoubleVar.hpp"
#include "Syntax/SNmeshAssignment.hpp"

// Element sentences
#include "Syntax/SNelement.hpp"
#include "Syntax/SNelementDoubleVar.hpp"
#include "Syntax/SNelementAssignment.hpp"
#include "Syntax/SNelementIntp.hpp"

// Quadrature sentences
#include "Syntax/SNquadrature.hpp"
#include "Syntax/SNquadratureDoubleVar.hpp"
#include "Syntax/SNquadratureAssignment.hpp"
#include "Syntax/SNquadratureGaussP.hpp"


// Var sentences
#include "Syntax/SNdoubleVar.hpp"
#include "Syntax/SNintVar.hpp"
#include "Syntax/SNconstVar.hpp"
#include "Syntax/SNfemVar.hpp"
#include "Syntax/SNvfemVar.hpp"
#include "Syntax/SNewiseVar.hpp"
#include "Syntax/SNmaterialVar.hpp"
#include "Syntax/SNfunctionDef.hpp"

// Scheme sentences
#include "Syntax/SNprogramModel.hpp"  // ProgramModel 
#include "Syntax/SNassignment.hpp"
#include "Syntax/SNlabel.hpp"
#include "Syntax/SNwrite.hpp"
#include "Syntax/SNstring.hpp"        // only for SNwrite(021122)
#include "Syntax/SNexpr.hpp"          // only for SNwrite(021122)
#include "Syntax/SNif.hpp"
#include "Syntax/SNparametric.hpp"
#include "Syntax/SNelementType.hpp"  // specify element type in GiD

#include "Syntax/SNoption.hpp"
#include "Syntax/SNperspect.hpp"
#include "Syntax/SNoutput.hpp"


#include "Syntax/SNsolve.hpp"
#include "Syntax/SNsolveSolver.hpp"
#include "Syntax/SNsolveQuadrature.hpp"
#include "Syntax/SNsolveParametric.hpp"
#include "Syntax/SNsolveNonlinear.hpp"
#include "Syntax/SNsolveWeq.hpp"
#include "Syntax/SNsolveDirichlet.hpp"
#include "Syntax/SNsolveNeumann.hpp"

#include "Syntax/SNweqTerm.hpp"
#include "Syntax/SNweqTerms.hpp"

// Expression components
#include "Syntax/SNand.hpp"
#include "Syntax/SNor.hpp"
#include "Syntax/SNxor.hpp"

#include "Syntax/SNequal.hpp"
#include "Syntax/SNnequal.hpp"

#include "Syntax/SNgt.hpp"
#include "Syntax/SNge.hpp"
#include "Syntax/SNlt.hpp"
#include "Syntax/SNle.hpp"

#include "Syntax/SNplus.hpp"     // +
#include "Syntax/SNsub.hpp"      // -
#include "Syntax/SNmul.hpp"      // *
#include "Syntax/SNdiv.hpp"      // /

#include "Syntax/SNminus.hpp"    // - (single op)
#include "Syntax/SNname.hpp"
#include "Syntax/SNsymbol.hpp"
#include "Syntax/SNint.hpp"
#include "Syntax/SNdouble.hpp"
#include "Syntax/SNfunction.hpp"
#include "Syntax/SNbracket.hpp"
#include "Syntax/SNexprlist.hpp"
#include "Syntax/SNidentifierlist.hpp"

#include "../class/Expression.hpp"

#include "rinji.hpp" 


extern "C" {
#include "lex.h"
}

// parse trees
void debug_execute( list <void *> &,list <void *> &,list <void *> &);

#include "../class/parseExternals.hpp"


stack <SNunit *>   parseSNunitStack;
stack <SNname *>   parseSNnameStack;
stack <SNunit *>   parseElementStack;
stack <SNunit *>   parseQuadratureStack;
stack <SNunit *>   parseSolveStack;
stack <SNunit *>   parseOptionStack;
stack <SNunit *>   parseWriteStack;


int numberOfErrors;

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
  char                *asString;
  long                 asInteger;
  double               asDouble;
  SNname              *asName; 
  SNunit              *asSNunit;
  SNidentifierlist    *asSNidentifierlist;
  Expression          *asExpression;
  SNweqTerms          *asSNweqTerms;
  SNweqTerm           *asSNweqTerm;
  SNsolveNeumannPairs *asSNsolveNeumannPairs;
}

%token GEOM            /*  geom  */
%token MESH            /*  mesh  */
%token MESHER
%token PROBLEM
%token DIMENSION
%token POINT
%token EDGE
%token PEDGE          /*  parameter edge */
%token SURFACE
%token VOLUME
%token SUBDOMAIN
%token REGION
%token DOMAIN
%token VERTICES
%token GENERATOR

%token ELEMENT
%token QUADRATURE

%token VAR
%token INT
%token DOUBLE
%token CONST
%token FEM
%token VFEM
%token EWISE
%token MATERIAL
%token FUNCTION

%token SCHEME
%token PROGRAMMODEL
%token ELEMENTTYPE
%token IF
%token THEN
%token ELSE
%token WHERE
%token GOTO
%token RETURN
%token WHILE
%token WRITE

%token PERSPECT
%token OUTPUT


%token SOLVE
%token SOLVER
%token PARAMETRIC
%token NONLINEAR
%token METHOD
%token WEQ
%token INTEGRAL
%token BINTEGRAL
%token DBC
%token NBC
%token IN
%token AT
%token ON

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
%token <asString>  String

%type  <asName>    identifier
%type  <asInteger> identifierlist
%type  <asSNidentifierlist>  Identifierlist

%type  <asSNweqTerm>  weq_term
%type  <asSNweqTerms> weq_terms

%type  <asSNsolveNeumannPairs> neumann_terms

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
%type  <asSNunit>  Exprlist

%type  <asInteger> regionIdentifierList
%type  <asInteger> holeIdentifierList


%start program

%%

program   : /* empty */
          | blocks



blocks    : block
          | blocks block

block     : mesh_block
          | geom_block
          | var_block
          | element_definition
          | quadrature_definition
          | scheme_block

/*-------------*/
/* geom block  */   
/*-------------*/

geom_block : GEOM '{' geom_statements '}'
 
geom_statements
: geom_statement
| geom_statements geom_statement
;

geom_statement
 : MESHER    Identifier ';' { SNgeomMesher *np = new SNgeomMesher($2);
                              np->LineNumber(numberOfLines);
                              parseGeomLst.addlast(np);
                            }                         
 | DIMENSION Integer ';' { SNgeomDimension *np = new SNgeomDimension($2);
                           np->LineNumber(numberOfLines);
                           parseGeomLst.addlast(np);
                         }                         
 | PROBLEM   Identifier ';' { SNgeomProblem *np = new SNgeomProblem($2);
                              np->LineNumber(numberOfLines);
                              parseGeomLst.addlast(np);
                         }                         

 | POINT   '(' Identifierlist ')' ';'
                         {    SNgeomPoint *np = new SNgeomPoint($3);
                              np->LineNumber(numberOfLines);
                              parseGeomLst.addlast(np);
                         }                         

 | EDGE    '(' Identifierlist ')' ';'
                         {    SNgeomEdge *np = new SNgeomEdge($3);
                              np->LineNumber(numberOfLines);
                              parseGeomLst.addlast(np);
                         }                      

 | SURFACE '(' Identifierlist ')' ';'
                         {    SNgeomSurface *np = new SNgeomSurface($3);
                              np->LineNumber(numberOfLines);
                              parseGeomLst.addlast(np);
                         }                         

 | REGION  '(' Identifierlist ')' ';'
                         {    SNgeomRegion *np = new SNgeomRegion($3);
                              np->LineNumber(numberOfLines);
                              parseGeomLst.addlast(np);
                         }

 | MATERIAL  Identifier '(' Identifierlist ')' ';'
                         {    
			   SNgeomMaterialRegion *np = 
			     new SNgeomMaterialRegion($2,$4);
			   np->LineNumber(numberOfLines);
			   parseGeomLst.addlast(np);
			 }
 ;

/*-------------*/
/* mesh block  */   
/*-------------*/

mesh_block : MESH '{' mesh_statements '}'

mesh_statements 
: mesh_statement
| mesh_statements mesh_statement
;
mesh_statement
 : DIMENSION Integer ';'   { SNdimension *np = new SNdimension($2);
                             np->LineNumber(numberOfLines);
                             parseMeshLst.addlast(np);             }
 | POINT point_list ';'
 | EDGE  edge_list  ';'
 /* with both two ends, and without number of points */
 | PEDGE Identifier '(' Identifierlist ')' '[' '(' Expression ',' Expression ')' ',' Identifier '=' Expression ',' Expression ']' ';' 
                    { SNpedge *np = new SNpedge($2,$4,$8,$10,$13,$15,$17);
                      np->LineNumber(numberOfLines);
		      disposeString($2);
		      disposeString($13);
                      parseMeshLst.addlast(np);             }

 /* with start points omitted (including many points are specified) 
    and without number of points */
 | PEDGE Identifier '(' ',' Identifierlist ')' '[' '(' Expression ',' Expression ')' ',' Identifier '=' Expression ',' Expression ']' ';' 
                    { SNpedge *np= new SNpedge(1,$2,$5,$9,$11,$14,$16,$18);
                      np->LineNumber(numberOfLines);
		      disposeString($2);
		      disposeString($14);
                      parseMeshLst.addlast(np);             }

/* without both side points and without number of points */
 | PEDGE Identifier  '[' '(' Expression ',' Expression ')' ',' Identifier '=' Expression ',' Expression ']' ';' 
                    { SNpedge *np = new SNpedge($2,$5,$7,$10,$12,$14);
                      np->LineNumber(numberOfLines);
		      disposeString($2);
		      disposeString($10);
                      parseMeshLst.addlast(np);             }

 /* with both side points (including many points are specified)*/
 | PEDGE Identifier '(' Identifierlist ')' '[' '(' Expression ',' Expression ')' ',' Identifier '=' Expression ',' Expression ',' Integer ']' ';' 
                    { SNpedge *np = new SNpedge($2,$4,$8,$10,$13,$15,$17,$19);
                      np->LineNumber(numberOfLines);
		      disposeString($2);
		      disposeString($13);
                      parseMeshLst.addlast(np);             }

 /* with start points omitted (including many points are specified)*/
 | PEDGE Identifier '(' ',' Identifierlist ')' '[' '(' Expression ',' Expression ')' ',' Identifier '=' Expression ',' Expression ',' Integer ']' ';' 
                    { SNpedge *np= new SNpedge(1,$2,$5,$9,$11,$14,$16,$18,$20);
                      np->LineNumber(numberOfLines);
		      disposeString($2);
		      disposeString($14);
                      parseMeshLst.addlast(np);             }

/* without both side points */
 | PEDGE Identifier  '[' '(' Expression ',' Expression ')' ',' Identifier '=' Expression ',' Expression ',' Integer ']' ';' 
                    { SNpedge *np = new SNpedge($2,$5,$7,$10,$12,$14,$16);
                      np->LineNumber(numberOfLines);
		      disposeString($2);
		      disposeString($10);
                      parseMeshLst.addlast(np);             }


 | REGION Identifier '[' Identifier ']' '(' regionIdentifierList ')' ';'
                    {
		      SNregion *np = new SNregion($2,$4,$7);
		      np->LineNumber(numberOfLines);
		      (*np)[0] = parseSNunitStack.pop();
		      for(int i = 1 ; i < $7; i++) {
			(*np)[$7-i] = parseSNunitStack.pop();
		      }

		      disposeString($2);
		      disposeString($4);
		      parseMeshLst.addlast(np);
                    }

 | DOMAIN Identifier '(' Identifierlist ')' ';'
                    { SNdomain *np = new SNdomain( $2 , $4);
   	  	      np->LineNumber(numberOfLines);
                      parseMeshLst.addlast(np);
                    }

 | VERTICES '(' Integer ')' ';'
                    { 
                      SNvertices *np = new SNvertices($3);
   	  	      np->LineNumber(numberOfLines);
                      parseMeshLst.addlast(np);
                    }

 | DOUBLE mesh_double_defs ';'
 
 | Identifier '=' Expression ';' 
                    { 
                      SNmeshAssignment *np = new SNmeshAssignment($1,$3);
   	  	      np->LineNumber(numberOfLines);
                      parseMeshLst.addlast(np);
		      disposeString($1);
                    }   
            
 ; 


point_list
 :   point_argument
 |   point_list ',' point_argument

point_argument
 : Identifier '(' Exprlist ')' 
                           { SNpoint *np = new SNpoint($1, $3 );
                             np->LineNumber(numberOfLines);
                             parseMeshLst.addlast(np);             
                             disposeString($1);                  }

edge_list
 :  edge_argument
 |  edge_list ',' edge_argument


edge_argument
 :  Identifier '(' Identifierlist ')'
                           { SNedge *np = new SNedge($1, $3);
                             np->LineNumber(numberOfLines);
                             parseMeshLst.addlast(np);             
                             disposeString($1);                  }

regionIdentifierList
  :  Identifierlist                { parseSNunitStack.push($1); 
                                     $$ = 1;                   }
  |  Identifierlist ':' holeIdentifierList
                                   { parseSNunitStack.push($1); 
                                     $$ = $3 + 1;              }
holeIdentifierList
  :  '[' Identifierlist ']'        { parseSNunitStack.push($2); 
                                     $$ = 1;                   }
  |  holeIdentifierList ',' '[' Identifierlist ']'
                                   { parseSNunitStack.push($4); 
	 			   $$ = $1 + 1;                } 

mesh_double_defs 
  :  mesh_double_def
  |  mesh_double_defs ',' mesh_double_def


mesh_double_def 
  :  Identifier 
                 { 
                   SNmeshDoubleVar *np = new SNmeshDoubleVar($1);
                   np->LineNumber(numberOfLines);
                   parseMeshLst.addlast(np);             
                   disposeString($1);                  
                 }
  |  Identifier '=' Expression
                 { 
                   SNmeshDoubleVar *np = new SNmeshDoubleVar($1,$3);
                   np->LineNumber(numberOfLines);
                   parseMeshLst.addlast(np);             
                   disposeString($1);                  
                 }

/*-------------*/
/*  var block  */   
/*-------------*/
var_block : VAR '{' var_statements '}'
  ;

var_statements
  : var_statement
  | var_statements var_statement

var_statement
  : DOUBLE double_var_defs ';' 
  | INT int_var_defs       ';'  
  | CONST Identifier '=' Expression ';' 
                              {  
                                 SNconstVar *np = new SNconstVar($2,$4);
                                 np->LineNumber(numberOfLines);
				 disposeString($2);
                                 parseVarLst.addlast(np);
                              }
  | FEM fem_var_defs ';'
  | VFEM vfem_var_defs ';'
  | EWISE ewise_var_defs ';'
  | MATERIAL material_var_defs ';'
  | FUNCTION function_def ';'
  ;


double_var_defs
  : double_var_def
  | double_var_defs ',' double_var_def
  ;

double_var_def
  : Identifier      
               {  
                 SNdoubleVar *np = new SNdoubleVar($1);
                 np->LineNumber(numberOfLines);
                 parseVarLst.addlast(np);
		 disposeString($1);
               }

  | Identifier '=' Expression
               {  
                 SNdoubleVar *np = new SNdoubleVar($1,$3);
                 np->LineNumber(numberOfLines);
                 parseVarLst.addlast(np);
		 disposeString($1);
               }
  ;

int_var_defs
  : int_var_def
  | int_var_defs ',' int_var_def
  ;

int_var_def
  : Identifier      
               {  
                 SNintVar *np = new SNintVar($1);
                 np->LineNumber(numberOfLines);
                 parseVarLst.addlast(np);
		 disposeString($1);
               }
  | Identifier '=' Expression
               {  
                 SNintVar *np = new SNintVar($1,$3);
                 np->LineNumber(numberOfLines);
                 parseVarLst.addlast(np);
		 disposeString($1);
               }
  ;

fem_var_defs
  : fem_var_def
  | fem_var_defs ',' fem_var_def

fem_var_def
  : Identifier '[' Identifier ']'  
                              {  
                                 SNfemVar *np = new SNfemVar($1,$3);
                                 np->LineNumber(numberOfLines);
				 disposeString($1);
				 disposeString($3);
                                 parseVarLst.addlast(np);
                              }
  ;

vfem_var_defs
  : vfem_var_def
  | vfem_var_defs ',' vfem_var_def

vfem_var_def
  : Identifier '[' Identifier ']'  
                              {  
                                 SNvfemVar *np = new SNvfemVar($1,$3);
                                 np->LineNumber(numberOfLines);
				 disposeString($1);
				 disposeString($3);
                                 parseVarLst.addlast(np);
                              }
  ;

ewise_var_defs
  : ewise_var_def
  | ewise_var_defs ',' ewise_var_def

ewise_var_def
  : Identifier
                              {  
                                 SNewiseVar *np = new SNewiseVar($1);
                                 np->LineNumber(numberOfLines);
				 disposeString($1);
                                 parseVarLst.addlast(np);
                              }
  | Identifier '[' Identifier ']'
                              {  
                                 SNewiseVar *np = new SNewiseVar($1,$3);
                                 np->LineNumber(numberOfLines);
				 disposeString($1);
				 disposeString($3);
                                 parseVarLst.addlast(np);
                              }
  ;

material_var_defs
  : material_var_def
  | material_var_defs ',' material_var_def


material_var_def
  : Identifier  option {  SNmaterialVar *np = 
  			    new SNmaterialVar($1,parseOptionStack);
                            np->LineNumber(numberOfLines);
  			    disposeString($1);
                            parseVarLst.addlast(np);
                       }
  ;

function_def  
  : Identifier '(' Identifierlist ')' { SNfunctionDef *np = 
                                          new SNfunctionDef($1,$3);
                                          np->LineNumber(numberOfLines);
                                          disposeString($1);
                                          parseVarLst.addlast(np);
                                      }
  ;

/*----------------*/
/* element block  */   
/*----------------*/
element_definition 
: ELEMENT Identifier '[' Identifier ']'
'{' element_statements '}'      
   {
     SNelement *np = new SNelement($2,$4,parseElementStack);
     np->LineNumber(numberOfLines);
     parseElementLst.addlast(np);
     disposeString($2);
     disposeString($4);
   }

element_statements
: element_statement
| element_statements element_statement
;

element_statement
  : DOUBLE element_double_defs ';'
  | Identifier '=' Expression ';'
                    { 
                      SNelementAssignment *np = new SNelementAssignment($1,$3);
   	  	      np->LineNumber(numberOfLines);
                      parseElementStack.push(np);
		      disposeString($1);
                    }   
  | interpolation_def ';'
  ;

interpolation_def
   : '(' Exprlist ')' ':' Expression 
                    {
                      SNelementIntp *np = new SNelementIntp($2,$5);
                      np->LineNumber(numberOfLines);
                      parseElementStack.push(np);
                    }
   | '(' Exprlist ')' '[' Identifier ']' ':' Expression 
                    {
                      SNelementIntp *np = new SNelementIntp($2,$5,$8);
                      np->LineNumber(numberOfLines);
                      parseElementStack.push(np);
		      disposeString($5);
                    }
   ;

element_double_defs
  : element_double_def
  | element_double_defs ',' element_double_def

element_double_def
  : Identifier 
               {
		 SNelementDoubleVar *np = new SNelementDoubleVar($1);
                 np->LineNumber(numberOfLines);
                 parseElementStack.push(np);
                 disposeString($1);
	       }
  | Identifier '=' Expression
               {
                 SNelementDoubleVar *np = new SNelementDoubleVar($1,$3);
                 np->LineNumber(numberOfLines);
                 parseElementStack.push(np);             
                 disposeString($1);              
               }
  ;          


/*------------------*/
/* quadrature block */   
/*------------------*/
quadrature_definition
: QUADRATURE Identifier '[' Identifier ']'
'{' quadrature_statements '}'      
   {
     SNquadrature *np = new SNquadrature($2,$4,parseQuadratureStack);
     np->LineNumber(numberOfLines);
     parseQuadratureLst.addlast(np);
     disposeString($2);
     disposeString($4);
   }

quadrature_statements
: quadrature_statement
| quadrature_statements quadrature_statement
;

quadrature_statement
  : DOUBLE quadrature_double_defs ';'
  | Identifier '=' Expression ';'
                    { 
                      SNquadratureAssignment *np = 
			new SNquadratureAssignment($1,$3);
   	  	      np->LineNumber(numberOfLines);
                      parseQuadratureStack.push(np);
		      disposeString($1);
                    }   
  | gauss_point_def ';'
  ;

gauss_point_def
   : '(' Exprlist ')' ':' Expression 
                    {
                      SNquadratureGaussP *np = new SNquadratureGaussP($2,$5);
                      np->LineNumber(numberOfLines);
                      parseQuadratureStack.push(np);
                    }

quadrature_double_defs
  : quadrature_double_def
  | quadrature_double_defs ',' quadrature_double_def

quadrature_double_def
  : Identifier 
               {
		 SNquadratureDoubleVar *np = new SNquadratureDoubleVar($1);
                 np->LineNumber(numberOfLines);
                 parseQuadratureStack.push(np);
                 disposeString($1);
	       }
  | Identifier '=' Expression
               {
                 SNquadratureDoubleVar *np = new SNquadratureDoubleVar($1,$3);
                 np->LineNumber(numberOfLines);
                 parseQuadratureStack.push(np);             
                 disposeString($1);              
               }
  ;          



/*---------------*/
/* scheme block  */   
/*---------------*/
scheme_block : SCHEME '{' scheme_statements '}'

scheme_statements
             : scheme_statement
             | scheme_statements scheme_statement
             ;

scheme_statement
 :PROGRAMMODEL Identifier ';'
                             { SNprogramModel *np = new SNprogramModel($2);
                               np->LineNumber(numberOfLines);
                               parseSchemeLst.addlast(np);
			       disposeString($2);
                             }


 | ELEMENTTYPE Identifierlist ';' 
                             {
                               SNelementType *np = new SNelementType($2);
			       np->LineNumber(numberOfLines);
			       parseSchemeLst.addlast(np);
                             }

 | PARAMETRIC Identifier ';' { 
                               SNparametric *np = new SNparametric($2);
			       np->LineNumber(numberOfLines);
			       parseSchemeLst.addlast(np);
			       disposeString($2);
                             }

 | solve_block

 | Identifier '=' Expression ';' 
                             { SNassignment *np = new SNassignment($1,$3);
                               np->LineNumber(numberOfLines);
                               parseSchemeLst.addlast(np);
			       disposeString($1);
                             }
 | Identifier '=' Expression ',' AT Identifierlist ';'
                             { SNassignment *np = 
				 new SNassignment($1,$3,SN_ASSIGNMENT_AT,$6);
                               np->LineNumber(numberOfLines);
                               parseSchemeLst.addlast(np);
			       disposeString($1);
                             }

 | Identifier '=' Expression ',' ON Identifierlist ';'
                             { SNassignment *np = 
				 new SNassignment($1,$3,SN_ASSIGNMENT_ON,$6);
                               np->LineNumber(numberOfLines);
                               parseSchemeLst.addlast(np);
			       disposeString($1);
                             }

 | Identifier '=' Expression ',' IN Identifierlist ';'
                             { SNassignment *np = 
				 new SNassignment($1,$3,SN_ASSIGNMENT_IN,$6);
                               np->LineNumber(numberOfLines);
                               parseSchemeLst.addlast(np);
			       disposeString($1);
                             }
 | Identifier '=' Expression ',' WHERE '(' Expression ')' ';'
                             { SNassignment *np = 
  	                      new SNassignment($1,$3,SN_ASSIGNMENT_WHERE,$7);
                               np->LineNumber(numberOfLines);
                               parseSchemeLst.addlast(np);
			       disposeString($1);
                             }

 | Identifier '=' INTEGRAL '(' Expression ')' ';'
                             { SNassignment *np =
	                   new SNassignment($1,$5,ASSIGNMENT_TYPE_INTEGRAL);
                               np->LineNumber(numberOfLines);
                               parseSchemeLst.addlast(np);
			       disposeString($1);
                             }

/*  integral with numerical integration specified */
 | Identifier '=' INTEGRAL '[' Identifier ']' '(' Expression ')' ';'
                        { SNassignment *np =
	                   new SNassignment($1,$5,$8,ASSIGNMENT_TYPE_INTEGRAL);
                           np->LineNumber(numberOfLines);
                           parseSchemeLst.addlast(np);
   		           disposeString($1);
                           disposeString($5);
                        }


 | Identifier ':'            { SNlabel *np = 
				 new SNlabel($1);
                                 np->LineNumber(numberOfLines);
                                 parseSchemeLst.addlast(np);
	 		         disposeString($1);
                             }

 | PERSPECT '[' Expression ']' ';'  
                             { SNperspect *np =
				 new SNperspect($3);
			         np->LineNumber(numberOfLines);
			         parseSchemeLst.addlast(np);
			     }
 | PERSPECT '[' Expression ']' option ';'
                             { SNperspect *np =
				 new SNperspect($3,parseOptionStack);
			         np->LineNumber(numberOfLines);
			         parseSchemeLst.addlast(np);
			     }

 | OUTPUT '[' Identifierlist ']' ';' 
                              {
                               SNoutput *np = new SNoutput($3);
			       np->LineNumber(numberOfLines);
			       parseSchemeLst.addlast(np);
                              }


 | OUTPUT '[' Identifierlist ']' option ';'
                             { SNoutput *np =
                                 new SNoutput($3,parseOptionStack);
                 	         np->LineNumber(numberOfLines);
                                 parseSchemeLst.addlast(np);
                             }

 | WRITE  '[' write_list ']' ';'
                             { SNwrite *np =
                                 new SNwrite(parseWriteStack);
                 	         np->LineNumber(numberOfLines);
                                 parseSchemeLst.addlast(np);
                             }

 | IF '(' Expression ')' GOTO Identifier ';'
                             { SNif *np =
                                 new SNif($3,$6);
   			         np->LineNumber(numberOfLines);
				 parseSchemeLst.addlast(np);
                             }
 ; 



           /* test */


write_list
 : write_item
 | write_item ',' write_list
 ;

write_item
 : Expression 
             { SNexpr *np = new SNexpr($1);
	       np->LineNumber(numberOfLines);
               parseWriteStack.push(np);
             }


 | String    { SNstring *np = new SNstring($1);
	       np->LineNumber(numberOfLines);
               parseWriteStack.push(np);
             }

option
 : '(' option_list ')'
 ;
 

option_list
 :  option_item
 |  option_item ',' option_list
 ;

option_item
 :  Identifier '=' Expression 
    {
      SNoption *np = new SNoption($1, $3);
      disposeString($1);
      np->LineNumber(numberOfLines);
      parseOptionStack.push(np);
    }

 |  Identifier '=' String
    {
      SNoption *np = new SNoption($1, $3);
      disposeString($1);
      disposeString($3);
      np->LineNumber(numberOfLines);
      parseOptionStack.push(np);
    }
 ;


solve_block
 : SOLVE '[' Identifierlist ';' Identifierlist ']' '{' solve_statements '}' 
   {
     SNsolve *np = new SNsolve($3,$5,parseSolveStack);
     np->LineNumber(numberOfLines);
     parseSchemeLst.addlast(np);
   }
 ;

solve_statements
 : solve_statement
 | solve_statements solve_statement
 ;

solve_statement
 : QUADRATURE Identifier ';'{
                             SNsolveQuadrature *np = new SNsolveQuadrature($2);
       	                     np->LineNumber(numberOfLines);
                             disposeString($2);
                             parseSolveStack.push(np);
                            }
 | PARAMETRIC Identifier ';'{
                             SNsolveParametric *np = new SNsolveParametric($2);
			     np->LineNumber(numberOfLines);
			     disposeString($2);
			     parseSolveStack.push(np);
                            }

 | SOLVER     Identifier ';'{
                             SNsolveSolver *np = new SNsolveSolver($2);
       	                     np->LineNumber(numberOfLines);
                             disposeString($2);
                             parseSolveStack.push(np);
                            }
 | NONLINEAR ';'            {
                             SNsolveNonlinear *np = new 
			       SNsolveNonlinear("default");
       	                     np->LineNumber(numberOfLines);
                             parseSolveStack.push(np);
                            }

 | NONLINEAR Identifier ';' {
                             SNsolveNonlinear *np = new 
			       SNsolveNonlinear($2);
       	                     np->LineNumber(numberOfLines);
                             disposeString($2);
                             parseSolveStack.push(np);
                            }
 | WEQ  weq_terms  '=' weq_terms ';' {
                             SNsolveWeq *np = new 
			       SNsolveWeq($2,$4);
       	                     np->LineNumber(numberOfLines);
                             parseSolveStack.push(np);
                             }
 | DBC  Identifier '=' Expression ',' ON Identifierlist ';' {
                             SNsolveDirichlet *np = new
			       SNsolveDirichlet($2,$4,$7);
			     np->LineNumber(numberOfLines);
			     parseSolveStack.push(np);
			     disposeString($2);
                             }
 | NBC  neumann_terms ',' ON Identifierlist ';' {
                             SNsolveNeumann *np = new
			       SNsolveNeumann($2,$5);
   			       np->LineNumber(numberOfLines);
			       parseSolveStack.push(np);
                             }
 ;

neumann_terms
 : Identifier '=' Expression   {
                                SNsolveNeumannPairs *np = new
				  SNsolveNeumannPairs($1,$3);
				np->LineNumber(numberOfLines);
				disposeString($1);
                                $$ = np;
                               }
 | neumann_terms ',' Identifier '=' Expression
                                    {
                                     SNsolveNeumannPairs *np = $1;
                                     np->addPair($3,$5);
				     disposeString($3);
				     $$ = np;
                                    }
 ;


weq_terms
 : weq_term                { SNweqTerms *np = new SNweqTerms( 1,$1); 
       	                     np->LineNumber(numberOfLines);
                             $$ = np;                               }
                             
 | '-' weq_term            { SNweqTerms *np = new SNweqTerms(-1,$2); 
       	                     np->LineNumber(numberOfLines);
                             $$ = np;                               }

 | weq_terms '+' weq_term  { SNweqTerms *np = $1; 
                             np->addWeqTerm( 1,$3);
                             $$ = np;                               }

 | weq_terms '-' weq_term  { SNweqTerms *np = $1; 
                             np->addWeqTerm(-1,$3);
                             $$ = np;                               }
 ;

weq_term
 :  INTEGRAL '(' Expression ')' { SNweqTerm *np = 
				    new SNweqTerm(TYPE_REGIONAL_INTEGRAND,
						  $3                      );
       	                          np->LineNumber(numberOfLines);
                                  $$ = np;                                  }
 |  INTEGRAL '[' Identifier ']' '(' Expression ')'
                                { SNweqTerm *np = 
				    new SNweqTerm(TYPE_REGIONAL_INTEGRAND,
						  $3                     ,
						  $6                      );
                     		  disposeString($3);
       	                          np->LineNumber(numberOfLines);
                                  $$ = np;                                  }

 | BINTEGRAL '(' Expression ')' { SNweqTerm *np = 
				    new SNweqTerm(TYPE_BOUNDARY_INTEGRAND,
						  $3                      );
       	                          np->LineNumber(numberOfLines);
                                  $$ = np;                                  }

 | BINTEGRAL '[' Identifier ']' '(' Expression ')'
                                { SNweqTerm *np = 
				    new SNweqTerm(TYPE_BOUNDARY_INTEGRAND,
						  $3                     ,
						  $6                      );
                     		  disposeString($3);
       	                          np->LineNumber(numberOfLines);
                                  $$ = np;                                  }
 ;

/*------------------------------*/
/* basic grammatical components */
/*------------------------------*/

identifier : Identifier 
             { SNname *np = new SNname($1);
	       np->LineNumber(numberOfLines);
               $$ = np;
               disposeString($1);
             }
           ;


Identifierlist  :  identifierlist              { 
               SNidentifierlist *identifierlistPtr = 
		                                 new SNidentifierlist( $1 );
               identifierlistPtr->LineNumber(numberOfLines);
               for(int i = $1 -1 ; i >= 0; i--) {
                 (*identifierlistPtr)[i] = parseSNnameStack.pop();
               }
	       $$ = identifierlistPtr;
             }



identifierlist  
  :  identifier                    { parseSNnameStack.push($1);
                                     $$ = 1;                   }
  |  identifierlist ',' identifier { parseSNnameStack.push($3);
                                     $$ = $1 + 1;              }
  ;

/*---------------*/
/* expressions   */
/*---------------*/

Expression
  : expression {
                 Expression *exprPtr = new Expression($1);
		 exprPtr->LineNumber(numberOfLines);
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
               exprlistPtr->LineNumber(numberOfLines);
               for(int i = $3 -1 ; i >= 0; i--) {
                 (*exprlistPtr)[i] = parseSNunitStack.pop();
               }
	       newSNunit2(SNfunction,$1,exprlistPtr);
   	       disposeString($1);
             }


          ;

Exprlist  :  exprlist              { 
               SNexprlist * exprlistPtr = new SNexprlist( $1 );
               exprlistPtr->LineNumber(numberOfLines);
               for(int i = $1 -1 ; i >= 0; i--) {
                 (*exprlistPtr)[i] = parseSNunitStack.pop();
               }
	       $$ = exprlistPtr;
             }



exprlist  :  expression              { parseSNunitStack.push($1);
                                       $$ = 1; }
          |  exprlist ',' expression { parseSNunitStack.push($3);
                                       $$ = $1 + 1; }
          ;

  
%%

void yyerror(const char *errmsg)
{
   extern int feelfem_web;
   numberOfErrors++;

   if(feelfem_web) {
   std::cout << feelfem_currentFileName << ":";
   std::cout << numberOfLines   << ":";
   std::cout << errmsg          << "\n";
   }
   else {
   std::cerr << feelfem_currentFileName << ":";
   std::cerr << numberOfLines   << ":";
   std::cerr << errmsg          << "\n";
   }

   if(numberOfErrors > MaxNumberOfErrors) {
     std::cerr << feelfem_currentFileName << ":" << numberOfLines << ":" ;
     std::cerr << "too many errors.\n";
     exit(1);
   }
   return;
}

