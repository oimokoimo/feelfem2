      subroutine get_ielem(iunit,ielem,matno,neelem,nenode)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: read ielem,matno array
*  
*  Caution:
*
*-------------------------------------------------------------------
      dimension ielem(nenode,neelem)
      dimension matno(neelem)
*
      rewind(iunit)
*
      read(iunit) ne,np
*
      if(ne .ne. neelem .or. np.ne. nenode) stop 'get_ielem mismatch'
*
      read(iunit) ((ielem(i,j),i=1,nenode),j=1,neelem)
      read(iunit) (matno(i),i=1,neelem)
*
      return
      end

