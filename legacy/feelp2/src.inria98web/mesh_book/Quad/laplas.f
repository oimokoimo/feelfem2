C*****************************************************************
C
C     LAPLACIAN METHOD           laplas.f
C
C******************************************************************
      SUBROUTINE LAPLAS( NODE,NELM,MMTJ,PX,PY,IFIX,KTJ,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      PARAMETER( KED = 20000 )
      PARAMETER( KCM = 20 )
C
      DIMENSION MMTJ( KTE,4 ),PX( KTJ ),PY( KTJ ),IFIX( KTJ )
      DIMENSION JNB( KED ),NEI( KED,KCM )
C
      IF ( NODE.GT.KED ) THEN
         WRITE(*,*) 'KED IS TOO SMALL'
         STOP
      ENDIF
C
      DO 10 I = 1,KED
         JNB( I ) = 0
         DO 20 J = 1,KCM
            NEI( I,J ) = 0
 20      CONTINUE
 10   CONTINUE
C
C     COMPUTATION OF RELATION BETWEEN NODE AND ADJACENT ELEMENTS
C
      DO 30 I = 1,NELM
         DO 40 J = 1,4
            IP = MMTJ( I,J )
            JNB( IP ) = JNB( IP ) + 1
            if ( ip.gt.ked .or. jnb(ip).gt.kcm ) then
               write(*,*) 'i and j = ',i,j
               write(*,*) 'ip and jnb = ',ip,jnb(ip)
               stop
            endif
            NEI( IP,JNB( IP ) ) = I
 40      CONTINUE
 30   CONTINUE
C
C     ITERATION TIMES
C
c      WRITE(*,*) ' '
c      WRITE(*,*) ' INPUT ITERATION NUMBER.'
c      READ(*,*) ITERA
C
c      DO 100 IT = 1,ITERA
      DO 100 IT = 1,5
c         WRITE(*,*) '     ITERATION ',IT
         DO 110 I = 1,NODE
            IF( IFIX( I ).EQ.0 ) THEN
               GX = 0.D0
               GY = 0.D0
               AR = 0.D0
               DO 120 J = 1,JNB( I )
                  IELM = NEI( I,J )
                  J1 = MMTJ( IELM,1 )
                  J2 = MMTJ( IELM,2 )
                  J3 = MMTJ( IELM,3 )
                  J4 = MMTJ( IELM,4 )
                  S = AREA( KTE,KTJ,IELM,MMTJ,PX,PY )
                  XC =( PX( J1 ) + PX( J2 ) + PX( J3 ) + PX( J4 ) ) / 4.D0
                  YC =( PY( J1 ) + PY( J2 ) + PY( J3 ) + PY( J4 ) ) / 4.D0
C
                  AR = AR + S
                  GX = GX + S * XC
                  GY = GY + S * YC
 120           CONTINUE
C
               CGRAX = GX / AR 
               CGRAY = GY / AR
               PX( I ) = CGRAX
               PY( I ) = CGRAY
            ENDIF
 110     CONTINUE
 100  CONTINUE
C
      RETURN
      E N D





         
