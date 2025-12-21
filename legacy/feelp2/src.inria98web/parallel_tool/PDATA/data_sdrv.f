      subroutine data_sdrv1 (nreadsd,nreadrv,npesum,
     $     jain,npeint,npmax,nsendlist,nrecvlist,
     $     nk1)
*
*     ++++++++++++++++++++++++++++++++++++++++++++
*     各全体剛性行列用EDAT集合用のデータから
*     送信、受信用データ(以前のse1,re1.PE*データを作る。)
*     ++++++++++++++++++++++++++++++++++++++++++++
*     nk1 : インターフェース上の節点数
*
      implicit real*8 (a-h,o-z)
*
      dimension nreadsd(npesum),nreadrv(npesum)
      dimension jain(0:npmax),npeint(npmax*npesum,2)
      dimension nsendlist(npesum),nrecvlist(npesum)
*
      minpe1=0
      minban1=0
      mfre=0
      mfse=0
*     nsendlist(*),nrecvlist(*)のゼロクリア
      do 503 i=1,npesum
         nsendlist(i)=0
         nrecvlist(i)=0
 503  continue
      do 510 i=1,nk1
         minpe1=npeint(jain(i-1),1)
         minban1=jain(i-1)
         do 520 j=jain(i-1)+1,jain(i)-1
            minpe1=min0(minpe1,npeint(j,1))
            if (minpe1.eq.npeint(j,1)) then
               minban1=j
            end if
 520     continue
         do 550 nj=jain(i-1),jain(i)-1
            if (nj.ne.minban1) then
               nsendlist(npeint(nj,1))=1
            else if (nj.eq.minban1) then
               nrecvlist(npeint(nj,1))=1
            end if
 550     continue
 510  continue
*
      do 751 i=1,npesum
         nreadsd(i)=0
 751  continue
*
      do 752 i=1,npesum
         nreadrv(i)=0
 752  continue
*
      minpe=0
      minban=0
      do 340 i=1,nk1
         minpe=npeint(jain(i-1),1)
         minban=jain(i-1)
         do 350 j=jain(i-1)+1,jain(i)-1
            minpe=min0(minpe,npeint(j,1))
            if (minpe.eq.npeint(j,1)) then
               minban=j
            end if
 350     continue
*     
         do 360 j=jain(i-1),jain(i)-1
*
*-------------データを送る側のデータ作成。
*
            if (j.ne.minban) then
               open (unit=14+npeint(j,1)+2*npesum,status=
     $              'scratch',form='unformatted')
*    従来の方程式番号ではなく、節点の対応だけにする。
*
               write (14+npeint(j,1)+2*npesum) npeint(minban,1),
     $              npeint(j,2),npeint(minban,2)
               nreadsd(npeint(j,1))=nreadsd(npeint(j,1))+1
*
*------------- データを受け取る側のデータ作成。
*
            else if (j.eq.minban) then
               open (unit=14+npeint(j,1)+3*npesum
     $              ,status='scratch',
     $              form='unformatted')
*
               do 410 mk=jain(i-1),jain(i)-1
                  if (mk.ne.minban) then           
                     write (14+npeint(minban,1)+3*npesum) 
     $                    npeint(mk,1),
     $                    npeint(j,2),
     $                    npeint(mk,2)
                  end if
 410           continue
               nreadrv(npeint(minban,1))=nreadrv(npeint(minban,1))
     $              +(jain(i)-jain(i-1)-1)
            end if
 360     continue
*
 340  continue
*
      return
      end
*
*---------------------------
*
      subroutine data_sdrv2 (nsendlist,nrecvlist,nreadsd,
     $     nreadrv,npesum,npmax,nsendtable,nkrt,nlsd,
     $     nsendsub,lread,icheck,mcheban,nsequ)
*
*     +++++++++++++++++++++++++++
*     各全体剛性行列用EDAT集合に対して
*     送信用、受信用データを作成する。
*     +++++++++++++++++++++++++++
*
      implicit real*8 (a-h,o-z)
*
      dimension nreadsd(npesum),nreadrv(npesum)
      dimension nsendlist(npesum),nrecvlist(npesum)
*
      dimension lread(npesum*2)
*
      dimension nsendtable(npesum)
      dimension nkrt(npesum)
      dimension nlsd(npmax)
      dimension nsequ(npmax,npesum)
      dimension nsendsub(npmax)
*
      dimension icheck(npesum),mcheban(npesum)
*
*     データを送信する側で送信先ごとに分類する。
*     /*send buffer receive bufferにため込む時こう
*     でないと駄目 */
      do 500 iw=1,npesum
         if (nsendlist(iw).eq.1) then
            rewind (14+iw+2*npesum)
         end if
*
         if (nrecvlist(iw).eq.1) then
            rewind (14+iw+3*npesum)
         end if
*
 500  continue
*
      do 700 iw=1,npesum
*/注意点：データを送信する部分領域かどうか、受信する領域か 
*     どうかちゃんと判定してファイルを開くこと。(そうしない
*     とないファイルを読みに行ってしまう。)  /
*     部分領域 iw のデータ(PE番号iw-1)
*
*     ---- icheck,mchebanのゼロクリア ----
         do 650 ih=1,npesum
            icheck(ih)=0
 650     continue
         do 651 ih=1,npesum
            mcheban(ih)=0
 651     continue
*     
         if (nsendlist(iw).eq.1) then
*
            lread(iw)=0
*
*     ------ 送信先の部分領域番号の登録
*            "nsendtable(*)" -----------
            read(14+iw+2*npesum) nsendtable(1),ndummy,ndummy
*
            icheck(nsendtable(1))=1
*     
            lread(iw)=lread(iw)+1
*
            mcheban(nsendtable(1))=lread(iw)
*
            do 10 i=2,nreadsd(iw)
               read (14+iw+2*npesum) nseg,ndummy,ndummy
               if (icheck(nseg).eq.0) then
                  lread(iw)=lread(iw)+1
                  nsendtable(lread(iw))=nseg
                  icheck(nseg)=1
*/* その送信先部分領域が何番目か登録 */
                  mcheban(nseg)=lread(iw)
*     
               end if
 10         continue
*
*--------------------------------
*     nsendtable(i)(i=1,.. lread(iw))...部分領域 iw
*     からの送信先の部分領域番号。
*--------------------------------
            rewind (14+iw+2*npesum)
            do 30 i=1,nreadsd(iw)
               read (14+iw+2*npesum) nsendsub(i),nlsd(i),ndummy
 30         continue
*
*     ---初期化 ------------
            do 35 i=1,lread(iw)
               nkrt(i)=0
 35         continue
*     ---初期化 ------------
*     
            do 50 i=1,nreadsd(iw)  
               nkrt(mcheban(nsendsub(i)))=
     $              nkrt(mcheban(nsendsub(i)))+1

               nsequ(nkrt(mcheban(nsendsub(i))),
     $              mcheban(nsendsub(i)))=nlsd(i)
 50         continue
*     
            write (14+iw+5*npesum,9001) lread(iw)
            do 70 mq=1,lread(iw)
               write (14+iw+5*npesum,9001) nkrt(mq)
               do 80 j=1,nkrt(mq)
                  write (14+iw+5*npesum,9011) nsendtable(mq),
     $                 nsequ(j,mq)
 80            continue
 70         continue
         end if
 700  continue
*
*     データを受信する側で発信元ごとに分類する。
*
      do 710 iw=1,npesum
*
*     ++++++ icheck,mchebanのゼロクリア +++++
*
         do 713 ih=1,npesum
            icheck(ih)=0
 713     continue
*
         do 716 ih=1,npesum
            mcheban(ih)=0
 716     continue
*
*    
*
         if (nrecvlist(iw).eq.1) then
*
            rewind (14+iw+3*npesum)
*
            lread(iw)=0
*
*     部分領域 iw のデータ(PE番号iw-1)
*     ------ 発信元の部分領域番号の登録
*            "nsendtable(*)" -----------
            read (14+iw+3*npesum) nsendtable(1),ndummy,ndummy
*
            icheck(nsendtable(1))=1
*
            lread(iw)=lread(iw)+1
*
            mcheban(nsendtable(1))=lread(iw)
*
            do 390 i=2,nreadrv(iw)
               read (14+iw+3*npesum) nseg,ndummy,ndummy
*
               if (icheck(nseg).eq.0) then
                  lread(iw)=lread(iw)+1
                  nsendtable(lread(iw))=nseg
                  icheck(nseg)=1
*     その受信元領域が何番目か登録
                  mcheban(nseg)=lread(iw)
               end if
 390        continue
*--------------------------------
*     nsendtable(i)(i=1,.. lread(iw))...部分領域 iw
*     でデータを受信する時の発信元の部分領域番号。
*--------------------------------
*
            rewind (14+iw+3*npesum)
*
            do 410 i=1,nreadrv(iw)
               read (14+iw+3*npesum) nsendsub(i),nlsd(i),ndummy
 410        continue
*
*     ---初期化 ------------
            do 415 i=1,lread(iw)
               nkrt(i)=0
 415        continue
*     ---初期化 ------------
*     
            do 420 i=1,nreadrv(iw)
               nkrt(mcheban(nsendsub(i)))=
     $              nkrt(mcheban(nsendsub(i)))+1
*
               nsequ(nkrt(mcheban(nsendsub(i))),
     $              mcheban(nsendsub(i)))=nlsd(i)
*
 420        continue
*     
            write (14+iw+5*npesum,9001) lread(iw)
            do 440 mq=1,lread(iw)
               write (14+iw+5*npesum,9001) nkrt(mq)
               do 450 j=1,nkrt(mq)
                  write (14+iw+5*npesum,9011) 
     $                 nsendtable(mq),nsequ(j,mq)
 450           continue
 440        continue
         end if
 710  continue
*
 9001 format(i8)
 9011 format(2i8)
*
      return 
      end


