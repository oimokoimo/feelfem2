      subroutine read_node(iunit,ndim,x,y,z,nverdate)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem P2DRAMA System subroutine
c     
c     MODULE READ_NODE reading NODE data
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      integer*4 iunit,ndim
      real*8    x(*),y(*),z(*)
      integer*4 nverdate
c --------------------------------------------------------------------
      if(nverdate .NE. 20000412) call abortexit(0,'read_node version')
*
      if(ndim .EQ. 1) then
 8001    read(iunit,9001,end=8900) inp,xx
 9001    format(i8,1PE12.5)
         if(inp .eq. 0) return
         x(inp) = xx
         goto 8001
      endif
c --------------------------------------------------------------------
      if(ndim .EQ. 2) then
 8201    read(iunit,9201,end=8900) inp,xx,yy
 9201    format(i8,1PE12.5,1PE12.5)
         if(inp .eq. 0) return
         x(inp) = xx
         y(inp) = yy
         goto 8201
      endif
c --------------------------------------------------------------------
      if(ndim .EQ. 3) then
 8301    read(iunit,9301,end=8900) inp,xx,yy,zz
 9301    format(i8,1PE12.5,1PE12.5,1PE12.5)
         if(inp .eq. 0) return
         x(inp) = xx
         y(inp) = yy
         z(inp) = zz
         goto 8301
      endif
c --------------------------------------------------------------------
 8900 write(*,*) 'NODE DATA ERROR'
      call abortexit(0,'read_node error')
      end
