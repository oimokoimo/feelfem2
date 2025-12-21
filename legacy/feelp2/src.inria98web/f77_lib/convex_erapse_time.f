      subroutine timeinit
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
      real * 4 tzero,CPUTIME
      common /eratime/tzero
*      
      tzero = CPUTIME( 0.0 )
      return
      end
*-------------------------------------------------------------------
      real*8 function erapstime()
      implicit real*8 (a-h,o-z)
      real *4 tzero,CPUTIME,time
      common /eratime/tzero
      time = CPUTIME( tzero )
      erapstime = dble( time )
      return
      end
