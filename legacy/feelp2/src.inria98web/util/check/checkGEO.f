      program checkGEO
      implicit real*8 (a-h,o-z)
      dimension px(100),py(100)
      dimension np(10,100)
      dimension nps(10)
      character ncha*3

      read(*,*) iregions,iana
      if(iregions .gt. 10) stop 'too many regions'

      read(*,*) (nps(i),i=1,iregions)

      read(*,*) num
      
      do 100 i=1,iregions
         read(*,*) (np(i,j),j=1,nps(i))
 100  continue

      read(*,*) npp,nx

      do 200 i=1,npp
         read(*,*) px(i),py(i)
 200  continue

      xmin = px(1)
      xmax = px(1)
      ymin = py(1)
      ymax = py(1)
      do 300 i=2,npp
         if(xmin .gt. px(i)) xmin = px(i)
         if(xmax .lt. px(i)) xmax = px(i)

         if(ymin .gt. py(i)) ymin = py(i)
         if(ymax .lt. py(i)) ymax = py(i)
 300  continue

      xmin = xmin - (xmax-xmin)/20.0
      xmax = xmax + (xmax-xmin)/20.0

      ymin = ymin - (ymax-ymin)/20.0
      ymax = ymax + (ymax-ymin)/20.0

      call openpl
      call fspace(xmin,ymin,xmax,ymax)
      
      do 400 i=1,iregions
         call fmove(px(np(i,nps(i))),py(np(i,nps(i))))
         do 500 j=1,nps(i)
            call fcont(px(np(i,j)),py(np(i,j)))
            call fpeke(px(np(i,j)),py(np(i,j)))
            write(ncha,'(I3)') np(i,j)
            call fsymbol(px(np(i,j)),py(np(i,j)),ncha)
 500     continue
 400  continue

      call closepl
      stop
      end
