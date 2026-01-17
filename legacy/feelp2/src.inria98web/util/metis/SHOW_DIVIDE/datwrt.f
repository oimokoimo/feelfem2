      subroutine datwrt(feel)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feel p2 fort77 program
c     Copyright(C) NEC Corporation 1993
c ======================================
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
c --------------------------------------------------------------------
c     EDAT  for the first only
c --------------------------------------------------------------------
      i = 1
	no    = i
	nelem = n_edat(no,1)
	np    = n_edat(no,2)

        np_push = np_work
        call f_alloc(np_ielem,'EDAT WRITE(ielem)',nelem*np,0)
        call f_alloc(np_matno,'EDAT WRITE(matno)',nelem   ,0)
        iunit = i + io_edat - 1
        call get_ielem(iunit,feel(np_ielem),feel(np_matno),
     $                 nelem,np)

* Allocate mesh partition information array        
        call f_alloc(np_npart,'EDAT PARTITION(npart)',nelem,0)
	call ReadMetisBamg(feel(np_npart),nelem,nparts)

        call f_alloc(np_metis2f,'METIS TO FEEL',nelem,0)
	call MetisOrdering(feel(np_metis2f),feel(np_npart),nelem)

        call divideshow(feel(np_x),feel(np_y),npmax,
     $                  feel(np_ielem),feel(np_matno),feel(np_metis2f),
     $                  np,nelem,ietype,nparts) 
        
      np_work=np_push
      return
      end
