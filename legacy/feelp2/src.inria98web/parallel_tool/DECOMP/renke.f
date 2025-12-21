      SUBROUTINE RENKE (MANOD,NMAX,NSUU,IBOUD,NNODE,NMESH,
     $  LNODE,NTRIA,NGL,IL,JA)
*  --- Let's make the data "NGL" and  "IL" ! ---
*
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* % CODI(I,J) (J=1,2): (X-coordinate,Y-coordinate) of I-th node  %
* % IBOUD(I) : if 1,I-th node on the boundary                    %
* %            if 0,I-th node is an interior node.               %
* % NNODE   : number of nodes                                    % 
* % NMESH   : number of meshes                                   %
* % NTRIA : number of nodes which one mesh has                   %
* % NSUU : sup(NTRIA)                                            %
* % LNODE(I,J): J-th node of I-th mesh                           %
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION LNODE(MANOD,NSUU)
      DIMENSION NGL(2*NMAX),IL(0:MANOD)
      DIMENSION JA(MANOD,NSUU)
*
      OPEN (1,FILE='MESH.PLN')
      NMESH=0
*     -- Read number of nodes ---
      READ (1,*) NNODE
      if (NNODE.GT.MANOD) then
         stop ' number of node error'
      end if
      DO 1 I=1,NNODE
         READ (1,*) DUMMY1
 1    CONTINUE
*
*     --- Read number of domains ---
      READ (1,*) NDOMA
      if (NDOMA.le.0) then
         stop 'error NDOMA'
      end if
*
      DO 60 ND=1,NDOMA
*     --- Read number of meshes ---
         READ (1,*) NMESUB
         if (nmesh+NMESUB.gt.manod) then
            stop 'NUMBER OF MESHES'
         end if
*     --- Read number of nodes which one mesh has -----
         READ (1,*) NTRIA
         if (ntria.gt.nsuu) then
            stop 'ntria error'
         end if
*     --- Read NTRIA-nodes,NTRIA-meshes adjacent to one mesh, number of 
*     domain ,mesh number ---
         DO 801 I=NMESH+1,NMESH+NMESUB
            READ (1,*) (LNODE(I,J),J=1,NTRIA),
     $           (JA(I,J),J=1,NTRIA),NRYOI,IMESH
 801     CONTINUE
*     
         NMESH=NMESH+NMESUB
 60   CONTINUE
      IF (NMESH.GT.manod) THEN
         STOP 'NUMBER OF MESHES'
      END IF
      CLOSE (1)
*
      IL(0)=1
      DO 10 I=1,NMESH
         NSUM=0
         DO 20 J=1,NTRIA
            IF (JA(I,J).NE.0) THEN
               NSUM=NSUM+1
            END IF
 20      CONTINUE
         IL(I)=IL(I-1)+NSUM
 10   CONTINUE
*
      LL1=0
      DO 30 I=1,NMESH
         DO 40 J=1,NTRIA
            IF (JA(I,J).NE.0) THEN
               LL1=LL1+1
               NGL(LL1)=JA(I,J)
               if (LL1.gt.NMAX) then
                  stop 'nmax error'
               end if
            END IF
 40      CONTINUE
 30   CONTINUE
*
      RETURN 
      END 



