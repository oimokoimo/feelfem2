      subroutine MPP_movedata(IFROM,ITO,N)
      integer * 4 IFROM(*),ITO(*)
      do 100 i=1,N
         ITO(i) = IFROM(i)
 100  continue
      return
      end
