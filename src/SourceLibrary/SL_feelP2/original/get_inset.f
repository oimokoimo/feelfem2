      subroutine get_inset(iunit,inset,nodes,np)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: read insetrm  array
*  
*  Caution:
*
*-------------------------------------------------------------------
      dimension inset(np,nodes)
*
      rewind(iunit)
*
      read(iunit) n1,n2
*
      if(n1 .ne. nodes .or. n2 .ne. np) stop 'get_inset mismatch'
*
      read(iunit) ((inset(i,j),i=1,np),j=1,nodes)
*
      return
      end

