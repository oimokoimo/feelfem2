      subroutine p_make_eqno(nodsum,nnod,
     $     IPFsub,ipdsub,nneq,neqsum,npmaxsub)
*
*
      dimension nnod(nodsum)
      dimension nneq(neqsum)
*
*     
      dimension IPFsub(npmaxsub),ipdsub(npmaxsub)
*++++++++++++++++++++++++++++++++++++++++
*     Make equation number array(nneq(neqsum)) from
*     node number array(nnod(nodsum))
*++++++++++++++++++++++++++++++++++++++++++++++++
      nruiseki=1
      do 10 i=1,nodsum
         if (IPFsub(nnod(i)).eq.0) then
            stop 'nnod error'
         end if
         do 20 j=1,IPFsub(nnod(i))
            nneq(nruiseki+j-1)=ipdsub(nnod(i))+
     $           j-1
 20      continue
         nruiseki=nruiseki+IPFsub(nnod(i))
 10   continue
*
      return
      end
