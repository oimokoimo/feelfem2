C**********************************************************************
C
C     SEARCH FOR TRIANGLES TO BE MODIFIED         search.f
C
C**********************************************************************
      SUBROUTINE SEARCH( IP,IQ,JNB,NEI,NELM,MTJ,JAC,IV,KV,KTE,KTJ,KCM,
     &     PX,PY )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( KTE,3 ),JAC( KTE,3 ),JNB( KTJ )
      DIMENSION KV( KTE ),NEI( KTJ,KCM ),PX( KTJ + 3 ),PY( KTJ + 3 )
C
C******** INITIALIZATION
C
      XP = PX(IP)
      YP = PY(IP)
      VX = PX(IQ) - XP
      VY = PY(IQ) - YP
C
      IV = 0 
      DO 10 I = 1,NELM
         KV( I ) = 0
 10   CONTINUE
C
      DO 20 I = 1,JNB( IP )
         IELM = NEI( IP,I )
         J = IVERT( IELM,IP,MTJ,KTE )
         JA = MOD( J,3 ) + 1
         JB = MOD( JA,3 ) + 1
C
         J1 = MTJ(IELM,J)
         J2 = MTJ(IELM,JA)
         J3 = MTJ(IELM,JB)
         IF ( J1.EQ.IQ .OR. J2.EQ.IQ .OR. J3.EQ.IQ ) THEN
            WRITE(*,*) 'ERROR IN SEARCH'
            STOP
         ENDIF
C
         VAX = PX(J2) - XP
         VAY = PY(J2) - YP
         VBX = PX(J3) - XP
         VBY = PY(J3) - YP
C
         VAV = VAX*VY - VAY*VX
         VBV = VBX*VY - VBY*VX
C
         IF ( VAV.GT.0.D0 .AND. VBV.LT.0.D0 ) THEN
            IV = IV + 1
            KV(IV) = IELM
            IELM = JAC(IELM,JA)
            IV = IV + 1
            IF ( IV.GT.NELM ) THEN
               WRITE(*,*) 'ERROR DETECTED IN SEARCH '
               STOP
            ENDIF
            KV(IV) = IELM
            GOTO 1000
         ENDIF
 20   CONTINUE
C
      WRITE( *,* )' *** ERROR IN SUBROUTINE SEARCH *** '
      WRITE( *,* )' ********* ISTACK IS EMPTY ******** '
      STOP
C
 1000 CONTINUE
C
      J1 = MTJ(IELM,1)
      J2 = MTJ(IELM,2)
      J3 = MTJ(IELM,3)
      IF ( J1.EQ.IQ .OR. J2.EQ.IQ .OR. J3.EQ.IQ ) RETURN
C
      DO 30 JA = 1,3
         JB = MOD(JA,3) + 1
C
         J2 = MTJ(IELM,JA)
         J3 = MTJ(IELM,JB)
C
         VAX = PX(J2) - XP
         VAY = PY(J2) - YP
         VBX = PX(J3) - XP
         VBY = PY(J3) - YP
C
         VAV = VAX*VY - VAY*VX
         VBV = VBX*VY - VBY*VX
C
         IF ( VAV.GT.0.D0 .AND. VBV.LT.0.D0 ) THEN
            IELM = JAC(IELM,JA)
            IV = IV + 1
            IF ( IV.GT.NELM ) THEN
               WRITE(*,*) 'ERROR DETECTED IN SEARCH '
               STOP
            ENDIF
            KV(IV) = IELM
            GOTO 1000
         ENDIF
 30   CONTINUE
C
      WRITE( *,* )' *** ERROR IN SUBROUTINE SEARCH *** '
      WRITE( *,* )' ******** BRANCH IS CLOSED ******** '
      STOP
C
      E N D

