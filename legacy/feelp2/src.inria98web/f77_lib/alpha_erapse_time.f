      subroutine timeinit
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
      real * 4 tzero,SECNDS
      common /eratime/tzero
*      
      tzero = SECNDS( 0.0 )
      return
      end
*-------------------------------------------------------------------
      real*8 function erapstime()
      implicit real*8 (a-h,o-z)
      real *4 tzero,SECNDS,time
      common /eratime/tzero
      time = SECNDS( tzero )
      erapstime = dble( time )
      return
      end
