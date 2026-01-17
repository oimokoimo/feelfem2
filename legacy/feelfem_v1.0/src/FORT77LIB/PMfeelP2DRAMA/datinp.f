      subroutine datinp(feel,ndim,npmax,nemax,nedat,nnset,nnum,nip,
     $                  np_x,np_y,np_z,np_ip,nvars_fem,nvars_ewise,
     $                  netype,nverdate)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem/P2DRAMA program model system subroutine
c     Copyright NEC Corporation 2000    
c     
c     2000/04/12 Programmed by Hidehiro FUJIO    
c     2000/05/05 Modified (getsciunit is added in this file)
c     
c     MODULE DATINP routine  (feel_dat reader program)
c
c     UNIT NUMBER 7 used
c
c     EXTERNAL ROUTINE  abortexit,
c
c     DATA FILE:
c       feel_dat     P2 program model FEM input file
c
c     INPUT
c       real   *4    feel(*)   memory allocation array
c
c     OUTPUT
c       integer*4    nemax     the number of region elements
c                              (not boundary elements for boundary conditions)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c R.1 In this version, the memory for reading is freed except node
c     cordinates and ip information.
c
c R.2 nemax is set in EDAT reading section of this subroutine
c
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      real   *4   feel(*)

      integer*4   myrank

      integer*4   ndim,npmax,nemax,nedat,nnset,nnum,nip
      integer*4   np_x,np_y,np_z,np_ip
      integer*4   nvars_fem,nvars_ewise
      integer*4   nverdate

      integer  *4 iunit
      character*4 word
      integer  *4 nelem

c --------------------------------------------------------------------
      if(nverdate .NE. 20000412) then
         call abortexit(0,'datinp version mismatch')
      endif
c --------------------------------------------------------------------
      nemax  = 0
*
      iunit  = 7
      OPEN(unit=iunit,file='feel_dat',status='OLD',err=9999)
c---------------------------
c Read first keyword 'FEEL'
c---------------------------
      read(iunit,9000) word
 9000 format(a4)
      if(word .ne. 'FEEL') then
        write(*,*) 'FEEL DATA ERROR(KEYWORD FEEL NOT FOUND)'
        goto 9998
      endif

c---------------------------
c Read fundamental parameter
c---------------------------
      read(iunit,9001) ndim,npmax,nedat,nnset,nnum,nip
 9001 format(6i8)
*
      call setsciunit(nedat,nnset)
*
      read(iunit,9002) mode_ex,mode_output
 9002 format(2i8)
*
      read(iunit,9003) nvars_fem,nvars_ewise
 9003 format(2i8)
*
      if(ndim .ne. 1 .and. ndim .ne. 2 .and. ndim .ne.3 ) then
         write(*,*) 'ndim data error  ndim=',ndim
         goto 9998
      endif
*--------------------------------------------------------------------
      if(nvars_ewise.eq.0) goto 200
      do 150 i=1,nvars_ewise
        read(iunit,9005) n_ewise_dom_no,n_ewise_pts_par_element
 9005   format(2i8)
  150 continue
  200 continue
c --------------------------------------------------------------------
* Memory allocation here
*------------------------
      np_x = 1
      np_y = 1
      np_z = 1
*
      call f_alloc(np_x,'(x in datinp)',npmax,1,0)
      if(ndim .gt. 1) call f_alloc(np_y,'(y in datinp)',npmax,1,0)
      if(ndim .eq. 3) call f_alloc(np_z,'(z in datinp)',npmax,1,0)
*
      if(nip .NE. 0) then
         call f_alloc(np_ip,'(ip in datinp)',nip,0,0)
      endif
c --------------------------------------------------------------------
 8001 continue
*
      read(iunit,9010,end=8900) word
 9010 format(a4)
*
      if(word .eq. 'END ') goto 8010
      if(word .eq. 'NODE') then

       call read_node(iunit,ndim,feel(np_x),feel(np_y),feel(np_z),
     $                20000412)

      endif
c --------------------------------------------------------------------
      if(word .eq. 'EDAT') then
        read(iunit,'(4i8)') no,nelem,np,netype
*
        if(nemax .LT. nelem) nemax = nelem
*
        call f_alloc_push

        call f_alloc(np_ielem,'EDAT READ(ielem)',nelem*np,0,0)
        call f_alloc(np_matno,'EDAT READ(matno)',nelem   ,0,0)

        call read_edat(iunit,no,nelem,np,feel(np_ielem),feel(np_matno),
     $                 20000412)        

        call f_alloc_pop

      endif
c --------------------------------------------------------------------
      if(word .eq. 'NSET') then
        read(iunit,'(3i8)') no,nodes,np
*
        call f_alloc_push

        call f_alloc(np_inset,'NSET READ(inset)',nodes*np,0,0)
        call read_nset(iunit,no,nodes,np,feel(np_inset),
     $                 20000412)

        call f_alloc_pop

      endif
c --------------------------------------------------------------------
      if(word .eq. 'NUM ') call abortexit(0,'future function NUM')
c --------------------------------------------------------------------
      if(word .eq. 'IP  ') call read_ip(iunit,feel(np_ip),nip,
     $                                  20000412)
c --------------------------------------------------------------------
       goto 8001
c --------------------------------------------------------------------
 8900 continue
      write(io_stderr,9901)
 9901 format(' no end key word')
c --------------------------------------------------------------------
 8010 continue
c
*      if(mode_output .eq. 0) call inpdat_wrt
*      if(mode_output .eq. 1) call inpdat_wrt
c
      close(unit=iunit)
      return
c --------------------------------------------------------------------
 9998 continue
      close(unit=iunit)
      goto 9997
 9999 write(*,*) 'ERROR:(PE0) Cannot open feel_dat'
      call abortexit(myrank,'Cannot open feel_dat')
 9997 continue
*
      call abortexit(0,'DATINP ERROR')
*
      return
*
      end
      subroutine setsciunit(nedat_sv,nnset_sv)
*
      common /pfeel_scn/nedat,nnset
*
      nedat = nedat_sv
      nnset = nnset_sv
*
      return
      end 
      integer function getsciunit(word,no)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem Parallel version prototype
c     
c     MODULE GETSCIUNIT GetSCratch Unit number
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      parameter (IUNITBASE=11)
*
      character*4 word
      integer     no
*---------------------------------------------------------------------
      common /pfeel_scn/nedat,nnset
*---------------------------------------------------------------------
      if(word .EQ. 'EDAT') then
       if(no .LT. 1 .OR. no .GT. nedat) then
         write(*,*) 'ERR REPORT:  EDATno=',no
         call abortexit(-1,'EDAT no error in getsciunit')
       endif

       iunit = IUNITBASE+no-1
      else

       if(word .EQ. 'NSET') then
          if(no.LT.1 .OR. no.GT.nnset) then
            write(*,*) 'ERR REPORT: NSET no=',no
            call abortexit(-1,'NSET no error in getsciunit')
	  endif

          iunit = IUNITBASE+nedat+no-1
         else
          stop 'WORD ERR(getsciunit)'
       endif

      endif

      getsciunit = iunit
      return
      end
