C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSN(A,LA,N,MA,JA,IU,X,Y)                                    
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSN                                                  
C                                                                               
C     PURPOSE : MATRIX T * VECTOR.                                              
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),IU(N)                                        
C                                                                               
      DIMENSION X(N),Y(N)                                                       
C                                                                               
C                                              Y = AT * X                       
C                                                                               
      DO 10 I=1,N                                                               
         Y(I) = 0.D0                                                            
   10 CONTINUE                                                                  
C                                                                               
      DO 20 I=1,N                                                               
*VDIR NODEP                                                                     
         DO 30 JJ=1,IU(I)                                                       
            J = JA(I,JJ)                                                        
            Y(J) = Y(J) + A(I,JJ)*X(I)                                          
   30    CONTINUE                                                               
   20 CONTINUE                                                                  
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
