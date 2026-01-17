      subroutine sumupdegree(mypeid,nprocs,nparams,
     $                       ibuf,icount,idispl,
     $                       isumup,neqtotal,myeqfrom,myeqto)
*-------------------------------------------------------------
*     2000/05/30 (feelfem_stokes version)
*
*     Make a sumup degree of freedom information array + alpha
*
*-------------------------------------------------------------
      parameter (NCTRL_ITEMS_HERE = 4)
*
      integer*4 ibuf(*),icount(*),idispl(*)
      integer*4 isumup(*)
*-------------------------------------------------------------
      if(NCTRL_ITEMS_HERE .NE. nparams) then
         call abortexit(myrank,'Mismatch NCTRL_ITEMS(sumupdegree)')
      endif
*-------------------------------------------------------------
      mypeidx = mypeid + 1
*-------------------------------------------------------------
      isumup(1) = 0
      do 100 i=1,nprocs
         neq  =   ibuf(idispl(i) + 4)
         isumup(i+1) = isumup(i) + neq
 100  continue
*---
      neqtotal = isumup(nprocs+1)
      myeqfrom = isumup(mypeidx  ) + 1
      myeqto   = isumup(mypeidx+1)
*---
      return
      end


      
