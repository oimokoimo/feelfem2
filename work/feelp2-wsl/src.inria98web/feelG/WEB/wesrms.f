      SUBROUTINE WESRMS(A,LA,N,MA,JA,JD,F,U,IDS,IPR,RPR,IW,W,OUT,IERR)          
C----------------------------------------------------------------------         
C                                                                               
C SUBROUTINE NAME : WESRMS                                                      
C                                                                               
C PURPOSE :                                                                     
C                                                                               
C            THIS SUBROUTINE SOLVES NONSYMMETRIC RANDOM SPARCE LINEAR           
C       SYSTEMS BY THE PRECONDITIONED CONJUGATE GRADIENT SQUARED (PCGS)         
C       METHODS.  THE INCOMPLETE LU (ILU) FACTORIZATION PRECONDITIONER          
C       AND THE SYMMETRIC SOR (SSOR) MATRIX SPLITTING PRECONDITIONER            
C       ARE AVAILABLE FOR ACCELERATING CONVERGENCE RATE.                        
C                                                                               
C FORMAT :                                                                      
C                 - -- - -- -- -- -   --- --- ---                               
C     CALL WESRMS(A,LA,N,MA,JA,JD,F,U,IDS,IPR,RPR,IW,W,OUT,IERR)                
C                                   -     --- ---      --- ----                 
C                                                                               
C ARGUMENTS :                                                                   
C                                                                               
C  A(LA,MA) (REAL*8) ------------- COEFFICIENT MATRIX                           
C  JA(LA,MA) (INTEGER*4) --------- COLUMN NO. TABLE                             
C                                  JA(I,J) IS COLUMN NO. OF A(I,J) ELEMENT.     
C  N (INTEGER*4) ----------------- VECTOR SIZE                                  
C  JD (INTEGER*4) ---------------- A(*,JD),JA(*,JD) ARE DIAGONAL ELEM           
C  F(*) (REAL*8) ----------------- RIGHT-HAND SIDE'S VECTOR                     
C  U(*) (REAL*8) ----------------- SOLUTION VECTOR                              
C  IDS (INTEGER*4) --------------- DEFAULT SWITCH                               
C  IPR(10) (INTEGER*4) ----------- INTEGER PARAMETER                            
C                 IPR(1) (IN) .... MAXIMUM NUMBER OF ITERATION                  
C                 IPR(2) (OUT) ... ACTUAL NUMBER OF ITERATION                   
C                 IPR(3) (IN) .... INITIAL SELECTION SW.                        
C                 IPR(4) (IN) .... RESIDUAL NORM OUTPUT CONTROL                 
C                 IPR(5) (IN) .... PRECONDITIONER SELECTION SW.                 
C                 IPR(6) (IN) .... MODIFICATION ON/OFF SW.                      
C                 IPR(7) (IN) .... MODIFICATION PARAMETER DEF. SW.              
C                 IPR(8) (IN) .... INVERSION MODE SW.                           
C  RPR(10) (REAL*8) -------------- REAL PARAMETER                               
C                 RPR(1) (IN) .... ADMISSIBLE RESIDUAL NORM                     
C                 RPR(2) (OUT) ... FINAL RESIDUAL NORM                          
C                 RPR(3) (OUT) ... CPU TIME                                     
C                 RPR(4) (IN) .... SINGULARITY CHECK PARAMETER                  
C                 RPR(5) (IN) .... MODIFICATION PARAMETER                       
C  IW(N,5) (INTEGER*4) ----------- INTEGER WORK AREA                            
C  W(N,7 OR 6+MA) (REAL*8) ------- REAL WORK AREA                               
C                 W(*,1) ......... RESIDUAL VECTOR                              
C  OUT(*) (REAL*8) --------------- OUTPUT AREA FOR                              
C                                  INTERMEDIATE RESIDUAL NORMS                  
C  IERR (INTEGER*4) -------------- RETURN CODE                                  
C                 .EQ. 0 ......... NORMAL TERMINATION                           
C                 .GE. 1000 ...... WARNING: USEING DEFAULT VALUES               
C                 .GE. 3000 ...... FATAL ERROR: ABNORMAL TERMINATION            
C                                                                               
C                                                                               
C                      COPYRIGHT : ALL RIGHTS ARE RESERVED BY NEC.              
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION A(LA,MA),JA(LA,MA),F(N),U(N)                                    
C                                                                               
      DIMENSION IPR(10),RPR(10)                                                 
C                                                                               
      DIMENSION IW(N,5),W(N,*),OUT(*)                                           
C                                                                               
      DIMENSION THT(4)                                                          
C                                                                               
      DATA THT/0.D0 , 5.D-2 , 1.D-1 , 2.D-1/                                    
C                                                                               
      CALL CLOCK(C0)                                                            
C                                                                               
      IERR = 0                                                                  
C                                                                               
C                                      PARAMETER CHECK                          
C                                                                               
      CALL WWRMSP(IDS,IPR,RPR,N,IERR)                                           
C                                                                               
C                                      PARAMETER SET                            
C                                                                               
      ITRM = IPR(1)                                                             
      ITRO = IPR(2)                                                             
      INTF = IPR(3)                                                             
      IPRT = IPR(4)                                                             
      IPRC = IPR(5)                                                             
      IMDF = IPR(6)                                                             
      IATM = IPR(7)                                                             
      INVF = IPR(8)                                                             
C                                                                               
      EPS  = RPR(1)                                                             
      RSD  = RPR(2)                                                             
      CPT  = RPR(3)                                                             
      SNG  = RPR(4)                                                             
      RNP  = RPR(5)                                                             
C                                                                               
      JL   = IW(1,5)                                                            
      JU   = IW(2,5)                                                            
      MPN  = IW(3,5)                                                            
C                                                                               
C                                      DIAGONAL CHECK                           
C                                                                               
      CALL WWRMSD(A,LA,N,MA,JA,JD,IERR)                                         
C                                                                               
C                                      ERROR CHECK                              
C                                                                               
      IF ( IERR.GE.3000 ) THEN                                                  
         GOTO 400                                                               
      ELSEIF ( IERR.EQ.1000 ) THEN                                              
         U(1) = F(1)/A(1,JD)                                                    
         GOTO 400                                                               
      ENDIF                                                                     
C                                                                               
C                                      INITIAL SELECTION                        
C                                                                               
      IF ( INTF.EQ.1 ) THEN                                                     
         GOTO 100                                                               
      ELSEIF ( INTF.EQ.2 ) THEN                                                 
         GOTO 200                                                               
      ELSEIF ( INTF.EQ.3 ) THEN                                                 
         GOTO 300                                                               
      ENDIF                                                                     
C                                                                               
C                                      MAKE INITIAL VALUE                       
C                                                                               
      DO 10 I=1,N                                                               
         U(I) = F(I)/A(I,JD)                                                    
   10 CONTINUE                                                                  
C                                                                               
  100 CONTINUE                                                                  
C                                                                               
C                                      MAKE ROW'S LIST                          
C                                                                               
      CALL WWRMSR(A,LA,N,MA,JA,JD,JL,JU,IW(1,1),IW(1,2))                        
C                                                                               
C                                      MAKE HYPER PLANE'S LIST                  
C                                                                               
      IF ( INVF.EQ.0 ) THEN                                                     
         CALL WWRMSH(JA,LA,N,MA,JD,JL,JU,IW(1,1),IW(1,2),                       
     &                        INVF,MPN,IW(1,3),IW(1,4),IW(1,5))                 
         IF ( INVF.EQ.2 ) IERR = 1600                                           
C                                                                               
      ELSEIF ( INVF.EQ.1 ) THEN                                                 
         CALL WWRMSH(JA,LA,N,MA,JD,JL,JU,IW(1,1),IW(1,2),                       
     &                        INVF,MPN,IW(1,3),IW(1,4),IW(1,5))                 
         IF ( INVF.EQ.2 ) IERR = 3100                                           
      ENDIF                                                                     
C                                                                               
  200 CONTINUE                                                                  
C                                                                               
C                                      PRECONDITIONING                          
C                                                                               
      IF ( IPRC.EQ.0 .AND. IMDF.EQ.0 ) THEN                                     
         CALL WWRMSI(A,LA,N,MA,JA,JD,IW(1,1),IW(1,2),                           
     &                               SNG,0,RNP,W(1,7),IERR)                     
C                                                                               
      ELSEIF ( IPRC.EQ.0 .AND. IMDF.EQ.1 ) THEN                                 
         IF ( IATM.EQ.0 ) RNP = .95D0                                           
         DO 20 I=1,4                                                            
            IERM = 0                                                            
            RNP = RNP - THT(I)                                                  
            CALL WWRMSI(A,LA,N,MA,JA,JD,IW(1,1),IW(1,2),                        
     &                                  SNG,1,RNP,W(1,7),IERM)                  
            IF ( IERM.LT.3000 ) GOTO 300                                        
   20    CONTINUE                                                               
         IERR = 1500                                                            
         RNP = 0.D0                                                             
         CALL WWRMSI(A,LA,N,MA,JA,JD,IW(1,1),IW(1,2),                           
     &                               SNG,0,RNP,W(1,7),IERR)                     
C                                                                               
      ELSEIF ( IPRC.EQ.1 .AND. IMDF.EQ.0 ) THEN                                 
         CALL WWRMSE(A,LA,N,MA,JA,JD,IW(1,1),IW(1,2),                           
     &                               SNG,0,RNP,W(1,7),IERR)                     
C                                                                               
      ELSEIF ( IPRC.EQ.1 .AND. IMDF.EQ.1 ) THEN                                 
         IF ( IATM.EQ.0 ) RNP = .95D0                                           
         DO 30 I=1,4                                                            
            IERM = 0                                                            
            RNP = RNP - THT(I)                                                  
            CALL WWRMSE(A,LA,N,MA,JA,JD,IW(1,1),IW(1,2),                        
     &                                  SNG,1,RNP,W(1,7),IERM)                  
            IF ( IERM.LT.3000 ) GOTO 300                                        
   30    CONTINUE                                                               
         IERR = 1500                                                            
         RNP = 0.D0                                                             
         CALL WWRMSE(A,LA,N,MA,JA,JD,IW(1,1),IW(1,2),                           
     &                               SNG,0,RNP,W(1,7),IERR)                     
C                                                                               
      ELSEIF ( IPRC.EQ.2 ) THEN                                                 
         IF ( IATM.EQ.0 ) RNP = 1.6D0                                           
         DO 40 I=1,N                                                            
            W(I,7) = 1.D0/A(I,JD)                                               
   40    CONTINUE                                                               
      ENDIF                                                                     
C                                                                               
  300 CONTINUE                                                                  
C                                                                               
C                                      ERROR CHECK                              
C                                                                               
      IF ( IERR.GE.3000 ) GOTO 400                                              
C                                                                               
C                                      CGS' ITERATION                           
C                                                                               
      CALL WWRMSS(A,LA,N,MA,JA,JD,F,U,                                          
     &            ITRM,ITRO,IPRT,IPRC,INVF,EPS,RSD,RNP,                         
     &            JL,JU,IW(1,1),IW(1,2),MPN,IW(1,3),IW(1,4),                    
     &            W(1,1),W(1,2),W(1,3),W(1,4),W(1,5),W(1,6),W(1,7),             
     &            OUT,IERR)                                                     
C                                                                               
C                                      ENDING                                   
C                                                                               
  400 CONTINUE                                                                  
C                                                                               
      CALL CLOCK(C1)                                                            
C                                                                               
      CPT = C1 - C0                                                             
C                                                                               
      IW(1,5) = JL                                                              
      IW(2,5) = JU                                                              
      IW(3,5) = MPN                                                             
C                                                                               
      IPR(2) = ITRO                                                             
      IPR(8) = INVF                                                             
C                                                                               
      RPR(2) = RSD                                                              
      RPR(3) = CPT                                                              
      RPR(5) = RNP                                                              
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
