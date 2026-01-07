      subroutine get_edat(feel, no,  np_ielem,np_matno,np,nelem)
*--------------------------------------------------------------
*     feelfem P2 Program Model system subroutine
*    (for parallel version, etc)
*--------------------------------------------------------------
      real   *4  feel(*)
*
      integer*4  no
      integer*4  np_ielem,np_matno
      integer*4  np,nelem
*
      integer*4  getsciunit
*--------------------------------------------------------------
      iunitsc = getsciunit('EDAT',no)
*      
      rewind(iunitsc)
      read(iunitsc) noread
      if(noread .ne. no) call abortexit(0,'get_edat, no .ne. noread')
*
      read(iunitsc) nelem,np
*
      call f_alloc(np_ielem,'ielem(get_edat)',nelem*np,0,0)
      call f_alloc(np_matno,'matno(get_edat)',nelem   ,0,0)
*
      call readscfileIJ(iunitsc,feel(np_ielem),np,nelem)
      call readscfileI (iunitsc,feel(np_matno),nelem   )
*      
      return
      end
