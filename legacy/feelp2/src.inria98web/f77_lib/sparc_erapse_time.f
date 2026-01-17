      subroutine timeinit
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*     do nothing for SUN
*      
      return
      end
*-------------------------------------------------------------------
      real*8 function erapstime()
      implicit real*8 (a-h,o-z)
      real time1,time2,tr(2)
      time1 =  etime( tr )
      erapstime = time1/1000.0
      return
      end
