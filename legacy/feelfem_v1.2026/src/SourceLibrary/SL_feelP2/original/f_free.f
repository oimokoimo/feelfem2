      subroutine f_free(cha , n , itype)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine f_free
*-------------------------------------------------------------------
*  Purpose: free allocated memory
*-------------------------------------------------------------------
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
c --------------------------------------------------------------------
*
      write(*,*) 'changement 2001/01/27 f_alloc modify'
      write(*,*) 'f_free is not used, I suppose.'
      stop 'f_free'
*
      nn = 0
      if(itype.eq. 0) then
	nn = n
      endif
      if(itype .eq. 1) then
	nn = n * 2
      endif
      if(nn.eq.0) then
	write(io_stderr,*) 'f_free: itype error'
	stop 'f_free'
      endif

      np_work = np_work - nn
      if(np_work .lt. 1) then
	write(io_stderr,*) 'f_free <1 error for ',cha
	stop 'f_free'
      endif
      return
      end

