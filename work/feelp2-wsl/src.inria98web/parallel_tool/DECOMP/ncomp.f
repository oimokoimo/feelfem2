      SUBROUTINE NCOMP(NMAX,NNODE,MANOD,NEDGE,NGL,IL,NCOL,
     $         INGL,NLC,NDLC,KCO,JA)
*  --- Let's calculate number of connected components  
*              of the given Graph and 
*     a component number to which the given node belongs. ---
*
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* % NMAX : maximum number of the edges of the subGraph         %   
* % NNODE : number of the nodes of the Graph                   %
* % MANOD : sup(NNODE)                                         %
* % NEDGE : number of the edges of the Graph                   %
* % NGL( ): IL(I-1)...IL(I)-1 ;node number which is connected  %
* %                       with the I-th node                   %
* % IL(I-1)...IL(I)-1 ; I-th bound                             %
* % INGL( ): if =0,"Nuritubushita!",else if,"Nuritubushitenai!"%  
* % NCOL( ) : connected component number to which the given    %
* %          node belongs                                      %
* % NLC( ): Shiraberu ten no bangou                            %
* % NDLC( ) : NLC( ) ni tunagatteiru ten no bangou             %
* % NCOL(I): connected component number to which I-th node     %
* %           belongs                                          %
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* 
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION NGL(2*NMAX),NCOL(MANOD)
      DIMENSION INGL(2*NMAX)
      DIMENSION IL(0:MANOD)
      DIMENSION NLC(MANOD),NDLC(MANOD)
      DIMENSION JA(MANOD)
*
      DO 900 I=1,NNODE
         JA(I)=1
 900  CONTINUE
*
         NDUIL=IL(0)
*
      DO 200 I=1,NNODE
         IL(I)=IL(I)-IL(0)+1
 200  CONTINUE
      IL(0)=1
*
      DO 10 K=1,2*NEDGE
         INGL(K)=NGL(K)
 10   CONTINUE
*
*  --- KCO-th connected component ----
*    -- KL step ----
*    --- set the initial connected component number 'KCO' ---  
      KCO=1
      KPHAN=1
      NLC(1)=1
      NCOL(1)=1
*
      JA(1)=0
*
*    ---- finish the setting of the initial condition ----
*
 2    NIHOW=0
*   
      DO 14 KP=1,KPHAN
      DO 20 I=IL(NLC(KP)-1),IL(NLC(KP))-1
         IF (JA(INGL(I)).NE.0) THEN
            NCOL(NGL(I))=KCO
            NIHOW=NIHOW+1
            NDLC(NIHOW)=INGL(I)
*
            JA(INGL(I))=0
         END IF 
 20   CONTINUE
 14   CONTINUE
*
*
*  --- determination of the next 'NLC(KP)' ----
* -- Change the component number 'KCO'(if KPHAN.EQ.0) or 
*      not (if KPHAN.NE.0)-----
*
      IF (NIHOW.NE.0) THEN
         DO 50 KK1=1,NIHOW
            NLC(KK1)=NDLC(KK1)
 50      CONTINUE
         KPHAN=NIHOW
         GO TO 2
      ELSE 
         DO 70 I=1,NNODE
            IF (JA(I).NE.0) THEN
               NLC(1)=I
               KCO=KCO+1
               NCOL(NLC(1))=KCO
               KPHAN=1
***
               JA(I)=0
               GO TO 2
            END IF
 70      CONTINUE
      END IF
*
      DO 850 I3=2,NNODE
         IF (IL(I3-1).EQ.IL(I3)) THEN
            KCO=KCO+1
            NCOL(I3)=KCO
         END IF
 850  CONTINUE
*  --- KCO ;number of connected components ---
*  --- I-th node belongs to NCOL(I)-th connected component.---
*
      DO 510 I=0,NNODE
         IL(I)=IL(I)+NDUIL-1
 510  CONTINUE
      RETURN
      END




            
         
         











