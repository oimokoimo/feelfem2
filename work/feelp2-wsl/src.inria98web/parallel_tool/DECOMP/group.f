      SUBROUTINE GROUP(NMAX,NP,NKBU,BUN,NA,VEC,LBU,W,GAM,SAL,SBE,NGRU,
     $      NNGRU,NBB,KK,NNODE) 
*    --- Let's divide the nodes of the Graph 
*           into the KK (=2 or 3) groups ----
*    
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* %  KK    : number of the groups                               %
* %  NKBU  : sup (KK)                                           %
* %  W(KK) : weight                                             %
* %  NMAX  : sup(NNODE)                                         %
* %  NNODE : number of the nodes of the graph                   %
* %  VEC(I): value on the I-th node (I=1...NNODE)               %
* %  ALP   : Min(Vec(i))                                        %
* %  BETA  : Max(Vec(i))                                        %
* %  NPP   : number of the intervals in [ALP,BETA]              %
* %  NP    : sup(NPP)                                           %
* %  NA(I) : number of the nodes which belong in the            %
* %       I-th interval                                         %
* %  LBU(I) : interval number which the I-th division point     %
* %  BUN(I) :=ALP+(DBLE(L)/DBLE(NP))*(BETA-ALP)                 %
* %  NBB(I) : number of the nodes in the groups (1+....+I-th )  % 
* %  NGRU( ): node number which belongs to each group           %
* %  GAM(I) : I-th point for dividing the nodes                 %
* %         into KK groups                                      %
* % [SAL(I),SBE(I)]: I-th interval for the bisection method     %
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
*
      IMPLICIT REAL*8 (A-H,O-Z) 
*
      DIMENSION BUN(0:NP),NA(NP)
      DIMENSION VEC(NMAX)
      DIMENSION LBU(NKBU)
      DIMENSION W(NKBU)
      DIMENSION GAM(0:NKBU),SAL(NKBU-1),SBE(NKBU-1)
      DIMENSION NGRU(NMAX)
*
      DIMENSION NNGRU(NMAX)
* 
      DIMENSION NBB(0:NKBU)
*
*   --- setting NBB(0) ---
      NBB(0)=0
*%%%   --- setting NPP ---
      NPP=100
*
*
      ALP=VEC(1)
      BETA=VEC(1) 
      DO 10 I=2,NNODE
         ALP=DMIN1(ALP,VEC(I)) 
         BETA=DMAX1(BETA,VEC(I))
 10   CONTINUE
*
*    --- Let's set GAM(0)-----
      GAM(0)=ALP
*
*    --- determination of the division points ---
*
      DO 20 L=0,NPP
         BUN(L)=ALP+(DBLE(L)/DBLE(NPP))*(BETA-ALP)
 20   CONTINUE
*
*   --- determination of NA(K)  -----
*
      DO 30 K=1,NPP
         NA(K)=0
 30   CONTINUE
*
      DO 40 K=1,NPP
      DO 50 I=1,NNODE
       IF ((VEC(I).GE.BUN(K-1)).AND.(VEC(I).LT.BUN(K))) THEN
          NA(K)=NA(K)+1
       END IF
 50   CONTINUE
 40   CONTINUE
*
      DO 56 I=1,NNODE
        IF (VEC(I).EQ.BETA) THEN 
           NA(NPP)=NA(NPP)+1
        END IF 
 56   CONTINUE
*
*
      DO 60 K=1,KK-1
       LBU(K)=1
 60   CONTINUE
*
      DO 65 K=2,KK
         W(K)=W(K)+W(K-1)
 65   CONTINUE
*
*    --- determination of the K-th division point ---
      NB1=0
      DO 70 K=1,KK-1
         DO 80 L=LBU(K),NPP
            IF ((NB1.LT.DBLE(NNODE)*(W(K)/W(KK))).AND.
     $      (NB1+NA(L).GE.DBLE(NNODE)*(W(K)/W(KK)))) THEN
         SAL(K)=BUN(L-1)
         SBE(K)=BUN(L)
         LBU(K)=L
         LBU(K+1)=L
         NBB(K)=NB1+NA(L)
*          GO TO 80
          GO TO 81
            ELSE 
             NB1=NB1+NA(L)
          END IF
 80    CONTINUE
 81    PRI=0.D0
 70   CONTINUE
*
*    --- Let's use the bisection method for 
*          the determination of the K-th division point ---
      DO 901 L=1,KK-1
         GAM(L)=SBE(L)
 901  CONTINUE
*
      DO 90 K=1,KK-1
 93      YTR=0.D0
*         %%%% Kensaku of NBB(K) %%%%
            NBB(K)=0
            DO 100 I=1,NNODE
               IF (VEC(I).LT.GAM(K)) THEN 
                  NBB(K)=NBB(K)+1
               END IF
 100        CONTINUE
       IF (DABS(SBE(K)-SAL(K)).GT.1.D-4*(BETA-ALP)) THEN 
            IF (DBLE(NBB(K))-DBLE(NNODE)*(W(K)/W(KK)).GT.
     $         DBLE(NNODE)*1.D-2) THEN
            SBE(K)=GAM(K)
            GAM(K)=5.D-1*(SAL(K)+GAM(K))
              GO TO 93
            ELSE IF (DBLE(NNODE)*(W(K)/W(KK))-DBLE(NBB(K)).GT.
     $             DBLE(NNODE)*1.D-2) THEN
            SAL(K)=GAM(K)
            GAM(K)=5.D-1*(GAM(K)+SBE(K))
             GO TO 93
*
            END IF
         END IF
 90   CONTINUE
*     %%% Output the element numbers of KK groups  %%%
      LNUB=1
      DO 110 K=1,KK-1
         DO 120 I=1,NNODE
            IF ((VEC(I).GE.GAM(K-1)).AND.
     $         (VEC(I).LT.GAM(K))) THEN
               NNGRU(LNUB)=NGRU(I)
               LNUB=LNUB+1
            END IF
 120     CONTINUE
 110  CONTINUE
*
      DO 140 I=1,NNODE
         IF (VEC(I).GE.GAM(KK-1)) THEN
         NNGRU(LNUB)=NGRU(I)
         LNUB=LNUB+1
         END IF
 140  CONTINUE
*
      NBB(KK)=NNODE
*
      DO 210 I=1,NNODE
         NHEN=NGRU(I)
         NGRU(I)=NNGRU(I)
         NNGRU(I)=NHEN
 210  CONTINUE
*
* &&&& W( ) : weight wo modosu &&&&&
      DO 142 K=KK,2,-1
         W(K)=W(K)-W(K-1)
 142  CONTINUE
* &&&& W( ) : weight wo modosu &&&&&
*
*
      RETURN 
      END

               



