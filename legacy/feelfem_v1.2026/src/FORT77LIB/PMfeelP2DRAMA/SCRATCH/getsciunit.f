      subroutine sciunitset(nedat_sv,nnset_sv)
*
      common /pfeel_scn/nedat,nnset
*
      nedat = nedat_sv
      nnset = nnset_sv
*
      return
      end 
      integer function getsciunit(word,no)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem Parallel version prototype
c     
c     MODULE GETSCIUNIT GetSCratch Unit number
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      parameter (IUNITBASE=11)
*
      character*4 word
      integer     no
*---------------------------------------------------------------------
      common /pfeel_scn/nedat,nnset
*---------------------------------------------------------------------
      if(word .EQ. 'EDAT') then
       if(no .LT. 1 .OR. no .GT. nedat) stop 'EDAT NO ERR(getsciunit)'        
       iunit = IUNITBASE+no-1
      else

       if(word .EQ. 'NSET') then
          if(no.LT.1 .OR. no.GT.nnset) stop 'NSET NO ERR(getsciunit)'        
          iunit = IUNITBASE+nedat+no-1
         else
          stop 'WORD ERR(getsciunit)'
       endif

      endif

      getsciunit = iunit
      return
      end
