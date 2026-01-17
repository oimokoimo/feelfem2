      subroutine mkloccoor(myrank,nprocs,
     $                     x,y,loc  ,npmax,
     $                     xloc,yloc,mynode )
*--------------------------------------------------------
*     Make local coordinate
*--------------------------------------------------------
*-------
* INPUT
*-------
*      x(npmax),y(npmax)  global coordinate
*      LOC(2,npmax)    Node information in Global Node number
*           loc(1,*)    PE id
*           loc(2,*)    Local node number
*-------
* OUTPUT
*-------
*     xloc(mynode),yloc(mynode)
*--------------------------------------------------------
      integer*4 myrank,nprocs
      real*8    x(*),y(*)
      integer*4 loc(2,npmax)

*-OUT-
      real*8 xloc(*),yloc(*)
*--------------------------------------------------------
      mypeid = myrank
*--------------------------------------------------------
* XLOC/YLOC/(ZLOC)
*-----------------
      iptr = 0
      do 100 i=1,npmax
         if(loc(1,i) .eq. mypeid) then
            iptr = iptr + 1
            xloc(iptr) = x(i)
            yloc(iptr) = y(i)
            if(iptr .ne. loc(2,i)) then
               call abortexit(myrank,'Contradiction/mkmainlocdat')
            endif
         endif
 100  continue
*-----------------
      if(mynode .ne. iptr) then
         call abortexit(myrank,'Error in mkloccoor/02-May-00')
      endif
*--------------------------------------------------------
      return
      end

