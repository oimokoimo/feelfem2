      subroutine divideshow(x,y,npmax,ielem,matno,npart,
     $                      np,nelem,ietype,nparts       )
*
      implicit real*8 (a-h,o-z)
      parameter (MAX_SUB=512)
      dimension x(npmax),y(npmax)
      dimension ielem(np,nelem)
      dimension matno(nelem)
      dimension npart(nelem)
*
      dimension dx(4),dy(4)
      dimension xd(MAX_SUB),yd(MAX_SUB),ipts(MAX_SUB)
*
      do 1 i=1,MAX_SUB
         xd(i)=0.0d0
         yd(i)=0.0d0
         ipts(i)=0
 1    continue
*
      xmin = x(1)
      xmax = x(1)
      ymin = y(1)
      ymax = y(1)

*
      do 100 i=1,npmax
         if(xmin .gt. x(i)) xmin = x(i)
         if(ymin .gt. y(i)) ymin = y(i)
         if(xmax .lt. x(i)) xmax = x(i)
         if(ymax .lt. y(i)) ymax = y(i)
 100  continue
*
      xlen = xmax-xmin
      ylen = ymax-ymin
*
      call openpl

      call fspace(xmin-xlen/20.0d0,ymin-ylen/20.d0,
     $            xmax+xlen/20.0d0,ymax+ylen/20.d0  )
*----------------------------------------------------------
      do 200 i=1,nelem

         do 210 j=1,ietype
	    dx(j)=x(ielem(j,i))
	    dy(j)=y(ielem(j,i))
 210     continue

	 call xcolorlist(npart(i)+1)
         call fpolygon(ietype,dx,dy) 

 200  continue

*-----------------------------------------------------------
      call xcolorlist(0)
*
      ippmax = 1
      do 300 i=1,nelem

         ipp   = npart(i)+1
         if(ippmax .LT. ipp) then
            ippmax = ipp
            if(ippmax .GT. MAX_SUB) then
               stop 'TOO MANY SUBDOMAIN(divideshow)'
            endif
         endif
         

         xlast = x(ielem(ietype,i))
         ylast = y(ielem(ietype,i))
         
         xsum  = 0.0d0
         ysum  = 0.0d0

         do 310 j=1,ietype
            xx = x(ielem(j,i))
            yy = y(ielem(j,i))
            xsum = xsum + xx
            ysum = ysum + yy

            if(npmax.LT.1000) then
            call fline(xlast,ylast,xx,yy)
	    endif

            xlast = xx
            ylast = yy
        
	    dx(j)=x(ielem(j,i))
	    dy(j)=y(ielem(j,i))
 310     continue

         xc = xsum / dble(ietype)
         yc = ysum / dble(ietype)
         
         xd(ipp)  = xd(ipp)+xc
         yd(ipp)  = yd(ipp)+yc
         ipts(ipp)= ipts(ipp)+1



 300  continue

      do 350 i=1,ippmax
         xc = xd(i)/dble(ipts(i))
         yc = yd(i)/dble(ipts(i))
         call fnumber(xc,yc,i)
 350  continue

      if(npmax.ge.1000) write(*,*) 'mesh is not drawin over 1000 nodes'

      call xwait

      return
      end
