      subroutine seti(it,num,n)
      dimension it(n)
*
      do 100 i=1,n
        it(i) = num
 100  continue
      return
      end
      subroutine setd(dt,dnum,n)
      real*8 dt,dnum
      dimension dt(n)
*
      do 100 i=1,n
        dt(i) = dnum
 100  continue
      return
      end
