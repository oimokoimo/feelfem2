C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSV(A,LA,N,MA,JA,JD,IL,IU,RNP,WPC,X,Y)                      
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSV                                                  
C                                                                               
C     PURPOSE : LUT INVERSE BY SSOR.                                            
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),IL(N),IU(N),WPC(N)                           
C                                                                               
      DIMENSION X(N),Y(N)                                                       
C                                                                               
C                                              Y = UT INV * X                   
C                                                                               
      DO 10 I=1,N                                                               
         Y(I) = X(I)                                                            
   10 CONTINUE                                                                  
C                                                                               
*VDIR NOVECTOR                                                                  
      DO 20 I=1,N                                                               
         DINV = RNP*WPC(I)                                                      
*VDIR NODEP                                                                     
         DO 30 JJ=JD+1,IU(I)                                                    
            J = JA(I,JJ)                                                        
            Y(J) = Y(J) - DINV*A(I,JJ)*Y(I)                                     
   30    CONTINUE                                                               
   20 CONTINUE                                                                  
C                                                                               
C                                              Y = LT INV * Y                   
C                                                                               
      DO 40 I=N,1,-1                                                            
         Y(I) = Y(I)*WPC(I)                                                     
*VDIR NODEP                                                                     
         DO 50 JJ=1,IL(I)                                                       
            J = JA(I,JJ)                                                        
            Y(J) = Y(J) - RNP*A(I,JJ)*Y(I)                                      
   50    CONTINUE                                                               
   40 CONTINUE                                                                  
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
