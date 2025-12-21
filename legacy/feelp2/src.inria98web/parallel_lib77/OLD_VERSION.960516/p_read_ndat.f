      subroutine p_read_ndat (iunit,np_ibsubelem,neukaz,neunum,
     $     ndisub,neusub,feelpara,idat,nbase,nhenkaz1,nmade,ipe)
*
*------------------------------
*
*     Neumann条件の読み込み
*
*----------------------------
      implicit real*8 (a-h,o-z)
*
      real*4 feelpara(*)
      dimension np_ibsubelem(neusub)
      dimension neukaz(neusub),neunum(neusub)
      dimension idat(2,*),nbase(2,*)
*
*
      do 10 i=1,neusub
         if (neukaz(i).gt.0) then
            read (iunit,9001) nosub
*
*     境界要素内節点と部分節点番号との対応
            call f_alloc (np_ibsubelem(i),'Read ibsubelem',
     $           neukaz(i)*neunum(i),0)
            idat(1,nmade+23+i+2*ndisub)=np_ibsubelem(i)
     $           -nbase(1,ipe)+nbase(1,1)
            idat(2,nmade+23+i+2*ndisub)=neukaz(i)*neunum(i)
*
            call p_read_n_edat (iunit,neukaz(i),neunum(i),
     $           feelpara(np_ibsubelem(i)))
*
         end if
 10   continue
*
 9001 format(i8)
*
      return
      end
