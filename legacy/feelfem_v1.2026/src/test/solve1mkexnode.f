      subroutine solve1mkexnode(feel,myrank,nprocs,nparams,
     $     x,y,npmax,fem_v,
     $  enptr,con,nelem,
     $  enptr_ex,con_ex,nelem_ex,
     $  ibuf,icount,idispl,
     $  dbuf,dcount,ddispl,
     $  nouter,
     $  np_ndno,np_peno,np_ipfex,np_ipdex,np_xex,np_yex
     $  ,npfex_v)
*------------------------------------------------------------
      parameter (MAX_PROCS = 256)
      parameter (NCTRL_ITEMS_HERE = 4)
*
      real*4    feel(*)
      real   *8 x(*),y(*)
      integer*4 enptr(2,*),con(2,*)
      integer*4 enptr_ex(2,*),con_ex(2,*)
      integer*4 ibuf(*)
      real   *8 dbuf(*)
      integer*4 icount(*),idispl(*)
      integer*4 dcount(*),ddispl(*)
*
      real   *8 fem_v(*)
*
      integer*4 procbuf(MAX_PROCS)
*----------------------------------------------------------
      if(MAX_PROCS .LT. nprocs) then
         call abortexit(myrank,'Too many procs (makepielem)')
      endif
*
      if(NCTRL_ITEMS_HERE .NE. nparams) then
         call abortexit(myrank,'Mismatch (mkexnode)')
      endif
*
      mypeid = myrank
      mypeidx= myrank+1
*---------------------------------------------------
* Count the number of outer nodes (with duplication)
*---------------------------------------------------
      nouter = 0
*---
      do 100 i=1,nelem
         ipos_from = enptr(1,i  )
         ipos_to   = enptr(1,i+1)-1
*
         do 110 j=ipos_from,ipos_to
            if(con(2,j) .ne. mypeid) nouter = nouter+1
 110     continue
 100  continue
*
      do 150 i=1,nelem_ex
         ipos_from = enptr_ex(1,i  )
         ipos_to   = enptr_ex(1,i+1)-1
*
         do 160 j=ipos_from,ipos_to
            if(con_ex(2,j) .ne. mypeid) nouter = nouter+1
 160     continue
 150  continue
*
      call f_alloc_push
      call f_alloc(np_ndno,'makepnode(ndno)',nouter,0,0)
      call f_alloc(np_peno,'makepnode(peno)',nouter,0,0)
*
      call mkexnd_outerlst(mypeid,
     $            enptr,   con   ,nelem,
     $            enptr_ex,con_ex,nelem_ex,
     $            nouter  ,feel(np_ndno),feel(np_peno))
*-----
* Memory move
*-------------------------------------
      call f_alloc_pop
*
      call f_alloc(np_ndno,'makepnode(ndno.2)',nouter,0,0)
      np_penobak = np_peno
      call f_alloc(np_peno,'makepnode(peno.2)',nouter,0,0)
      call f_move(feel(np_penobak),feel(np_peno),nouter)
*
      call f_alloc(np_ipfex,'makenode(ipfex)',nouter,0,0)
      call f_alloc(np_ipdex,'makenode(ipdex)',nouter,0,0)
      call f_alloc(np_xex  ,'makenode(xex)'  ,nouter,1,0)
      call f_alloc(np_yex  ,'makenode(yex)'  ,nouter,1,0)
      call f_alloc(npfex_v,'mkexnd(v)',nouter,1,0)
      call solve1mkpnd_co(nouter,feel(np_ndno),feel(np_peno),
     $                    feel(np_ipfex),feel(np_ipdex),
     $                    feel(np_xex ),feel(np_yex ),
     $ feel(npfex_v),
     $                    ibuf,icount,idispl,
     $                    dbuf,dcount,ddispl,nparams,nprocs)
*
      return
      end
      subroutine solve1mkpnd_co(nouter,ndno,peno,
     $       ipfex,ipdex,xex ,yex,
     $ femex_v,
     $       ibuf,icount,idispl,
     $       dbuf,dcount,ddispl, nparams, nprocs)
*------------------------------------------------------------
      parameter (NCTRL_ITEMS_HERE = 4)
*
      integer*4 ndno(*),peno(*)
      integer*4 nd,pe,pex
      integer*4 ipfex(*),ipdex(*)
      real   *8 xex(*),yex(*)
      real   *8 femex_v(*)
*
      integer*4 ibuf(*)
      real   *8 dbuf(*)
      integer*4 icount(*),idispl(*)
      integer*4 dcount(*),ddispl(*)
*----------------------------------------------------------
      if(NCTRL_ITEMS_HERE .NE. nparams) then
         call abortexit(myrank,'Mismatch parameters(makepnode1)')
      endif
*----------------------------------------------------------
      do 100 i=1,nouter
         nd = ndno(i)
         pe = peno(i)
         pex= pe + 1
*
         if(pe .GE. nprocs  .OR. pe.LT.0) then
           call abortexit(999,'illegal number in mkexnd_co')
         endif
*
         ne2send          = ibuf(idispl(pex)+1)
         nconsiz          = ibuf(idispl(pex)+2)
         nn2send          = ibuf(idispl(pex)+3)
         iptr_enptr_send  = idispl(pex) + NCTRL_ITEMS_HERE+1
         iptr_con_send    = idispl(pex) + NCTRL_ITEMS_HERE+
     $                      2*(ne2send+1) + 1
         iptr_matno_send  = iptr_con_send    + nconsiz * 2
         iptr_nodeno_send = iptr_matno_send  + ne2send
         iptr_ipf_send    = iptr_nodeno_send + nn2send
         iptr_ipd_send    = iptr_ipf_send    + nn2send
*
         iptr_x_send      = ddispl(pex) + 1
         iptr_y_send      = ddispl(pex) + nn2send + 1
         iptr_v_send = ddispl(pex) + nn2send*2+1
         call solve1mkexnd_sel(nd,
     $                           nn2send,
     $                           ibuf(iptr_nodeno_send),
     $                           ibuf(iptr_ipf_send),
     $                           ibuf(iptr_ipd_send),
     $                           dbuf(iptr_x_send),
     $                           dbuf(iptr_y_send),
     $                           dbuf(iptr_v_send),
     $        ipfex(i),ipdex(i),xex(i),yex(i),femex_v(i))
*
 100  continue
*
      return
      end
      subroutine solve1mkexnd_sel(nd,nn2send,
     $      nodeno,ipf,ipd,x,y,femex_v,
     $      ipfex,ipdex,xex,yex,v_ex)
*-------------------------------------------------------------
      integer*4 nd,nn2send
      integer*4 nodeno(*),ipf(*),ipd(*)
      real*8    x(*),y(*)
      real*8    femex_v(*)
      integer*4 ipfex,ipdex
      real*8    xex,yex
      real*8    v_ex
*------------------------------------------------------------
      do 100 i=1,nn2send
         if(nodeno(i) .eq. nd) then
            ipfex = ipf(i)
            ipdex = ipd(i)
            xex   =   x(i)
            yex   =   y(i)
            v_ex = femex_v(i)
            return
         endif
 100  continue
*
      call abortexit(999,'cannot find node in makepnode1')
      end
