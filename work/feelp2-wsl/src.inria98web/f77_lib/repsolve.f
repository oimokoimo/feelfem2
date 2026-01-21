      subroutine rep_solve(no,istat,itype,method,idat1,idat2,idat3)
*-------------------------------------------------
*  FEEL process time report routine
* ----------------------------------
* parameters
*  istat   0   Come to solve routine (initialize the time)
*         11   Preparation
*         12   Making Matrix
*         13   put int Boundary Conditions   
*         14   Solving Matrix
*         15   Dividing the data
*         99   MAKE PEPORT   
*         
*  itype   0   linear problem
*          1   nonlinear problem
*
*  method  0   direct method
*          1   iterative method
*
*  idat        information data
*-------------------------------------------------
      parameter(MAX_SOLVE = 50)

      dimension itimes(MAX_SOLVE)
      dimension iter(MAX_SOLVE)
      dimension neq(MAX_SOLVE)
      dimension nwork(MAX_SOLVE)
      dimension dtime(:wq


      save itimes,iter
