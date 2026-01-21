      subroutine read_node1 (x,npmax)
*
*  ------------------
*     1次元座標値を読む
*  ------------------
*
      implicit real*8 (a-h,o-z)
*
      dimension x(npmax)
*
      do 10 i=1,npmax
         read (15,100) i,x(i)
 10   continue
      read (15,101) izero
 100  format(i8,1PE12.5)
 101  format(i8)
      return
      end
*
*
      subroutine read_node2 (x,y,npmax)
*     
*  ------------------
*     2次元座標値を読む
*  ------------------
*
      implicit real*8(a-h,o-z)
*
      dimension x(npmax),y(npmax)
*
      do 10 i=1,npmax
         read (15,100) i,x(i),y(i)
 10   continue
 100  format (i8,1PE12.5,1PE12.5)
      read (15,101) izero
 101  format(i8)
      return
      end 
*
*
      subroutine read_node3(x,y,z,npmax)
*
*  ------------------
*     3次元座標値を読む
*  ------------------
*
      implicit real*8 (a-h,o-z)
*
      dimension x(npmax),y(npmax),z(npmax)
*     
      do 10 i=1,npmax
         read (15,100) i,x(i),y(i),z(i)
 10   continue
 100  format(i8,1PE12.5,1PE12.5,1PE12.5)
      read (15,101) izero
 101  format(i8)
      return
      end
*





