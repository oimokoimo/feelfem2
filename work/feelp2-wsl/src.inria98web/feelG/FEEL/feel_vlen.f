      subroutine feel_vlen(npmax,x,y,d)
      implicit real*8 (a-h,o-z)
      dimension x(*),y(*),d(*)
      do 100 i=1,npmax
	d(i) = dsqrt(x(i)*x(i)+y(i)*y(i))
100   continue
      return
      end

