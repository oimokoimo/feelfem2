      subroutine data_nodsub1 (iunit,x,npmaxsub)
*
      implicit real*8 (a-h,o-z)
*
      dimension x(*)

      do 10 i=1,npmaxsub
         read (iunit,9001) x(i)
 10   continue
*     
 9001 format(1PE12.5)
      return
      end
*
*++++++++++++++++++++++++++++++++++++++++++
      subroutine data_nodsub2 (iunit,x,y,npmaxsub)
*
      implicit real*8 (a-h,o-z)
*
      dimension x(*),y(*)
*
      do 10 i=1,npmaxsub
         read (iunit,9001) x(i),y(i)
 10   continue
*     
 9001 format(1PE12.5,1PE12.5)
      return
      end 
*++++++++++++++++++++++++++++++++++     
      subroutine data_nodsub3 (iunit,x,y,z,npmaxsub)
*
      implicit real*8 (a-h,o-z)
*
      dimension x(*),y(*),z(*)
*
      do 10 i=1,npmaxsub
         read (iunit,9001) x(i),y(i),z(i)
 10   continue
*     
 9001 format(1PE12.5,1PE12.5,1PE12.5)
      return
      end
      


