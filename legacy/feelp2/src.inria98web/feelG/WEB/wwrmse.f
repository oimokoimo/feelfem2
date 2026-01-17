C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSE(A,LA,N,MA,JA,JD,IL,IU,SNG,IMDF,RNP,WPC,IERR)            
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSE                                                  
C                                                                               
C     PURPOSE : ILU DECOMPOSITION FOR NON-ZERO ELEMENTS (NILU).                 
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),IL(N),IU(N)                                  
C                                                                               
      DIMENSION WPC(N,MA)                                                       
C                                                                               
      DO 10 JJ=1,MA                                                             
         DO 20 I=1,N                                                            
            WPC(I,JJ) = A(I,JJ)                                                 
   20    CONTINUE                                                               
   10 CONTINUE                                                                  
C                                                                               
      IF ( IMDF.EQ.0 ) THEN                                                     
         DO 30 I=1,N                                                            
            DO 40 JJ=1,IL(I)                                                    
               J = JA(I,JJ)                                                     
               JUP = JD                                                         
C                                                                               
   50          CONTINUE                                                         
               IF ( JUP.GE.IU(J) ) THEN                                         
                  GOTO 40                                                       
               ELSE                                                             
                  JUP = JUP + 1                                                 
               ENDIF                                                            
C                                                                               
               IF ( JA(J,JUP).LT.I ) THEN                                       
                  JST = 1                                                       
                  JGL = IL(I)                                                   
               ELSE                                                             
                  JST = JD                                                      
                  JGL = IU(I)                                                   
               ENDIF                                                            
C                                                                               
               DO 60 JDW=JST,JGL                                                
                  IF ( JA(J,JUP).EQ.JA(I,JDW) ) THEN                            
                     WPC(I,JDW) = WPC(I,JDW) - WPC(I,JJ)*WPC(J,JUP)             
                     GOTO 50                                                    
                  ENDIF                                                         
   60          CONTINUE                                                         
               GOTO 50                                                          
   40       CONTINUE                                                            
C                                                                               
            DI = WPC(I,JD)                                                      
            IF ( DABS(DI/A(I,JD)).LT.SNG ) THEN                                 
               IERR = 1400                                                      
               DI = A(I,JD)*SNG                                                 
            ENDIF                                                               
            DI = 1.D0/DI                                                        
            WPC(I,JD) = DI                                                      
*VDIR NODEP                                                                     
            DO 70 JJ=JD+1,IU(I)                                                 
               WPC(I,JJ) = DI*WPC(I,JJ)                                         
   70       CONTINUE                                                            
   30    CONTINUE                                                               
C                                                                               
      ELSE                                                                      
C                                                                               
         DO 80 I=1,N                                                            
            ERS = 0.D0                                                          
            DO 90 JJ=1,IL(I)                                                    
               J = JA(I,JJ)                                                     
               JDW = JJ                                                         
               JUP = JD                                                         
C                                                                               
  100          CONTINUE                                                         
               IF ( JUP.GE.IU(J) ) THEN                                         
                  GOTO 90                                                       
               ELSE                                                             
                  JUP = JUP + 1                                                 
               ENDIF                                                            
C                                                                               
               IF ( JA(J,JUP).LT.I ) THEN                                       
                  JST = 1                                                       
                  JGL = IL(I)                                                   
               ELSE                                                             
                  JST = JD                                                      
                  JGL = IU(I)                                                   
               ENDIF                                                            
C                                                                               
               DO 110 JDW=JST,JGL                                               
                  IF ( JA(J,JUP).EQ.JA(I,JDW) ) THEN                            
                     WPC(I,JDW) = WPC(I,JDW) - WPC(I,JJ)*WPC(J,JUP)             
                     GOTO 100                                                   
                  ENDIF                                                         
  110          CONTINUE                                                         
               ERS = ERS + WPC(I,JJ)*WPC(J,JUP)                                 
               GOTO 100                                                         
   90       CONTINUE                                                            
C                                                                               
            DI = WPC(I,JD) - RNP*ERS                                            
            IF ( DABS(DI/A(I,JD)).LT.SNG ) THEN                                 
               IERR = 3500                                                      
               RETURN                                                           
            ENDIF                                                               
            DI = 1.D0/DI                                                        
            WPC(I,JD) = DI                                                      
*VDIR NODEP                                                                     
            DO 120 JJ=JD+1,IU(I)                                                
               WPC(I,JJ) = DI*WPC(I,JJ)                                         
  120       CONTINUE                                                            
   80    CONTINUE                                                               
C                                                                               
      ENDIF                                                                     
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
