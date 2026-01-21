      subroutine datinp(feel)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c Date: Wed Jul 12 20:02:55 JST 1995
c User: Hidehiro Fujio
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 2000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 100)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
      real*4 feel(*)
      character*4 word
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE)
      common /feel_oim/ietype
c --------------------------------------------------------------------
      read(io_in,9000) word
 9000 format(a4)
      if(word .ne. 'FEEL') then
        write(io_stderr,*) 'FEEL DATA ERROR'
        stop 'NOT FEEL DATA FILE'
      endif
c --------------------------------------------------------------------
      read(io_in,9001) ndim,npmax,nedat,nnodeset,numset,nip
 9001 format(6i8)
*
      read(io_in,9002) mode_ex,mode_output
 9002 format(2i8)
*
      read(io_in,9003) nvars_fem,nvars_ewise
 9003 format(2i8)
      if(ndim .ne. 1 .and. ndim .ne. 2 .and. ndim .ne.3 ) then
        stop 'ndim error'
      endif
*
      if(nedat .gt. MAX_EDATSET) then
       stop 'nedat error'
      endif
*
      if(nnodeset .gt. MAX_NODESET) then
	write(*,*) 'nnodeset =',nnodeset
        stop 'nodeset error'
      endif
*
      if(numset .gt. MAX_NUMSET) then
        stop 'numset error'
      endif
*
      do 100 i = 1,nedat
        n_edat(i,1) = 0
 100  continue
*
      do 101 i = 1,nnodeset
        n_nset(i,1) = 0
        n_nset(i,2) = 0
 101  continue
*
      do 102 i = 1,numset
        n_num(i) = 0
 102  continue
*
      if(nvars_ewise.eq.0) goto 200
      do 150 i=1,nvars_ewise
        read(io_in,9005) n_ewise(i,1),n_ewise(i,2)
 9005   format(2i8)
  150 continue
  200 continue
c --------------------------------------------------------------------
      np_x = 1
      np_y = np_x + (npmax * 2)
      np_z = np_y + (npmax * 2)
*
      if(ndim .eq. 1) np_work = np_y
      if(ndim .eq. 2) np_work = np_z
      if(ndim .eq. 3) np_work = np_z + (npmax * 2)
c --------------------------------------------------------------------
 8001 continue
*
      read(io_in,9010,end=8900) word
 9010 format(a4)
*
      if(word .eq. 'END ') goto 8010
      if(word .eq. 'NODE') then

        if(ndim .eq. 1) call dat_node1(feel(np_x))

        if(ndim .eq. 2) call dat_node2(feel(np_x),feel(np_y))

        if(ndim .eq. 3) call dat_node3(feel(np_x),feel(np_y),
     &                                 feel(np_z))

      endif
c --------------------------------------------------------------------
      if(word .eq. 'EDAT') then
        read(io_in,'(4i8)') no,nelem,np,netype
	if(no.eq.1) ietype = netype
*
        np_push = np_work
        call f_alloc(np_ielem,'EDAT READ(ielem)',nelem*np,0)
        call f_alloc(np_matno,'EDAT READ(matno)',nelem   ,0)
        n_edat(no,1) = nelem
        n_edat(no,2) = np
        call dat_edat(no,nelem,np,feel(np_ielem),feel(np_matno))
        np_work = np_push
      endif
c --------------------------------------------------------------------
      if(word .eq. 'NSET') then
        read(io_in,'(3i8)') no,nodes,np
*
        if(no .lt. 1 .or. no .gt.nnodeset) then
          write(*,*) 'nodeset no = ',no
          stop 'nodeset error'
        endif
*
        n_nset(no,1) = nodes
        n_nset(no,2) = np
        np_push = np_work
        call f_alloc(np_inset,'NSET READ(inset)',nodes*np,0)
        call dat_nodeset(no,nodes,np,feel(np_inset))
        np_work = np_push
      endif
c --------------------------------------------------------------------
      if(word .eq. 'NUM ') call dat_num
c --------------------------------------------------------------------
      if(word .eq. 'IP  ') call dat_ip
c --------------------------------------------------------------------
c --------------------------------------------------------------------
       goto 8001
c --------------------------------------------------------------------
 8900 continue
      write(io_stderr,9901)
 9901 format(' no end key word')
c --------------------------------------------------------------------
 8010 continue

*      if(mode_output .eq. 0) call inpdat_wrt(feel)
*      if(mode_output .eq. 1) call inpdat_wrt(feel)
c
      return
      end



