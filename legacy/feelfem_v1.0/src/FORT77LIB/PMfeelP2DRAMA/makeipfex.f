      subroutine makeipfex(mypeid,nenfre,MAX_ELEMENT_FREEDOM,NEG,
     $                          enptr,con,nelem,npmax,ipf)
*-------------------------------------------------------------
*   2000/05/30  (Not problem dependent version feelfem_stoes version)
*
*   Make freedom array for each node  
*
*   Parallel version with the DRAMA double index
*
*   ndfmax : Maximum degree of freedom in one element
*
*
*   This subroutine depends on each problem(especially the second
*   element of con array)
*
*
*
*   LIMITATION:  It is not took into account that new degree of
*                freedom supplied from other PE's element.
*              |
*     .--------.-------.----
*     |        |       |
*     |   PE0  |  PE1  |
*     |        |       |
*     .--------x-------.----
*        Node x belongs to PE0, but new degree of freedom 
*        given from PE1 controlled element.
*--------------------------------------------------------------      
      integer con(2,*),enptr(2,*)
      integer ipf(*)
*--------------------------------------------------------------
      dimension nenfre(MAX_ELEMENT_FREEDOM,NEG)
*--------------------------------------------------------------
* Initialization
*---------------
      do 100 i=1,npmax
         ipf(i) = 0
 100  continue
*--------------------------------------------------------------
      do 200 i=1,nelem
         ipos_from = enptr(1,i  )
         ipos_to   = enptr(1,i+1)-1

         ietype    = enptr(2,i) 

         if(ietype .ge. 1 .and.  ietype .le. NEG) then
            do 201 j=ipos_from,ipos_to
               iptr = j-ipos_from+1
               if(con(2,j) .ne. mypeid) goto 201
               ipf(con(1,j)) = nenfre(iptr,ietype)
 201        continue
            goto 299
         endif
*
         call abortexit(mypeid,'No corresponding nenfre(makeipfex)')
*
 299     continue
*---

 200  continue
*--------------------------------------------------------------------
      return
      end

