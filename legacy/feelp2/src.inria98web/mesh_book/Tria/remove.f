C**********************************************************************
C
C     REMOVE ALL TRIANGLES OUTSIDE OF BOUNDARY       remove.f
C
C**********************************************************************
      SUBROUTINE REMOVE( NEX,INDEX,NELM,MTJ,JAC,IDM,KBD,KTE )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION INDEX( KBD + 1 ),MTJ( KTE,3 ),JAC( KTE,3 ),IDM( KTE )
      DIMENSION MKP( 3 ),JKP( 3 )
C
      IELM = 0
      INDEX( 1 )  = 1
      DO 10 I = 1,NEX
         IZ = I
         INELM = 0
         DO 20 J = INDEX( I ),NELM 
            IF( IDM( J ).EQ.IZ ) THEN
               IELM = IELM + 1
               JELM = J
               INELM = INELM + 1
               IF( IELM.NE.JELM ) THEN
                  DO 30 K = 1,3 
                     MKP( K ) = MTJ( IELM,K )
                     JKP( K ) = JAC( IELM,K )
 30               CONTINUE
                  IKP = IDM( IELM )
C
                  DO 40 K = 1,3
                     KELM = JAC( JELM,K )
                     IF( KELM.NE.0 ) THEN
                        CALL EDGE( KELM,JELM,JAC,KTE,KEDG )
                        JAC( KELM,KEDG ) = IELM + KTE + 1
                     ENDIF
 40               CONTINUE
C
                  DO 50 L = 1,3
                     LELM = JKP( L )
                     IF( LELM.NE.0 ) THEN
                        CALL EDGE( LELM,IELM,JAC,KTE,LEDG )
                        JAC( LELM,LEDG ) = JELM + KTE + 1
                     ENDIF
 50               CONTINUE
C
                  DO 60 K = 1,3
                     JAC( IELM,K ) = MOD( JAC( IELM,K ),KTE + 1 )
                     JAC( JELM,K ) = MOD( JAC( JELM,K ),KTE + 1 )
                     KELM = JAC( IELM,K )
                     LELM = JAC( JELM,K )
                     if ( kelm .ne. 0 ) then
                        DO 70 L = 1,3
                           JAC( KELM,L ) = MOD( JAC( KELM,L ),KTE + 1 )
 70                     CONTINUE
                     endif
                     if ( lelm .ne. 0 ) then
                        DO 75 L = 1,3
                           JAC( LELM,L ) = MOD( JAC( LELM,L ),KTE + 1 )
 75                     CONTINUE
                     endif
 60               CONTINUE
C
                  DO 80 K = 1,3
                     JKP( K ) = JAC( IELM,K )
 80               CONTINUE
C
                  DO 90 K = 1,3
                     MTJ( IELM,K ) = MTJ( JELM,K )
                     JAC( IELM,K ) = JAC( JELM,K )
                     MTJ( JELM,K ) = MKP( K )
                     JAC( JELM,K ) = JKP( K )
 90               CONTINUE
C
                  IDM( IELM ) = IDM( JELM )
                  IDM( JELM ) = IKP
C
               ENDIF
            ENDIF
C
 20      CONTINUE
         INDEX( I + 1 ) = INDEX( I ) + INELM
 10   CONTINUE
C
      DO 100 I = 1,IELM
         DO 100 J = 1,3
            IF( JAC( I,J ).GT.IELM ) THEN
               JAC( I,J ) = 0
            ENDIF
 100  CONTINUE
C
      DO 110 I = IELM + 1,NELM
         DO 110 J = 1,3 
            MTJ( I,J ) = 0
            JAC( I,J ) = 0
 110  CONTINUE
C
      NELM = IELM
      RETURN
      END



                        
