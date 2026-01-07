      subroutine pmeminitloc(feel,myrank,nprocs,
     $           mynode,np_xloc,np_yloc,xloc,yloc,
     $           nredat,myelem,
     $           np_redatinfo,np_enptrlst,np_matnolst,np_conlst,
     $           redatinfo,enptrlst,matnolst,conlst,
     $           nbedat,np_inbctr2,inbctr2,
     $           nbnset,np_idbctr2,idbctr2                       )
*--------------------------------------------------------------------
*
*
*     integer*4 redatinfo(3,*)     redatinfo(1,*)  REDAT No.
*                                  redatinfo(2,*)  number of elements(myelem)
*                                  redatinfo(3,*)  size for con(2,*)
*--------------------------------------------------------------------
      real   *4 feel(*)
      integer*4 myrank,nprocs
*
      integer*4 mynode,np_xloc,np_yloc
      real   *8 xloc(*),yloc(*)
*
      integer*4 nredat,myelem
      integer*4 np_redatinfo,np_enptrlst,np_matnolst,np_conlst
*
      integer*4 redatinfo(3,*)
      integer*4 enptrlst(*),matnolst(*),conlst(*)

      integer*4 nbedat
      integer*4 np_inbctr2,inbctr2(5,*)
*
      integer*4 nbnset
      integer*4 np_idbctr2,idbctr2(5,*)
*--------------------------------------------------------------------
      call np_work_set_falloc(1)
*--------------------------------------------------------------------
* xloc,yloc
*----------
      call pmeminitloc_movd(feel,xloc,mynode,np_xloc)
      call pmeminitloc_movd(feel,yloc,mynode,np_yloc)
*
*--------------------------------------------------------------------
* redatinfo,enptrlst,matnolst,conlst
*-----------------------------------
      call pmeminitloc_movi(feel,redatinfo,3*nredat,np_redatinfo)
      call f_alloc(np_enptrlst,'np_enptrlst(pmeminitloc)',nredat,0,0)
      call f_alloc(np_matnolst,'np_matnolst(pmeminitloc)',nredat,0,0)
      call f_alloc(np_conlst,  'np_conlst  (pmeminitloc)',nredat,0,0)
*
      do 100 i=1,nredat
         no    = redatinfo(1,i)
         nelem = redatinfo(2,i)
         nitem = redatinfo(3,i)
*
         call pmeminitloc_movi(feel,feel(enptrlst(i)),
     $                              (nelem+1)*2,np_enptr)
         call pmeminitloc_movi(feel,feel(matnolst(i)),
     $                               nelem     ,np_matno)
         call pmeminitloc_movi(feel,feel(conlst(i)),
     $                              nitem*2    ,np_con  )
*
         call feelset_npi(feel,np_enptrlst,i,np_enptr)
         call feelset_npi(feel,np_matnolst,i,np_matno)
         call feelset_npi(feel,np_conlst  ,i,np_con  )
 100  continue
*
*--------------------------------------------------------------------
* bedat
*-----------------------------------
      if(nbedat .NE. 0) then
         call f_alloc(np_inbctr2,'(inbctr2 pmem)',nbedat*5,0,0)
         call pmeminit_inbctr2(feel,nbedat,
     $                         inbctr2,feel(np_inbctr2) )
      else
         np_inbctr2 = 1
      endif
*--------------------------------------------------------------------
* bnset
*-----------------------------------
      if(nbnset .NE. 0) then
         call f_alloc(np_idbctr2,'(idbctr2 pmem)',nbnset*5,0,0)
         call pmeminit_idbctr2(feel,nbnset,
     $                         idbctr2,feel(np_idbctr2))
      else
         np_idbctr2 = 1
      endif
*
*--------------------------------------------------------------------
      return
      end
      subroutine pmeminit_idbctr2(feel,nbnset,idbctr2old,idbctr2)
*----------------------------------------------------------------
      real   *4 feel(*)
      integer*4 nbnset
      integer*4 idbctr2old(5,*)
      integer*4 idbctr2   (5,*)
*----------------------------------------------------------------
      do 100 i=1,nbnset
         no          = idbctr2old(1,i)
         nodes       = idbctr2old(2,i)
         np          = idbctr2old(3,i)
         np_con_old  = idbctr2old(4,i)
         np_info_old = idbctr2old(5,i)
*
         idbctr2(1,i) = no
         idbctr2(2,i) = nodes
         idbctr2(3,i) = np
         call pmeminitloc_movi(feel,feel(np_con_old),nodes*2,
     $                                               np_con    )
         call pmeminitloc_movi(feel,feel(np_info_old),nodes*np,
     $                                               np_info   )
         idbctr2(4,i) = np_con
         idbctr2(5,i) = np_info
 100  continue
*----------------------------------------------------------------
      return
*
      end
      subroutine pmeminit_inbctr2(feel,nbedat,inbctr2old,inbctr2)
*----------------------------------------------------------------
      real   *4 feel(*)
      integer*4 nbedat
      integer*4 inbctr2old(5,*)
      integer*4 inbctr2   (5,*)
*----------------------------------------------------------------
      do 100 i=1,nbedat
         no           = inbctr2old(1,i)
         nelem        = inbctr2old(2,i)
         np_enptr_old = inbctr2old(3,i)
         np_con_old   = inbctr2old(4,i)
         np_matno_old = inbctr2old(5,i)
         nptr         = i_feelget(feel(np_enptr_old),1+2*nelem)
*
         inbctr2(1,i) = no
         inbctr2(2,i) = nelem
         call pmeminitloc_movi(feel,feel(np_enptr_old),(nelem+1)*2,
     $                                                  np_enptr)
         call pmeminitloc_movi(feel,feel(np_matno_old), nelem,
     $                                                  np_matno)
         call pmeminitloc_movi(feel,feel(np_con_old),  (nptr-1)*2,
     $                                                  np_con)
         inbctr2(3,i) = np_enptr
         inbctr2(4,i) = np_con
         inbctr2(5,i) = np_matno
 100  continue
      return
      end
      subroutine pmeminitloc_movd(feel,dat,n,np_ptr)
*--------------------------------------------------------------------
*     pmeminitloc service co-subroutine
*     allocate double array for n items, and copy dat to feel(np_ptr)
*--------------------------------------------------------------------
      real*4 feel(*)
      real*8 dat(*)
      integer*4 n,np_ptr
*--------------------------------------------------------------------
      call f_alloc(np_ptr,'(pmeminitloc_movd)',n,1,0)
      call pmeminitloc_copyd(dat,feel(np_ptr),n)
*
      return
      end
      subroutine pmeminitloc_copyd(from,to,n)
*--------------------------------------------------------------------
*     pmeminitloc service co-subroutine
*     allocate double array for n items, and copy dat to feel(np_ptr)
*--------------------------------------------------------------------
      real*8    from(*),to(*)
      integer*4 n
*--------------------------------------------------------------------
      do 100 i=1,n
         to(i)=from(i)
 100  continue
*
      return
      end
      subroutine pmeminitloc_movi(feel,idat,n,np_ptr)
*--------------------------------------------------------------------
*     pmeminitloc service co-subroutine
*     allocate integer array for n items, and copy dat to feel(np_ptr)
*--------------------------------------------------------------------
      real*4 feel(*)
      integer*4 idat(*)
      integer*4 n,np_ptr
*--------------------------------------------------------------------
      call f_alloc(np_ptr,'(pmeminitloc_movd)',n,0,0)
      call pmeminitloc_copyi(idat,feel(np_ptr),n)
*
      return
      end
      subroutine pmeminitloc_copyi(from,to,n)
*--------------------------------------------------------------------
*     pmeminitloc service co-subroutine
*     allocate double array for n items, and copy dat to feel(np_ptr)
*--------------------------------------------------------------------
      integer*4 from(*),to(*)
      integer*4 n
*--------------------------------------------------------------------
      do 100 i=1,n
         to(i)=from(i)
 100  continue
*
      return
      end


