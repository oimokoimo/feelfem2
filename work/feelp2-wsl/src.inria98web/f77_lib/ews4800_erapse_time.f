      subroutine timeinit
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*     do nothing for ews
*      
      return
      end
*-------------------------------------------------------------------
      real*8 function erapstime()
      implicit real*8 (a-h,o-z)
      call cptime( ii )
      erapstime = dble(ii) /1000.0d0
      return
      end
