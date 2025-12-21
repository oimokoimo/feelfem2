c**********************************************************************
c
c     renumber.f    programed by nsis matumoto  1993.06.08   '95/5/23
c     renumbering   for 4 node square element
c 
c**********************************************************************
      subroutine renum4( node,nelm,mtj,px,py,ifix,jnt,ktj,kte,nnd )
c
      implicit real*8( a-h,o-z )
      parameter ( nomax = 200000 )
      parameter ( kcm = 15 )
c
      dimension mtj( kte,4 )
      dimension px( ktj ),py( ktj ),ifix( ktj ),jnt( ktj )
      dimension jmem( nomax ),xj( nomax ),yj( nomax ),ij( nomax )
      dimension ip( nomax,9 ),jt( nomax*4 ),memjt( nomax*kcm )
      dimension joint( nomax ),newjt( nomax )
c
c**** renumbering
c
      id = 0
      do 10 i=1,node
         jmem(i) = 0
         xj(i) = px(i)
         yj(i) = py(i)
         ij(i) = ifix(i)
 10   continue
      do 11 i=1,nelm
         do 11 j=1,nnd
            ip(i,j) = mtj(i,j)
 11   continue
      do 12 i=1,nelm
         do 12 j=1,nnd
            jj = nomax*(j-1)+i
            jt(jj) = ip(i,j)
 12   continue
c
      do 20 j=1,nelm
         do 21 i=1,nnd
            jn = jt(nomax*(i-1)+j)
            jsub = (jn-1)*kcm
            do 22 k=1,nnd
               if ( k .ne. i ) then
                  jjt = jt(nomax*(k-1)+j)
                  men1 = jmem(jn)
                  if ( men1 .ne. 0 ) then
		     do 23 iii=1,men1
			if ( memjt(jsub+iii) .eq. jjt ) goto 22
 23                  continue
		  endif
		  jmem(jn) = jmem(jn)+1 
		  jqst = jsub+jmem(jn)
		  memjt(jqst) = jjt
		  iajn = abs(jn-jjt)
		  if ( iajn .gt. id ) id = iajn 
               endif
 22         continue
 21      continue
 20   continue
c      write(6,*) " "
c      write(6,*) " old max band width = ",id + 1
c
c***
c
      mem = node
      do 25 i=1,node
	 if ( mem .gt. jmem(i) ) mem = jmem(i)
 25   continue
c
      minmax = id
      do 30 ik=1,node
	 if ( jmem(ik)-mem .gt. 1 ) goto 30
	 do 31 j=1,node
	    joint(j) = 0
	    newjt(j) = 0
 31      continue
	 max = 0
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
	    ndiff = abs(i-k)
	    if ( ndiff .ge. minmax ) goto 30
	    if ( ndiff .gt. max ) max = ndiff
 32      continue
	 if ( k .eq. node ) goto 34
	 i=i+1
	 goto 33
 34      continue
	 minmax = max
	 do 35 j=1,node
	    jnt(j) = joint(j)
 35      continue
 30   continue
c      write(6,*) ' new max band width = ',minmax + 1
c
      do 40 k=1,nelm
	 do 40 l=1,nnd
	    jj = ip(k,l)
	    mtj(k,l) = jnt(jj)
 40   continue
      do 41 k=1,node
	 jj = jnt(k)
	 px(jj) = xj(k)
	 py(jj) = yj(k)
	 ifix(jj) = ij(k)
 41   continue
c
      return
      end

