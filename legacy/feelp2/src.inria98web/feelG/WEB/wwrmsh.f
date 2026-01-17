C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSH(JA,LA,N,MA,JD,JL,JU,IL,IU,INVF,MPN,IHL,IHP,IW)          
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUINE NAME : WWRMSH                                                   
C                                                                               
C     PURPOSE : MAKE HYPER PLANE'S LIST.                                        
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION JA(LA,MA),IL(N),IU(N),IHL(N),IHP(N),IW(N)                       
C                                                                               
      INVF = 1                                                                  
C                                                                               
      MLE = MAX((JL+JU-JD+1)/2,2)                                               
C                                                                               
      IELN = 0                                                                  
      IHP(1) = 1                                                                
C                                                                               
      IELO = 0                                                                  
      IPN = 1                                                                   
C                                                                               
      DO 10 I=1,N                                                               
         IF ( IL(I).EQ.0 ) THEN                                                 
            IELN = IELN + 1                                                     
            IHL(IELN) = I                                                       
            IW(I) = N                                                           
         ELSE                                                                   
            IW(I) = 0                                                           
         ENDIF                                                                  
   10 CONTINUE                                                                  
C                                                                               
      IHP(2) = IELN + 1                                                         
C                                                                               
   20 CONTINUE                                                                  
      IWCN = 0                                                                  
      IMIN = N                                                                  
      IMAX = 1                                                                  
C                                                                               
      DO 30 II=IELO+1,IELN                                                      
         I = IHL(II)                                                            
         DO 40 JJ=JD+1,IU(I)                                                    
            IWCN = IWCN + 1                                                     
            J = JA(I,JJ)                                                        
            IW(J) = IW(J) + 1                                                   
            IF ( IWCN.LE.N/2 ) IHP(N/2+IWCN) = J                                
            IMIN = MIN(J,IMIN)                                                  
            IMAX = MAX(J,IMAX)                                                  
   40    CONTINUE                                                               
   30 CONTINUE                                                                  
C                                                                               
      IELO = IELN                                                               
      IPN = IPN + 1                                                             
C                                                                               
      IF ( IWCN.LE.N/2 ) THEN                                                   
*VDIR NOVECTOR                                                                  
         DO 60 II=1,IWCN                                                        
            I = IHP(N/2+II)                                                     
            IF ( IL(I).EQ.IW(I) ) THEN                                          
               IELN = IELN + 1                                                  
               IHL(IELN) = I                                                    
               IW(I) = N                                                        
            ENDIF                                                               
   60    CONTINUE                                                               
      ELSE                                                                      
         DO 70 I=IMIN,IMAX                                                      
            IF ( IL(I).EQ.IW(I) ) THEN                                          
               IELN = IELN + 1                                                  
               IHL(IELN) = I                                                    
               IW(I) = N                                                        
            ENDIF                                                               
   70    CONTINUE                                                               
      ENDIF                                                                     
C                                                                               
      IHP(IPN+1) = IELN + 1                                                     
C                                                                               
      IF ( IPN.GE.N/MLE ) THEN                                                  
         INVF = 2                                                               
         RETURN                                                                 
      ELSEIF ( IELN.LT.N .AND. IELN.GT.IELO ) THEN                              
         GOTO 20                                                                
      ELSEIF ( IELN.LT.N .AND. IELN.EQ.IELO ) THEN                              
         INVF = 2                                                               
         RETURN                                                                 
      ENDIF                                                                     
C                                                                               
      MPN = IPN                                                                 
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
