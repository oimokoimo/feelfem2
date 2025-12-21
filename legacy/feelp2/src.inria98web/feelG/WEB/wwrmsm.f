C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSM(A,LA,N,MA,JA,JD,JL,JU,X,Y)                              
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSM                                                  
C                                                                               
C     PURPOSE : MATRIX * VECTOR.                                                
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA)                                              
C                                                                               
      DIMENSION X(N),Y(N)                                                       
C                                                                               
C                                              Y = A * X                        
C                                                                               
      DO 10 I=1,N                                                               
         Y(I) = A(I,JD)*X(I)                                                    
   10 CONTINUE                                                                  
C                                                                               
      DO 20 JJ=1,JL                                                             
         DO 30 I=1,N                                                            
            J = JA(I,JJ)                                                        
            Y(I) = Y(I) + A(I,JJ)*X(J)                                          
   30    CONTINUE                                                               
   20 CONTINUE                                                                  
C                                                                               
      DO 40 JJ=JD+1,JU                                                          
         DO 50 I=1,N                                                            
            J = JA(I,JJ)                                                        
            Y(I) = Y(I) + A(I,JJ)*X(J)                                          
   50    CONTINUE                                                               
   40 CONTINUE                                                                  
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
