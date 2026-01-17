      SUBROUTINE SETTEI (MANOD,NNODE,NMAX,NSKAI,NRIL,NRGL,NNRIL,
     $     NNRGL,NBBR,NBBL,LG,NZOKU,
     $     NGRU)
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION NRIL(0:MANOD),NNRIL(0:MANOD)
      DIMENSION NRGL(NMAX),NNRGL(NMAX)
*
      DIMENSION NZOKU(MANOD),LG(MANOD,2**(NSKAI-3))
      DIMENSION NGRU(MANOD)
*     
         DO 742 I=NBBR+1,NBBL
            NRIL(I)=NNRIL(I)
 742     CONTINUE
*   &&& "NRIL(I)" were determined &&&
*
         DO 752 I=NBBR+1,NBBL
            DO 762 L=NRIL(I-1),NRIL(I)-1
               NRGL(L)=NNRGL(L)
 762        CONTINUE
 752     CONTINUE
*     %%%%  "NRGL( )" were determined !!!!! %%%%
*
*
*  --- determination of "LG(I,K)" ---
         LG(1,NZOKU(NGRU(NBBR+1)))
     $    =NGRU(NBBR+1)
         NGBUN=NBBR
         DO 100 L=NBBR+2,NBBL
            IF (NZOKU(NGRU(L)).NE.NZOKU(NGRU(L-1))) THEN
               NGBUN=L-1
               LG(L-NGBUN,NZOKU(NGRU(L)))=NGRU(L)
            ELSE 
              LG(L-NGBUN,NZOKU(NGRU(L)))=NGRU(L)
            END IF
 100     CONTINUE
*  --- "LG(I,K)" were determined ---
*
*
         RETURN
         END

         
