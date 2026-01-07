      subroutine get_nset(feel, no, np_inset, np, nodes)
*--------------------------------------------------------------
*     Get NSET data from file
*    (for parallel version, etc)
*--------------------------------------------------------------
      real*4  feel(*)
      integer getsciunit
*--------------------------------------------------------------
      iunitsc = getsciunit('NSET',no)
*
      rewind(iunitsc)
      read(iunitsc) noread
      if(noread .ne. no) call abortexit(0,'get_nset, no .ne. noread')

      read(iunitsc) nodes,np

      call f_alloc(np_inset,'inset(get_nset)',nodes*np,0,0)

      call readscfileIJ(iunitsc,feel(np_inset),np,nodes)

      return
      end
