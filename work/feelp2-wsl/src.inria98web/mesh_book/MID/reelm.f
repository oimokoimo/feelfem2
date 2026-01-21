c**********************************************************************
c
c     renumbering element       reelm.f
c 
c**********************************************************************
      subroutine reelm( nelm,jac,iord,ktj,kte )
c
      implicit real*8( a-h,o-z )
      parameter ( nomax = 120000 )
      parameter ( kcm = 4 )
c
      dimension jac( kte,kcm ),iord( kte )
      dimension jmem( nomax )
      dimension ip( nomax,kcm ),jt( nomax*kcm ),memjt( nomax*kcm )
      dimension joint( nomax ),newjt( nomax )
c
c**** renumbering
c
      id = 0
      do 11 i=1,nelm
         do 11 j=1,kcm
            ip(i,j) = jac(i,j)
 11   continue
      do 12 i=1,nelm
	 jmem(i) = 0
         do 12 j=1,kcm
            jj = nomax*(j-1)+i
            jt(jj) = ip(i,j)
 12   continue
c
      do 20 j=1,nelm
         do 21 i=1,kcm
            jn = jt(nomax*(i-1)+j)
	    if ( jn .le. 0 ) goto 21
            jsub = (j-1)*kcm
	    jmem(j) = jmem(j)+1 
	    jqst = jsub+jmem(j)
	    memjt(jqst) = jn
 21      continue
 20   continue
c
c***
c
      imin = 1
 29   continue
      do 30 ik=1,nelm
	 if ( jmem(ik) .ne. imin ) goto 30
	 do 31 j=1,nelm
	    joint(j) = 0
	    newjt(j) = 0
 31      continue
	 i = 1
	 newjt(1) = ik
	 joint(ik) = 1
	 k = 1
 33      continue
	 k4 = jmem(newjt(i))
	 jsub = (newjt(i)-1)*kcm
	 do 32 jj=1,k4
	    k5 = memjt(jsub+jj)
	    if ( joint(k5) .gt. 0 ) goto 32
	    k = k+1
	    newjt(k) = k5
	    joint(k5) = k
 32      continue
	 if ( k .eq. nelm ) goto 34
	 i=i+1
	 goto 33
 30   continue
      imin = imin+1
      go to 29
 34   continue
      do 35 j=1,nelm
         iord(j) = newjt(j)
 35   continue
c
      return
      end

