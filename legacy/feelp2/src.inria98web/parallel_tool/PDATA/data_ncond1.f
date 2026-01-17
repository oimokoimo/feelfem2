      subroutine data_ncond0 (ibelem,neelem,nenode,
     $     npmax,npesum,npesub,npenum,neukaz,
     $     number,ndim)
*     
      implicit real*8 (a-h,o-z)
*
*++++++++++++++
*     Neumann条件の必要な並列化データを作る。
*     概要：Neumann条件が課されている節点を
*     各部分領域に部分節点番号に振り分けて
*     ファイルに落す。
*+++++++++++++
*
      dimension ibelem(nenode,neelem)
*
      dimension npesub(0:npmax)
      dimension npenum(npmax*npesum)
*
      dimension neukaz(npesum)
*
* 各部分領域iw(=1,..npesum)に属するNeumann条件が
*     課せられている境界要素の数をまず決定する。
*              :neukaz(npesum):
*
*+++++   neukaz(*)のゼロクリア ++++++
      do 3 iw=1,npesum
         neukaz(iw)=0
 3    continue
*
*     neelem : 境界要素数
*     nenode : 境界要素内節点数
      do 60 jn=1,neelem
*
         if (ndim.ne.2) then
            stop 'neumann error'
         end if
         do 70 mp1=npesub(ibelem(1,jn)-1),
     $        npesub(ibelem(1,jn))-1
            do 71 mp2=npesub(ibelem(2,jn)-1),
     $           npesub(ibelem(2,jn))-1
               if (npenum(mp1).eq.npenum(mp2)) then
                  iw=npenum(mp1)
                  neukaz(iw)=neukaz(iw)+1
                  go to 70
               end if
 71         continue
*
 70      continue
*     
 60   continue
*
*
      return
      end      
*
*++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*
      subroutine data_ncond1 (ibelem,ibmatno,neelem,nenode,
     $     npmax,npesum,npesub,npenum,npeloc,
     $     nregi,number)
*     
      implicit real*8 (a-h,o-z)
*
*++++++++++++++
*     Neumann条件の必要な並列化データを作る。
*     概要：Neumann条件が課されている節点を
*     各部分領域に部分節点番号に振り分けて
*     ファイルに落す。
*+++++++++++++
*
      character*20 fmt
*
      dimension ibelem(nenode,neelem)
      dimension ibmatno(neelem)
*
      dimension npesub(0:npmax)
      dimension npenum(npmax*npesum)
      dimension npeloc(npmax*npesum)
*
      dimension nregi(npmax)
*
*
*     neelem : 境界要素数
*     nenode : 境界要素内節点数
      do 60 jn=1,neelem
*
*     各境界要素内節点の部分節点番号の登録
         do 63 kt=1,nenode
            nregi(kt)=0
 63      continue
*
         do 70 mp1=npesub(ibelem(1,jn)-1),
     $        npesub(ibelem(1,jn))-1
            do 71 mp2=npesub(ibelem(2,jn)-1),
     $           npesub(ibelem(2,jn))-1
               if (npenum(mp1).eq.npenum(mp2)) then
*
*  ++++++++++++++++++++++++++++++++
*   境界要素の属す部分領域番号iwを求める
*  ++++++++++++++++++++++++++++++++
                  iw=npenum(mp1)
                  go to 70
               end if
 71         continue
*
 70         continue
*----------- nregi(*)への登録(境界要素上の節点の
*           部分領域での部分節点番号) ------
            ner=0
            do 73 kn=1,nenode
*
               do 75 my=npesub(ibelem(kn,jn)-1),
     $              npesub(ibelem(kn,jn))-1
                  if (npenum(my).eq.iw) then
                     ner=ner+1
                     nregi(ner)=npeloc(my)
                  end if
 75            continue
 73         continue
*
*     ++++++++++++++++++++++++++++
            write (fmt,9011) ner
 9011       format('(',i,'i8)')
*     EDAT集合番号-nmatrix : number
            write (14+iw+5*npesum,9001) number
*
*  /*この境界要素上の節点の部分領域での部分節点番号 */
            write (14+iw+5*npesum,fmt) (nregi(ih),ih=1,ner)
*
 60      continue
 50   continue
*
*
 9001 format(i8)
      return
      end


