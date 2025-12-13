      integer*4 function inbctr2search(no,inbctr2,nbedat)
*---------------------------------------------------------------
* Search index number in inbctr2 array for EDAT Number 'no'.
*
* inbctr2(1,*) : EDAT number
*---------------------------------------------------------------
      integer*4 no
      integer*4 inbctr2(5,nbedat)
*---------------------------------------------------------------
      if(nbedat .LT. 1) then
         call abortexit(999,'No Neumann EDAT data(search inbctr2)')
      endif
*
      do 100 i=1,nbedat
         if(inbctr2(1,i) .EQ. no) then
            inbctr2search = i
            return
         endif
 100  continue
*---
      call abortexit(999,'Cannot find B-EDAT set(search inbctr2)')
*
      end



