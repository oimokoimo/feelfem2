      subroutine mkexnd_outerlst(mypeid,
     $                            enptr   ,con   ,nelem,
     $                            enptr_ex,con_ex,nelem_ex,
     $                            nouter  ,ndno  ,peno     )
*------------------------------------------------------------
*  List up outer node (no duplication here)
*------------------------------------------------------------
      integer*4 enptr   (2,*),con   (2,*)
      integer*4 enptr_ex(2,*),con_ex(2,*)
      integer*4 ndno(*),peno(*)
*------------------------------------------------------------
      nouter = 0
*---------------
      do 100 i=1,nelem
         ipos_from = enptr(1,i  )
         ipos_to   = enptr(1,i+1)-1
*
         do 110 j=ipos_from,ipos_to
            if(con(2,j) .ne. mypeid) then
               call mkexnd_str(nouter,con(1,j),con(2,j),ndno,peno)
            endif
 110     continue
 100  continue
*---
* 
*---
      do 150 i=1,nelem_ex
         ipos_from = enptr_ex(1,i  )
         ipos_to   = enptr_ex(1,i+1)-1
*
         do 160 j=ipos_from,ipos_to
            if(con_ex(2,j) .ne. mypeid) then
               call mkexnd_str(nouter,con_ex(1,j),
     $                                con_ex(2,j),ndno,peno)
            endif
 160     continue
 150  continue
*---
      return
      end
      subroutine mkexnd_str(nouter,nd,pe,ndno,peno)
      integer*4 nd,pe
      integer*4 ndno(*),peno(*)
*-----------------------------------------------------
      do 100 i=1,nouter
         if(ndno(i) .EQ. nd  .AND. 
     $      peno(i) .EQ. pe         ) return
 100  continue
*
      nouter = nouter + 1
      ndno(nouter) = nd
      peno(nouter) = pe

      return
      end
