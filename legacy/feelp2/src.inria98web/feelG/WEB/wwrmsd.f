C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSD(A,LA,N,MA,JA,JD,IERR)                                   
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSD                                                  
C                                                                               
C     PURPOSE : MATRIX CHECK.                                                   
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA)                                              
C                                                                               
      IF ( N.LE.0 ) THEN                                                        
         IERR = 3000                                                            
         RETURN                                                                 
      ELSEIF ( N.EQ.1 ) THEN                                                    
         IERR = 1000                                                            
      ENDIF                                                                     
C                                                                               
      DO 10 I=1,N                                                               
         IF ( JA(I,JD).NE.I .OR. DABS(A(I,JD)).LT.1.D-72 ) THEN                 
            IERR = 5000                                                         
            RETURN                                                              
         ENDIF                                                                  
   10 CONTINUE                                                                  
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
