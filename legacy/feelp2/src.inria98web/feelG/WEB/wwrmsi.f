C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSI(A,LA,N,MA,JA,JD,IL,IU,SNG,IMDF,RNP,WPC,IERR)            
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSI                                                  
C                                                                               
C     PURPOSE : ILU DECOMPOSITION FOR DIAGONAL ELEMENTS (DILU).                 
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),IL(N),IU(N)                                  
C                                                                               
      DIMENSION WPC(N)                                                          
C                                                                               
      DO 10 I=1,N                                                               
         WPC(I) = A(I,JD)                                                       
   10 CONTINUE                                                                  
C                                                                               
      IF ( IMDF.EQ.0 ) THEN                                                     
         DO 20 I=1,N                                                            
            DO 30 JJ=1,IL(I)                                                    
               J = JA(I,JJ)                                                     
               DO 40 JUP=JD+1,IU(J)                                             
                  IF ( JA(J,JUP).EQ.I ) THEN                                    
                     WPC(I) = WPC(I) - A(I,JJ)*WPC(J)*A(J,JUP)                  
                     GOTO 30                                                    
                  ENDIF                                                         
   40          CONTINUE                                                         
   30       CONTINUE                                                            
C                                                                               
            IF ( DABS(WPC(I)/A(I,JD)).LT.SNG ) THEN                             
               IERR = 1400                                                      
               WPC(I) = A(I,JD)*SNG                                             
            ENDIF                                                               
            WPC(I) = 1.D0/WPC(I)                                                
   20    CONTINUE                                                               
C                                                                               
      ELSE                                                                      
C                                                                               
         DO 50 I=1,N                                                            
            ERS = 0.D0                                                          
            DO 60 JJ=1,IL(I)                                                    
               J = JA(I,JJ)                                                     
               DO 70 JUP=JD+1,IU(J)                                             
                  IF ( JA(J,JUP).EQ.I ) THEN                                    
                     WPC(I) = WPC(I) - A(I,JJ)*WPC(J)*A(J,JUP)                  
                  ELSE                                                          
                     ERS = ERS + A(I,JJ)*WPC(J)*A(J,JUP)                        
                  ENDIF                                                         
   70          CONTINUE                                                         
   60       CONTINUE                                                            
C                                                                               
            WPC(I) = WPC(I) - RNP*ERS                                           
            IF ( DABS(WPC(I)/A(I,JD)).LT.SNG ) THEN                             
               IERR = 3500                                                      
               RETURN                                                           
            ENDIF                                                               
            WPC(I) = 1.D0/WPC(I)                                                
   50    CONTINUE                                                               
C                                                                               
      ENDIF                                                                     
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
