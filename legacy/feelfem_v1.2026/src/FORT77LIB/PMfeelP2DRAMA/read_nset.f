      subroutine read_nset(iunit,no,nodes,np,inset)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem Parallel version prototype
c     
c     MODULE READ_NSET reading NSET data
c
c     no    : NSET number
c     nodes : number of nodes
c     np    : data par each node
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
c --------------------------------------------------------------------
      dimension inset(np,nodes)
      character fmt*10
      integer getsciunit
c --------------------------------------------------------------------
*-----------------
* make format
*-----------------      
      write(fmt,90) np
  90  format('(',I2,'I8)')

*-----------------
* read data
*-----------------      
      do 100 i=1,nodes
        read(iunit,fmt) (inset(j,i),j=1,np)
 100  continue
*
      iunitsc = getsciunit('NSET',no)
*
      open(unit=iunitsc,status='scratch',form='unformatted')
      call closefil(iunitsc)
*
      write(iunitsc) no
      write(iunitsc) nodes,np
      write(iunitsc) ((inset(j,i),j=1,np),i=1,nodes)
*
      return
c --------------------------------------------------------------------
      end
