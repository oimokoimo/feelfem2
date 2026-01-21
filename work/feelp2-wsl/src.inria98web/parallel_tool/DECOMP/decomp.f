      SUBROUTINE DECOMP (NMESH,NMAX,N,A,ALP,BETA,EIG,V,W,B2,VEC,
     $   DI,BL,BU,BV,CM,SG,LEX,VI,IL,NGL,KAISUU,NKU,nzen,
     $     RSUM,
     $     nord,kti)
*     Calculation of eigenvector for  domain decomposition (MESH) 
*      ---------------------------------------    
*  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*  % NMESH (=NNODE): size of Laplacian matrix (number of nodes )   %        
*  % NMAX : sup(NEDGE)                                             %
*  % NEDGE : number of the edges of the Graph                      %
*  %  N: =sup(NNODE)=sup(NMESH)                                    %
*  % A(I) : I-th diagonal element (=IL(I)-IL(I-1))(I=1...NMESH)    %           
*  %  ALP(I): I-th diagonal element of tridiagonarized matrix      %
*  %  BETA(I): I-th subdiagonal element of tridiagonarized matrix  % 
*  %  EIG(I): I-th eigenvalue of -A+2*SMAX*I                       %
*  %  SMAX :=MAX(A(I))=MAX(IL(I)-IL(I-1))                          %
*  %   V(I,2):V_k and V_k-1 in Lanczos method                      %
*  %   W(I): cf Lanczos method                                     %
*  %   VEC(I,1): I-th element of eigenvecor                        %
*  %    KBUN : Number of partitioning steps of domain              %
*  %            (You have to input the data 'KBUN')                %         
*  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*    
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
*     / Preconditond Reverse Cuthill-Mckee ordering /
      dimension nord(n)
*
      dimension A(N),IL(0:N),NGL(NMAX)
      DIMENSION ALP(N),BETA(0:N)
      DIMENSION EIG(N)
      DIMENSION V(N,2)
      DIMENSION W(N)
      DIMENSION B2(N)
      DIMENSION VEC(N,1)     
*
      DIMENSION DI(N),BL(N),BU(N),BV(N),CM(N)
      DIMENSION SG(N)
      DIMENSION LEX(N)
*
      DIMENSION VI(N)
*
      nduil=il(0)
*
      PAI=DATAN(1.D0)*4.D0
      NEIG=1
*
*
      DO 300 K=1,NMESH
         IL(K)=IL(K)-il(0)+1
 300  CONTINUE
      IL(0)=1
*
      CALL DATA(A,IL,N,NMESH,SMAX)
*
      DO 220 I=1,N
         V(I,1)=0.D0
 220  CONTINUE
*
*  --- Change the initial vector ----
*     -----Precondtioned Reverse Cuthill-Mckee ordering ---
         do 8888 i=1,nmesh
            v(nord(i),2)=dble(i)-(dble(nmesh)+1.d0)/2.d0
 8888    continue
*
*
*  --- normalize 'V(I,2)' ---
      RNOR=0.D0
      DO I=1,NMESH
         RNOR=RNOR+V(I,2)**2
      END DO
      RNOR=DSQRT(RNOR)
*
      DO I=1,NMESH
         V(I,2)=V(I,2)/RNOR
      END DO
*  --- normalize 'V(I,2)' --
      HOEIG=0.D0
      KK=1
*
 242  IF (KK.GE.2) HOEIG=EIG(1)
         DO 5 JJ=0,N
            BETA(JJ)=0.D0
 5       CONTINUE
*
         DO 230 JJ=1,N
            ALP(JJ)=0.D0
 230     CONTINUE
*
       IF (KK.NE.1) THEN 
*            V(0,2)=0.D0
         DO 210 I=1,N
            V(I,2)=VEC(I,1)
            V(I,1)=0.D0
 210     CONTINUE
       END IF
* --- NRA .... 'NKU/NRA' -------
* --- NRA .... 'NKU/NRA' -------
*
       CALL LANC(A,NGL,IL,N,NMAX,V,ALP,
     $      BETA,W,
     $      K21,NKU,VI,NMESH)              
*      
       CALL BISEC(EIG,ALP,
     $      BETA,B2,N,NKU)   
*
       CALL INVITR (N,ALP,BETA,EIG,VEC,NEIG,NKU,V,
     $      A,W,K21,SG,DI,BL,BU,BV,CM,LEX,VI,IL,NMESH,
     $      NGL,NMAX)
*
*
       DO 314 I=1,NMESH
          W(I)=0.D0
 314   CONTINUE
*
       DO 324 I=1,NMESH
          W(I)=W(I)+A(I)*VEC(I,1)
 324   CONTINUE
*
       DO 334 I=1,NMESH
          DO 354 L=IL(I-1),IL(I)-1
             W(I)=W(I)+VEC(NGL(L),1)
 354      CONTINUE
 334   CONTINUE
*
       RSUM=0.D0
       DO 364 I=1,NMESH
          RSUM=RSUM+(W(I)-EIG(1)*VEC(I,1))**2
 364   CONTINUE
       RSUM=DSQRT(RSUM)
*
       if ((kk+1)*nku.ge.nzen) then
          GO TO 243
       ELSE
          IF (RSUM.LE.1.D-6) THEN
             GO TO 243
          ELSE
             KK=KK+1
             GO TO 242
          END IF
       END IF
*     
*
 243   TYOU=0.D0
       KAISUU=KK
*
      DO 578 I=0,NMESH
         IL(I)=IL(I)+nduil-1
 578  CONTINUE
*
      END
*
*      %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
      SUBROUTINE DATA(A,IL,N,NMESH,SMAX)
*
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* % NNODE     : number of nodes                                     %
* % NMESH (=NNODE): number of meshes = number of nodes              %
* % NGL(IL(I-1))...NGL(IL(I)-1): node numbers which are connected   %        
* %                   with I-th node                                %
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION A(N),IL(0:N)
*
*    &&& Let's set the diagonal elements &&& 
      DO 33 I=1,NMESH
         A(I)=DBLE(IL(I)-IL(I-1))
 33   CONTINUE
*
* %%%%%%%%%%%%%%%%%%&&&&&&&&&&&&
*     
*
*
*   &&& Let's find the value SMAX:=MAX(IL(I)-IL(I-1)) &&&& 
*   &&& Let's use "Gershgorin's theorem " &&&&
      SMAX=A(1)
      DO 508 I=2,NMESH 
         SMAX=DMAX1(SMAX,A(I))
 508  CONTINUE
*    
      DO 500 I=1,NMESH
         A(I)=A(I)*(-1.0D0)+2.D0*SMAX
 500  CONTINUE
*
      RETURN 
      END
*
*      --------  Lanczos Algorithm ----------
*     
      SUBROUTINE LANC(A,NGL,IL,N,NMAX,V,ALP,BETA,W,
     $     K21,NKU,VI,NMESH)         
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION A(N),V(N,2),ALP(N),BETA(0:N)
      DIMENSION W(N)
      DIMENSION NGL(2*NMAX),IL(0:N)
      DIMENSION VI(N)
*
      DO 430 I=1,NMESH
         VI(I)=V(I,2)
 430  CONTINUE
*    #############################  
*  
*
      DO 10 K=1,NKU
*
         DO 15 I=1,NMESH
            W(I)=0.0D0
 15      CONTINUE
*     &&&&&&&&&&&&& Matrix * Vector  &&&&&&&&&&&&&&
*   &&&   Let's calculate the diagonal element &&&
         DO 325 I=1,NMESH
            W(I)=W(I)+A(I)*V(I,2)
 325     CONTINUE
*
         DO 101 I=1,NMESH
          DO 25 L=IL(I-1),IL(I)-1
             W(I)=W(I)+V(NGL(L),2)
 25         CONTINUE
 101     CONTINUE
*
*    &&&&&&&&&&&&&&& Matrix * Vector &&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
*
         ALP(K)=0.D0
         DO 40 L=1,NMESH
            W(L)=W(L)-BETA(K-1)*V(L,1)
            ALP(K)=ALP(K)+W(L)*V(L,2)
 40      CONTINUE
*
*
         DO 60 L3=1,NMESH
            W(L3)=W(L3)-ALP(K)*V(L3,2)
 60      CONTINUE
*
*
         ALP2=0.D0          
         DO 63 L=1,NMESH
            ALP2=ALP2+W(L)/DSQRT(DBLE(NMESH))
 63      CONTINUE
         DO 64 L=1,NMESH
            W(L)=W(L)-ALP2/DSQRT(DBLE(NMESH))
 64      CONTINUE
*
*
         BETA(K)=0.D0
         DO 65 L3=1,NMESH
            BETA(K)=BETA(K)+W(L3)*W(L3)
 65      CONTINUE
*
         BETA(K)=DSQRT(BETA(K))
*
         DO 70 L4=1,NMESH
            V(L4,1)=V(L4,2)
            V(L4,2)=W(L4)/BETA(K)
*     &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
*
 70      CONTINUE
*     
 10   CONTINUE
*  
      BETA(NKU)=0.D0
*
 233  PLL=0.0D0
* 
      RETURN
      END
*
*   %%% Bisection Method %%%%%%
*
       SUBROUTINE BISEC(EIG,ALP,BETA,B2,N,NKU) 
*
       IMPLICIT REAL*8 (A-H,O-Z)
*
       DIMENSION EIG(N),ALP(N),BETA(0:N)
       DIMENSION B2(N)
       INTEGER IPASS
*
*
       EPS=1.0D-8
*
*
*  -- NLS : If NLS.LT.0 then NEIG smallest eigenvalues 
*           will be computed
*
       NLS=2
       NEIG=1
*
*
* --- set initial bound for eigenvalues ----
*
       BETA(NKU)=0.0D0
       RANGE=DABS(ALP(1))+DABS(BETA(1))
       DO 10 I=2,NKU
          RANGE1=DABS(ALP(I))+DABS(BETA(I))+DABS(BETA(I-1))
          IF (RANGE1.GT.RANGE) RANGE=RANGE1
 10    CONTINUE
*
*
       IF (NLS.LT.0) RANGE=RANGE*(-1.0D0)
*
       B2(1)=0.0D0
       DO 20 I=2,NKU
          B2(I)=BETA(I-1)**2
 20    CONTINUE
*
       EPSA=DABS(RANGE)*EPS
       SMALL=EPSA*EPS
*
       DO 30 I=1,NEIG
          EIG(I)=RANGE*(-1.0D0)
 30    CONTINUE
*
       B=RANGE
*
* --- start bisection method ---
*
       DO 40 K=1,NEIG
*
       A=EIG(K)
*
 11   CONTINUE
*
      C=5.0D-1*(A+B)
*
      IF ((DABS(B-A).GT.EPSA)
     $         .AND.(C.NE.A)
     $         .AND.(C.NE.B)) THEN
*
      NNEG=0
      G=1.0D0
      IPASS=0
*
      DO 50 I=1,NKU
*
         IF (IPASS.EQ.0) THEN 
            G=C-ALP(I)-B2(I)/G
         ELSE IF (IPASS.EQ.1) THEN
            IPASS=2
         ELSE 
            G=C-ALP(I)
            IPASS=0
         END IF
*
         IF (IPASS.EQ.0) THEN
            IF (G.LE.0.0D0) NNEG=NNEG+1
            IF (DABS(G).LE.DABS(B2(I)*SMALL))
     $           IPASS=1
         END IF
*
 50   CONTINUE
*     
      IF (NLS.LT.0) NNEG=NKU-NNEG
*    
      IF (NNEG.LT.K) THEN 
         B=C
      ELSE 
         A=C
      DO 60 I=K,MIN(NNEG,NEIG)
         EIG(I)=C
 60   CONTINUE
      END IF
*
      GO TO 11
*
      END IF
 40   CONTINUE
*
      RETURN 
      END
*
*
* ---   Start  Inverse  Iteration  Method    ----
*
      SUBROUTINE INVITR (N,ALP,BETA,EIG,VEC,NEIG,NKU,V,
     $      A,W,K21,SG,DI,BL,BU,BV,CM,LEX,VI,IL,NMESH,
     $      NGL,NMAX)
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      DIMENSION A(N),V(N,2),ALP(N),BETA(0:N)
      DIMENSION W(N)
      DIMENSION NGL(2*NMAX),IL(0:N)
*
      DIMENSION EIG(N)
      DIMENSION VEC(N,1)
      DIMENSION DI(N),BL(N),BU(N),BV(N),CM(N)
      DIMENSION SG(N)
      DIMENSION LEX(N)
      DIMENSION VI(N)
*
*     ****************************
*     ALP(I)... I-th diagonal element of triangle matrix
*     BETA(I)... I-th subdiagonal element 
*     EIG(I)... eigenvalues 
*     VEC(N,NEIG).... eigenvector 
*      --------
*     DI(I)... I-th diagonal EIG(I)-ALP(I)
*     BL(I)... I-th lower subdiagonal 
*     BU(I)... I-th upper subdiagonal 
*     BV(I)... I-th 2-nd upper diagonal 
*     CM(I)... I-th multiplier of Gauss elimination 
*      --------
*    &&&& location &&&&
*     BL(I-1) DI(I) BU(I)   BV(I)    0        0
*      0      BL(I) DI(I+1) BU(I+1) BV(I+1)   0
*      0       0    BL(I+1) DI(I+2) BU(I+2) BV(I+2)
*
      CALL MACEPS (EPSMAC)
      EPS=EPSMAC*DMAX1(DABS(EIG(1)),DABS(EIG(NEIG)))
      SMALL=EPSMAC*EPS
      CRAND=EPSMAC/1664501
*
         V(0,2)=0.D0
      DO 600 I=1,NMESH
         V(I,2)=VI(I)
         V(I,1)=0.D0
 600  CONTINUE
*
*   --- inverse iteration ----
*
      NEIG=1
      DO 10 K=1,NEIG
*
*     ---- set DI(I),BL(I),BU(I) ----
      DO 20 I=1,NKU
         DI(I)=EIG(K)-ALP(I)
         BL(I)=-BETA(I)
         BU(I)=-BETA(I)
 20   CONTINUE
*
*    ---- LU decomposition by Gauss elimination ---
*
      DO 30 I=1,NKU-1
         IF (DABS(DI(I)).GT.DABS(BL(I))) THEN
*
*     --- row not exchanged ----            
*
      LEX(I)=0
      IF (DABS(DI(I)).LT.SMALL) DI(I)=SMALL
      CM(I+1)=BL(I)/DI(I)
      DI(I+1)=DI(I+1)-CM(I+1)*BU(I)
      BV(I)=0.D0
*
      ELSE 
*
*    --- row exchanged -----
*
      LEX(I)=1
      CM(I+1)=DI(I)/BL(I)
      S=BU(I)
      DI(I)=BL(I)
      BU(I)=DI(I+1)
      BV(I)=BU(I+1)
      DI(I+1)=S-CM(I+1)*BU(I)
      BU(I+1)=-CM(I+1)*BV(I)
*
      END IF
 30   CONTINUE
      IF (DABS(DI(NKU)).LT.SMALL) DI(NKU)=SMALL
*
*   --- set initial data of inverse iteration ----
*
      IRAND=1
*
      DO 40 I=1,NKU
         IRAND=MOD(1229*IRAND+351750,1664501)
         VEC(I,K)=DBLE(IRAND)*CRAND
 40   CONTINUE
*
      IF (K.EQ.1) THEN 
         KM=K
      ELSE IF (DABS(EIG(K)-EIG(KM)).GT.EPS) THEN 
*
*    ---- non-degenerate eigenvalues ----
*
      KM=K
*
      ELSE 
*
*    ---- degenerate eigenvalues ----
*    (KM-th through K-th eigenvalues are degenerate i.e.
*     degeneracy=K-KM+1)
*           orthogonalize vectors 
      DO 50 I=KM,K-1
*
      T=0.D0
      DO 60 J=1,NKU
         T=T+VEC(J,K)*VEC(J,I)
 60   CONTINUE
*
      S=T
      DO 70 J=1,NKU
         VEC(J,K)=VEC(J,K)-S*VEC(J,I)
 70   CONTINUE
*
*
 50   CONTINUE
*
      END IF
*
*     ---- start inverse iteration ----
*
      LEND=K-KM+2
      IF (LEND.GT.5) LEND=5
*
      DO 80 L=1,LEND 
      IF ((L.NE.1).OR.(K.NE.KM)) THEN
*
*   ----forward substitution ----- LU decomposition ----
*
       DO 90 I=1,NKU-1
          IF (LEX(I).EQ.0) THEN 
             VEC(I+1,K)=VEC(I+1,K)-CM(I+1)*VEC(I,K)
          ELSE                                                       
             S=VEC(I,K)             
             VEC(I,K)=VEC(I+1,K)
             VEC(I+1,K)=S-CM(I+1)*VEC(I,K)
          END IF
 90    CONTINUE
       END IF
*
*    ----- backward substitution ---- LU decomposition ----
*
       DO 100 I=NKU,1,-1
          S=VEC(I,K)
          IF (I.LE.NKU-1) S=S-BU(I)*VEC(I+1,K)
          IF (I.LE.NKU-2) S=S-BV(I)*VEC(I+2,K)
          VEC(I,K)=S/DI(I)
 100   CONTINUE
*
*   --- normalize vector to avoid overflow ----
*
       T=0.D0
       DO 110 I=1,NKU
          T=T+VEC(I,K)**2
 110   CONTINUE
*
       S=0.D0
       IF (T.NE.0.D0) S=DSQRT(1.D0/T)
       DO 120 I=1,NKU
          VEC(I,K)=VEC(I,K)*S
 120   CONTINUE
 80    CONTINUE
 10    CONTINUE
*
*
*
       DO 820 I=1,NMESH
          SG(I)=0.D0
 820   CONTINUE
*
*
       DO 5 K1=0,NMESH
          BETA(K1)=0.0D0
 5     CONTINUE
*
       DO 7 I2=1,NMESH
          V(I2,1)=0.0D0
 7     CONTINUE
**
*
*
        DO 710 K=1,NKU
*
*
        DO 715 I=1,NMESH
           W(I)=0.0D0
 715    CONTINUE
*     &&&&&&&&&&&&& Matrix * Vector  &&&&&&&&&&&&&&
*      Let's calculate the diagonal element 
         DO 101 I=1,NMESH
               W(I)=W(I)+A(I)*V(I,2)
 101     CONTINUE
*
         DO 325 I=1,NMESH
            DO 425 L=IL(I-1),IL(I)-1
               W(I)=W(I)+V(NGL(L),2)
 425        CONTINUE
 325     CONTINUE
*
*    &&&&&&&&&&&&&&& Matrix * Vector &&&&&&&&&&&&&&&&&&&&&&&&&&&&& 
*     
*
        ALP(K)=0.D0
        DO 740 L=1,NMESH
           W(L)=W(L)-BETA(K-1)*V(L,1)
           ALP(K)=ALP(K)+W(L)*V(L,2)
 740    CONTINUE
*
*
        DO 760 L3=1,NMESH
           W(L3)=W(L3)-ALP(K)*V(L3,2)
 760    CONTINUE
*
*
        ALP2=0.D0          
        DO 763 L=1,NMESH
           ALP2=ALP2+W(L)/DSQRT(DBLE(NMESH))
 763    CONTINUE
        DO 764 L=1,NMESH
           W(L)=W(L)-ALP2/DSQRT(DBLE(NMESH))
 764    CONTINUE
*
*
        BETA(K)=0.D0
        DO 765 L3=1,NMESH
           BETA(K)=BETA(K)+W(L3)*W(L3)
 765    CONTINUE
*
        BETA(K)=DSQRT(BETA(K))
*
      DO 770 L4=1,NMESH
         V(L4,1)=V(L4,2)
         V(L4,2)=W(L4)/BETA(K)
 770  CONTINUE
*     
*
*
       DO 160 I=1,NMESH
          SG(I)=SG(I)+V(I,1)*vec(K,1)
 160   CONTINUE
*    
 710  CONTINUE
*
*
      DO 870 I=1,NMESH
         VEC(I,1)=SG(I)
 870  CONTINUE
*
      SPU=0.D0
      DO 880 I=1,NMESH
         SPU=SPU+VEC(I,1)**2
 880  CONTINUE
*
      DO 890 I=1,NMESH
         VEC(I,1)=VEC(I,1)/DSQRT(SPU)
 890  CONTINUE
*
*
*     ----    
 967  OPU=2.D0
      RETURN 
      END
*
*     ---machine epsilon no subroutine ---
*
      SUBROUTINE MACEPS (EPSMAC)
*   
*    --- Get machine epsilon in double precision ---
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      EPSMAC=1.D0
 100  CONTINUE
*
      IF (1.D0+EPSMAC.LE.1.D0) THEN 
         EPSMAC=2.D0*EPSMAC
      RETURN 
      END IF 
      EPSMAC=EPSMAC*5.D-1
      GO TO 100 
*
      RETURN 
      END
*




       

             

      









