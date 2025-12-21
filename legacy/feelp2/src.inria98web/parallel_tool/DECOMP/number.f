      SUBROUTINE NUMBER (KK,LG1,MANOD,NMAX,NSKAI,NKBU,KTI,NBB,
     $     NZOKU,NGRU,NRIL,NRGL,NTASI,NSUB,NWAKE,NNRIL,NNRGL,
     $     NNGRU,LG,KCO,LNODE,CODI,NSUU,IBNUM,NOSUB,
     $     WEI,NCOL)
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION CODI(MANOD),WEI(NKBU),NCOL(MANOD,2**(NSKAI-3))
      DIMENSION NRIL(0:MANOD),NWAKE(0:NKBU)
      DIMENSION NRGL(NMAX)
      DIMENSION NZOKU(MANOD),NGRU(MANOD)
      DIMENSION NBB(0:2**NSKAI,0:NSKAI),NSUB(MANOD)
      DIMENSION NTASI(MANOD)
      DIMENSION NNGRU(MANOD),LG(MANOD,2**(NSKAI-3))
      DIMENSION NNRIL(0:MANOD),NNRGL(NMAX)
      DIMENSION LNODE(NMAX,NSUU)
*
* ------
      IF (KCO.EQ.1) THEN
         DO 1129 I=1,NOSUB
            NGRU(I+NBB(LG1-1,KTI-1))=NTASI(I)
 1129    CONTINUE
         DO 1130 KW=1,KK
            WEI(KW)=CODI(KW)
 1130    CONTINUE
      ELSE 
         LTK=0
         GTK=0
         DO 1131 I=1,NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1)
            IF (NCOL(I,LG1).LT.IBNUM) THEN
               LTK=LTK+1
               LNODE(LTK,1)=NGRU(I+NBB(LG1-1,KTI-1))
            ELSE IF (NCOL(I,LG1).GT.IBNUM) THEN
               GTK=GTK+1
               LNODE(GTK,2)=NGRU(I+NBB(LG1-1,KTI-1))
            END IF
 1131    CONTINUE
*
            DO 1136 I=1,NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1)
               NNGRU(I)=NGRU(I+NBB(LG1-1,KTI-1))
 1136       CONTINUE
*
            NWAKE(1)=NWAKE(1)+LTK
            NWAKE(2)=NWAKE(2)+LTK+GTK
*
            DO 1132 I=1,LTK
               NGRU(I+NBB(LG1-1,KTI-1))=LNODE(I,1)
 1132       CONTINUE
            DO 1133 I=LTK+1,LTK+NOSUB
               NGRU(I+NBB(LG1-1,KTI-1))=NTASI(I-LTK)
 1133       CONTINUE
            DO 1134 I=LTK+NOSUB+1,LTK+NOSUB+GTK
               NGRU(I+NBB(LG1-1,KTI-1))=LNODE(I-LTK-NOSUB,2)
 1134       CONTINUE
*
         END IF
*  --------------   %%%%%%%%%% -----------------
*  --------%%%%%%%%%%%%%%%%%%%%%%%%%%% ----------------
*
*   -- determination of the group number to which NGRU(I)-th
*         node belongs and a new node number in the subgroup --
      IF (LG1.GE.2) THEN 
         SPMA=DBLE(NZOKU(NGRU(NBB(LG1-2,KTI-1)+1)))
         DO 666 I=NBB(LG1-2,KTI-1)+1,NBB(LG1-1,KTI-1)
            SPMA=DMAX1(SPMA,DBLE(NZOKU(NGRU(I))))
 666     CONTINUE
      ELSE 
         SPMA=0.D0
      END IF 
*
      DO 46 K=1,KK
         DO 47 I=NWAKE(K-1)+1,NWAKE(K)
         NZOKU(NGRU(I+NBB(LG1-1,KTI-1)))=K+INT(SPMA)
         NSUB(NGRU(I+NBB(LG1-1,KTI-1)))=I
 47   CONTINUE
 46   CONTINUE
*
      DO 772 K=1,KK
         NBB(K+INT(SPMA),KTI)=NBB(LG1-1,KTI-1)+NWAKE(K)
 772  CONTINUE
      NBB(0,KTI)=0
*
*     --- Determination !!!! ------
*
*
*   &&&  determination of "NRIL(I)" &&&
      NRIL(0)=1
      NNRIL(0)=1
      DO 60 I=NBB(LG1-1,KTI-1)+1,NBB(LG1,KTI-1)
         NTASI(NSUB(NNGRU(I-NBB(LG1-1,KTI-1))))=0
         DO 64 L2=NRIL(I-1),NRIL(I)-1
            IF (NZOKU(LG(NRGL(L2),LG1)).EQ.
     $           NZOKU(NNGRU(I-NBB(LG1-1,KTI-1)))) THEN
                  NTASI(NSUB(NNGRU(I-NBB(LG1-1,KTI-1))))=
     $       NTASI(NSUB(NNGRU(I-NBB(LG1-1,KTI-1))))+1
            END IF
 64      CONTINUE
 60   CONTINUE                                                         
      DO 50 I=1,NBB(LG1,KTI-1)-NBB(LG1-1,KTI-1)
         NNRIL(I+NBB(LG1-1,KTI-1))=NNRIL(I+NBB(LG1-1,KTI-1)-1)+NTASI(I)
 50   CONTINUE
*
*
      DO 730 I=NBB(LG1-1,KTI-1)+1,NBB(LG1,KTI-1)
         LNAG=0
         DO 740 L=NRIL(I-1),NRIL(I)-1
            IF (NZOKU(LG(NRGL(L),LG1)).EQ.
     $           NZOKU(NNGRU(I-NBB(LG1-1,KTI-1)))) THEN
            NNRGL(NNRIL(NBB(LG1-1,KTI-1)+
     $              NSUB(NNGRU(I-NBB(LG1-1,KTI-1)))-1)+LNAG)
     $       =NSUB(LG(NRGL(L),LG1))-NWAKE(NZOKU(LG(NRGL(L),LG1))
     $       -INT(SPMA)-1)
            LNAG=LNAG+1
            END IF 
 740     CONTINUE
 730  CONTINUE
*
      RETURN 
      END

