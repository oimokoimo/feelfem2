      program showmesh
      parameter (MAXP=10000)
      implicit real*8 (a-h,o-z)
      dimension px(MAXP),py(MAXP)
      dimension ielem(4)
      open(unit=8,file='mesh.dat')
      read(8,'(i5)') max
      if(max .gt. maxp) then
         write(*,*) 'too many points',max
         stop
      endif
c
      do 100 i=1,max
         read(8,'(2e15.7)') px(i),py(i)
 100  continue
c
      xmin = px(1)
      xmax = px(1)
      ymin = py(1)
      ymax = py(1)
c
      do 1000 i=2,max
         if(xmin .gt. px(i)) xmin = px(i)
         if(ymin .gt. py(i)) ymin = py(i)
         if(xmax .lt. px(i)) xmax = px(i)
         if(ymax .lt. py(i)) ymax = py(i)
 1000 continue
c
      dx = (xmax - xmin) /20.0d0
      dy = (ymax - ymin) /20.0d0
c
      call openpl
      call fspace(xmin-dx,ymin-dy,xmax+dx,ymax+dy)
c
      read(8,'(I5)') num_reg
c
      do 2000 I=1,num_reg
c
         read(8,'(i5)') num_elem
         read(8,'(i5)') node_elem
c
         do 3000 J=1,num_elem
            read(8,'(4i5)') (ielem(k),k=1,node_elem)
            call fmove(px(ielem(node_elem)),py(ielem(node_elem)))
            do 4000 K=1,node_elem
               call fcont(px(ielem(K)),py(ielem(K)))
 4000       continue
 3000    continue
 2000 continue
c
      call closepl
      stop
      end
