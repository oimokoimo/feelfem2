      subroutine p_get_band (il,ir,neq_sub,A,JA,MJ,JDP,jl,jr)
c
c------------------------------------------------
c     Calculation of "JL,JR"
c                 JL : bandwidth of lower part
c                 JR : bandwidth of upper part
c------------------------------------------------
c     
      implicit real*8 (a-h,o-z)
c
      dimension il(neq_sub),ir(neq_sub)
      dimension A(neq_sub,MJ),JA(neq_sub,MJ)
*
      jl=0
      jr=JDP
      do 10 i=1,neq_sub
         il(i)=0
         ir(i)=JDP
 10   continue
*
      do 20 i=1,neq_sub
         do 30 j=1,JDP-1 
            if ((JA(i,j).lt.i).and.(JA(i,j).ge.1)) then
               il(i)=j
            end if
 30      continue
         jl=max0(jl,il(i))
 20   continue
*
      do 40 i=1,neq_sub
         do 50 j=JDP+1,MJ
            if ((JA(i,j).gt.i).and.(JA(i,j).le.neq_sub)) then
               ir(i)=j
            end if
 50      continue
         jr=max0(jr,ir(i))
 40   continue
*
      return
      end
      
               


