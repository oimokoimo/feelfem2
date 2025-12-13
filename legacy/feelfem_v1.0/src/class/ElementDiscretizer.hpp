/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2001
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : ElementDiscretizer.hpp
 *  Date     : 2002/01/11
 *  Modified : 
 *  
 *  Purpose  : Element Discretization control class
 *  
 */

#ifndef FEM_CLASS_ELEMENTDISCRETIZER
#define FEM_CLASS_ELEMENTDISCRETIZER

class ElementDiscretizer {

public:
  ElementDiscretizer();
  ~ElementDiscretizer();


  void linearDiscretize();
  void nonlinearDiscretize();

private:
  // unknowns
  int numberOfFemUnknowns;
  int numberOfEwiseUnknows;

  // knowns
  int numberOfSclarKnowns;
  int numberOfFemKnowns;
  int numberOfEwiseIntpKnowns;
  int numberOfEwiseGaussPKnowns;
  
};


#endif
