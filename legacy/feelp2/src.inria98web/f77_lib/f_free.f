      subroutine f_free(cha , n , itype)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine f_free
*-------------------------------------------------------------------
*  Purpose: free allocated memory
*-------------------------------------------------------------------
#COMMON
*
      nn = 0
      if(itype.eq. 0) then
	nn = n
      endif
      if(itype .eq. 1) then
	nn = n * 2
      endif
      if(nn.eq.0) then
	write(io_stderr,*) 'f_free: itype error'
	stop 'f_free'
      endif

      np_work = np_work - nn
      if(np_work .lt. 1) then
	write(io_stderr,*) 'f_free <1 error for ',cha
	stop 'f_free'
      endif
      return
      end

