C**********************************************************************
C
C     REMOVE UNNECESSARY ELEMENTS       delete.f 
C
C**********************************************************************
      SUBROUTINE DELETE( NELM,MTJ,JAC,IDM,KTE,IV,KV,MAP )
C
      IMPLICIT REAL*8( A-H,O-Z )
C
      DIMENSION KV( KTE ),MTJ( KTE,9 ),JAC( KTE,4 ),MAP( KTE )
      DIMENSION IDM( KTE )
C
C     INITIALIZATION
C
      M = 0
      N = 0
      DO 10 I = 1,NELM
         MAP( I ) = 1
 10   CONTINUE
C
      DO 20 I = 1,IV
         MAP( KV( I ) ) = 0 
 20   CONTINUE
C
      DO 30 I = 1,NELM
         IF( MAP( I ).NE.0 ) THEN
            M =M + 1
            MAP( I ) = M
         ENDIF
 30   CONTINUE
C
      DO 40 I = 1,NELM
         IF( MAP( I ).NE.0 ) THEN
            N = N + 1
            DO 50 IA = 1,4
               MTJ( N,IA ) = MTJ( I,IA )
               IDM( N ) = IDM( I )
               IF( JAC( I,IA ).EQ.0 ) THEN
                  JAC( N,IA ) = 0
               ELSE
                  JAC( N,IA ) = MAP( JAC( I,IA ) )
               ENDIF
 50         CONTINUE
         ENDIF
 40   CONTINUE
C
      DO 60 I = N+1,NELM
         DO 70 IA = 1,4
            MTJ( I,IA ) = 0
            JAC( I,IA ) = 0
            IDM( I ) = 0
 70      CONTINUE
 60   CONTINUE
C
      NELM = NELM - IV
C
      RETURN
      END

            
