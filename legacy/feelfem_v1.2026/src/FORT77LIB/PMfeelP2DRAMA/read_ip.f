      subroutine read_ip(iunit,ip,nip)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
c     feelfem Parallel version prototype
c     
c     MODULE READ_IP reading IP data
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      dimension ip(nip)
c ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 8001 read(iunit,9001,end=8900) (ip(i),i=1,nip)
 9001 format((8i8))
      return
c --------------------------------------------------------------------
 8900 write(*,*) 'IP DATA ERROR'
      stop 'read_ip'
      end
