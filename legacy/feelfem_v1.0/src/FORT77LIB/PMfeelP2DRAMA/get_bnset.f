      subroutine get_bnset(feel,nnset,idbctr)
*---------------------------------------------------------------------
* dimension idbctr(4,nbedat)
*
*           idbctr(1,*)  NSET number (This is 1 to nnset)
*           idbctr(2,*)  NSET np
*           idbctr(3,*)  NSET nodes
*           idbctr(4,*)  NSET NP_ pointer for inset
* ---
*---------------------------------------------------------------------
      parameter (NUR_OIMO = 0)
*
      real*4 feel(*)
      dimension idbctr(4,nnset)
*---------------------------------------------------------------------
      do 100 i=1,nnset
         idbctr(1,i) = i + NUR_OIMO
*
         call get_nset(feel, idbctr(1,i),
     $                       idbctr(4,i),
     $                       idbctr(2,i),idbctr(3,i))
 100  continue
*
      return
      end
