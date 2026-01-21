*   ---- The reverse Cuthill-Mckee algorithm  ------
      SUBROUTINE LEVEL (NMAX,MANOD,NNODE,NGL,IL,INGL,NLC,NDLC,
     $     ISMAX,NORD,NNORD,JA) 
*
      IMPLICIT REAL*8 (A-H,O-Z) 
*++++++++++++++++++++++++++++++++++++++++++++
*     
*   NMAX ... maximum of number of the edges
*   MANOD ... maximum of number of the nodes
*   NGL(K)... set of the nodes connected with L-th node 
*             (IL(L-1)<=K<=IL(L)-1)
*   NORD(I)... I-th ordering global node number 
*++++++++++++++++++++++++++++++++++++++++++++     
      DIMENSION NGL(NMAX),IL(0:MANOD),INGL(NMAX)
      DIMENSION NORD(MANOD),NLC(MANOD),NDLC(MANOD)
      DIMENSION ISMAX(MANOD),NNORD(MANOD)
      DIMENSION JA(MANOD)
      DO 71 I=1,NNODE
         JA(I)=1
 71   CONTINUE
*
      DO 111 I=1,NNODE
         IL(I)=IL(I)-IL(0)+1
 111  CONTINUE
      ILHO=IL(0)
      IL(0)=1
*
      NEDGE=(IL(NNODE)-IL(0))/2
*     ---Let's set the initial condition ---
      DO 1 K=1,2*NEDGE
         INGL(K)=NGL(K)
 1    CONTINUE
*
      KPHAN=1
      NLC(1)=1
      NSUM=1
*
      JA(NLC(1))=0
 2    NIHOW=0
*
      DO 10 KP=1,KPHAN
         NDGR=0
         DO 20 I=IL(NLC(KP)-1),IL(NLC(KP))-1
            IF (JA(INGL(I)).NE.0) THEN
               NDGR=NDGR+1
               ISMAX(NDGR)=INGL(I)
*
               JA(INGL(I))=0
            END IF 
 20      CONTINUE
         IF (NDGR.GE.2) THEN
            DO 30 L1=1,NDGR-1
               DO 40 K1=L1+1,NDGR
                  IF (IL(ISMAX(K1))-IL(ISMAX(K1)-1)
     $            .LT.IL(ISMAX(L1))-IL(ISMAX(L1)-1)) THEN
                     IS=ISMAX(L1)
                     ISMAX(L1)=ISMAX(K1)
                     ISMAX(K1)=IS
                  END IF
 40            CONTINUE
 30         CONTINUE
         END IF
         DO 50 I1=1,NDGR
            NNORD(NSUM+I1)=ISMAX(I1)
            NDLC(I1+NIHOW)=ISMAX(I1)
 50      CONTINUE
         NIHOW=NIHOW+NDGR
         NSUM=NSUM+NDGR
 10   CONTINUE
*      
      IF (NIHOW.NE.0) THEN
         DO 60 KK1=1,NIHOW
            NLC(KK1)=NDLC(KK1)
 60      CONTINUE
         KPHAN=NIHOW
         GO TO 2
      ELSE 
         DO 70 I=1,2*NEDGE
            IF (JA(INGL(I)).NE.0) THEN
               NLC(1)=INGL(I)
               KPHAN=1
               NSUM=NSUM+1
               NNORD(NSUM)=INGL(I)
*
               JA(INGL(I))=0
               GO TO 2
            END IF
 70      CONTINUE
      END IF
*      
      NOKORI=0
      DO 850 I3=2,NNODE
         IF (IL(I3-1).EQ.IL(I3)) THEN
            NOKORI=NOKORI+1
            NNORD(NSUM+NOKORI)=I3
         END IF
 850  CONTINUE
*
*   %%%% The Reverse Cuthill-McKee ordering %%%%
*
      DO 771 I=1,NNODE
         JA(I)=1
 771  CONTINUE
*
      DO 11 K=1,2*NEDGE
         INGL(K)=NGL(K)
 11   CONTINUE
*
      KPHAN=1
      NLC(1)=NNORD(NNODE)
      NNORD(1)=NNORD(NNODE)
*  ***
      LVL=0
*  ***
      NSUM=1
      JA(NNORD(1))=0
*
 12    NIHOW=0
*
       LVL=LVL+1
*
      DO 110 KP=1,KPHAN
         NDGR=0
*  ***
*  ***
         DO 120 I=IL(NLC(KP)-1),IL(NLC(KP))-1
            IF (JA(INGL(I)).NE.0) THEN
               NDGR=NDGR+1
               ISMAX(NDGR)=INGL(I)
*
               JA(INGL(I))=0
            END IF 
 120     CONTINUE
         IF (NDGR.GE.2) THEN
            DO 130 L1=1,NDGR-1
               DO 140 K1=L1+1,NDGR
                  IF (IL(ISMAX(K1))-IL(ISMAX(K1)-1)
     $            .LT.IL(ISMAX(L1))-IL(ISMAX(L1)-1)) THEN
                     IS=ISMAX(L1)
                     ISMAX(L1)=ISMAX(K1)
                     ISMAX(K1)=IS
                  END IF
 140           CONTINUE
 130         CONTINUE
         END IF
         DO 150 I1=1,NDGR
            NNORD(NSUM+I1)=ISMAX(I1)
            NDLC(I1+NIHOW)=ISMAX(I1)
 150      CONTINUE
         NIHOW=NIHOW+NDGR
         NSUM=NSUM+NDGR
 110   CONTINUE
*      
      IF (NIHOW.NE.0) THEN
         DO 160 KK1=1,NIHOW
            NLC(KK1)=NDLC(KK1)
 160      CONTINUE
         KPHAN=NIHOW
         GO TO 12
      ELSE 
*
         DO 170 I=1,2*NEDGE        
            IF (JA(INGL(I)).NE.0) THEN 
               NLC(1)=INGL(I)      
               KPHAN=1             
               NSUM=NSUM+1         
               NNORD(NSUM)=INGL(I) 
*
               JA(INGL(I))=0
               GO TO 12
            END IF
 170      CONTINUE
      END IF
*
      NOKORI=0
      DO 1850 I3=1,NNODE
         IF ((IL(I3-1).EQ.IL(I3)).AND.(I3.NE.NNORD(1))) THEN
            NOKORI=NOKORI+1
            NNORD(NSUM+NOKORI)=I3
         END IF
 1850 CONTINUE
*
      DO 180 I=1,NNODE
         ISMAX(I)=NORD(NNORD(I))
 180  CONTINUE
*
      DO 183 I=1,nnode
         ja(nnord(i))=i
 183  CONTINUE

      DO 190 I=1,NNODE
         NORD(I)=ISMAX(I)
 190  CONTINUE
*
      IL(0)=ILHO
      DO 204 I=1,NNODE
         IL(I)=ILHO+(IL(I)-1)
 204  CONTINUE
*
      RETURN 
      END

