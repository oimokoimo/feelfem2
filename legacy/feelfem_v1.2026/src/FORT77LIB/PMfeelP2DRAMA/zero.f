      subroutine zeroi(it,n)
*
* 2000/05/30 (feelfem_stokes version)
*
*
*
      dimension it(n)
      do 100 i=1,n
 100  it(i) = 0
      return
      end
      subroutine zerod(dt,n)
      real * 8   dt
      dimension dt(n)
      do 100 i=1,n
 100  dt(i) = 0.0d0
      return
      end
