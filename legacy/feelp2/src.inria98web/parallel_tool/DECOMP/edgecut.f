      SUBROUTINE EDGECUT (MANOD,NNODE,NMAX,NGL,IL,NFACE,LMEN,NSKAI,
     $     NZOKU,NGRU,NEUSUM)
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION IL(0:MANOD),NGL(NMAX),NZOKU(MANOD),NGRU(MANOD)
      DIMENSION NFACE((MANOD/2)+1,2**(NSKAI-3)),LMEN(2**(NSKAI-3))
*
*  --- 'Let's calculate number of the edges cut  NEUSUM !!! ' ---
      NEUSUM=0
      DO 1651 LG1=1,NZOKU(NGRU(NNODE))
         DO 1661 LB1=1,LMEN(LG1)
            DO 1671 LC1=IL(NFACE(LB1,LG1)-1),IL(NFACE(LB1,LG1))-1
               IF (NZOKU(NGL(LC1)).NE.NZOKU(NFACE(LB1,LG1))) THEN
                  NEUSUM=NEUSUM+1
               END IF
 1671       CONTINUE
 1661    CONTINUE
 1651    CONTINUE
*
*    % ==== NEUSUM is divided by "2" =====%
*
         NEUSUM=NEUSUM/2
*
*    % ==== NEUSUM is divided by "2" =====%
*  --- 'Let's calculate number of the edges cut  NEUSUM !!! ' ---
*
         RETURN 
         END 














