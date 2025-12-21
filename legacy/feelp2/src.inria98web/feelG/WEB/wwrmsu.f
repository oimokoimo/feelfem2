C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSU(A,LA,N,MA,JA,JD,                                        
     &                  INVF,JL,JU,IL,IU,MPN,IHL,IHP,RNP,WPC,X,Y)               
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSU                                                  
C                                                                               
C     PURPOSE : LU INVERSE BY SSOR.                                             
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),IL(N),IU(N),IHL(N),IHP(N),WPC(N)             
C                                                                               
      DIMENSION X(N),Y(N)                                                       
C                                                                               
      IF ( INVF.EQ.1 ) THEN                                                     
C                                                                               
C                                              Y = L INV * X                    
C                                                                               
         DO 10 IPN=1,MPN                                                        
*VDIR NODEP                                                                     
            DO 20 II=IHP(IPN),IHP(IPN+1)-1                                      
               I = IHL(II)                                                      
               J = JA(I,1)                                                      
               Y(I) = X(I) - RNP*A(I,1)*Y(J)                                    
   20       CONTINUE                                                            
C                                                                               
            DO 30 JJ=2,JL-1                                                     
*VDIR NODEP                                                                     
               DO 40 II=IHP(IPN),IHP(IPN+1)-1                                   
                  I = IHL(II)                                                   
                  J = JA(I,JJ)                                                  
                  Y(I) = Y(I) - RNP*A(I,JJ)*Y(J)                                
   40          CONTINUE                                                         
   30       CONTINUE                                                            
C                                                                               
*VDIR NODEP                                                                     
            DO 50 II=IHP(IPN),IHP(IPN+1)-1                                      
               I = IHL(II)                                                      
               J = JA(I,JL)                                                     
               Y(I) = WPC(I)*(Y(I)-RNP*A(I,JL)*Y(J))                            
   50       CONTINUE                                                            
   10    CONTINUE                                                               
C                                                                               
C                                              Y = U INV * Y                    
C                                                                               
         DO 60 IPN=MPN,1,-1                                                     
            DO 70 JJ=JD+1,JU                                                    
*VDIR NODEP                                                                     
               DO 80 II=IHP(IPN),IHP(IPN+1)-1                                   
                  I = IHL(II)                                                   
                  J = JA(I,JJ)                                                  
                  Y(I) = Y(I) - RNP*WPC(I)*A(I,JJ)*Y(J)                         
   80          CONTINUE                                                         
   70       CONTINUE                                                            
   60    CONTINUE                                                               
C                                                                               
      ELSE                                                                      
C                                                                               
C                                              Y = L INV * X                    
C                                                                               
         DO 90 I=1,N                                                            
            Y(I) = X(I)                                                         
*VDIR NODEP                                                                     
            DO 100 JJ=1,IL(I)                                                   
               J = JA(I,JJ)                                                     
               Y(I) = Y(I) - RNP*A(I,JJ)*Y(J)                                   
  100       CONTINUE                                                            
            Y(I) = WPC(I)*Y(I)                                                  
   90    CONTINUE                                                               
C                                                                               
C                                              Y = U INV * Y                    
C                                                                               
*VDIR NOVECTOR                                                                  
         DO 110 I=N-1,1,-1                                                      
            DINV = RNP*WPC(I)                                                   
*VDIR NODEP                                                                     
            DO 120 JJ=JD+1,IU(I)                                                
               J = JA(I,JJ)                                                     
               Y(I) = Y(I) - DINV*A(I,JJ)*Y(J)                                  
  120       CONTINUE                                                            
  110    CONTINUE                                                               
C                                                                               
      ENDIF                                                                     
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
