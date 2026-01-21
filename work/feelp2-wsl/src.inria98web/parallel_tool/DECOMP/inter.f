      SUBROUTINE INTER (MANOD,NMAX,NNODE,NZOKU,NGL,
     $       IL,NFACE,LP,NSKAI,NGRU,LSE,NUSUM)
*  --- Let's output the node number on the interface. ----
*
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* % NMAX : maximum number of the edges of the Graph            %
* % NNODE : number of the nodes of the Graph                   %
* % MANOD : sup(NNODE)                                         %
* % NGL( ) : IL(I-1)...IL(I)-1 ;node number which is connected % 
* %                        with the I-th node                  %
* % NFACE(I,K): I-th node number on the interface which        %    
* %        belongs to K-th group                               %
* % LP(K) : number of the nodes on the interface               %
* %           in the K-th group                                %
* % NSKAI : sup (times of decomposition )                      %
* % NZOKU(I) :I-th node in "NZOKU(I)"-th group                 %
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       
*
      DIMENSION NZOKU(MANOD),NGL(2*NMAX),IL(0:MANOD)
      DIMENSION NFACE((MANOD/2)+1,2**(NSKAI-3))
      DIMENSION LP(2**(NSKAI-3)),NGRU(MANOD)
      DIMENSION LSE(2**(NSKAI-3))
*
      DO 1 K=1,2**(NSKAI-3)
      LP(K)=0
 1    CONTINUE
*
      DO 10 I=1,NNODE
         DO 20 L1=IL(I-1),IL(I)-1
            IF (NZOKU(NGL(L1)).NE.NZOKU(I)) THEN
               LP(NZOKU(I))=LP(NZOKU(I))+1
               NFACE(LP(NZOKU(I)),NZOKU(I))=I
               GO TO 10
            END IF
 20      CONTINUE
 10   CONTINUE
*
*  / calculate the summation of number of the nodes on the interface /
      NUSUM=0
      DO 651 LG1=1,NZOKU(NGRU(NNODE))
         NUSUM=NUSUM+LP(LG1)
 651  CONTINUE
*
*  / calculate the summation of number of the nodes on the interface /
*
*
      RETURN
      END

