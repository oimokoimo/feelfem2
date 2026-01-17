      subroutine get_edat_lst(feel,nedats,nolst,icntr)
*-------------------------------------------------------------------
*  Read and store ielem/matno list
*-------------------------------------------------------------------
*  INPUT
*     nedat        Number of edat sets
*     nolst(nedat) EDAT no data list
* 
*  OUTPUT
*     icntr(1,*)   EDAT no
*     icntr(2,*)   np
*     icntr(3,*)   nelem
*     icntr(4,*)   np_ielem
*     icntr(5,*)   np_matno
*     
*-------------------------------------------------------------------      
      real   *4 feel(*)
      integer*4 nedats
      integer*4 nolst(*)
      integer*4 icntr(5,*)
*-------------------------------------------------------------------      
      do 100 i=1,nedats
         call get_edat(feel, nolst(i),np_ielem,np_matno,np,nelem)
*
         icntr(1,i) = nolst(i)
         icntr(2,i) = np
         icntr(3,i) = nelem
         icntr(4,i) = np_ielem
         icntr(5,i) = np_matno
*
 100  continue
*-------------------------------------------------------------------      
      return
      end


