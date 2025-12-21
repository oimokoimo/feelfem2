      subroutine mk_subdomain_nset(feel,ieg,neg,mats,matnos)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: show input data
*  
*  Caution:
*
*-------------------------------------------------------------------
      real*4    feel(*)
      dimension matnos(*)
*--------------------------------------------------------------------
#COMMON
*--------------------------------------------------------------------
*      np_push = np_work
      call f_alloc_push
*--------------------------------------------------------
      if(neg .gt. MAX_NODESET) then
        stop 'Error: Required edat no is too big in mk_subdom_edat'
      endif
*--------------------------------------------------------
      neelem = n_edat(ieg,1)
      nenode = n_edat(ieg,2)
      call f_alloc(np_ielem,'subdomain_nset',neelem*nenode,0)
      call f_alloc(np_matno,'subdomain_nset',neelem       ,0)
      iunit = ieg + io_edat -1
      call get_ielem(iunit,feel(np_ielem),feel(np_matno),
     $               neelem,nenode                       )
*--------------------------------------------------------
      call f_alloc(np_nset ,'subdomain_nset',neelem,0)
*--------------------------------------------------------
      iunit = io_node + neg -1
      call sd_wrt_nset(iunit,mats,matnos,
     $     feel(np_ielem),feel(np_matno),neelem,nenode,
     $     feel(np_nset),nodes)
*--------------------------------------------------------
      n_nset(neg,1) = nodes
      n_nset(neg,2) = 1
*
*      np_work=np_push
      call f_alloc_pop
*
      return
*--------------------------------------------------------
      end
      subroutine sd_wrt_nset(iunit,mats,matnos,
     $                             ielem,matno,neelem,nenode,
     $                             newise,nodes)
*-----------------------------------------------------------
*     SUB-SUBROUTINE [sd_wrt_nset] make sub region NSET data
*     ****************************
*-----------------------------------------------------------
      dimension matnos(neelem)
      dimension ielem(nenode,neelem),    matno  (neelem)
      dimension newise(neelem)
*-----------------------------------------------------------
      inos = 0
*
      do 100 i=1,mats
*
         mno = matnos(i)
*
         do 200 j=1,neelem
*
            if( matno(j) .eq. mno) then
               inos = inos + 1
               newise(inos) = j
            endif
 200     continue
*
 100  continue
*-----------------------------------------------------------
      open(unit = iunit, status='scratch',form='unformatted')
*
      write(iunit) inos,1
      write(iunit) (newise(i),i=1,inos)
*
      nodes = inos
*
      return
      end
