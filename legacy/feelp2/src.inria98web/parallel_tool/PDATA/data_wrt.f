      subroutine data_wrt1 (ndim,npesum,nbb,mryo,nmatrix,
     $     nedat,nodeset)
*
      implicit real*8 (a-h,o-z)
*
      parameter (MAX_FEEL=2000000)
      parameter (MAX_DOMAIN=10)
      parameter (MAX_EDATSET=38)
      parameter (MAX_NODESET=20)
      parameter (MAX_NUMSET = 20)
      parameter (MAX_EWISE  = 20)
*
      dimension mryo(npesum)
      dimension nbb(0:npesum)
*
      common /feel_dat/ n_edat(MAX_EDATSET,3),
     $     n_nset(MAX_NODESET,2),
     $     n_ewise(MAX_EWISE,2)
*
      common /feel_var/np_work,np_x,np_y,np_z,nvars_fem,
     $     nvars_ewise,
     &     np_fem,np_ewise,np_heap
      common /feel_ctl/mode_ex,mode_output,max_heap
*
*++++++++++++++++++++++++++++++++++
*     各dat.PE*にデータを書く。
*
*++++++++++++++++++++++++++++++++++
      do 10 iw=1,npesum
*     +++次元++++
         write (14+iw+5*npesum,9001) ndim
*     +++部分領域数++++
         write (14+iw+5*npesum,9001) npesum
*     ++++iw番目の部分領域の節点数+++++
         write (14+iw+5*npesum,9001) mryo(iw)
*     ++++ 全体剛性行列用EDAT集合の数++++
         write (14+iw+5*npesum,9001) nmatrix
*
*     ++++全体剛性行列用EDAT集合毎の部分領域iw
*     に属す要素数、要素内節点数 ++++
         do 20 j=1,nmatrix
            write (14+iw+5*npesum,9011) nbb(iw)-nbb(iw-1),
     $           n_edat(j,2)
 20      continue
*
         write (14+iw+5*npesum,9021) 'NSET'
*    ++++ NSET集合の数+++++
         write (14+iw+5*npesum,9001) nodeset
*
         write (14+iw+5*npesum,9021) 'EDAT'
*    ++++ 境界要素用EDAT集合の数++++
         write (14+iw+5*npesum,9001) nedat-nmatrix
*
 10   continue
*     
 9001 format(i8)
 9011 format(2i8)
 9021 format(a4)
      return
      end
*
*
*-------------------------------------------------
      subroutine data_wrt2 (x,y,npmax,mryo,npesum,
     $     nloglo)
*     +++++++++++++++++++++++++++++++++++
*     各部分領域に属す節点のx,y座標値を書く。
*     +++++++++++++++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
      dimension x(npmax),y(npmax)
      dimension mryo(npesum),nloglo(npmax,npesum)
*     
      do 10 iw=1,npesum
         do 20 j=1,mryo(iw)
            write (14+iw+5*npesum,9001) x(nloglo(j,iw)),
     $           y(nloglo(j,iw))
 20      continue
 10   continue
*
 9001 format(1PE12.5,1PE12.5)
*
      do 30 iw=1,npesum
         do 40 j=1,mryo(iw)
            write (14+iw+5*npesum,9011) nloglo(j,iw)
 40      continue
 30   continue
*
 9011 format(i8)
      return
      end
*
*++++++++++++++++++++++++++++++++++++++++++++
*     
      subroutine data_wrt3 (nlist,npesum)
*
      implicit real*8 (a-h,o-z)
*
      dimension nlist(npesum)
*
      do 10 iw=1,npesum
         do 20 jw=1,npesum
            write (14+iw+5*npesum,9001) nlist(jw)
 20      continue
 10   continue
*
 9001 format(i8)
      return
      end
*
*---------------------------------------------
*
      subroutine data_wrt4 (ilnode,neelem,nenode,matno,
     $     nbb,npesum,nelem)
*     ++++++++++++++++++++++++
*     全体剛性行列用EDAT集合毎に各部分領域での要素内節点と
*     部分節点番号との対応及び要素材料番号をファイルに書く。
*     +++++++++++++++++++++++
      implicit real*8 (a-h,o-z)
*
      character*20 fmt
      dimension ilnode(nenode,nelem)
      dimension nbb(0:npesum)
      dimension matno(neelem)
*
      write (fmt,9001) nenode+1
 9001 format('(',i,'i8)')
      do 10 iw=1,npesum
         do 20 j=1,nbb(iw)-nbb(iw-1)
            write (14+iw+5*npesum,fmt) (ilnode(ln,j+nbb(iw-1)),
     $           ln=1,nenode),matno(j+nbb(iw-1))
 20      continue
 10   continue
      return
      end
*
*+++++++++++++++++++++++++++++++++++++++++++++++++
*
      subroutine data_wrt5 (ngru,nbb,npesum,nelem)
*     
      implicit real*8 (a-h,o-z)
*
      dimension ngru(nelem),nbb(0:npesum)
*
*     +++++++++++++++++++++++++++++++++++++++
*     部分要素番号と全体要素番号との対応を書く。
*     ++++++++++++++++++++++++++++++++++++++++
      do 10 iw=1,npesum
         do 20 iq=1,nbb(iw)-nbb(iw-1)
            write (14+iw+5*npesum,9001) ngru(iq+nbb(iw-1))
 20      continue
 10   continue
*     
 9001 format(i8)
      return
      end
*---------------------------------------------
*
      subroutine data_wrt6 (nkaz,node,npesum)
*     ++++++++
*     Dirichlet条件集合(NSET集合)のdat.PE*への書き込み
*     ndikaz(im)を書く。(im=1,nodeset)
*     +++++++
*    ++++++++
*     Neumann条件用データEDAT集合のdat.PE*への書き込み
*     neukaz(im)(im=1,nedat-nmatrix)を書く。
*    ++++++++
      implicit real*8 (a-h,o-z)
*
      dimension nkaz(npesum)
*
      do 10 iw=1,npesum
         write (14+iw+5*npesum,9001) nkaz(iw),node
 10   continue
*
 9001 format(2i8)
      return
      end


