      integer*4 function ndsearch_ex(ind,ipe, ndno,peno,nouter)
*--------------------------------------------------------------
*  2000/05/30 (feelfem_stokes version)
*
*  Search function for nodes
*--------------------------------------------------------------
      integer*4 ndno(*),peno(*)
*
      do 100 i=1,nouter
         if(ind .eq. ndno(i)   .AND.
     $      ipe .eq. peno(i)         ) then
            ndsearch_ex = i
            return
         endif
 100  continue
*
      write(*,*) 'cannot find PE',ipe,'  ndno=',ind
*
      call   abortexit(999,'Cannot find ndsearch_ex')
      end
      integer*4 function ndsearch_ex2(ind,ipe, ndno,peno,nouter)
*--------------------------------------------------------------
*  Search function for nodes
*
*  If not find, return -1
*--------------------------------------------------------------
      integer*4 ndno(*),peno(*)
*
      do 100 i=1,nouter
         if(ind .eq. ndno(i)   .AND.
     $      ipe .eq. peno(i)         ) then
            ndsearch_ex2 = i
            return
         endif
 100  continue
*
      ndsearch_ex2 = -1
      return
*
      end
      


