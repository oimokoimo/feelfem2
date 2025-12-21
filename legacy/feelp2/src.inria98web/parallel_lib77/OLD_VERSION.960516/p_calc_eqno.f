      subroutine p_calc_eqno(nodsum,nnod,neqsum,
     $     IPFsub,npmaxsub)
*
      dimension nnod(nodsum)
*     
      dimension IPFsub(npmaxsub)
*+++++++++++++++++++++++++++++++++++++++++++++++++
*     calculate neqsum(maximum of equation number)
*+++++++++++++++++++++++++++++++++++++++++++++++++
      neqsum=0
      do 10 i=1,nodsum
         neqsum=neqsum+IPFsub(nnod(i))
 10   continue
      if (neqsum.eq.0) then
         stop 'neqsum error'
      end if
      return
      end
