      function i_feelget(idat,n)
      dimension idat(*)
      i_feelget=idat(n)
      return
      end
      function inp_feelget(feel,np,n)
      integer*4 feel(*)
      inp_feelget=feel(np+n-1)
      return
      end
      real *8 function d_feelget(ddat,n)
      real*8 ddat(*)
      d_feelget=ddat(n)
      return
      end
      subroutine feelset_npi(feel,np,i,num)
      integer*4 feel(*)
      feel(np+i-1) = num
      return
      end
      subroutine feelset_npd(feel,np,i,dat)
      real*8 dat
      real*4 feel(*)
      call subfeelset_npd(feel(np),i,dat)
      return
      end
      subroutine subfeelset_npd(dbuf,i,dat)
      real*8 dbuf(*),dat
      dbuf(i) = dat
      return
      end

