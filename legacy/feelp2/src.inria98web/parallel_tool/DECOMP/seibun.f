      SUBROUTINE SEIBUN (nosub,NSKAI,NMAX,MANOD,NRGL,NRIL,NCOL,
     $     INGL,NLC,NDLC,KCO,JA,CODI,LNODE,
     $     NBB,IBNUM,LG1,KTI,IBOUD,NHEN,NSUB,
     $     NWORK1)
*      
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION INGL(NMAX),NLC(NMAX),NDLC(NMAX)
      DIMENSION NRGL(NMAX),NRIL(0:MANOD)
      DIMENSION NCOL(MANOD,2**(NSKAI-1))
      DIMENSION JA(0:MANOD),CODI(2)
      DIMENSION LNODE(NMAX),NBB(0:2**NSKAI,0:NSKAI)
*
      DIMENSION IBOUD(MANOD),NSUB(MANOD)
      DIMENSION NHEN(MANOD)
      DIMENSION NWORK1(NMAX)
*   --- Let's calculate number of connected components 
*               of the given Graph and 
*       a component number to which the given node belongs. ---
*
         NBEDGE=(NRIL(NBB(LG1,KTI-1))
     $        -NRIL(NBB(LG1-1,KTI-1)))/2
         NBNODE=NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1)
         CALL NCOMP(NMAX,NBNODE,MANOD,NBEDGE,
     $        NRGL(NRIL(NBB(LG1-1,KTI-1))),
     $        NRIL(NBB(LG1-1,KTI-1)),NCOL(1,LG1),
     $        INGL,NLC,NDLC,KCO,
     $        NWORK1)
         CALL TAISYO (nosub,NMAX,MANOD,KCO,NBB,
     $  IBOUD,NHEN,NSUB,LNODE,NCOL,JA,
     $  CODI,NRIL,NBEDGE,NBNODE,NSKAI,
     $  LG1,KTI,NRGL,ibnum)
*
*         
         RETURN
         END
*
         SUBROUTINE TAISYO (nosub,NMAX,MANOD,KCO,NBB,
     $  IBOUD,NHEN,NSUB,LNODE,NCOL,JA,
     $  CODI,NRIL,NBEDGE,NBNODE,NSKAI,
     $  LG1,KTI,NRGL,ibnum)
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION NBB(0:2**NSKAI,0:NSKAI)
      DIMENSION NCOL(MANOD,2**(NSKAI-1)),CODI(2)
      DIMENSION NRIL(0:MANOD),IBOUD(MANOD)
      DIMENSION NHEN(MANOD)
      DIMENSION NSUB(MANOD),LNODE(NMAX),JA(0:MANOD)
*
      DIMENSION NRGL(NMAX)
*
*--- KCO : number of the connected components of the subgraph -
      if (kco.le.0) then
         stop 'KCO ZERO ERROR'
      end if
*
      IF (KCO.GE.2) THEN
*
      DO 2244 K=1,KCO
         IBOUD(K)=0
 2244 CONTINUE
*
*
      DO 2223 I=1,NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1)
         IBOUD(NCOL(I,LG1))=IBOUD(NCOL(I,LG1))+1
 2223 CONTINUE
*
*
      IKOSU=0
      IBNUM=1
      DO 2225 K=1,KCO
         IF ((IKOSU+IBOUD(K).GE.
     $        (NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1))/2)
     $   .AND.(IKOSU.LT.(NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1))/2)) THEN
            IKOSU=IKOSU+IBOUD(K)
         CODI(2)=DBLE(IKOSU-(NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1))/2)/
     $  DBLE(IBOUD(K))
*     ----
         IF (CODI(2).GT.1.D0) THEN
            STOP 'CODI(2) ERROR'
         END IF 
*     ----
            CODI(1)=1.D0-CODI(2)
            IBNUM=K
            GO TO 1190
         ELSE
            IKOSU=IKOSU+IBOUD(K)
         END IF
 2225 CONTINUE
*****************************
 1190 numb=0
      do 1121 i=1,nbb(LG1,KTI-1)-nbb(LG1-1,KTI-1)
      if (ncol(i,LG1).eq.ibnum) then
         numb=numb+1
         NHEN(numb)=i
         nsub(i)=numb
      else
         nsub(i)=0
      end if
 1121 continue
      ja(0)=1
      do 1112 k=1,numb
      ja(k)=nril(nbb(LG1-1,KTI-1)+NHEN(k))
     $        -nril(nbb(LG1-1,KTI-1)+NHEN(k)-1)
     $        +ja(k-1) 
 1112 continue 
      do 1113 k=1,numb
         do 1114 l=1,ja(k)-ja(k-1)
        lnode(l+ja(k-1)-1)=
     $           nsub(nrgl(l+nril(NHEN(k)+nbb(LG1-1,KTI-1)-1)-1))
        if (lnode(l+ja(k-1)-1).eq.0) then 
           stop 'lnode error'
        end if
 1114 continue
 1113 continue
***********************************
*
      NOSUB=NUMB
*
      else
      NOSUB=nbb(lg1,kti-1)-nbb(lg1-1,kti-1)
         ja(0)=1
         do 4326 i=1,nbb(lg1,kti-1)-nbb(lg1-1,kti-1)
         ja(i)=ja(i-1)+nril(i+nbb(lg1-1,kti-1))-
     $  nril(i+nbb(lg1-1,kti-1)-1)
 4326    continue
         do 4327 i=1,nbb(lg1,kti-1)-nbb(lg1-1,kti-1)
            do 4328 l=ja(i-1),ja(i)-1
               lnode(l)=nrgl(nril(nbb(lg1-1,kti-1))+l-1)
 4328       continue
 4327    continue
      end if
*
      RETURN 
      END


