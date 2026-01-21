      subroutine f_alloc(nptr , cha, n , itype)
*
      implicit real*8 (a-h,o-z)
*
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine f_alloc
*-------------------------------------------------------------------
*  Purpose:  Allocate memory
*-------------------------------------------------------------------
      character cha*(*)
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 2000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
c --------------------------------------------------------------------
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,nvars_ewise,
     &                 np_fem,np_ewise,np_heap
      common /feel_ctl/mode_ex,mode_output,max_heap
*
      common /feel_geo/ndim,npmax,ndomain,nedat,nnodeset,nnumdat,nip
      common /feel_fil/io_in,io_tmp,io_out,io_stderr,
     &                 io_edat,io_node,io_num,io_fem
      common /feel_dat/n_edat(MAX_EDATSET,3),
     &     n_nset(MAX_NODESET,2),
     &     n_ewise(MAX_EWISE,2)
c --------------------------------------------------------------------
*
      nn = 0
      if(itype .eq. 1) then
        if((np_work / 2) * 2 .eq. np_work) np_work = np_work+1
	nn = n * 2
      endif
      if(itype .eq. 0) then
	nn = n
      endif

      if(nn .eq. 0) then
	write(*,*) 'in allocate ',cha
	write(*,*) 'n = ',n,' itype = ',itype
	stop 'f_alloc itype error'
      endif
  
      np = np_work + nn
*--------ここもとりあえず削除
      if(np . gt . np_heap) then
        write(io_stderr,*) 'Cannot allocate array for ',cha 
        write(io_stderr,*) 'No space for ',np-np_heap ,' word'
        stop 'feel: memory allocation'
      endif
*--------ここもとりあえず削除
      nptr    = np_work
      np_work = np
      if(np_work.gt.max_heap) max_heap = np_work
      return
      end
