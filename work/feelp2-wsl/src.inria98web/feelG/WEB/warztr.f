C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WARZTR(A,NA,JA,IA,N,A2,LA,MA,JA2,JD,ISYM,IW,IERR)              
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WARZTR                                                  
C                                                                               
C     PURPOSE : DATA CONVERTER.                                                 
C                                                                               
C                 - -- -- -- -    -- --     -- ----                             
C     CALL WARZTR(A,NA,JA,IA,N,A2,LA,MA,JA2,JD,ISYM,IW,IERR)                    
C                              --       ---            ----                     
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(NA),JA(NA),IA(N+1)                                            
C                                                                               
      DIMENSION A2(LA,MA),JA2(LA,MA),IW(N,2)                                    
C                                                                               
      IERR = 0                                                                  
C                                                                               
      IF ( IA(N+1).NE.NA+1 ) THEN                                               
         IERR = 3100                                                            
         RETURN                                                                 
      ENDIF                                                                     
C                                                                               
      IF ( ISYM.NE.1 ) GOTO 10                                                  
C                                                                               
      DO 20 I=1,N                                                               
         IW(I,1) = 0                                                            
   20 CONTINUE                                                                  
C                                                                               
      DO 30 I=1,N                                                               
         DO 40 JJ=IA(I),IA(I+1)-1                                               
            J = JA(JJ)                                                          
            IW(J,1) = IW(J,1) + 1                                               
            JA2(J,IW(J,1)) = I                                                  
   40    CONTINUE                                                               
   30 CONTINUE                                                                  
C                                                                               
   10 CONTINUE                                                                  
C                                                                               
      DO 50 I=1,N                                                               
         JL = 0                                                                 
         JU = JD                                                                
C                                                                               
         IF ( ISYM.EQ.1 ) THEN                                                  
            DO 60 JJ=1,IW(I,1)                                                  
               IW(JJ,2) = JA2(I,JJ)                                             
   60       CONTINUE                                                            
         ENDIF                                                                  
C                                                                               
         DO 70 JJ=IA(I),IA(I+1)-1                                               
            J = JA(JJ)                                                          
C                                                                               
            IF ( J.GE.1 .AND. J.LT.I ) THEN                                     
               JL = JL + 1                                                      
               IF ( JL.GE.JD ) THEN                                             
                  IERR = 3200                                                   
                  RETURN                                                        
               ENDIF                                                            
               A2(I,JL) = A(JJ)                                                 
               JA2(I,JL) = JA(JJ)                                               
C                                                                               
            ELSEIF ( J.EQ.I ) THEN                                              
               A2(I,JD) = A(JJ)                                                 
               JA2(I,JD) = JA(JJ)                                               
C                                                                               
            ELSEIF ( J.GT.I .AND. J.LE.N ) THEN                                 
               JU = JU + 1                                                      
               IF ( JU.GT.MA ) THEN                                             
                  IERR = 3210                                                   
                  RETURN                                                        
               ENDIF                                                            
               A2(I,JU) = A(JJ)                                                 
               JA2(I,JU) = JA(JJ)                                               
C                                                                               
            ELSE                                                                
               IERR = 4000                                                      
               RETURN                                                           
            ENDIF                                                               
   70    CONTINUE                                                               
C                                                                               
         IF ( ISYM.NE.1 ) GOTO 80                                               
C                                                                               
         DO 90 KK=1,IW(I,1)                                                     
            K = IW(KK,2)                                                        
C                                                                               
            IF ( K.LT.I ) THEN                                                  
               JST = 1                                                          
               JGL = JL                                                         
            ELSE                                                                
               JST = JD                                                         
               JGL = JU                                                         
            ENDIF                                                               
C                                                                               
            DO 100 JJ=JST,JGL                                                   
               IF ( JA2(I,JJ).EQ.K ) GOTO 90                                    
  100       CONTINUE                                                            
C                                                                               
            IF ( K.LT.I ) THEN                                                  
               JL = JL + 1                                                      
               IF ( JL.GE.JD ) THEN                                             
                  IERR = 3200                                                   
                  RETURN                                                        
               ENDIF                                                            
               A2(I,JL) = 0.D0                                                  
               JA2(I,JL) = K                                                    
C                                                                               
            ELSE                                                                
               JU = JU + 1                                                      
               IF ( JU.GT.MA ) THEN                                             
                  IERR = 3210                                                   
                  RETURN                                                        
               ENDIF                                                            
               A2(I,JU) = 0.D0                                                  
               JA2(I,JU) = K                                                    
            ENDIF                                                               
   90    CONTINUE                                                               
C                                                                               
   80    CONTINUE                                                               
C                                                                               
         DO 110 JJ=JL+1,JD-1                                                    
            A2(I,JJ) = 0.D0                                                     
            JA2(I,JJ) = 0                                                       
  110    CONTINUE                                                               
C                                                                               
         DO 120 JJ=JU+1,MA                                                      
            A2(I,JJ) = 0.D0                                                     
            JA2(I,JJ) = 0                                                       
  120    CONTINUE                                                               
   50 CONTINUE                                                                  
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
