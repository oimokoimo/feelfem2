      program main
*  ---- Let's make the data of the Graph -----
*
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
* % NMAX : (maximum number of the edges of the Graph)*2          %
* % NNODE : number  of the nodes of the Graph                    %
* % MANOD : sup(NNODE)                                           %
* % NEDGE : number of the edges of the Graph                     %
* % NGL( ) : IL(I-1)...IL(I)-1 ; node number which is connected  %
* %                         with the I-th node                   %
* % INGL( ) : if =0,"Nuritubushita!",else if ,"Nuritubushitenai!"%
* % NLC( ): Shiraberu ten no bangou                              %
* % NDLC( ) : NLC( ) ni tunagatteiru ten no bangou               %
* % NCOL(I,K) : connected component number to which I-th node    %  
* %             belongs in K-th subgroup                         %
* % KCO : number of connected components                         %
* % A(I) : I-th diagonal element of Laplacian matrix             %
* % VEC(I): I-th element of eigenvector                          %
* % NGRU(NBB(K-1)+1)...NGRU(NBB(K)):node in K-th group           %
* % NRGL(I,K): I-th node number in K-th group                    %      
* % NRIL(I,K):{NRGL(NRIL(I-1),K)...NRGL(NRIL(I)-1,K)} ===        %      
* %        === node number which are connected with I-th node    %
* %            in K-th group                                     %
* % LG(I,K): I-th node in K-th group is LG(I,K)-th node of       %
* %             the first step                                   %
* % NZOKU(NGRU(I)): NGRU(I)-th node in NZOKU(NGRU(I))-th group   %        
* % NSUB(NGRU(I)) : NGRU(I)-th node is the NSUB(NGRU(I))-th node %
* %             in the NZOKU(NGRU(I))-th group.                  %
* % NSETU : number of meshes in finite element method            %
* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
*
*      PARAMETER (NMAX=25*10000,MANOD=5*20000,NP=100,NKBU=3)
       PARAMETER (NMAX=60000,MANOD=30000,NP=100,NKBU=3)
       PARAMETER (NSUU=8,NSKAI=10)
*
      IMPLICIT REAL*8 (A-H,O-Z)
*
      CHARACTER*10 CHA
*
      DIMENSION NGL(NMAX)
      DIMENSION IL(0:MANOD)
      DIMENSION VEC(MANOD)
      DIMENSION WEI(NKBU)
      DIMENSION NGRU(MANOD),NRGL(NMAX),NRIL(0:MANOD)
      DIMENSION NZOKU(MANOD),LG(MANOD,2**(NSKAI-3))
*
      DIMENSION NBB(0:2**NSKAI,0:NSKAI)
*
*  -- &&& 'SUBROUTINE RENKE' ni taisuru hairetu sengen  &&& ---
      DIMENSION CODI(MANOD,2),LNODE(NMAX,NSUU)
      DIMENSION JA(0:MANOD*NSUU) 
*  -- &&& 'SUBROUTINE RENKE' ni taisuru hairetu sengen &&&---
*
*  -- &&& 'subroutine level' ni taisuru hairetu sengen &&&---     
      dimension nord(manod)
*  -- &&& 'subroutine level' ni taisuru hairetu sengen &&&---     
*
*  --%%% 'SUBROUTINE DECOMP' ni taisuru hairetu sengen  %%%---
      DIMENSION WORK(MANOD,20),V(MANOD,2)
      DIMENSION NWORK(0:NMAX,20)
*  --%%% 'SUBROUTINE DECOMP' no hairetu sengen syuuryou %%%---
*
*  --&&& 'SUBROUTINE GROUP' ni taisuru hairetu sengen &&& ---
      DIMENSION NNGRU(MANOD),NTASI(MANOD),NNRIL(0:MANOD)
      DIMENSION NNRGL(NMAX),NHEN(MANOD)
*  --&&& 'SUBROUTINE GROUP' no hairetu sengen syuryou &&& ---
*  --&&& 'SUBROUTINE NCOMP' ni taisuru hairetu sengen &&& ---
      DIMENSION NCOL(MANOD,2**(NSKAI-3)),NNCOL(MANOD)
      DIMENSION NKCO(2**(NSKAI-3))
*  --&&& ' SUBROUTINE NCOMP' ni taisuru sengen syuuryou &&& ---
*
*  --&&& 'SUBROUTINE INTER' ni tasuru hairetu sengen &&& ---
      DIMENSION NFACE((MANOD/2)+1,2**(NSKAI-3)),LMEN(2**(NSKAI-3))
      DIMENSION LSE(2**(NSKAI-3))
*  --&&& 'SUBROUTINE INTER' ni taisuru sengen syuuryou &&& ---
*
*  %%%    Calculation of CPUTIME %%%
cc      REAL*8 CPUTIME,time,tzero
*++++++++++++default 
*      nku=10
*      nzen=10
*++++++++++++default 
      IARGS = IARGC()
*
      do 345 I=1,IARGS
         CALL GETARG( I,CHA)
         if (i.eq.1) then
            READ (CHA,'(i)') NANKAI
*         else if (i.eq.2) then
*            READ (CHA,'(i)') NKU
*         else if (i.eq.3) then
*            READ (CHA,'(i)') NZEN
         end if
 345  CONTINUE
      KAZASA=1
      KK=2
*      NKU=10
      WEI(1)=1.D0
      WEI(2)=1.D0
*   --- Input number of the groups ---
*      WRITE (6,*) 'Input number of the groups KK='
*      READ (*,*) KK
*
      IF (KK.LT.1) THEN
         STOP 'KK DATA ERROR'
      END IF
*
*     
*
*
      OPEN (15,FILE='MESH.PARA')
      DO 2224 KG=1,KAZASA
*   --- Let's make the Data "NGL(I)" and "IL(I)" ----
*    %%% 'NGL(I)' and 'IL(I)' de 'SUBROUTINE HAJIME' %%%
*
*
*
         CALL HAJIME (MANOD,NMAX,NNODE,NSKAI,NSUU,NWORK,
     $        NSETU,NTRIA,NGL,IL,NRIL,NRGL,NBB,
     $        NZOKU,NGRU,LG,JA)
*
         nzen=50
         nku=50
*     Precondtioned reverse Cuthill-Mckee ordering 
         do i=1,nnode
            nord(i)=i
         end do
         call level (nmax,manod,nnode,ngl,il,nwork(1,1),
     $        nwork(1,2),nwork(1,3),nwork(1,4),
     $        nord,nwork(1,5),nwork(1,6))
*     Precondtioned reverse Cuthill-Mckee ordering 
*
         PAI=DATAN(1.D0)*4.D0
*
*      === NANKAI: times of decomposition ===
         DO 200 KTI=1,NANKAI
*
*     === NGRSU: number of the groups at KTI-1 time decomposition ===
            NGRSU=NZOKU(NGRU(NNODE))
            DO 210 LG1=1,NGRSU
*
*   --- Let's calculate number of connected components 
*               of the given Graph and 
*       a component number to which the given node belongs. ---
*
*
*     Precondtioned reverse Cuthill-Mckee ordering 
         do 1326 ibt=1,nbb(lg1,kti-1)-nbb(lg1-1,kti-1)
            nord(ibt)=ibt
 1326    continue
*     
         call level (nmax,manod,nbb(lg1,kti-1)-nbb(lg1-1,kti-1),
     $        nrgl(nril(nbb(lg1-1,kti-1))),
     $        nril(nbb(lg1-1,kti-1)),
     $        nwork(1,1),
     $        nwork(1,2),nwork(1,3),nwork(1,4),
     $        nord,nwork(1,5),nwork(1,6))
*     
*     Precondtioned reverse Cuthill-Mckee ordering                
               CALL SEIBUN (nosub,NSKAI,NMAX,MANOD,NRGL,NRIL,NCOL,
     $              NWORK(1,1),
     $      NWORK(1,2),NWORK(1,3),KCO,JA,CODI(1,1),LNODE(1,3),NBB,
     $  IBNUM,LG1,KTI,NWORK(1,4),NHEN,NWORK(1,5),NWORK(1,6))
* /--------------------------------------------/
*
*
*
*    &&& 'VEC(i)' de 'SUBROUTINE DECOMP' &&&
         CALL DECOMP (NOSUB,NMAX,MANOD,work(1,1),work(1,2),
     $           work(1,3),
     $           work(1,13),V,work(1,4),work(1,5),VEC,work(1,6),
     $      work(1,7),work(1,8),work(1,9),work(1,10),work(1,11),
     $      nwork(1,1),work(1,12),
     $      JA,LNODE(1,3),
     $       KAISUU,nku,
     $              nzen,
     $           RSUM,
     $           nord,kti)
*         stop 'decomp'
*    &&& The data 'Vec(i)' were made. &&&
*
*
*  %%% Let's decompose the given Graph by the Data 'Vec(i)' %%%
         IF (kco.EQ.1) THEN
            DO 1126 I=1,NOSUB
               NTASI(I)=NGRU(NBB(LG1-1,KTI-1)+I)
 1126       CONTINUE
            DO 1127 KW=1,KK
               CODI(KW,1)=WEI(KW)
 1127       CONTINUE
         ELSE
            DO 1128 I=1,NOSUB
               NTASI(I)=NGRU(NHEN(I)+NBB(LG1-1,KTI-1))
 1128       CONTINUE
         END IF
*         stop 'wakaran'
*
      CALL GROUP(MANOD,NP,NKBU,work(1,1),nwork(1,1),VEC,
     $        nwork(1,2),CODI(1,1),work(1,2),work(nkbu+2,2),
     $     work(2*nkbu+1,2),
     $     NTASI,NNGRU,
     $     nwork(1,3),KK,
     $     NOSUB) 
*
*  --------------   %%%%%%%%%% -----------------
*
         CALL NUMBER (KK,LG1,MANOD,NMAX,NSKAI,NKBU,KTI,NBB,
     $  NZOKU,NGRU,NRIL,NRGL,NTASI,NWORK(1,1),NWORK(1,3),NNRIL,NNRGL,
     $  NNGRU,LG,KCO,LNODE,CODI(1,1),NSUU,IBNUM,NOSUB,
     $  WEI,NCOL)
*
*
 210  CONTINUE
*
      DO 213 LG1=1,NGRSU
*
*     %%% determination of the "NRIL( )","NRGL( )" and
*          "LG(  ,  )"  at KTI-th decomposition %%%
*
         CALL SETTEI (MANOD,NNODE,NMAX,NSKAI,NRIL,NRGL,NNRIL,NNRGL,
     $        NBB(LG1-1,KTI-1),NBB(LG1,KTI-1),LG,NZOKU,
     $        NGRU)
*
*     %%% determination of the "NRIL( )","NRGL( )" and
*          "LG(  ,  )"  at KTI-th decomposition %%%
*
 213     CONTINUE
*   === End of decomposition of KTI-th time !!!!======
*
**********************************************
*
 200  CONTINUE
*
*  ++++ End of NANKAI-times decomposition !!!!! +++++
**********************************************************
*   --- Let's calculate number of connected components 
*               of the given Graph and 
*       a component number to which the given node belongs. ---

      DO 1650 LG1=1,NZOKU(NGRU(NNODE))
         NBEDGE=(NRIL(NBB(LG1,NANKAI))
     $        -NRIL(NBB(LG1-1,NANKAI)))/2
         NBNODE=NBB(LG1,NANKAI)-NBB(LG1-1,NANKAI)
*
         CALL NCOMP(NMAX,NBNODE,MANOD,NBEDGE,
     $        NRGL(NRIL(NBB(LG1-1,NANKAI))),
     $        NRIL(NBB(LG1-1,NANKAI)),NCOL(1,LG1),
     $        nwork(1,1),nwork(1,2),nwork(1,3),KCO,
     $        JA)
*
          NKCO(LG1)=KCO
*
 1650  CONTINUE
**********************************************************
*
*     ---- Let's calculate the nodes on the interface of 
*        the LG-th group -----
*
       CALL INTER (MANOD,NMAX,NNODE,NZOKU,NGL,IL,NFACE,LMEN,NSKAI
     $      ,NGRU,LSE,NUSUM)
*
*
*  --- 'Let's calculate number of the edges cut  NEUSUM!!! ' ---
*
      CALL EDGECUT (MANOD,NNODE,NMAX,NGL,IL,NFACE,LMEN,NSKAI,
     $     NZOKU,NGRU,NEUSUM)
*  --- 'Let's calculate number of the edges cut  NEUSUM !!! ' ---
*
*    ---- LG-th group ha ikutu-no group ni sessiteiru-ka-na? ---
*
      if (dble(nnode).gt.1.d+8) then
         stop 'format error'
      end if
*
      write (15,9001) nankai
      do 8001 i=1,(2**nankai+1)/6
         write (15,9011) (nbb(k,nankai),k=(i-1)*6,i*6-1)
 8001 continue
*     
      if (((2**nankai+1)/6)*6.le.2**nankai) then
         write (15,9011) (nbb(k,nankai),k=((2**nankai+1)/6)
     $        *6,2**nankai)
      end if
      do 8011 i=1,nnode/6
         write (15,9011) (ngru(k),k=(i-1)*6+1,i*6)
 8011 continue
*     
      if (((nnode/6)*6+1).le.nnode) then
         write (15,9011) (ngru(k),k=(nnode/6)*6+1,nnode)
      end if
*      
*
      do 20 i=1,nnode/6
         write (15,9011) (nzoku(k),k=(i-1)*6+1,i*6)
 20   continue
*
      if (((nnode/6)*6+1).le.nnode) then
         write (15,9011) (nzoku(k),k=(nnode/6)*6+1,nnode)
      end if
*
      do 30 i=1,(2**nankai)/6
         write (15,9011) (nkco(k),k=(i-1)*6+1,i*6)
 30   continue
*
      if (((2**nankai)/6)*6+1.le.2**nankai) then
         write (15,9011) (nkco(k),k=((2**nankai)/6)*6+1,2**nankai)
      end if
*
      write (15,9001) neusum
*+++++++++++++++++++++++++++++++++++++++++++++++++
*
 2224 CONTINUE
      CLOSE (15)
*
      OPEN (15,FILE='MESH.SUB')
      do 1201 i=1,nnode/6
         write (15,9011) (nzoku(k),k=(i-1)*6+1,i*6)
 1201 continue
*
      if (((nnode/6)*6+1).le.nnode) then
         write (15,9011) (nzoku(k),k=(nnode/6)*6+1,nnode)
      end if
      close (15)
 9001 FORMAT(I8)
 9011 FORMAT(6I8)
*
      END





