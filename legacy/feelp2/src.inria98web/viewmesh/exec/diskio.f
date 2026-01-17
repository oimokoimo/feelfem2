      subroutine diskwrti(iunit,num,idat)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: 整数配列をファイルに書く
*-------------------------------------------------------------------
      dimension idat(num)
*
      write(iunit) (idat(i),i=1,num)
      return
      end
      subroutine diskwrtd(iunit,num,dat)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: 実数配列をファイルに書く
*-------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
      dimension dat(num)
*
      write(iunit) (dat(i),i=1,num)
      return
      end
      subroutine diskrdi(iunit,num,idat)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: 整数配列をファイルから読む
*-------------------------------------------------------------------
      dimension idat(num)
*
      read(iunit) (idat(i),i=1,num)
      return
      end
      subroutine diskrdd(iunit,num,dat)
*-------------------------------------------------------------------
*  FEEL P2 System Subroutine
*-------------------------------------------------------------------
*  Purpose: 実数配列をファイルから読む
*-------------------------------------------------------------------
      implicit real*8 (a-h,o-z)
      dimension dat(num)
*
      read(iunit) (dat(i),i=1,num)
      return
      end
