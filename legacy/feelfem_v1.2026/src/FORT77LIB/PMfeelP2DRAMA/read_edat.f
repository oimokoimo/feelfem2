      subroutine read_edat(iunit,no,nelem,np,ielem,matno,nverdate)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem Parallel version prototype
c     
c     MODULE READ_EDAT reading EDAT data
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      dimension ielem(np,nelem),matno(nelem)
      integer*4 iunit,no,nelem,np,nverdate

      character*20 fmt
      integer getsciunit
c --------------------------------------------------------------------
      if(nverdate .NE. 20000412) call abortexit(0,'ver read_edat')
*-----------------
* make format
*-----------------
      write(fmt,9003) np+1
 9003 format('(',I2,'I8)')

*-----------------
* read data
*-----------------
      do 100 i=1,nelem
        read(iunit,fmt,end=8902) (ielem(j,i),j=1,np),matno(i)
  100 continue

*-----------------
* write scratch
*-----------------
      iunitsc = getsciunit('EDAT',no)

      open(unit=iunitsc,status='scratch',form='unformatted')
      call closefil(iunitsc)

      write(iunitsc) no
      write(iunitsc) nelem,np
      write(iunitsc) ((ielem(i,j),i=1,np),j=1,nelem)
      write(iunitsc) (matno(i),i=1,nelem)
*----------------------------------------------------------------------
      return
*----------------------------------------------------------------------
 8902 write(io_stderr,*) 'edat data error'
      call abortexit(0,'read_edat')
*----------------------------------------------------------------------
      end
