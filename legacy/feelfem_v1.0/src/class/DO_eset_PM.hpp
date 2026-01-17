/*
 *  feelfem version 1.0  Copyright(c)  NEC Corporation 1999-2003
 *                       Programmed by Hidehiro  FUJIO
 *
 *  Filename : PM_eset.hpp
 *  Date     : 2003/02/13
 *  Modified : 
 *  
 *  Purpose  : Eset related common routine for ProgramModel
 *  
 */
void GenerateCoSolveEcalRoutines(SolveElement *);
void GenerateEsetRoutines(SolveElement *);
void pushEsetRoutineName(int,int,int);

void doEsetCalcInterpolation(SolveElement *,
			     DiscretizedComponent *dcPtr,
                	     int solveNo,int elemNo,int quadNo);
void doEsetCalcInterpolationSub(int quadNo,
        	        	SolveElement *,
				Element *,
				int type        );
