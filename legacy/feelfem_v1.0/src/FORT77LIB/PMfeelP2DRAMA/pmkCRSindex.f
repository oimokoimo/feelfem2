      subroutine pmkCRSindex(mypeid,nprocs,ndfmax,
     $     isumup,myeqfrom,myeqto,neqtotal,
     $     enptr,con,nelem,
     $     ipf,ipd,npmax,
     $     enptr_ex,con_ex,nelem_ex,
     $     ndno,peno,ipfex,ipdex,nouter,
     $     ic,ip,ncon,neq,
     $     indrow,
     $     ncof,maxnzpr    )
*--------------------------------------------------------------
*  Make distributed CRS index array from DRAMA double index 
*
*  parameter MAX  Assumed 
*
*  ip(neq+1)   iptrcol
*  ic(ncof,neq) -> indrow(ncof)
*
*  ipt(*)  global equation number /pointer-> iptr
*  ipno(*) local equation number for row/ pointer-> iptr_ipno
*
*--------------------------------------------------------------*
      parameter (MAX = 100)
*--
      integer*4 isumup(*)
      integer*4 enptr(2,*),con(2,*)
      integer*4 ipf(*),ipd(*)
      integer*4 enptr_ex(2,*),con_ex(2,*)
      integer*4 ndno(*),peno(*),ipfex(*),ipdex(*)
      integer*4 ic(ncon,*),ip(*)
      integer*4 indrow(*)
*
      integer*4 ipt (MAX)
      integer*4 ipno(MAX)
*
      integer*4 nd,pe
*--------------------------------------------------------------
      if(ndfmax .gt. MAX) then
         call abortexit(999,'pmkCRSindex(MAX too small)')
      endif
*---
      maxnzpr = 0
*
      do 100 i=1,neq
         ip(i)=0
 100  continue
*--------------------------------------------------------
* Make IC array
*--------------------------------------------------------
* PE's element loop, (next other PE's element loop)
*------------------
      do 200 i=1,nelem
*------------------
* STEP 1
* make ipt(*) array for each element
*      ipt(*) contatins all the equation no relating this element
*      iptr   is its counter
*------------------
         iptr      = 0
         iptr_ipno = 0
*
         ipos_from = enptr(1,i  )
         ipos_to   = enptr(1,i+1)-1
*
         do 210 j=ipos_from,ipos_to
            nd = con(1,j)
            pe = con(2,j)
*
*-----------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            if(pe .eq. mypeid) then
               do 211 k=1,ipf(nd)
                  iptr = iptr + 1
                  ipt(iptr)=(ipd(nd)+(k-1))+(myeqfrom -1)

                  iptr_ipno = iptr_ipno + 1
                  ipno(iptr_ipno) = ipd(nd)+(k-1)
 211           continue
            else
*
* search in outer node
*               
               do 215 ks=1,nouter
                  if(nd .eq. ndno(ks) .AND. pe .eq. peno(ks)) then
                     goto 216
                  endif
 215           continue
*
*err
               call abortexit(999,'cannot find outer nd(pmkCRSindex)')
*
 216           continue
*     
               do 218 k=1,ipfex(ks)
                  iptr = iptr + 1
                  ipt(iptr)=(ipdex(ks)+(k-1))+(isumup(pe+1))
 218           continue
            endif
*-----------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 210     continue

*
* update ic,ip
*
         do 250 j=1,iptr_ipno
*
* FOR ROW nj  (ipno(*) is local equation number)
*
            nj = ipno(j)
*---
            do 255 k=1,iptr
*
* store (nj,nk)  [nj is local number, nk is global number)
*
               nk = ipt(k)
               do 256 l = 1, ip(nj)
                  if(ic(l,nj) .eq. nk) goto 255
 256           continue
*
* set ic,ip     
               ip(nj)        =ip(nj)+1
               ic(ip(nj),nj) = nk
*
 255        continue
 250     continue

*----------------------
* PE's own element loop
*-----------------------
 200  continue

*--------------------------------------------------------
* Other PE's element loop
*------------------
      do 300 i=1,nelem_ex
*------------------
* STEP 1
* make ipt(*) array for each element
*      ipt(*) contatins all the equation no relating this element
*      iptr   is its counter
*------------------
         iptr      = 0
         iptr_ipno = 0
*
         ipos_from = enptr_ex(1,i  )
         ipos_to   = enptr_ex(1,i+1)-1
*
         do 310 j=ipos_from,ipos_to
            nd = con_ex(1,j)
            pe = con_ex(2,j)
*
*-----------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
            if(pe .eq. mypeid) then
               do 311 k=1,ipf(nd)
                  iptr = iptr + 1
                  ipt(iptr)=(ipd(nd)+(k-1))+(myeqfrom -1)

                  iptr_ipno = iptr_ipno + 1
                  ipno(iptr_ipno) = ipd(nd)+(k-1)
 311           continue
            else
*
* search in outer node
*               
               do 315 ks=1,nouter
                  if(nd .eq. ndno(ks) .AND. pe .eq. peno(ks)) then
                     goto 316
                  endif
 315           continue
*
*err
               call abortexit(999,'cant find nd(ex)(pmkCRSindex)')
*
 316           continue
*     
               do 318 k=1,ipfex(ks)
                  iptr = iptr + 1
                  ipt(iptr)=(ipdex(ks)+(k-1))+(isumup(pe+1))
 318           continue
            endif
*-----------<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
 310     continue

*
* update ic,ip
*
         do 350 j=1,iptr_ipno
*
* FOR ROW nj  (ipno(*) is local equation number)
*
            nj = ipno(j)
*---
            do 355 k=1,iptr
*
* store (nj,nk)  [nj is local number, nk is global number)
*
               nk = ipt(k)
               do 356 l = 1, ip(nj)
                  if(ic(l,nj) .eq. nk) goto 355
 356           continue
*
* set ic,ip     
               ip(nj)        =ip(nj)+1
               ic(ip(nj),nj) = nk
*
 355        continue
 350     continue

*----------------------
* Other PE's element loop
*-----------------------
 300  continue



*----------------------------------------------------------
* Make indrow in the SAME allocation area of IC
* 
*  THIS IS NOT APPLICABLE FOR VECTOR PROCESSING!!!!!!!!!!!!
*----------------------------------------------------------
      maxnzpr = ip(1)
      irptr   =    1
*
      do 400 i=2,neq
         if(maxnzpr .LT. ip(i)) maxnzpr = ip(i)

         irptrsv = irptr
         irptr   = irptr   + ip(i-1)
         ip(i-1) = irptrsv
*
         do 410 j=0,ip(i)-1
            indrow(j+irptr) = ic(j+1,i)
 410     continue
 400  continue
*
      irptrsv   = irptr
      irptr     = irptr   + ip(neq)
      ip(neq)   = irptrsv
      ip(neq+1) = irptr
      
      ncof    = irptr   - 1

      return
      end







