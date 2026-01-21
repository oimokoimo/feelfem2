      subroutine p_memory_move (ia,ib,nsize)
*
*     ---------------------
*     メモリの移動を行う。
*
*     --------------------
      implicit real*8 (a-h,o-z)
*
*
      dimension ia(*),ib(*)
      do 1 i=1,nsize
         ib(i)=ia(i)
 1    continue
*
      return
      end




