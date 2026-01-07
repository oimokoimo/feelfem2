      subroutine dat_nodeset(no,nodes,np,inset)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 10000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 10)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 5)
      parameter (MAX_SOLVE = 1)
c --------------------------------------------------------------------
*
      dimension inset(np,nodes)
      character fmt*10
c --------------------------------------------------------------------
c --------------------------------------------------------------------
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_ctl/mode_ex,mode_output,max_heap
      common /feel_var/np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &                 n_nset(MAX_NODESET,2),n_num(MAX_NUMSET),
     &                 n_ewise(MAX_EWISE,2),n_nodeno(MAX_IP)
      common /feel_sol/n_sstat(MAX_SOLVE),n_smaxp(MAX_SOLVE)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
c----------------------------
c  no     nodeset number
c  nodes  number of nodes
c  np     data par each node
c----------------------------
      if(no .gt. MAX_NODESET .or. no .lt. 1) then
        write(io_stderr,*) 'node set No. ERROR ',no
        stop 'nodeset read routine'
      endif
c --------------------------------------------------------------------
      write(fmt,90) np
  90  format('(',I2,'I8)')
*
      do 100 i=1,nodes
        read(io_in,fmt) (inset(j,i),j=1,np)
 100  continue
*
      iunit = io_node + no - 1
      open(unit=iunit,status='scratch',form='unformatted')
      call closefil(iunit)
*
      write(iunit) nodes,np
      write(iunit) ((inset(j,i),j=1,np),i=1,nodes)
*
      return
c --------------------------------------------------------------------
      end
