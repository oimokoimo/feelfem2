#include "Solve.hpp"
#include "Source.hpp"
#include "SolveScheme.hpp"
#include "ElemScheme.hpp"
#include "EcalScheme.hpp"

// Solve class
int Solve::solves       = 0;

// Source class
FILE *Source::fpSource   = NULL;
int   Source::divideFlag = 0;

// SolveScheme class
int SolveScheme::solveSchemes = 0;

// ElemScheme class
int ElemScheme::elemSchemes = 0;

int EcalScheme::ecalSchemes = 0;


