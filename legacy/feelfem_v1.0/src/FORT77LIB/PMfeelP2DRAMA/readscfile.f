      subroutine readscfileIJ(iunitsc,idat,ni,nj)
      dimension idat(ni,nj)
      read(iunitsc) ((idat(i,j),i=1,ni),j=1,nj)
      return
      end
      subroutine readscfileI (iunitsc,idat,ni)
      dimension idat(ni)
      read(iunitsc) (idat(i),i=1,ni)
      return
      end

