      subroutine rmkjac(node,nelm,mmtj,jac,iwork,kte,ifrm)
c
      dimension mmtj(kte,4),jac(kte,4),iwork(kte*2,4)
c
      do 100 i=1,nelm
         do 110 j=1,4
            jac(i,j) = 0
 110     continue
 100  continue
c
      imax = 0
      do 120 i=1,nelm
         do 130 j=1,ifrm
            if ( j.eq.ifrm ) then
               nna = mmtj(i,j)
               nnb = mmtj(i,1)
            else
               nna = mmtj(i,j)
               nnb = mmtj(i,j+1)
            endif
c
            do 140 k=1,imax
               if ( iwork(k,1).eq.nnb .and. iwork(k,2).eq.nna ) then
                  jac(i,j) = iwork(k,3)
                  jac(iwork(k,3),iwork(k,4)) = i
c
                  iwork(k,1) = iwork(imax,1)
                  iwork(k,2) = iwork(imax,2)
                  iwork(k,3) = iwork(imax,3)
                  iwork(k,4) = iwork(imax,4)
                  imax = imax - 1
c
                  goto 130
               endif
 140        continue
c
            imax = imax + 1
            if ( imax.gt.kte*2 ) then
               write(*,*) 'Work spase is short in sobroutine rmkjac.'
               stop
            endif
c
            iwork(imax,1) = nna
            iwork(imax,2) = nnb
            iwork(imax,3) = i
            iwork(imax,4) = j
 130     continue
 120  continue
c                                             check check
      do 150 i=1,imax
         if ( jac(iwork(i,3),iwork(i,4)).ne.0 ) then
            write(*,*) 'Error detected for boundary edge in rmkjac.'
            stop
         endif
 150  continue
c
      do 160 i=1,nelm
         do 170 j=1,ifrm
            ij = jac(i,j)
            if ( ij.eq.0 ) goto 170
            do 180 k=1,ifrm
               if ( jac(ij,k).eq.i ) goto 170
 180        continue
            write(*,*) 'Error detected for jac compatibility in rmkjac'
            stop
 170     continue
 160  continue
c
      return
c
      e n d
