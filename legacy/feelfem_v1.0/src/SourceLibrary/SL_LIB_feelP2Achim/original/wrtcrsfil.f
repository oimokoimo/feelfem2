      subroutine wrtCRSfil(no,neq,ncof,maxnzpr,
     $                     valmat,indrow,iptrcol,vfg,v)
*----------------------------------------------------------------------
*    no            : solve number
*    neq           : total number of equations
*    ncof          : total number of nonzero cofficient in matrix array
*    maxnzpr       : maximum number of nonzero per row
*    valmat(ncof)  : matrix
*    indrow(ncof)  : column pointer
*    iptrcol(neq+1): row starting pointer
*    vfg           : right hand vector
*    v             : initial guess and solution
*----------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
*
      dimension valmat(*)
      dimension indrow(*)
      dimension iptrcol(*)
      dimension vfg(*)
      dimension v(*)
*
      character filname*11
*
      write(filname,10) no
 10   format('solve',i1,'.crs')
*
      call binopen(filname,10)
*                       12345678901234567890
      call binwritestr('crs matrix feelfem  ',20)
      call binwriteint(neq)
      call binwriteint(maxnzpr)
      call binwriteints(iptrcol,neq+1)
      call binwritedbls(valmat ,ncof )
      call binwriteints(indrow ,ncof )
      call binwritedbls(vfg    ,neq  )
      call binwritedbls(v      ,neq  )
*
      call binclose

      return
      end



