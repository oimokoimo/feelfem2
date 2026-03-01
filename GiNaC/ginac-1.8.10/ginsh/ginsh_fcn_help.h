insert_help("charpoly",
"charpoly(matrix, symbol)"
" - characteristic polynomial of a matrix"
);
insert_help("coeff",
"coeff(expression, object, number)"
" - extracts coefficient of object^number from a polynomial"
);
insert_help("collect",
"collect(expression, object-or-list)"
" - collects coefficients of like powers (result in recursive form)"
);
insert_help("collect_distributed",
"collect_distributed(expression, list)"
" - collects coefficients of like powers (result in distributed form)"
);
insert_help("collect_common_factors",
"collect_common_factors(expression)"
" - collects common factors from the terms of sums"
);
insert_help("conjugate",
"conjugate(expression)"
" - complex conjugation"
);
insert_help("content",
"content(expression, symbol)"
" - content part of a polynomial"
);
insert_help("decomp_rational",
"decomp_rational(expression, symbol)"
" - decompose rational function into polynomial and proper rational function"
);
insert_help("degree",
"degree(expression, object)"
" - degree of a polynomial"
);
insert_help("denom",
"denom(expression)"
" - denominator of a rational function"
);
insert_help("determinant",
"determinant(matrix)"
" - determinant of a matrix"
);
insert_help("diag",
"diag(expression...)"
" - constructs diagonal matrix"
);
insert_help("diff",
"diff(expression, symbol [, number])"
" - partial differentiation"
);
insert_help("divide",
"divide(expression, expression)"
" - exact polynomial division"
);
insert_help("evalf",
"evalf(expression)"
" - evaluates an expression to a floating point number"
);
insert_help("evalm",
"evalm(expression)"
" - evaluates sums, products and integer powers of matrices"
);
insert_help("expand",
"expand(expression)"
" - expands an expression"
);
insert_help("factor",
"factor(expression)"
" - factorizes an expression (univariate)"
);
insert_help("find",
"find(expression, pattern)"
" - returns a list of all occurrences of a pattern in an expression"
);
insert_help("fsolve",
"fsolve(expression, symbol, number, number)"
" - numerically find root of a real-valued function within an interval"
);
insert_help("gcd",
"gcd(expression, expression)"
" - greatest common divisor"
);
insert_help("has",
"has(expression, pattern)"
" - returns '1' if the first expression contains the pattern as a subexpression, '0' otherwise"
);
insert_help("integer_content",
"integer_content(expression)"
" - integer content of a polynomial"
);
insert_help("inverse",
"inverse(matrix)"
" - inverse of a matrix"
);
insert_help("is",
"is(relation)"
" - returns '1' if the relation is true, '0' otherwise (false or undecided)"
);
insert_help("lcm",
"lcm(expression, expression)"
" - least common multiple"
);
insert_help("lcoeff",
"lcoeff(expression, object)"
" - leading coefficient of a polynomial"
);
insert_help("ldegree",
"ldegree(expression, object)"
" - low degree of a polynomial"
);
insert_help("lsolve",
"lsolve(equation-list, symbol-list)"
" - solve system of linear equations"
);
insert_help("map",
"map(expression, pattern)"
" - apply function to each operand; the function to be applied is specified as a pattern with the '$0' wildcard standing for the operands"
);
insert_help("match",
"match(expression, pattern)"
" - check whether expression matches a pattern; returns a list of wildcard substitutions or 'FAIL' if there is no match"
);
insert_help("nops",
"nops(expression)"
" - number of operands in expression"
);
insert_help("normal",
"normal(expression)"
" - rational function normalization"
);
insert_help("numer",
"numer(expression)"
" - numerator of a rational function"
);
insert_help("numer_denom",
"numer_denom(expression)"
" - numerator and denumerator of a rational function as a list"
);
insert_help("op",
"op(expression, number)"
" - extract operand from expression"
);
insert_help("power",
"power(expr1, expr2)"
" - exponentiation (equivalent to writing expr1^expr2)"
);
insert_help("prem",
"prem(expression, expression, symbol)"
" - pseudo-remainder of polynomials"
);
insert_help("primpart",
"primpart(expression, symbol)"
" - primitive part of a polynomial"
);
insert_help("quo",
"quo(expression, expression, symbol)"
" - quotient of polynomials"
);
insert_help("rank",
"rank(matrix)"
" - rank of a matrix"
);
insert_help("rem",
"rem(expression, expression, symbol)"
" - remainder of polynomials"
);
insert_help("resultant",
"resultant(expression, expression, symbol)"
" - resultant of two polynomials with respect to symbol s"
);
insert_help("series",
"series(expression, relation-or-symbol, order)"
" - series expansion"
);
insert_help("series_to_poly",
"series_to_poly(series)"
" - convert a series into a polynomial by dropping the Order() term"
);
insert_help("sprem",
"sprem(expression, expression, symbol)"
" - sparse pseudo-remainder of polynomials"
);
insert_help("sqrfree",
"sqrfree(expression [, symbol-list])"
" - square-free factorization of a polynomial"
);
insert_help("sqrfree_parfrac",
"sqrfree_parfrac(expression, symbol)"
" - square-free partial fraction decomposition of rational function"
);
insert_help("sqrt",
"sqrt(expression)"
" - square root"
);
insert_help("subs",
"subs(expression, relation-or-list)"
);
insert_help("subs",
"subs(expression, look-for-list, replace-by-list)"
" - substitute subexpressions (you may use wildcards)"
);
insert_help("tcoeff",
"tcoeff(expression, object)"
" - trailing coefficient of a polynomial"
);
insert_help("time",
"time(expression)"
" - returns the time in seconds needed to evaluate the given expression"
);
insert_help("trace",
"trace(matrix)"
" - trace of a matrix"
);
insert_help("transpose",
"transpose(matrix)"
" - transpose of a matrix"
);
insert_help("unassign",
"unassign('symbol')"
" - unassign an assigned symbol (mind the quotes, please!)"
);
insert_help("unit",
"unit(expression, symbol)"
" - unit part of a polynomial"
);
