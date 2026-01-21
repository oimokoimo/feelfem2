      subroutine data_num0 (feelpara,ielem,ngru,nzoku,
     $     npos,nbb,npesum,nelem,nel,number,nsuu,ignode,
     $     neelem,nenode,npmax)
*
      implicit real*8 (a-h,o-z)
*
      real*4 feelpara(*)
*     この配列宣言はわかりにくいかな。。。。3/8
      dimension ignode(nenode,nelem)
*
      dimension nel(npesum)
      dimension nbb(0:npesum)
      dimension nzoku(nelem)
      dimension ielem(nenode,neelem)
      dimension ngru(nelem)
*
*    ----------------------
*
      dimension npos(npmax,0:npesum)
      dimension nsuu(npmax)
*     ------------------
*     (注意点): 現状では分割数が2**nankaiになっていること
*     に注意。(nankai<=nskai=6)
*--------------------------------------------------------
*+++++++++++++++++++++++++++++
*     全体節点番号と各部分領域での部分節点番号との
*     対応配列npos(npmax,0:npesum)(npos(i,j) iは
*     全体節点番号
*     
*+++++++++++++++++++++++++++++

*
      do 10 ip=1,npesum
         nel(ip)=nbb(ip)-nbb(ip-1)
         if (nel(ip).gt.nelem) then
            stop 'nel(ip) error'
         end if
 10   continue
*
*    ---- ignode(ln,ie+nbb(ip-1))----- の作成。
      do 20 ip=1,npesum
         do 30 ie=1,nel(ip)
            do 40 ln=1,nenode
               ignode(ln,ie+nbb(ip-1))=ielem(ln,ngru(ie+
     $              nbb(ip-1)))
               if (ignode(ln,ie+nbb(ip-1)).eq.0) then
                  stop 'ignode zero error'
               end if
 40         continue
 30      continue
 20   continue
*
*     npos(npmax,npesum) : npos(i,j)(i: global node number)の
*     属するj番目の部分領域番号。
*     ia(npmax) : ia(i)(i: global node number)の
*     部分領域npos(i)での節点番号。
*     の作成。
*
*     最初の剛性行列用EDAT集合の時だけゼロクリア
      if (number.eq.1) then
         do 63 i=1,npmax
            nsuu(i)=0
 63      continue
         do 65 j=1,npesum
            do 66 i=1,npmax
               npos(i,j)=0
 66         continue
 65      continue
      end if
*
*     nelem=neelemは同じと思って良い。
      do 50 i=1,neelem
         do 60 j=1,nenode
            do 53 k=1,nsuu(ielem(j,i))
               if (npos(ielem(j,i),k).eq.nzoku(i)) go to 60
 53         continue
            nsuu(ielem(j,i))=nsuu(ielem(j,i))+1
            if (nsuu(ielem(j,i)).gt.npesum) then
               stop 'nsuu error'
            end if
*
            npos(ielem(j,i),nsuu(ielem(j,i)))=nzoku(i)
 60      continue
 50   continue
*
      return
      end 
*
*     ---------------------------
      subroutine data_num1 (npos,nsuu,mryo,ia,npmax,
     $     npesum)
*
*     ------------------------
*     各部分領域内節点数 "mryo"と
*     全体節点番号と部分節点番号との対応 "ia"を
*     決定する。
*     ------------------------
*
      implicit real*8 (a-h,o-z)
*
      dimension npos(npmax,0:npesum)
      dimension nsuu(npmax)
      dimension ia(npmax,npesum)
      dimension mryo(npesum)
*
*
      do 82 j=1,npesum
         mryo(j)=0
 82   continue
*
      do 80 i=1,npmax
         do 83 k=1,nsuu(i)
            do 70 j=1,npesum
               if (npos(i,k).eq.j) then
                  mryo(j)=mryo(j)+1
                  ia(i,k)=mryo(j)
               end if
 70         continue
 83      continue
 80   continue
*
      do 91 i=1,npesum
         if (mryo(i).eq.0) then
            stop 'mryo(i) zero error'
         end if
 91   continue
      return 
      end
*
*----------------------------------------------
*
      subroutine data_num2 (feelpara,nel,ilnode,ia,ielem,
     $     nbb,ignode,npos,ngru,nsuu,mryo,npesum,nenode,
     $     nelem,npmax,neelem)
*
      implicit real*8 (a-h,o-z)
*
      real*4 feelpara(*)
      dimension nel(npesum)
      dimension ilnode(nenode,nelem)
      dimension ia(npmax,npesum)
      dimension ielem(nenode,neelem),nbb(0:npesum)
      dimension ignode(nenode,nelem),npos(npmax,0:npesum)
      dimension ngru(nelem),nsuu(npmax),mryo(npesum)
*     ------------------
*     全体剛性行列用のEDAT集合の
*     要素内節点番号と部分節点番号との対応を作る
*      -------------------
*++++++++++++++++++++++++++++++++++++++++++++++
*
*     npos(npmax,npesum) : npos(i,j)(i: global node number)の
*     属するj番目の部分領域番号。
*     ia(npmax,npesum) : ia(i)(i: global node number)の
*     部分領域npos(i)での節点番号。
*     の作成。
      do 90 ip=1,npesum
         do 100 ie=1,nel(ip)
            do 110 ln=1,nenode
               do 120 k=1,nsuu(ignode(ln,ie+nbb(ip-1)))        
                  if (npos(ignode(ln,ie+nbb(ip-1)),k)
     $                 .eq.ip) then
                     ilnode(ln,ie+nbb(ip-1))=
     $                    ia(ielem(ln,ngru(ie+nbb(ip-1))),k)
*
                     if (ilnode(ln,ie+nbb(ip-1)).gt.mryo(ip)) 
     $                    then
                        stop 'ilnode over error'
                     end if
*
                  end if
 120           continue
 110        continue
 100     continue
 90   continue
      return
      end 
*
*
*     ----------------------------------
*
      subroutine data_num3 (nloglo,ia,npos,nsuu,mryo,
     $     npmax,npesum)
*
      implicit real*8 (a-h,o-z)
*
      dimension nloglo(npmax,npesum)
      dimension ia(npmax,npesum),npos(npmax,0:npesum)
      dimension nsuu(npmax)
      dimension mryo(npesum)
*
*     ----- 各部分領域での部分節点番号と
*     全体節点番号との対応付け ------
*
*
      do 200 kn=1,npmax
         do 210 ln=1,nsuu(kn) 
            nloglo(ia(kn,ln),npos(kn,ln))=kn
 210     continue
 200  continue
*
*
      do 300 i=1,npesum
         do 310 j=1,mryo(i)
            if (nloglo(j,i).eq.0) then
               stop 'nloglo zero error'
            end if
 310     continue
 300  continue
*
      return 
      end





