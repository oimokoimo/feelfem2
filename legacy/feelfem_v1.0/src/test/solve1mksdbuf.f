      subroutine solve1mksdbuf(myrank,nprocs,npmax,nelem,
     $  ne2send,nconsiz,nn2send,neq,
     $  enptr,con,matno,eflag,nflag,
     $  x,y,ipf,ipd,fem_v,
     $  ctrl_send,enptr_send,con_send,matno_send,
     $  nodeno_send,ipf_send,ipd_send,
     $  x_send,y_send,fem_v_send)
*------------------------------------------------------------
      real*8    x(*),y(*)
      integer*4 enptr(2,*),con(2,*),matno(*)
      integer*4 nflag(*),eflag(*)
      integer*4 ipf(*),ipd(*)
      real*8    fem_v(*)
*
      integer*4 ctrl_send(*)
      integer*4 enptr_send(2,*),con_send(2,*),matno_send(*)
      integer*4 nodeno_send(*),ipf_send(*),ipd_send(*)
      real   *8 x_send(*),y_send(*)
      real   *8 fem_v_send(*)
*------------------------------------------------------------
      ctrl_send(1) = ne2send
      ctrl_send(2) = nconsiz
      ctrl_send(3) = nn2send
      ctrl_send(4) = neq
*------------------------------------------------------------
      if(ne2send .EQ. 0) goto 995
*
      iptr = 0
      ipos = 1
*
      do 100 i=1,nelem
*
        if(eflag(i) .EQ. 0) goto 100
        iptr = iptr + 1
*
        enptr_send(1,iptr) = ipos
        enptr_send(2,iptr) = enptr(2,i)
        matno_send(iptr  ) = matno(i)
*
        ipos_from = enptr(1,i  )
        ipos_to   = enptr(1,i+1)-1
*
        do 110 j=ipos_from,ipos_to
          con_send(1,ipos) = con(1,j)
          con_send(2,ipos) = con(2,j)
          ipos = ipos + 1
 110    continue
*
 100  continue
*
      enptr_send(1,iptr+1) = ipos
      enptr_send(2,iptr+1) = 999
*
*------------------------------------------------------------
*
*------------------------------------------------------------
 995  continue
*------------------------------------------------------------
*
*------------------------------------------------------------
      iptr = 0
      do 200 i=1,npmax
        if(nflag(i) .EQ. 1) then
          iptr = iptr + 1
          nodeno_send(iptr) = i
          ipf_send   (iptr) = ipf(i)
          ipd_send   (iptr) = ipd(i)
          x_send     (iptr) = x(i)
          y_send     (iptr) = y(i)
          fem_v_send(iptr) = fem_v(i)
        endif
 200  continue
*
      if(iptr .ne. nn2send) then
        call abortexit(myrank,'OKASHII mksdbuf')
      endif
*------------------------------------------------------------
      return
      end
