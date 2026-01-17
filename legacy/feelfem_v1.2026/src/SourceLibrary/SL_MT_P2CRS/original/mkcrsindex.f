      subroutine mkcrsindex(ic,ic2,ip,ncon,neq,ndf,
     $                      ielem,nelem,np,
     $                      ipf,ipd,npmax,ncof,maxnzpr)
*-------------------------------------------------------------------
* Make CRS index array
*
* Input   ielem(np,nelem)  /element-node correspondance array
*         ipf(npmax)        freedom per each node
*         ipd(npmax)        count-up degree of freedom
*         
*         ndf               total degree of freedom in one element
*                          (This is valid for only one element type)
* -------
*
* Work    IPT(*) 
*         IC(ncon=maximum connection, neq)  
* -------
* Output  IC or IC2  INDROW  (row pointer  size=ncof)
*         IP(neq+1)  IPTRCOL
*
*         IC2(*)     Same address of ic:   used to make final ic
*         ncof       Total nonzero number
*         maxnzpr    Maximum number of nonzeros per row      
*-------------------------------------------------------------------
      parameter (MAX = 100)

      dimension ic(ncon,neq),ip(neq+1)
      dimension ic2(*)
      dimension ielem(np,nelem)
      dimension ipf(npmax),ipd(npmax)
*
      dimension ipt(MAX)
*--------------------------------------------------------------
      if(ndf .gt. MAX) stop 'element matrix arraysize too huge'
*
      maxnzpr = 0
*
      do 100 i=1,neq
        ip(i)=0
100   continue
*--------------------------------------------------------------
* Make IC array
*--------------------------------------------------------------
* i: element loop
*----------------
      do 200 i=1,nelem
*--------------------------------------
* make ipt(*) array for each element
*      ipt(*) contains the equation no.
*      iptr is its counter
*--------------------------------------
       iptr = 0
*-------------------
* j: node loop
*-------------------
       do 201 j=1,np
*-------------------
* nno = node number
*-------------------
       nno = ielem(j,i)
*---------------------
* k: node freedom loop
*---------------------
        do 202 k=1,ipf(nno)
*	write(*,*) 'loop k=',k,' ipf(nno)= ',ipf(nno)
	iptr = iptr+1
	ipt(iptr)=ipd(nno)+k-1 
***     write(*,*) 'iptr=',iptr,'  ipt(iptr)=',ipt(iptr)
202     continue
201    continue
*---------------------------------
* finish to make ipt(*) array
* then make ic(*,neq) array
*---------------------------------
       if(ndf .ne. iptr) stop 'mkcrsindex ndf,iptr mismatch'
       do 210 j=1,ndf
*
* for Row nj
*
        nj = ipt(j)

        do 215 k=1,ndf
*
* store (nj,nk) index
*
	 nk = ipt(k)
	 do 216 l=1,ip(nj)
	 if(ic(l,nj) .eq. nk) goto 215
216      continue
         ip(nj)=ip(nj)+1
	 ic(ip(nj),nj) = nk
215     continue
210    continue
*----------------
* element loop
*----------------
200   continue

*--------------------------
* Make indrow array in IC2 *** NOT FOR VECTOR PROCESSING***
*--------------------------
      maxnzpr = ip(1)
      irptr   = 1
*
      do 300 i=2,neq
       
       if(maxnzpr .LT. ip(i)) maxnzpr = ip(i)
         
       irptrsv = irptr
       irptr   = irptr+ip(i-1)
       ip(i-1) = irptrsv
*
       do 310 j=0,ip(i)-1
         ic2(j+irptr)=ic(j+1,i)
310    continue
*
300   continue
*
      irptrsv = irptr
      irptr   = irptr + ip(neq)
      ip(neq) = irptrsv

      ncof = irptr-1
*new 
      ip(neq+1) = ncof + 1
 
      return
      end
