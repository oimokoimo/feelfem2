      real*8 function dramafemval(mypeid, ind,ipe,val,npmax,
     $                                            valex,
     $                            ndno,peno,nouter)
*--------------------------------------------------------------
*    Get fem value by nd/pe double index pair
*
*    val(npmax)  
*    valex(nouter),ndno(nouter),peno(nouter)
*--------------------------------------------------------------
      integer*4 mypeid
      integer*4 ind,ipe
      real   *8 val(*)
      integer*4 npmax
      real   *8 valex(*)
      integer*4 ndno(*),peno(*)
      integer*4 nouter
*--------------------------------------------------------------
      if(mypeid .eq. ipe) then
         dramafemval = val(ind)
      else
*
         nd = ndsearch_ex(ind,ipe,ndno,peno,nouter)
         dramafemval = valex(nd)
      endif
*
      return
      end


