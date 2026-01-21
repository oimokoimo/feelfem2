      subroutine mk_subdomain_edat(feel,ieg,neg,mats,matnos)
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
c --------------------------------------------------------------------
      parameter (MAX_FEEL = 2000000)
      parameter (MAX_DOMAIN = 10)
      parameter (MAX_EDATSET = 38)
      parameter (MAX_NODESET = 20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
      parameter (MAX_IP    = 8)
      parameter (MAX_SOLVE = 11)
c --------------------------------------------------------------------
      dimension ipattern(MAX_EDATSET,2)
c --------------------------------------------------------------------
#COMMON
c --------------------------------------------------------------------
      data    icounter/0/ 
*--------------------------------------------------------------------
      save    icounter,ipattern
*--------------------------------------------------------------------
*      np_push = np_work  OLD F_ALLOC 
      call f_alloc_push
*--------------------------------------------------------
      do 1 i=1,icounter
	if(ipattern(i,1) .eq. ieg   .and.
     $     ipattern(i,2) .eq. neg         ) return
1     continue
*--------------------------------------------------------------------
      icounter = icounter + 1
      ipattern(i,1) = ieg
      ipattern(i,2) = neg
*--------------------------------------------------------------------
*--------------------------------------------------------------------
      if(neg .gt. MAX_EDATSET) then
        stop 'Error: Required edat no is too big in mk_subdom_edat'
      endif
*--------------------------------------------------------
      neelem = n_edat(ieg,1)
      nenode = n_edat(ieg,2)
      call f_alloc(np_ielem,'sub_region',neelem*nenode,0)
      call f_alloc(np_matno,'sub_region',neelem       ,0)
      iunit = ieg + io_edat -1
      call get_ielem(iunit,feel(np_ielem),feel(np_matno),
     $               neelem,nenode                       )
*--------------------------------------------------------
      call sd_count(feel(np_ielem),feel(np_matno),
     $     neelem,nenode,mats,matnos,neelem_new)
*--------------------------------------------------------
      n_edat(neg,1) = neelem_new
      n_edat(neg,2) = nenode
*--------------------------------------------------------
      call f_alloc(np_ielem_new,'sub_reg2',neelem_new*nenode,0)
      call f_alloc(np_matno_new,'sub_reg2',neelem_new       ,0)
*--------------------------------------------------------
      iunit = io_edat + neg -1
      call sd_wrt_edat(iunit,mats,matnos,
     $     feel(np_ielem),feel(np_matno),neelem,nenode,
     $     feel(np_ielem_new),feel(np_matno_new),neelem_new)
*--------------------------------------------------------
*      np_work=np_push   OLD F_ALLOC
      call f_alloc_pop
      return
*--------------------------------------------------------
      end
      subroutine sd_wrt_edat(iunit,mats,matnos,
     $                             ielem,matno,neelem,nenode,
     $                             ielem_n,matno_n,neelem_n )
*-----------------------------------------------------------
*     SUB-SUBROUTINE [sd_wrt_edat] make sub region EDAT data
*     ****************************
*-----------------------------------------------------------
      dimension matnos(neelem)
      dimension ielem(nenode,neelem),    matno  (neelem)
      dimension ielem_n(nenode,neelem_n),matno_n(neelem_n)
*-----------------------------------------------------------
      ino = 0
      do 100 i=1,mats
         mno = matnos(i)
*-----------------------------------------------------------
         do 200 j=1,neelem
*
            if(matno(j).eq.mno) then
               ino = ino + 1
*
               do 300 k=1,nenode
                  ielem_n(k,ino) = ielem(k,j)
 300           continue
*
               matno_n(ino) = matno(j)
            endif
*
 200     continue
 100  continue
*
*-----------------------------------------------------------
      if(ino .ne. neelem_n) stop 'Error@sub_region(sd_wrt_edat)'
*-----------------------------------------------------------
      open(unit = iunit, status='scratch',form='unformatted')
*
      write(iunit) neelem_n,nenode
      write(iunit) ((ielem_n(i,j),i=1,nenode),j=1,neelem_n)
      write(iunit) (matno_n(i),i=1,neelem_n)
*
      return
      end
      subroutine sd_count(ielem,matno,neelem,    nenode,
     $                    mats,matnos,neelem_new         )
*----------------------------------------------------------
*     SUB-SUBROUTINE: [sd_count]   Count subregion elements
*----------------------------------------------------------
      dimension ielem(nenode,neelem),matno(neelem)
      dimension matnos(mats)
*--------------------------------------------------------
      neelem_new = 0
*--------------------------------------------------------
      do 100 i=1,mats
*
         mno = matnos(i)
*
         do 101 ii=1,i-1
            if(mno .eq. matnos(ii)) stop 'matnos ERROR @sub_region'
 101     continue
*
         do 200 j=1,neelem
            if(matno(j) .eq. mno) neelem_new = neelem_new + 1
 200     continue
*
 100  continue
      if(neelem_new .eq. 0) stop 'neelem_new=0 error @sub_region(count)'
     $
*

*      write(*,*) 'count: mats       ',mats
*      write(*,*) 'count: matnos(1)  ',matnos(1)
*      write(*,*) 'count: neelem     ',neelem
*      write(*,*) 'count: nenode     ',nenode
*      write(*,*) 'count: neelem_new ',neelem_new

      return
      end
