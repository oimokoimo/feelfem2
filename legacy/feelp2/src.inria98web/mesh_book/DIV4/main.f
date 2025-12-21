C*********************************************************************
C
C     4 DIVISION TOOL          main.f
C
C*********************************************************************
      PROGRAM DIV4
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      PARAMETER( KTJ = 200000 )
      PARAMETER( KTE = 200000 )
      PARAMETER( KTB = 100 )
      PARAMETER( KTC = 500 )
C
      DIMENSION PX( KTJ ),PY( KTJ ),MTJ( KTE,9 ),JAC( KTE,4 )
      DIMENSION IDM( KTE ),IFIX( KTJ )
      DIMENSION MMTJ( KTE,4 ),IDMM( KTE )
      DIMENSION JNT( KTJ ),IEDG( KTB,6 ),IBND( KTB,KTC ),imed(4)
C
      CALL INPUT( NODE,NELM,MTJ,JAC,IDM,IFIX,PX,PY,KTJ,KTE,
     &     NEDG,IEDG,KTB,ifrm )
C
      eps = 1.d72
      do i = 1,nelm
         do j = 1,ifrm
            in0 = mtj(i,j)
            if (j.ne.ifrm) then
               in1 = mtj(i,j + 1)
            else
               in1 = mtj(i,1)
            endif
            tmp = (px(in1) - px(in0))**2 +(py(in1) - py(in0))**2
            eps = min(eps,tmp)
         enddo
      enddo
      eps = sqrt(eps)/10
c
      newnod = node
      newelm = 0
c
      do i = 1,nelm
         do j = 1,ifrm
            in0 = mtj(i,j)
            if (j.ne.ifrm) then
               in1 = mtj(i,j + 1)
            else
               in1 = mtj(i,1)
            endif
            xtmp = (px(in0) + px(in1))/2
            ytmp = (py(in0) + py(in1))/2
c
            do k = node + 1,newnod
               tmp = (px(k) - xtmp)**2 + (py(k) - ytmp)**2
               if (sqrt(tmp).lt.eps) goto 1000
            enddo
            newnod = newnod + 1
            px(newnod) = xtmp
            py(newnod) = ytmp
            ifix(newnod) = min(ifix(in0),ifix(in1))
            k = newnod
c
 1000       continue
            imed(j) = k
         enddo
c
         if (ifrm.eq.4) then
            xtmp = 0.d0
            ytmp = 0.d0
            do j = 1,4
               xtmp = xtmp + px(mtj(i,j))
               ytmp = ytmp + py(mtj(i,j))
            enddo
            newnod = newnod + 1
            px(newnod) = xtmp/4
            py(newnod) = ytmp/4
c
            do j = 1,4
               newelm = newelm + 1
               mmtj(newelm,1) = mtj(i,j)
               mmtj(newelm,2) = imed(j)
               mmtj(newelm,3) = newnod
               if (j.eq.1) then
                  mmtj(newelm,4) = imed(4)
               else
                  mmtj(newelm,4) = imed(j - 1)
               endif
               idmm(newelm) = idm(i)
            enddo
c
         else
            do j = 1,3
               newelm = newelm + 1
               mmtj(newelm,1) = mtj(i,j)
               mmtj(newelm,2) = imed(j)
               if (j.eq.1) then
                  mmtj(newelm,3) = imed(3)
               else
                  mmtj(newelm,3) = imed(j - 1)
               endif
               idmm(newelm) = idm(i)
            enddo
            newelm = newelm + 1
            mmtj(newelm,1) = imed(1)
            mmtj(newelm,2) = imed(2)
            mmtj(newelm,3) = imed(3)
            idmm(newelm) = idm(i)
         endif
      enddo
c
      if (newelm.ne.4*nelm) stop 'Error newelm'
c
      CALL RENUM4( newnod,newelm,MMTJ,PX,PY,IFIX,JNT,KTJ,KTE,ifrm )
C
      CALL RMKJAC( newnod,newelm,MMTJ,JAC,MTJ,KTE,ifrm )
C
      CALL BNDNOD( newnod,newelm,MMTJ,JAC,IDMM,JNT,
     &     IEDG,IBND,KTJ,KTE,KTB,KTC,NEDG,MTJ,ifrm )
C
      CALL OUTPUT( newnod,newelm,MMTJ,JAC,IDMM,PX,PY,IFIX,
     &     IEDG,IBND,KTJ,KTE,KTB,KTC,NEDG,ifrm)
C
      STOP
      E N D
