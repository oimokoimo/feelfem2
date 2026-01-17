C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSS(A,LA,N,MA,JA,JD,F,U,                                    
     &                  ITRM,ITRO,IPRT,IPRC,INVF,EPS,RSD,RNP,                   
     &                  JL,JU,IL,IU,MPN,IHL,IHP,R,R0,P,E,H,W,WPC,               
     &                  OUT,IERR)                                               
C----------------------------------------------------------------------         
C                                                                               
C SUBROUTINE NAME : WWRMSS                                                      
C                                                                               
C PURPOSE :  SOLVE THE EQUATION BY CGS.                                         
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),F(N),U(N)                                    
C                                                                               
      DIMENSION IL(N),IU(N),IHL(N),IHP(N)                                       
C                                                                               
      DIMENSION R(N),R0(N),P(N),E(N),H(N),W(N),WPC(N,*),OUT(*)                  
C                                                                               
C                                                                               
C                                  CGS METHOD ITERATION                         
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
C                                            R = A * U                          
C                                                                               
      CALL WWRMSM(A,LA,N,MA,JA,JD,JL,JU,U,R)                                    
C                                                                               
C                                            R0 = F - R                         
C                                                                               
      DO 30 I=1,N                                                               
         R0(I) = F(I) - R(I)                                                    
   30 CONTINUE                                                                  
C                                                                               
C                                            P = (LU) INV * R0                  
C                                                                               
      IF ( IPRC.EQ.0 ) THEN                                                     
         CALL WWRMSJ(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,R0,P)                     
C                                                                               
      ELSEIF ( IPRC.EQ.1 ) THEN                                                 
         CALL WWRMSF(JA,LA,N,MA,JD,                                             
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,R0,P)                     
C                                                                               
      ELSE                                                                      
         CALL WWRMSU(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,RNP,WPC,R0,P)                 
      ENDIF                                                                     
C                                                                               
      DO 40 I=1,N                                                               
C                                            R = R0                             
         R(I) = R0(I)                                                           
C                                            E = R0                             
         E(I) = R0(I)                                                           
   40 CONTINUE                                                                  
C                                                                               
C                                            RIR = (R0,R0)                      
C                                                                               
      RIR = 0.D0                                                                
      DO 50 I=1,N                                                               
         RIR = RIR + R0(I)*R0(I)                                                
   50 CONTINUE                                                                  
C                                                                               
      IF ( DABS(RIR).LT.1.D-72 ) THEN                                           
         GOTO 2000                                                              
      ELSEIF ( DABS(RIR).GT.1.D72 ) THEN                                        
         IERR = 4100                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            RSD = SQRT(RIR)/FNRM               
C                                                                               
      RSD = DSQRT(RIR)/FNRM                                                     
C                                                                               
      IF ( RSD.LT.EPS ) GOTO 2000                                               
C                                                                               
      IF ( IPRT.GT.0 ) THEN                                                     
         IPRTC = 1                                                              
         OUT(IPRTC) = RSD                                                       
      ENDIF                                                                     
C                                                                               
C                                       ITERATION                               
C                                                                               
      ITR = 0                                                                   
C                                                                               
 1000 CONTINUE                                                                  
      ITR = ITR + 1                                                             
C                                                                               
C                                            H = A * P                          
C                                                                               
      CALL WWRMSM(A,LA,N,MA,JA,JD,JL,JU,P,H)                                    
C                                                                               
C                                            RIP = (H,R0)                       
C                                                                               
      RIP = 0.D0                                                                
      DO 60 I=1,N                                                               
         RIP = RIP + H(I)*R0(I)                                                 
   60 CONTINUE                                                                  
C                                                                               
      IF ( DABS(RIP).LT.1.D-72 ) THEN                                           
         IERR = 4300                                                            
         GOTO 2000                                                              
      ELSEIF ( DABS(RIP).GT.1.D72 ) THEN                                        
         IERR = 4310                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            ALP = RIR/RIP                      
C                                                                               
      ALP = RIR/RIP                                                             
C                                                                               
      DO 70 I=1,N                                                               
C                                            H = E - ALP*H                      
         H(I) = E(I) - ALP*H(I)                                                 
C                                            E = E + H                          
         E(I) = E(I) + H(I)                                                     
   70 CONTINUE                                                                  
C                                                                               
C                                            E = (LU) INV * E                   
C                                                                               
      IF ( IPRC.EQ.0 ) THEN                                                     
         CALL WWRMSJ(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,E,E)                      
C                                                                               
      ELSEIF ( IPRC.EQ.1 ) THEN                                                 
         CALL WWRMSF(JA,LA,N,MA,JD,                                             
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,E,E)                      
C                                                                               
      ELSE                                                                      
         CALL WWRMSU(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,RNP,WPC,E,E)                  
      ENDIF                                                                     
C                                                                               
C                                            W = A * E                          
C                                                                               
      CALL WWRMSM(A,LA,N,MA,JA,JD,JL,JU,E,W)                                    
C                                                                               
      DO 80 I=1,N                                                               
C                                            U = U + ALP*E                      
         U(I) = U(I) + ALP*E(I)                                                 
C                                            R = R - ALP*W                      
         R(I) = R(I) - ALP*W(I)                                                 
   80 CONTINUE                                                                  
C                                                                               
C                                            RSD = (R,R)                        
C                                                                               
      RSD = 0.D0                                                                
      DO 90 I=1,N                                                               
         RSD = RSD + R(I)*R(I)                                                  
   90 CONTINUE                                                                  
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
C                                            RIRO = RIR                         
C                                                                               
      RIRO = RIR                                                                
C                                                                               
C                                            RIR = (R,R0)                       
C                                                                               
      RIR = 0.D0                                                                
      DO 100 I=1,N                                                              
         RIR = RIR + R(I)*R0(I)                                                 
  100 CONTINUE                                                                  
C                                                                               
      IF ( DABS(RIR).LT.1.D-72 ) THEN                                           
         IERR = 4200                                                            
         GOTO 2000                                                              
      ELSEIF ( DABS(RIR).GT.1.D72 ) THEN                                        
         IERR = 4210                                                            
         GOTO 2000                                                              
      ENDIF                                                                     
C                                                                               
C                                            BET = RIR/RIRO                     
C                                                                               
      BET = RIR/RIRO                                                            
C                                                                               
      DO 110 I=1,N                                                              
C                                            E = R + BET*H                      
         E(I) = R(I) + BET*H(I)                                                 
C                                            W = E + BET*H                      
         W(I) = E(I) + BET*H(I)                                                 
  110 CONTINUE                                                                  
C                                                                               
C                                            W = (LU) INV * W                   
C                                                                               
      IF ( IPRC.EQ.0 ) THEN                                                     
         CALL WWRMSJ(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,W,W)                      
C                                                                               
      ELSEIF ( IPRC.EQ.1 ) THEN                                                 
         CALL WWRMSF(JA,LA,N,MA,JD,                                             
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,WPC,W,W)                      
C                                                                               
      ELSE                                                                      
         CALL WWRMSU(A,LA,N,MA,JA,JD,                                           
     &               INVF,JL,JU,IL,IU,MPN,IHL,IHP,RNP,WPC,W,W)                  
      ENDIF                                                                     
C                                                                               
C                                            P = W + BET*BET*P                  
C                                                                               
      DO 120 I=1,N                                                              
         P(I) = W(I) + BET*BET*P(I)                                             
  120 CONTINUE                                                                  
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
