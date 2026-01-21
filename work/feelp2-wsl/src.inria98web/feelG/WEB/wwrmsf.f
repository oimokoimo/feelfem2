C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSF(JA,LA,N,MA,JD,                                          
     &                  INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,X,Y)                   
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSF                                                  
C                                                                               
C     PURPOSE : LU INVERSE BY NILU.                                             
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION JA(LA,MA),IL(N),IU(N),IHL(N),IHP(N),WPC(N,MA)                   
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
               Y(I) = X(I) - WPC(I,1)*Y(J)                                      
   20       CONTINUE                                                            
C                                                                               
            DO 30 JJ=2,JL-1                                                     
*VDIR NODEP                                                                     
               DO 40 II=IHP(IPN),IHP(IPN+1)-1                                   
                  I = IHL(II)                                                   
                  J = JA(I,JJ)                                                  
                  Y(I) = Y(I) - WPC(I,JJ)*Y(J)                                  
   40          CONTINUE                                                         
   30       CONTINUE                                                            
C                                                                               
*VDIR NODEP                                                                     
            DO 50 II=IHP(IPN),IHP(IPN+1)-1                                      
               I = IHL(II)                                                      
               J = JA(I,JL)                                                     
               Y(I) = WPC(I,JD)*(Y(I)-WPC(I,JL)*Y(J))                           
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
                  Y(I) = Y(I) - WPC(I,JJ)*Y(J)                                  
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
               Y(I) = Y(I) - WPC(I,JJ)*Y(J)                                     
  100       CONTINUE                                                            
            Y(I) = WPC(I,JD)*Y(I)                                               
   90    CONTINUE                                                               
C                                                                               
C                                              Y = U INV * Y                    
C                                                                               
         DO 110 I=N-1,1,-1                                                      
*VDIR NODEP                                                                     
            DO 120 JJ=JD+1,IU(I)                                                
               J = JA(I,JJ)                                                     
               Y(I) = Y(I) - WPC(I,JJ)*Y(J)                                     
  120       CONTINUE                                                            
  110    CONTINUE                                                               
C                                                                               
      ENDIF                                                                     
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
