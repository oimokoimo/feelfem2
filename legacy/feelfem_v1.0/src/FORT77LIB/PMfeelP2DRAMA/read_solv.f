      subroutine read_solv(feel,medatno,nredat,nbedat,nsolvs,
     $                     np_redatlst,np_bedatlst             )
*----------------------------------------------------------------
* OUTPUT
*     integer*4   medatno   Main EDAT data number
*     integer*4   nredat    Number of region edat data sets
*     integer*4   nbedat    Number of boundary edat data sets
*     integer*4   nsolvs    Number of solve data
*  
*     integer*4   np_redatlst   List of region   EDAT data
*     integer*4   np_bedatlst   List of boundary EDAT data
*
*     ***********************************
*     WARNING:::::SOLV data not read NOW.
*     ***********************************
*
*----------------------------------------------------------------
      real   *4   feel(*)

      integer*4   nmedat,nredat,nbedat
*
      integer*4   nsolvs
*
      integer*4   np_redatlst,np_bedatlst
*
      integer*4   iunit
      character*4 word
*----------------------------------------------------------------
      iunit = 7
*
      open(unit=iunit,file='solv_dat',status='old',err=9999)
c--
      read(iunit,9000,err=9997) word
 9000 format(a4)
      if(word .ne. 'PROB') then
         write(*,*) 'solv_dat DATA ERR(KEYWORD PROB NOT FOUND)'
         goto 9998
      endif
*---
*--------------------------------------------------------------------
* MEDT
*------
      read(iunit,9000,err=9997) word
      if(word .ne. 'MEDT') then
         write(*,*) 'solv_dat DATA ERR(KEYWORD MEDT NOT IN 2ND LINE)'
         goto 9998
      endif
*---
* read Main EDAT no
*---
      read(iunit,9001,err=9997) medatno
 9001 format(i8)

*--------------------------------------------------------------------
* REDT
*------
      read(iunit,9000,err=9997) word
      if(word .ne. 'REDT') then
         write(*,*) 'solv_dat DATA ERR(KEYWORD REDT NOT IN 4TH LINE)'
         goto 9998
      endif
*---
* read number of region EDAT data sets
*---
      read(iunit,9001,err=9997) nredat
*---
      call f_alloc(np_redatlst,'REDATLST(read_solv)',nredat,0,0)
      call read_solv_i8(iunit,feel(np_redatlst),nredat)
*---------------------------------------------------------------------      

*--------------------------------------------------------------------
* BEDT
*------
      read(iunit,9000,err=9997) word
      if(word .ne. 'BEDT') then
         write(*,*) 'solv_dat DATA ERR(KEYWORD BEDT NOT FOUND)'
         goto 9998
      endif
*---
* read number of region EDAT data sets
*---
      read(iunit,9001,err=9997) nbedat
      if(nbedat .eq. 0) then
         np_bedatlst = 1
         goto 8001
      endif
*---
      call f_alloc(np_bedatlst,'BEDATLST(read_solv)',nbedat,0,0)
      call read_solv_i8(iunit,feel(np_bedatlst),nbedat)
 8001 continue
*---------------------------------------------------------------------      
      
*--------------------------------------------------------------------
* SLVS
*------
      read(iunit,9000,err=9997) word
      if(word .ne. 'SLVS') then
         write(*,*) 'solv_dat DATA ERR(KEYWORD SLVS NOT FOUND)'
         goto 9998
      endif

      read(iunit,9001,err=9997) nsolvs
      if(nsolvs .LT. 0 ) then
         write(*,*) 'ERR: reading nsolvs=',nsolvs
         goto 9998
      endif
*----------
* SOLV loop
*----------
      do 100 i=1,nsolvs
      read(iunit,9000,err=9997) word
      if(word .NE. 'SOLV') then
        *write(*,*) 'ERR: reading keyword SOLV'
	goto 9998
      endif

      read(iunit,9001,err=9997) no
         

*-----------------
      close(iunit)
      return
*--------------------------------------------------------------------
 9998 continue
      close(unit=iunit)
      goto 9997
*
 9999 write(*,*) 'ERROR: Cannot open solv_dat'
      call abortexit(-1,'READ_SOLV ERR')
*     
 9997 continue
      call abortexit(-1,'READING ERR')
*
      end
      subroutine read_solv_i8(iunit,lst,n)
      integer*4 iunit
      integer*4 lst(*)
      integer*4 n
      read(iunit,100,end=9999,err=9998)(lst(i),i=1,n)
 100  format((8i8))
      return
*
 9999 call abortexit(-1,'End of File in read_solv_i8')
 9998 call abortexit(-1,'ERROR in read_solv_i8')
      end
