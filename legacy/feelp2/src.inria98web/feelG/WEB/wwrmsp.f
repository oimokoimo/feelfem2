C                                                                               
C                                                                               
C                                                                               
      SUBROUTINE WWRMSP(IDS,IPR,RPR,N,IERR)                                     
C----------------------------------------------------------------------         
C                                                                               
C     SUBROUTINE NAME : WWRMSP                                                  
C                                                                               
C     PURPOSE : PARAMETER CHECK.                                                
C                                                                               
C----------------------------------------------------------------------         
C                                                                               
      IMPLICIT REAL*8(A-H,O-Z)                                                  
C                                                                               
      DIMENSION IPR(10),RPR(10)                                                 
C                                                                               
      IF ( IDS.LT.0 .OR. IDS.GT.4 ) THEN                                        
         IDS    = 0                                                             
         IERR   = 1200                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IDS.EQ.0 ) THEN                                                      
         IPR(1) = 5*INT(SQRT(REAL(N)))                                          
         IPR(3) = 0                                                             
         IPR(4) = 0                                                             
         IPR(5) = 0                                                             
         IPR(6) = 0                                                             
         IPR(7) = 0                                                             
         IPR(8) = 0                                                             
         RPR(1) = 1.D-12                                                        
         RPR(4) = 1.D-1                                                         
         RPR(5) = 0.D0                                                          
C                                                                               
      ELSEIF ( IDS.EQ.1 ) THEN                                                  
         IPR(3) = 0                                                             
         IPR(4) = 0                                                             
         IPR(5) = 0                                                             
         IPR(6) = 0                                                             
         IPR(7) = 0                                                             
         IPR(8) = 0                                                             
         RPR(4) = 1.D-1                                                         
         RPR(5) = 0.D0                                                          
C                                                                               
      ELSEIF ( IDS.EQ.2 ) THEN                                                  
         IPR(3) = 0                                                             
         IPR(4) = 0                                                             
         IPR(5) = 1                                                             
         IPR(6) = 0                                                             
         IPR(7) = 0                                                             
         IPR(8) = 0                                                             
         RPR(4) = 1.D-1                                                         
         RPR(5) = 0.D0                                                          
C                                                                               
      ELSEIF ( IDS.EQ.3 ) THEN                                                  
         IPR(3) = 0                                                             
         IPR(4) = 0                                                             
         IPR(5) = 2                                                             
         IPR(6) = 0                                                             
         IPR(7) = 0                                                             
         IPR(8) = 0                                                             
         RPR(4) = 1.D-1                                                         
         RPR(5) = 0.D0                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(1).LE.0 ) THEN                                                   
         IPR(1) = 5*INT(SQRT(REAL(N)))                                          
         IERR   = 1210                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(3).LT.0 .OR. IPR(3).GT.3 ) THEN                                  
         IPR(3) = 0                                                             
         IERR   = 1230                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(4).LT.0 ) THEN                                                   
         IPR(4) = 0                                                             
         IERR   = 1240                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(5).LT.0 .OR. IPR(5).GT.2 ) THEN                                  
         IPR(5) = 0                                                             
         IERR   = 1250                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(6).LT.0 .OR. IPR(6).GT.1 ) THEN                                  
         IPR(6) = 0                                                             
         IERR   = 1260                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(7).LT.0 .OR. IPR(7).GT.1 ) THEN                                  
         IPR(7) = 0                                                             
         IERR   = 1270                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(8).LT.0 .OR. IPR(8).GT.2 ) THEN                                  
         IPR(8) = 0                                                             
         IERR   = 1280                                                          
      ENDIF                                                                     
C                                                                               
      IF ( RPR(1).LT.1.D-72 ) THEN                                              
         RPR(1) = 1.D-12                                                        
         IERR   = 1310                                                          
      ENDIF                                                                     
C                                                                               
      IF ( RPR(4).LT.1.D-7 .OR. RPR(4).GT.1.D0 ) THEN                           
         RPR(4) = 1.D-1                                                         
         IERR   = 1340                                                          
      ENDIF                                                                     
C                                                                               
      IF ( IPR(5).EQ.0 .OR. IPR(5).EQ.1 ) THEN                                  
         IF ( RPR(5).GT.1.D0 ) THEN                                             
            RPR(5) = .95D0                                                      
            IERR   = 1350                                                       
         ENDIF                                                                  
C                                                                               
      ELSE                                                                      
         IF ( RPR(5).GT.2.D0 ) THEN                                             
            RPR(5) = 1.6D0                                                      
            IERR   = 1350                                                       
         ENDIF                                                                  
      ENDIF                                                                     
C                                                                               
      RETURN                                                                    
C                                                                               
      E  N  D                                                                   
