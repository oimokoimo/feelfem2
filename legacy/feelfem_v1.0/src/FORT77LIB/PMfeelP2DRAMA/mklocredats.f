      subroutine mklocredats(feel,myrank,nprocs,
     $                       loc ,npmax,
     $                       metis,nelem_g,
     $                       myelem,
     $                       nredat,redatctr,
     $                       redatinfo,
     $                       enptrlst_np,matnolst_np,conlst_np)
*--------------------------------------------------------
*     Make main enptr/con data from loc(2,*) array
*-------
* INPUT
*-------
*      LOC(2,npmax)    Node information in Global Node number
*         loc(1,*)    PE id
*         loc(2,*)    Local node number
*
*      metis(*)         Metis data
*
*      nredat
*      redatctr(5,*)
*      myelem
*-------
* OUTPUT
*-------
*     
*
*      redatinfo(3,nredat) redatinfo(1,*) EDAT number
*                          redatinfo(2,*) myelem
*                          redatinfo(3,*) number of nodes in con(half con size)
*
*
*--------------------------------------------------------
*-IN--
*
      real*4    feel(*)
*
      integer*4 myrank,nprocs
*
      dimension loc(2,npmax)
      integer*4 metis(*)
      integer*4 redatctr(5,*),nredat
      integer*4 myelem

*-OUT-
      integer*4 redatinfo(3,*)
      integer*4 enptrlst_np(*),matnolst_np(*),conlst_np(*)
*--------------------------------------------------------
      mypeid = myrank
*--------------------------------------------------------
      do 100 i=1,nredat
         no       = redatctr(1,i)
         np       = redatctr(2,i)
	 nelem    = redatctr(3,i)
	 np_ielem = redatctr(4,i)
	 np_matno = redatctr(5,i)
*
         redatinfo(1,i) = no
	 redatinfo(2,i) = myelem
	 redatinfo(3,i) = myelem*np

         call f_alloc(np_enptr,'(enptr_loc)',(myelem+1)*2,0,0)
         call f_alloc(np_matno,'(matno_loc)',myelem      ,0,0)
         call f_alloc(np_con  ,'(con_loc  )',myelem*np*2 ,0,0)
*
         enptrlst_np(i) = np_enptr
         matnolst_np(i) = np_matno
         conlst_np  (i) = np_con
*
         call mklocredats_co(myrank,nprocs,
     $                       feel(np_ielem),metis,feel(np_matno),
     $                       np,nelem,loc  ,npmax,
     $                       myelem,feel(np_enptr),feel(np_con),
     $                              feel(np_matno))

*----
 100  continue
*
      return
      end
      subroutine mklocredats_co(myrank,nprocs,
     $                          ielem,metis,matno,
     $                        np,nelem,loc,npmax,
     $                        myelem,enptr,con,matnoloc)
*--------------------------------------------------------
      parameter(NUR_ONE_ETYPE = 1)

      integer*4 myrank,nprocs
* global
      integer*4 np,nelem
      integer*4 ielem(np,nelem)
      integer*4 metis(*)
      integer*4 matno(*)
      integer*4 loc(2,*),npmax
* local
      integer*4 myelem,enptr(2,*),con(2,*),matnoloc(*)
*--------------------------------------------------------
* Make enptr,con
*-----------------
      mypeid = myrank
*
      ieptr = 0
      ipos  = 1
* 
* ieptr++ at the beginning, but ipos++ at the end
*
      do 200 i=1,nelem
         if(metis(i) .EQ. mypeid) then
*
            ieptr          = ieptr + 1
            enptr(1,ieptr) = ipos
            enptr(2,ieptr) = NUR_ONE_ETYPE
            matnoloc(ieptr)= matno(i)
*
            do 210 j=1,np
               con(1,ipos+j-1) = loc(2,ielem(j,i))
               con(2,ipos+j-1) = loc(1,ielem(j,i))
 210        continue
*
            ipos = ipos + np
         endif
 200  continue
*
      if( myelem .NE. ieptr) then
         call abortexit(myrank,'myelem .ne. ieptr(mkmainlocdat)')
      endif
*
      ieptr          = ieptr + 1
      enptr(1,ieptr) = ipos
*
      return
      end
