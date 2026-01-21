C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSB(A,LA,N,MA,JA,JD,F,U,                                    
     &                  ITRM,ITRO,IPRT,IPRC,INVF,EPS,RSD,RNP,                   
     &                  JL,JU,IL,IU,MPN,IHL,IHP,R,RS,P,PS,W1,W2,WPC,            
     &                  OUT,IERR)                                               
C----------------------------------------------------------------------         
C                                                                               
C SUBROUTINE NAME : WWRMSB                                                      
C                                                                               
C PURPOSE :  SOLVE THE EQUATION BY BCG.                                         
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),F(N),U(N)                                    
C                                                                               
      DIMENSION IL(N),IU(N),IHL(N),IHP(N)                                       
C                                                                               
      DIMENSION R(N),RS(N),P(N),PS(N),W1(N),W2(N),WPC(N,*),OUT(*)               
C                                                                               
C                                  BCG METHOD ITERATION                         
C                                       INITIALIZE                              
C                                                                               
C                                            FNRM = (F,F)                       
C                                                                               
      FNRM = 0.D0                                                               
      DO 10 I=1,N                                                               
         FNRM = FNRM + F(I)*F(I)                                                
   10 CONTINUE                                                                  
C                                                                               
      IF ( FNRM.LT.1.D-72 ) THEN                                                
         IERR = 1100                                                            
         DO 20 I=1,N                                                            
            U(I) = 0.D0                                                         
   20    CONTINUE                                                               
         GOTO 2000                                                              
      ELSEIF ( FNRM.GT.1.D72 ) THEN                                             
         IERR = 4000                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            FNRM = SQRT(FNRM)                  
C                                                                               
      FNRM = DSQRT(FNRM)                                                        
C                                                                               
C                                            RS = A * U                         
C                                                                               
      CALL WWRMSM(A,LA,N,MA,JA,JD,JL,JU,U,RS)                                   
C                                                                               
      RSD = 0.D0                                                                
      DO 30 I=1,N                                                               
C                                            R = F - RS                         
         R(I) = F(I) - RS(I)                                                    
C                                            RSD = (R,R)                        
         RSD = RSD + R(I)*R(I)                                                  
   30 CONTINUE                                                                  
C                                                                               
      IF ( RSD.GT.1.D72 ) THEN                                                  
         IERR = 4100                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            RSD = SQRT(RSD)/FNRM               
C                                                                               
      RSD = DSQRT(RSD)/FNRM                                                     
C                                                                               
      IF ( RSD.LT.EPS ) GOTO 2000                                               
C                                                                               
      IF ( IPRT.GT.0 ) THEN                                                     
         IPRTC = 1                                                              
         OUT(IPRTC) = RSD                                                       
      ENDIF                                                                     
C                                                                               
C                                            P = (LU) INV * R                   
C                                                                               
      IF ( IPRC.EQ.0 ) THEN                                                     
         CALL WWRMSJ(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,R,P)                      
C                                                                               
      ELSEIF ( IPRC.EQ.1 ) THEN                                                 
         CALL WWRMSF(JA,LA,N,MA,JD,                                             
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,R,P)                      
C                                                                               
      ELSE                                                                      
         CALL WWRMSU(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,RNP,WPC,R,P)                  
      ENDIF                                                                     
C                                                                               
      DO 40 I=1,N                                                               
C                                            RS = R                             
         RS(I) = R(I)                                                           
C                                            PS = R                             
         PS(I) = R(I)                                                           
   40 CONTINUE                                                                  
C                                                                               
C                                            RIP = (R,RS)                       
C                                                                               
      RIP = 0.D0                                                                
      DO 50 I=1,N                                                               
         RIP = RIP + R(I)*RS(I)                                                 
   50 CONTINUE                                                                  
C                                                                               
      IF ( DABS(RIP).LT.1.D-72 ) THEN                                           
         IERR = 4200                                                            
         GOTO 2000                                                              
      ELSEIF ( DABS(RIP).GT.1.D72 ) THEN                                        
         IERR = 4210                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                      ITERATION                                
C                                                                               
      ITR = 0                                                                   
C                                                                               
 1000 CONTINUE                                                                  
      ITR = ITR + 1                                                             
C                                                                               
C                                            W1 = A * P                         
C                                                                               
      CALL WWRMSM(A,LA,N,MA,JA,JD,JL,JU,P,W1)                                   
C                                                                               
C                                            PIP = (W1,PS)                      
C                                                                               
      PIP = 0.D0                                                                
      DO 60 I=1,N                                                               
         PIP = PIP + W1(I)*PS(I)                                                
   60 CONTINUE                                                                  
C                                                                               
      IF ( DABS(PIP).LT.1.D-72 ) THEN                                           
         IERR = 4300                                                            
         GOTO 2000                                                              
      ELSEIF ( DABS(PIP).GT.1.D72 ) THEN                                        
         IERR = 4310                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            W2 = AT * PS                       
C                                                                               
      CALL WWRMSN(A,LA,N,MA,JA,IU,PS,W2)                                        
C                                                                               
C                                            W2 = (LU)T INV * W2                
C                                                                               
      IF ( IPRC.EQ.0) THEN                                                      
         CALL WWRMSK(A,LA,N,MA,JA,JD,IL,IU,WPC,W2,W2)                           
C                                                                               
      ELSEIF ( IPRC.EQ.1 ) THEN                                                 
         CALL WWRMSG(JA,LA,N,MA,JD,IL,IU,WPC,W2,W2)                             
C                                                                               
      ELSE                                                                      
         CALL WWRMSV(A,LA,N,MA,JA,JD,IL,IU,RNP,WPC,W2,W2)                       
      ENDIF                                                                     
C                                                                               
C                                            ALP = RIP/PIP                      
C                                                                               
      ALP = RIP/PIP                                                             
C                                                                               
      DO 70 I=1,N                                                               
C                                            U = U + ALP*P                      
         U(I) = U(I) + ALP*P(I)                                                 
C                                            R = R - ALP*W1                     
         R(I) = R(I) - ALP*W1(I)                                                
C                                            RS = RS - ALP*W2                   
         RS(I) = RS(I) - ALP*W2(I)                                              
   70 CONTINUE                                                                  
C                                                                               
C                                            RSD = (R,R)                        
C                                                                               
      RSD = 0.D0                                                                
      DO 80 I=1,N                                                               
         RSD = RSD + R(I)*R(I)                                                  
   80 CONTINUE                                                                  
C                                                                               
      IF ( RSD.GT.1.D72 ) THEN                                                  
         IERR = 4100                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            RSD = SQRT(RSD)/FNRM               
C                                                                               
      RSD = DSQRT(RSD)/FNRM                                                     
C                                                                               
C                                            TEST                               
C                                                                               
      IF ( IPRT.GT.0 .AND. MOD(ITR,IPRT).EQ.0 ) THEN                            
         IPRTC = IPRTC + 1                                                      
         OUT(IPRTC) = RSD                                                       
      ENDIF                                                                     
C                                                                               
      IF ( RSD.LT.EPS ) GOTO 2000                                               
C                                                                               
      IF ( ITR.GE.ITRM ) THEN                                                   
         IERR = 2000                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            W2 = (LU) INV * R                  
C                                                                               
      IF ( IPRC.EQ.0 ) THEN                                                     
         CALL WWRMSJ(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,R,W2)                     
C                                                                               
      ELSEIF ( IPRC.EQ.1 ) THEN                                                 
         CALL WWRMSF(JA,LA,N,MA,JD,                                             
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,R,W2)                     
C                                                                               
      ELSE                                                                      
         CALL WWRMSU(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,RNP,WPC,R,W2)                 
      ENDIF                                                                     
C                                                                               
C                                            RIPO = RIP                         
C                                                                               
      RIPO = RIP                                                                
C                                                                               
C                                            RIP = (R,RS)                       
C                                                                               
      RIP = 0.D0                                                                
      DO 90 I=1,N                                                               
         RIP = RIP + R(I)*RS(I)                                                 
   90 CONTINUE                                                                  
C                                                                               
      IF ( DABS(RIP).LT.1.D-72 ) THEN                                           
         IERR = 4200                                                            
         GOTO 2000                                                              
      ELSEIF ( DABS(RIP).GT.1.D72 ) THEN                                        
         IERR = 4210                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            BET = RIP/RIPO                     
C                                                                               
      BET = RIP/RIPO                                                            
C                                                                               
      DO 100 I=1,N                                                              
C                                            P = W2 + BET*P                     
         P(I) = W2(I) + BET*P(I)                                                
C                                            PS = RS + BET*PS                   
         PS(I) = RS(I) + BET*PS(I)                                              
  100 CONTINUE                                                                  
C                                                                               
C                                       NEXT LOOP                               
C                                                                               
      GOTO 1000                                                                 
C                                                                               
C                                       ENDING                                  
C                                                                               
 2000 CONTINUE                                                                  
C                                                                               
      IF ( IPRT.GT.0 ) THEN                                                     
         IPRTC = IPRTC + 1                                                      
         OUT(IPRTC) = RSD                                                       
      ENDIF                                                                     
C                                                                               
      ITRO = ITR                                                                
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
