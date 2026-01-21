C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSG(JA,LA,N,MA,JD,IL,IU,WPC,X,Y)                            
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSG                                                  
C                                                                               
C     PURPOSE : LUT INVERSE BY NILU.                                            
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION JA(LA,MA),IL(N),IU(N),WPC(N,MA)                                 
C                                                                               
      DIMENSION X(N),Y(N)                                                       
C                                                                               
C                                              Y = UT INV * X                   
C                                                                               
      DO 10 I=1,N                                                               
         Y(I) = X(I)                                                            
   10 CONTINUE                                                                  
C                                                                               
      DO 20 I=1,N                                                               
*VDIR NODEP                                                                     
         DO 30 JJ=JD+1,IU(I)                                                    
            J = JA(I,JJ)                                                        
            Y(J) = Y(J) - WPC(I,JJ)*Y(I)                                        
   30    CONTINUE                                                               
   20 CONTINUE                                                                  
C                                                                               
C                                              Y = LT INV * Y                   
C                                                                               
      DO 40 I=N,1,-1                                                            
         Y(I) = WPC(I,JD)*Y(I)                                                  
*VDIR NODEP                                                                     
         DO 50 JJ=1,IL(I)                                                       
            J = JA(I,JJ)                                                        
            Y(J) = Y(J) - WPC(I,JJ)*Y(I)                                        
   50    CONTINUE                                                               
   40 CONTINUE                                                                  
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
