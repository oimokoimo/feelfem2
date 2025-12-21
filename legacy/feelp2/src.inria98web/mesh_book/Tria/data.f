C**********************************************************************
C
C     DATA TO FILE        data.f
C
C**********************************************************************
      SUBROUTINE DATA( NEX,NIN,NODE,NELM,MTJ,JAC,IDM,
     &     JNT,IBEX,IBIN,IBNN,IBNO,KBD,KTJ,PX,PY,IFIX )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION MTJ( 2*KTJ + 1,3 ),JAC( 2*KTJ + 1,3 ),IDM( 2*KTJ + 1 )
      DIMENSION JNT( KTJ ),IBEX( KBD ),IBIN( KBD )
      DIMENSION IBNN( KBD,2,KTJ/100 ),IBNO( KBD,KTJ )
      DIMENSION PX( KTJ + 3 ),PY( KTJ + 3 ),IFIX( KTJ + 3 ),IWORK(1000)
C
      DO 100 II=1,KTJ+3
         IFIX(II) = 0
 100  CONTINUE
C
      DO 110 II=1,NELM
         IIDM = IDM(II)
         IF ( JAC(II,1).EQ.0 .OR. IDM(JAC(II,1)).NE.IIDM ) THEN
            IFIX(MTJ(II,1)) = 1
            IFIX(MTJ(II,2)) = 1
         ENDIF
         IF ( JAC(II,2).EQ.0 .OR. IDM(JAC(II,2)).NE.IIDM ) THEN
            IFIX(MTJ(II,2)) = 1
            IFIX(MTJ(II,3)) = 1
         ENDIF
         IF ( JAC(II,3).EQ.0 .OR. IDM(JAC(II,3)).NE.IIDM ) THEN
            IFIX(MTJ(II,3)) = 1
            IFIX(MTJ(II,1)) = 1
         ENDIF
 110  CONTINUE
C
      OPEN( 9,FILE = 'MESH.PLN' )
      WRITE( 9,620 ) NODE
      WRITE( 9,640 )( PX( I ), PY( I ), IFIX(I) ,I,I = 1,NODE )
C     
      ISBD = 0
      DO 10 II=1,NELM
         IF ( IDM(II) .NE. ISBD ) THEN
            ISBD = ISBD + 1
            IF ( IDM(II) .NE. ISBD ) THEN
               WRITE(*,*) 'ERROR DETECTED IN DATA.F'
               STOP
            ENDIF
            IWORK(ISBD) = II
         ENDIF
 10   CONTINUE
      IWORK(ISBD+1) = NELM + 1
C     
      WRITE( 9,620 ) ISBD
      DO 20 II=1,ISBD
         WRITE( 9,620 ) IWORK(II+1)-IWORK(II)
         WRITE( 9,620 ) 3
         WRITE( 9,630 ) ((MTJ(I,J),J=1,3),(JAC(I,J),J=1,3),IDM(I),I,
     *        I = IWORK(II),IWORK(II+1)-1 )
 20   CONTINUE
C     
      NEDG = 0
      DO 30 I=1,NEX
         NEDG = NEDG + IBEX(I)
 30   CONTINUE
      DO 40 I=1,NIN
         NEDG = NEDG + IBIN(I)
 40   CONTINUE
C     
      WRITE( 9,620 ) NEDG
C     
      DO 50 I=1,NEX
         NXTEDG = 1
         NXTNOD = JNT(IBNN(I,1,NXTEDG))
         DO 60 J=1,KTJ/2
            IF ( IBNO(I,J).EQ.NXTNOD ) THEN
               IWORK(NXTEDG) = J
               IF ( NXTEDG.GT.IBEX(I) ) THEN
                  GOTO 1000
               ELSE
                  NXTEDG = NXTEDG + 1
                  NXTNOD = JNT(IBNN(I,1,NXTEDG))
               ENDIF
            ENDIF
 60      CONTINUE
         WRITE(*,*) 'ERROR DETECTED AFTER DO 60 OF SUBROUTINE DATA'
         STOP
C     
 1000    CONTINUE
C     
         DO 160 J=1,IBEX(I)
            ITMP = IWORK(J+1) - IWORK(J) + 1
            WRITE(9,650) IBNN(I,1,J),IBNN(I,1,J+1),ITMP,I
            IPNT = IWORK(J)
            DO 165 K=1,(ITMP-1)/10+1
               WRITE(9,660) (IBNO(I,L),L=IPNT,MIN(IPNT+9,IWORK(J+1)))
               IPNT = IPNT + 10
 165        CONTINUE
 160     CONTINUE
 50   CONTINUE
C     
      DO 70 I=1,NIN
         NXTEDG = 1
         NXTNOD = JNT(IBNN(I,2,NXTEDG))
         DO 80 J=KTJ/2+1,KTJ
            IF ( IBNO(I,J).EQ.NXTNOD ) THEN
               IWORK(NXTEDG) = J
               IF ( NXTEDG.GT.IBIN(I) ) THEN
                  GOTO 1010
               ELSE
                  NXTEDG = NXTEDG + 1
                  NXTNOD = JNT(IBNN(I,2,NXTEDG))
               ENDIF
            ENDIF
 80      CONTINUE
         WRITE(*,*) 'ERROR DETECTED AFTER DO 80 OF SUBROUTINE DATA'
         STOP
C     
 1010    CONTINUE
C     
         DO 170 J=1,IBIN(I)
            ITMP = IWORK(J+1) - IWORK(J) + 1
            WRITE(9,650) IBNN(I,2,J),IBNN(I,2,J+1),ITMP,0
            IPNT = IWORK(J)
            DO 175 K=1,(ITMP-1)/10+1
               WRITE(9,660) (IBNO(I,L),L=IPNT,MIN(IPNT+9,IWORK(J+1)))
               IPNT = IPNT + 10
 175        CONTINUE
 170     CONTINUE
 70   CONTINUE
      
 620  FORMAT( I6 )
 630  FORMAT( 8I7 )
 640  FORMAT( 2E15.7 , I3 , I6)
 650  FORMAT( 4I6 )
 660  FORMAT( 10I7 )
      CLOSE( 9 )
C
      RETURN
      END

