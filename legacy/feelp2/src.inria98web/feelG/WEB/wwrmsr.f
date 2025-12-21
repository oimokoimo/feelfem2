C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSR(A,LA,N,MA,JA,JD,JL,JU,IL,IU)                            
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSL                                                  
C                                                                               
C     PURPOSE : MAKE MATRIX ROW'S LIST.                                         
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),IL(N),IU(N)                                  
C                                                                               
      JL = 0                                                                    
      JU = JD                                                                   
C                                                                               
      DO 10 I=1,N                                                               
         IL(I) = 0                                                              
         IU(I) = JD                                                             
   10 CONTINUE                                                                  
C                                                                               
      DO 20 I=1,N                                                               
         ICEF = 0                                                               
         DO 30 JJ=1,JD-1                                                        
            IF ( ICEF.EQ.0 ) THEN                                               
               IF ( JA(I,JJ).GE.1 .AND. JA(I,JJ).LT.I ) THEN                    
                  IL(I) = JJ                                                    
               ELSE                                                             
                  ICEF = 1                                                      
                  JA(I,JJ) = I                                                  
                  A(I,JJ) = 0.D0                                                
               ENDIF                                                            
            ELSE                                                                
               JA(I,JJ) = I                                                     
               A(I,JJ) = 0.D0                                                   
            ENDIF                                                               
   30    CONTINUE                                                               
         JL = MAX(JL,IL(I))                                                     
C                                                                               
         ICEF = 0                                                               
         DO 40 JJ=JD+1,MA                                                       
            IF ( ICEF.EQ.0 ) THEN                                               
               IF ( JA(I,JJ).GT.I .AND. JA(I,JJ).LE.N ) THEN                    
                  IU(I) = JJ                                                    
               ELSE                                                             
                  ICEF = 1                                                      
                  JA(I,JJ) = I                                                  
                  A(I,JJ) = 0.D0                                                
               ENDIF                                                            
            ELSE                                                                
               JA(I,JJ) = I                                                     
               A(I,JJ) = 0.D0                                                   
            ENDIF                                                               
   40    CONTINUE                                                               
         JU = MAX(JU,IU(I))                                                     
   20 CONTINUE                                                                  
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
