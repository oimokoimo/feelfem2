      subroutine p_msbicg_stab (rank,npesum,U,B,neq_sub,naisum,
     $     naieq,ninner,nintotal,IT,A,JA,MJ,w,eps,IPM,
     $     srb,nsrequ,nsendnum,nrecvnum,
     $     nsesum,nresum,rnorm,nsendlist,nrecvlist,
     $     nsendkaz,nrecvkaz,nsendtable,nrecvtable,
     $     JDP,KTI,feelpara)
* 
c---------------------------------------------------
c     Scaled BiCGSTAB method (two dimensinal array)
c---------------------------------------------------
*
      implicit real*8 (a-h,o-z)
      include 'mpi.incl'
c
      integer rank
*
      real*4 feelpara(*)
*
      dimension nsendlist(npesum),nrecvlist(npesum)
      dimension nsendkaz(npesum),nrecvkaz(npesum)
      dimension nsendtable(npesum),nrecvtable(npesum)      
c     
      dimension IPM(2)
c
      dimension B(neq_sub)
*
      dimension w(neq_sub,8)
*
      dimension naieq(naisum)
*
      dimension ninner(*)
*
      dimension A(neq_sub,MJ),JA(neq_sub,MJ)
      dimension U(neq_sub)
*
*     ---- send_buffer(srb(i),i=1,nsesum) & 
*     receive buffer(srb(i),i=nsesum+1,nsesum+nresum) ----
      dimension srb(nsesum+nresum)
*
      dimension nsrequ(nsesum+nresum)
*
c---------------------------------------
c   Set the value 'KTI'
c---------------------------------------
      KTI = IT
c
c-----------------------------------------------
c     Calculation of "JL,JR"
c                 JL : bandwidth of lower part
c                 JR : bandwidth of upper part
c-----------------------------------------------
      call f_alloc (np_il,'solve_il',neq_sub,0)
      call f_alloc (np_ir,'solve_ir',neq_sub,0)
c
      call p_get_band (feelpara(np_il),feelpara(np_ir),neq_sub,
     $     A,JA,MJ,JDP,JL,JR)
c
c--------------------------------------
c     Initialization of w(*,8) ( = 0)
c--------------------------------
      do 610 i=1,8
         do 620 j=1,neq_sub
            w(j,i)=0.d0
 620     continue
 610  continue      
c
c------------------------------------
*     Bi-CGSTAB method
c-------------------------------------------------------
c     Calculation of L^(2) norm of the right hand vector
c-------------------------------------------------------
c     
      bsahen=0.d0
      bsahenint=0.d0
      bsahennai=0.d0
      do 300 i=1,naisum
         bsahennai=bsahennai+B(naieq(i))*B(naieq(i))
 300  continue
*
      if (nrecvlist(rank+1).eq.1) then
         do 310 i=1,nintotal
            bsahenint=bsahenint+B(ninner(i))*B(ninner(i))
 310     continue
      end if
      bsahen=bsahenint+bsahennai
*
*c
*c
      call mpi_allreduce(bsahen,bsahen,1,
     $     mpi_double_precision,mpi_sum,mpi_comm_world,
     $     ierror)               
*
*---------------------------
* check of the right side
*--------------------------
*
*------------------------------------
*     Get machine epsilon in double precision 
*------------------------------------
c
      epsmac=1.d-36
c
*
      if (bsahen.lt.epsmac) then
         do 500 i=1,neq_sub
            U(i)=0.d0
 500     continue
      end if
c
c-------------------------------------------
c     Setting of the initial vector U(i)
c             : U = B * (DIAG(A))^(-1)
c--------------------------------------------
c
c--------------------------------------------     
c     IPM(1)=0 : Scaled BiCGSTAB method
c--------------------------------------------
c
      if (IPM(1).eq.0) then
         do 200 i=1,neq_sub
            w(i,7)=A(i,JDP)
 200     continue
c
c------------------------------------------------------
c     summation of the values on the interface
c------------------------------------------------------
c
         call data_plus (rank,neq_sub,w(1,7),srb,
     $        nsrequ,
     $        nsendnum,nrecvnum,npesum,
     $        nsesum,nresum,nsendkaz,nrecvkaz,nsendlist,
     $        nrecvlist,nsendtable,nrecvtable)
c
c-----------------------------------------
c     check diagonal component of A(*,*) 
c-----------------------------------------
         do 210 i=1,neq_sub
            if (dabs(w(i,7)).eq.epsmac) then
               stop ' diagonal element too small '
            end if
            U(i)=B(i)/w(i,7)
 210     continue
      end if
c
c------------------------------------
c   Initialization of w(i,1) ( = 0 )
c-------------------------------------
c
      do 29 i=1,neq_sub
         w(i,1)=0.d0
 29   continue
c
c----------------------------------------
c     w(i,1):residual vector r_k(i)
c----------------------------------------
c     Upper Element 
c      
      do 10 j=1,JL
         do 20 i=1,neq_sub
            w(i,1)=w(i,1)+A(i,j)*U(JA(i,j))
 20      continue
 10   continue
c
c--------------------------------------
c     Diagonal Element
c--------------------------------------
c     
      do 11 i=1,neq_sub
         w(i,1)=w(i,1)+A(i,JDP)*U(JA(i,JDP))
 11   continue
c
c-----------------------------------------------
c    Lower Element
c-----------------------------------------------
c
      do 12 j=JDP+1,JR
         do 22 i=1,neq_sub
            w(i,1)=w(i,1)+A(i,j)*U(JA(i,j))
 22      continue
 12   continue
c
c-----------------------------------------------------------
c Summation of the residual vector 'w(*,1)' on the interface
c-----------------------------------------------------------
c
      call data_plus (rank,neq_sub,w(1,1),srb,
     $     nsrequ,
     $     nsendnum,nrecvnum,npesum,
     $     nsesum,nresum,nsendkaz,nrecvkaz,nsendlist,
     $     nrecvlist,nsendtable,nrecvtable)
c
c--------------------------------------------
c Initial residual vector ' w(*,8) '
c--------------------------------------------
c
      do 30 i=1,neq_sub
         w(i,1)=B(i)-w(i,1)
         w(i,8)=w(i,1)
 30   continue
c
c------------------------------------
c     Calculation of inner product 
c------------------------------------
c    
c    
      rnai=0.d0
      do 40 i=1,naisum
         rnai=rnai+w(naieq(i),1)*w(naieq(i),1)
 40   continue
c
c
      rint=0.d0
      if (nrecvlist(rank+1).eq.1) then
         do 50 i=1,nintotal
            rint=rint+w(ninner(i),1)*w(ninner(i),1)
 50      continue
      end if
c
      rtotal=0.d0
      rtotal=rint+rnai
c
      call mpi_reduce(rtotal,rtotal,1,
     $     mpi_double_precision,mpi_sum,0,mpi_comm_world,
     $     ierror)
c
c---------------------------------------------
c     Convergence (about the initial vector)
c---------------------------------------------
c
      if (rank.eq.0) then
         rnorm=rtotal/bsahen
         if (rnorm.le.eps) then
            mflg=1
         else
            mflg=0
         end if
      end if
c
      call mpi_bcast(mflg,1,mpi_integer,0,mpi_comm_world,
     $     ierror)
c
      if (mflg.eq.1) return      
c
c---------------------------------------------------
c     Setting of the initial vector 
c                                  :p_k(i)=w(i,2)
c                                  :A*p_k(i)=w(i,3)
c---------------------------------------------------
      do 60 i=1,neq_sub
         w(i,2)=0.d0
         w(i,3)=0.d0
 60   continue
*
      alpha=1.d0
      omega=1.d0
c
c-----------------------------------
c     rprerotal = (r_0,r_{-1})
c-----------------------------------
      rpretotal=1.d0
c
      do 100 k=1,IT
c
c------------------------------------
c Calculation of 'beta'
c-----------------------------------     
c
c     
         if (rank.eq.0) then
            if (dabs((rpretotal*omega)).le.epsmac) then
               write (6,*) 'Iteration count,
     $              (r_0,r_{i-2}),omega_{i-1}',
     $              k,rpretotal,omega
               stop '(r_0,r_{i-2})*omega_{i-1} too small'
            end if
            beta=(rtotal*alpha)/(rpretotal*omega)
         end if
c
         call mpi_bcast(beta,1,mpi_double_precision,0,
     $        mpi_comm_world,ierror)
c
c
c     w(i,2)=p_k
         do 110 i=1,neq_sub
            w(i,3)=(w(i,1)-beta*omega*w(i,3))/w(i,7)
            w(i,2)=w(i,3)+beta*w(i,2)
 110     continue
c
c----------------------------------------
c  Calculation of 'alpha'
c----------------------------------------
c--------------------------
c     w(i,3)=A*p_k
c--------------------------
         do 120 i=1,neq_sub
            w(i,3)=0.d0
 120     continue
c---------------------------
c    Upper Element
c---------------------------
c    
         do 130 j=1,JL
            do 140 i=1,neq_sub
               w(i,3)=w(i,3)+A(i,j)*w(JA(i,j),2)
 140        continue
 130     continue
c----------------------------------
c    Diagonal Element
c----------------------------------
         do 131 i=1,neq_sub
            w(i,3)=w(i,3)+A(i,JDP)*w(JA(i,JDP),2)
 131     continue
c----------------------------------
c    Lower Element
c---------------------------------
         do 132 j=JDP+1,JR
            do 142 i=1,neq_sub
               w(i,3)=w(i,3)+A(i,j)*w(JA(i,j),2)
 142        continue
 132     continue
c--------------------------------------
c Summation of w(*,3) on the interface
c--------------------------------------
c     
         call data_plus (rank,neq_sub,w(1,3),srb,
     $        nsrequ,
     $        nsendnum,nrecvnum,npesum,
     $        nsesum,nresum,nsendkaz,nrecvkaz,nsendlist,
     $        nrecvlist,nsendtable,nrecvtable)
c------------------------------------
c   Calculation of the inner product
c------------------------------------
         raseki=0.d0
c  
         do 150 i=1,naisum
            raseki=raseki+w(naieq(i),8)*w(naieq(i),3)
 150     continue
c     
         riseki=0.d0
         if (nrecvlist(rank+1).eq.1) then
            do 160 i=1,nintotal
               riseki=riseki+w(ninner(i),8)*w(ninner(i),3)
 160        continue
         end if
         rseki=0.d0
         rseki=riseki+raseki
c
         call mpi_reduce(rseki,rseki,1,
     $        mpi_double_precision,mpi_sum,0,mpi_comm_world,
     $        ierror)         
c
         if (rank.eq.0) then
            if (dabs(rseki).le.epsmac) then
               write (6,*) '(r_0,Ap_i),epsmac',rseki,epsmac
               write (6,*) ' Iteration count = ',k
               stop ' (r_0,Ap_i) too small '
            end if
            alpha=rtotal/rseki
            rpretotal=rtotal
         end if
c
         call mpi_bcast(alpha,1,mpi_double_precision,0,
     $        mpi_comm_world,ierror)
c
         do 170 i=1,neq_sub
            w(i,4)=w(i,1)-alpha*w(i,3)
            w(i,5)=w(i,4)/w(i,7)
 170     continue
c------------------------------
c  Calculation of 'omega'
c------------------------------
c     w(i,6)=A*s_k
c------------------------------
         do 180 i=1,neq_sub
            w(i,6)=0.d0
 180     continue
c------------------------------
c Upper Element
c------------------------------ 
         do 190 j=1,JL
            do 700 i=1,neq_sub
               w(i,6)=w(i,6)+A(i,j)*w(JA(i,j),5)
 700        continue
 190     continue
c--------------------------------
c Diagonal Element
c--------------------------------
         do 191 i=1,neq_sub
            w(i,6)=w(i,6)+A(i,JDP)*w(JA(i,JDP),5)
 191     continue
c----------------------------------
c Lower Element    
c-----------------------------------
         do 192 j=JDP+1,JR
            do 702 i=1,neq_sub
               w(i,6)=w(i,6)+A(i,j)*w(JA(i,j),5)
 702        continue
 192     continue
c---------------------------------------
c Summation of w(*,6) on the interface
c---------------------------------------
c
         call data_plus (rank,neq_sub,w(1,6),srb,
     $        nsrequ,
     $        nsendnum,nrecvnum,npesum,
     $        nsesum,nresum,nsendkaz,nrecvkaz,nsendlist,
     $        nrecvlist,nsendtable,nrecvtable)
c
         ramseki=0.d0
         do 710 i=1,naisum
            ramseki=ramseki+w(naieq(i),6)*w(naieq(i),6)
 710     continue
*
         rimseki=0.d0
         if (nrecvlist(rank+1).eq.1) then
            do 720 i=1,nintotal
               rimseki=rimseki+w(ninner(i),6)*w(ninner(i),6)
 720        continue
         end if
*     
         rmseki=0.d0
         rmseki=ramseki+rimseki
c
         call mpi_reduce(rmseki,rmseki,1,
     $        mpi_double_precision,mpi_sum,0,mpi_comm_world,
     $        ierror)         
c
         ranseki=0.d0
         rinseki=0.d0
         rnseki=0.d0
         do 730 i=1,naisum
            ranseki=ranseki+w(naieq(i),4)*w(naieq(i),6)
 730     continue
c
         if (nrecvlist(rank+1).eq.1) then
            do 740 i=1,nintotal
               rinseki=rinseki+w(ninner(i),4)*w(ninner(i),6)
 740        continue
         end if
c
         rnseki=rinseki+ranseki
c     
         call mpi_reduce(rnseki,rnseki,1,
     $        mpi_double_precision,mpi_sum,0,mpi_comm_world,
     $        ierror)         
c
         if (rank.eq.0) then
            if (dabs(rmseki).le.epsmac) then
               write (6,*) ' ( As_{i},As_{i} ) = ',rmseki
               stop ' ( As_{i},As_{i} ) too small '
            end if
            omega=rnseki/rmseki
         end if
c
         call mpi_bcast(omega,1,mpi_double_precision,0,
     $        mpi_comm_world,ierror)                  
c
         do 750 i=1,neq_sub
            U(i)=U(i)+alpha*w(i,2)+omega*w(i,5)
            w(i,1)=w(i,4)-omega*w(i,6)
 750     continue
c--------------------------------------
c Convergence Criterion 
c-------------------------------------    
         razan=0.d0
         rizan=0.d0
         rzan=0.d0
         do 760 i=1,naisum
            razan=razan+w(naieq(i),1)*w(naieq(i),1)
 760     continue
c     
         if (nrecvlist(rank+1).eq.1) then
            do 770 i=1,nintotal
               rizan=rizan+w(ninner(i),1)*w(ninner(i),1)
 770        continue
         end if
c     
         rzan=razan+rizan
c
         call mpi_reduce(rzan,rzan,1,
     $        mpi_double_precision,mpi_sum,0,mpi_comm_world,
     $        ierror)         
c
         if (rank.eq.0) then
            rnorm=rzan/bsahen
c
            if (rnorm.le.eps) then
               nflg=1
c---------------------------
c     Iteration Count : KTI
c---------------------------
               KTI=k
            else 
               nflg=0
            end if
         end if
c
         call mpi_bcast(nflg,1,mpi_integer,0,mpi_comm_world,
     $        ierror)
         if (nflg.eq.1) return
c-------------------------------------------------------
c Calculation of (r_{0},r_{i}) = rtotal
c----------------------------------------
c
         ratotal=0.d0
         ritotal=0.d0
         rtotal=0.d0
         do 780 i=1,naisum
            ratotal=ratotal+w(naieq(i),1)*w(naieq(i),8)
 780     continue
c
         if (nrecvlist(rank+1).eq.1) then
            do 790 i=1,nintotal
               ritotal=ritotal+w(ninner(i),1)*w(ninner(i),8)
 790        continue
         end if
c
         rtotal=ratotal+ritotal
c
         call mpi_reduce(rtotal,rtotal,1,
     $        mpi_double_precision,mpi_sum,0,mpi_comm_world,
     $        ierror)  
c
 100  continue
      return
      end

