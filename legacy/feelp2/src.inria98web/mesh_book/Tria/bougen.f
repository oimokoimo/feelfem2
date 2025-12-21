C****************************************************************
C
C     MESH GENERATION FOR DOMAIN SURROUNDED BY BOUNDARIES    bougen.f
C
C****************************************************************
      SUBROUTINE BOUGEN( IZ,NP,LIST,NTP,PX,PY,JNB,NEI,NELM,MTJ,JAC,
     *     IDM,IADRES,ISTACK,KV,IBR,MAP,NODE,KTE,KTJ,KCM )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION PX( KTJ + 3 ),PY( KTJ + 3 ),MTJ( KTE,3 ),JAC( KTE,3 )
      DIMENSION NEI( KTJ,KCM ),LIST( KTJ ),IADRES( KTJ + 3 )
      DIMENSION ISTACK( KTJ ),KV( KTE ),IBR( KTE ),MAP( KTE )
      DIMENSION IDM( KTE ),JNB( KTJ )
C
C******* INITIALIZATION
C
      INP = 0
      DO 10 I = 1, KTJ + 3
         IADRES( I ) = 0
 10   CONTINUE
C
      DO 20 I = 1, NP
         IADRES( LIST( I ) ) = I
 20   CONTINUE
C
C******* CREATE THREE TRIANGLES BY INSERTION OF THE FIRST POINT
C
      IS = LIST( 1 )
      IF( IS.GT.NODE ) THEN
         INP = INP + 1
         CALL DELAUN( IZ,IS,IS,NTP,PX,PY,JNB,NEI,NELM,MTJ,JAC,
     *        IDM,IADRES,ISTACK,KTE,KTJ,KCM )
      ENDIF
C******* LOOP OVER EACH POINT AND CONSTRUCT BOUNDARY EDGES
C
      DO 30 I = 1, NP
         IP = LIST( MOD( I,NP ) + 1 )
         IQ = LIST( I )
C
         IF( ( IP.GT.NODE ).AND.( I.NE.NP ) ) THEN
            INP = INP + 1
            CALL DELAUN( IZ,IP,IP,NTP,PX,PY,JNB,NEI,NELM,MTJ,JAC,IDM,
     *           IADRES,ISTACK,KTE,KTJ,KCM )
         ENDIF
c         write(*,*) ''
c         write(*,*) 'nelm in bougen = ',nelm
c         do 111 ijk=1,nelm
c            write(*,*) mtj(ijk,1),mtj(ijk,2),mtj(ijk,3)
c 111     continue
C
         DO 40 J = 1, JNB( IQ )
            DO 40 K = 1,3
               IF( MTJ( NEI( IQ,J ), K ).EQ.IP ) GOTO 30
 40      CONTINUE
C
C******* SEARCH FOR THE TRIANGLES BETWEEN NEW DATA POINT AND
C          OLD DATA POINT
C
         CALL SEARCH(IP,IQ,JNB,NEI,NELM,MTJ,JAC,IV,KV,KTE,KTJ,KCM,
     *        PX,PY)
c         CALL SEARCH( IZ,IP,IQ,JNB,NEI,NELM,MTJ,JAC,IDM,ISTACK,IV,KV,
c     *        IADRES,IBR,KTE,KTJ,KCM,PX,PY )
c         write(*,*) 'iv = ',iv
c         do 113 ij=1,iv
c            write(*,*) 'kv = ',kv(ij)
c 113     continue
C
C******* REMOVE TRIANGLES BETWEEN NEW DATA POINT AND OLD DATA POINTAND
C           SUBDIVIDE
C        THE POLYGON CONSISTED BY THEM
C
         CALL POLY(IQ,IP,IV,KV,PX,PY,NELM,MTJ,JAC,JNB,NEI,MAP,
     *        KTE,KTJ,KCM)
C
 30   CONTINUE
C
      NODE = NODE + INP
C
      RETURN
      END




         
