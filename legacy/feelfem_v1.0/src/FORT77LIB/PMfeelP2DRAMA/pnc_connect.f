      subroutine pnc_connect(mypeid, nc, npmax, 
     $            enptr,   con,   nelem,
     $            enptr_ex,con_ex,nelem_ex,
     $            ncmax                     )
*--------------------------------------------------------------
* 2000/05/30  (feelfem_stokes version)
*
* Count the maximum number of connecting elements
*
* DRAMA double index version
*--------------------------------------------------------------
      integer*4 nc(*)
      integer*4 enptr   (2,*),con   (2,*)
      integer*4 enptr_ex(2,*),con_ex(2,*)
*--------------------------------------------------------------
      do 100 i=1,npmax
         nc(i) = 0
 100  continue
*---------------------
* Count the connecting elements
* PART1: for my PE's elements
*---------------------
      do 200 i=1,nelem
         ipos_from = enptr(1,i  )
         ipos_to   = enptr(1,i+1)-1
*
         do 210 j=ipos_from,ipos_to
            if(con(2,j) .ne. mypeid) goto 210
            nc(con(1,j)) = nc(con(1,j)) + 1

 210     continue
 200  continue
*-------------
* PART 2: For other PE's elements
*-------------
      do 250 i=1,nelem_ex
         ipos_from = enptr_ex(1,i  )
         ipos_to   = enptr_ex(1,i+1)-1
*
         do 260 j=ipos_from,ipos_to
            if(con_ex(2,j) .ne. mypeid) goto 260
            nc(con_ex(1,j)) = nc(con_ex(1,j)) + 1
 260     continue
 250  continue
*-------------

*-------------------
* Search the maximum
*-------------------
      ncmax = nc(1)
      do 300 i=2,npmax
         if(ncmax .lt. nc(i)) then
            ncmax = nc(i)
         endif
 300  continue
*-------------
      return
      end

