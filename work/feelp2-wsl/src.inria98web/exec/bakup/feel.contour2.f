      program show_contour
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
      character*25 cha
*
      real*4 feel(MAX_FEEL)
*------------------------------------------------------------
      IWD = 0
      write(*,*) 'INPUT WINDOW SIZE'
      read(*,*) IWINSIZ
*
 100  continue
      write(*,*) 'INPUT FILE NAME'
      read(*,'(a)') fname
      open(unit=11,file=fname,err=999,form='unformatted',status='old')
      goto 110
*
 999  write(*,998) fname
 998  format(' cannot open ',a25)
      goto 100
*
 110  continue
      iopen = 1
*
 1000 continue
      read(11,END=9999) npmax,neelem,nenode,ietype
      read(11) xmin,xmax,ymin,ymax
      read(11) IWD,IWW,IWH,IFLG,ITYP,IDIV,ISCL,IOUT,IMSH,UMAX,UMIN
*
      write(*,*) 'INPUT UMAX'
      read(*,*) UMAX
      write(*,*) 'INPUT UMIN'
      read(*,*) UMIN
      write(*,*) 'INPUT IDIV'
      read(*,*) IDIV
      write(*,*) 'INPUT IOUT'
      read(*,*) IOUT
      write(*,*) 'INPUT GRAY'
      read(*,*) IGRY
      write(*,*) 'INPUT IMSH'
      read(*,*) IMSH
      IWD  = 0
      IWW  = IWINSIZ
      IWH  = IWINSIZ
      IFLG = 3

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
* Window Position
*      IWX = 0
*      IWY = 0
*
* Window Size
*      IWW = 600
*      IWH = 600
*
* Para FLAG 0:automatic 1:disp. range 2:value range 3:manual
*      IFLG = 0
*
* Contour TYPE   0:normal  1:ln
*      ITYP = 0
*
* Contour lines 
*      IDIV = 20
*
* show scale 0 now show  1 show
*      ISCL = 0
* graph type     0:paint   1:line only
*      IOUT = 0
*
* Mesh draw flag 0:no mesh line  1:draw mesh line
*      IMSH = 1
*
      if(iopen.eq.1) then
      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX,IGRY)
      iopen = 0
      endif
*
      call FEEL_CONTOUR(npmax,neelem,feel(np_x),feel(np_y),feel(np_u),
     $     feel(np_ielem),nenode,IWX,IWY,IWW,IWH,IWD,IFLG,
     $     XMIN,XMAX,YMIN,YMAX,UMIN,UMAX,
     $     ietype,ITYP,IOUT,IMSH,IDIV,ISCL)
*
      write(*,*) 'push RETURN to continue'
      read(*,'(a)') cha
      goto 1000
 9999 continue
      close(11)
      goto 100
      end


      
