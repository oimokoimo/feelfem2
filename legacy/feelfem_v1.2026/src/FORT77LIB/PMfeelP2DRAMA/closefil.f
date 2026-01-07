      subroutine closefil(no)
      parameter(MAX=100)
      dimension iunits(MAX)
      common /pfeel_cls/ip,iunits
      if(no .EQ. 0) then
       ip = 0
       return
      endif
      if(no .LT. 0) then
      do 100 i=1,ip
       close(unit=iunits(i))
100   continue
      return
      endif
*
      if(ip.EQ.MAX) stop 'too many close file to store'
      ip=ip+1
      iunits(ip) = no
      return
      end
      subroutine doclosefil
      parameter(MAX=100)
      dimension iunits(MAX)
      common /pfeel_cls/ip,iunits
      do 100 i=1,ip
       close(unit=iunits(i))
100   continue
      ip = 0
      return
      end


