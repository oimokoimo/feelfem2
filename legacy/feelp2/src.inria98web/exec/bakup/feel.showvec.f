      program show_vector
*
*   FEEL P2 System Utility Program
*
      implicit real*8 (a-h,o-z)
      parameter (MAX_FEEL = 1000000)
      character*50 fname
      real*4 feel(MAX_FEEL)
*
      IWD = 0
*
 100  continue
      write(*,*) 'INPUT FILE NAME'
      read(*,'(a)') fname
      open(unit=11,file=fname,err=999,form='unformatted',status='old')
      goto 110
*
 999  write(*,998) fname
 998  format(' cannot open ',a50)
      goto 100
*
 110  continue
      iopen = 1
*
 1000 continue
      read(11,END=9999) npmax,neelem,nenode
      read(11) IWX,IWY,IWW,IWH,IWD,IGRY
      read(11) XMIN,XMAX,YMIN,YMAX,VMAX
      read(11) ID,ITYPE,IFLG,IOUT,IMSH
      read(11) VM
	
*
      np_ielem = 1
      np_x     = np_ielem + nenode * neelem
      np_y     = np_x     + npmax  * 2
      np_u     = np_y     + npmax  * 2
      np_v     = np_u     + npmax  * 2
      np_wk    = np_v     + npmax  * 2
      np_iwk   = np_wk    + npmax  * 2 * 9
      np_end   = np_iwk   + neelem * 2

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
      call diskrdd(11,npmax,feel(np_v))
*
* Window ID      IWD 
* ID (triangle or rectangle)      ID = 4,3
* Window Positio      (IWX,IWY)
* Window Size         (IWW,IWH)
* Para IFLG (NO INFLUENCE?)          IFLG = 1
* ALLOW TYPE   0:paint 1:line only1  IOUT = 0
* VM vector factor                     VM = 1.000000
* Mesh draw flag 0:no mesh line  1:draw mesh line      IMSH = 1
* Gray scale 0=color 1=gray      IGRY = 0
* ITYPE      1 = each node, 0 = each element      ITYPE = 1
*      IWD = 0
      call FEEL_XINIT(IWX,IWY,IWW,IWH,IWD,XMIN,XMAX,YMIN,YMAX,IGRY)
*
      call FEEL_VECTOR(feel(np_u),feel(np_v),npmax,neelem,
     $     feel(np_x),feel(np_y),feel(np_ielem),nenode,ID,I
     $TYPE,IWX,IWY,IWW,IWH,IWD,IFLG,XMIN,XMAX,YMIN,YMAX,VMAX,
     $VM,IOUT,IMSH,feel(np_WK),feel(np_IWK))
*
      write(*,*) 'click window to continue'
      call vewt(IWD)
      goto 1000
 9999 continue
      close(11)
      goto 100
      end
