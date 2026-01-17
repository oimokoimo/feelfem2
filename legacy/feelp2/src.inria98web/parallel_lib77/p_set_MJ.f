      subroutine p_set_MJ (MJ,isubelem,nelemsub,np,nenfre,
     $     KK_MJ,npmaxsub,KK_MJR,KK_MJL)
*
*+++++++++++++++++++++++++++++++++++++++++++++
*     Purpose : SET the bandwidth "MJ" for an
c               Unsymmetric Sparse Matix
*    
*++++++++++++++++++++++++++++++++++++++++++++
      include 'mpi.incl'
      implicit real*8 (a-h,o-z)
*
      dimension isubelem(np,nelemsub)
      dimension KK_MJR(npmaxsub),KK_MJL(npmaxsub)
      dimension KK_MJ(npmaxsub)
      dimension nenfre(*) 
*
*++++++++++++++++++++++++++++++++++++++++++
*   Initialization "KK_MJL(*)","KK_MJR(*)"
*+++++++++++++++++++++++++++++++++++++++++
      do 1 i=1,npmaxsub
         KK_MJL(i)=0
         KK_MJR(i)=0
 1    continue
*     
      do 10 i=1,nelemsub
         do 20 j=1,np
            do 30 k=1,np
               if (isubelem(k,i).gt.isubelem(j,i)) 
     $              then
                  KK_MJR(isubelem(j,i))=
     $                 KK_MJR(isubelem(j,i))+1
               else if (isubelem(k,i).lt.isubelem(j,i)) 
     $                 then
                  KK_MJL(isubelem(j,i))=
     $                 KK_MJL(isubelem(j,i))+1
               end if
c
c
                  if ((isubelem(j,i).le.0).or.(
     $                 isubelem(j,i).gt.npmaxsub)) then
                     write (6,*) 'isubelem,j,i',isubelem(j,i),
     $                    j,i
                     stop 'isubelem error'
                  end if
c
*                  
 30         continue
 20      continue
 10   continue
*
      do 15 i=1,npmaxsub
         KK_MJ(i)=max0(KK_MJR(i),KK_MJL(i))
         KK_MJ(i)=2*KK_MJ(i)+1
 15   continue
*
      
      MJ=0
      MJ=KK_MJ(1)
      do 40 i=2,npmaxsub
         MJ=max0(MJ,KK_MJ(i))
 40   continue
*     
      nfree=0
      nfree=nenfre(1)
      do 50 i=2,np
         nfree=max0(nfree,nenfre(i))
 50   continue
*
      MJ=MJ*nfree
*
      return
      end

