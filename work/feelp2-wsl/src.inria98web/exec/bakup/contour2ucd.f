      program avs_contour
*-------------------------------------------------------------------
*  FEEL P2 System Subprogram
*-------------------------------------------------------------------
*  Purpose: contour_file¤Î¿Þ²½
*-------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
*
      parameter (MAX_FEEL = 1000000)
*
      character*25 fname
      character*80 cha
*
      real*4 feel(MAX_FEEL)
*
      open(unit=5,file='/dev/tty')
 100  continue
      write(5,*) 'INPUT FILE NAME'
      read(*,'(a)',end=997) fname
      open(unit=11,file=fname,err=999,form='unformatted',status='old')
      goto 110
*
 999  write(5,998) fname
 998  format(' cannot open ',a25)
      goto 100
 997  stop 'Terminate'
*
 110  continue
      iopen = 1
*
 1000 continue
      read(11,END=9999) npmax,neelem,nenode,ietype
      read(11) xmin,xmax,ymin,ymax
      read(11) IWD,IWW,IWH,IFLG,ITYP,IDIV,ISCL,IOUT,IMSH,UMAX,UMIN
*
      np_ielem = 1
      np_x     = np_ielem + nenode * neelem
      np_y     = np_x     + npmax  * 2
      np_u     = np_y     + npmax  * 2
      np_end   = np_u     + npmax  * 2
      if(np_end .gt. MAX_FEEL) then
         write(*,*) 'not enough heap area ',np_end - MAX_FEEL
         close(11)
         goto 100
      endif
*
      call diskrdi(11,neelem*nenode,feel(np_ielem))
      call diskrdd(11,npmax,feel(np_x))
      call diskrdd(11,npmax,feel(np_y))
      call diskrdd(11,npmax,feel(np_u))
*
*      IWD = 0
*
      write(*,*) npmax,neelem,1,0,0
      call write_pos(feel(np_x),feel(np_y),npmax)
      call write_ele(feel(np_ielem),nenode,neelem,ietype)
      call write_sca(feel(np_u),npmax)
*
      goto 1000
 9999 continue
      close(11)
      goto 100
      end
      subroutine write_pos(x,y,npmax)
      real*8 x(*),y(*)
      write(*,*)(i,x(i),y(i),0,i=1,npmax)
      return
      end
      subroutine write_ele(ie,node,ne,ID)
      dimension ie(node,ne)
      if(ID.eq.3) then
      do 100 i=1,ne
      write(*,*)i-1,' 1 tri ',ie(1,i),ie(2,i),ie(3,i)
100   continue
      else
      do 111 i=1,ne
      write(*,*)i-1,' 1 quad ',ie(1,i),ie(2,i),ie(3,i),ie(4,1)       
111   continue
      endif
      return
      end
      subroutine write_sca(u,npmax)
      real*8 u(*)
      write(*,*) 1,1
      write(*,*) 'scalar, m'
      do 100 i=1,npmax
      write(*,*) i,u(i)
100   continue
      return
      end
      

